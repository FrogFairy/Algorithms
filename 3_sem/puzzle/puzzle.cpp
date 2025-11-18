#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <queue>
#include <functional>

using namespace std;

enum class Direction {
    UP,
    RIGHT, 
    DOWN,
    LEFT
};

struct DirectionHelper {
    static constexpr pair<int, int> offset(Direction dir) {
        switch (dir) {
            case Direction::UP:    return {-1, 0};
            case Direction::RIGHT: return {0, 1};
            case Direction::DOWN:  return {1, 0};
            case Direction::LEFT:  return {0, -1};
        }
        return {0, 0};
    }
    
    static constexpr string_view name(Direction dir) {
        switch (dir) {
            case Direction::UP:    return "UP";
            case Direction::RIGHT: return "RIGHT";
            case Direction::DOWN:  return "DOWN";
            case Direction::LEFT:  return "LEFT";
        }
        return "UNKNOWN";
    }
    
    static const vector<Direction>& all() {
        static const vector<Direction> all_directions = {
            Direction::UP, Direction::RIGHT, Direction::DOWN, Direction::LEFT
        };
        return all_directions;
    }
};

class Puzzle {
private:
    static const int SIZE = 4;
    
    vector<vector<int>> board;
    int empty_row, empty_col;
    
    vector<vector<int>> target_board = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };

public:
    Puzzle(const vector<vector<int>>& initial_board) : board(initial_board) {
        find_empty_cell();
    }
    
    Puzzle(const Puzzle& other) 
        : board(other.board), empty_row(other.empty_row), empty_col(other.empty_col) {}
    
private:
    void find_empty_cell() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == 0) {
                    empty_row = i;
                    empty_col = j;
                    return;
                }
            }
        }
    }
    
public:
    bool is_target() const {
        return board == target_board;
    }
    
    string get_hash() const {
        string hash;
        for (const auto& row : board) {
            for (int val : row) {
                hash += to_string(val) + ",";
            }
        }
        return hash;
    }
    
    bool can_move(Direction dir) const {
        auto offset = DirectionHelper::offset(dir);
        int new_row = empty_row + offset.first;
        int new_col = empty_col + offset.second;
        return new_row >= 0 && new_row < SIZE && new_col >= 0 && new_col < SIZE;
    }
    
    vector<Direction> get_possible_directions() const {
        vector<Direction> possible;
        for (Direction dir : DirectionHelper::all()) {
            if (can_move(dir)) {
                possible.push_back(dir);
            }
        }
        return possible;
    }
    
    unique_ptr<Puzzle> move(Direction dir) const {
        if (!can_move(dir)) return nullptr;
        
        auto new_state = make_unique<Puzzle>(*this);
        auto offset = DirectionHelper::offset(dir);
        int new_row = empty_row + offset.first;
        int new_col = empty_col + offset.second;
        
        swap(new_state->board[empty_row][empty_col], 
             new_state->board[new_row][new_col]);
        
        new_state->empty_row = new_row;
        new_state->empty_col = new_col;
        
        return new_state;
    }
    
    string get_direction_name(Direction dir) const {
        return string(DirectionHelper::name(dir));
    }

    vector<pair<unique_ptr<Puzzle>, string>> get_next_states() const {
        vector<pair<unique_ptr<Puzzle>, string>> next_states;
        
        auto possible_dirs = get_possible_directions();
        for (Direction dir : possible_dirs) {
            auto new_state = this->move(dir);
            if (new_state) {
                next_states.emplace_back(std::move(new_state), get_direction_name(dir));
            }
        }
        
        return next_states;
    }
    
    pair<int, int> get_empty_position() const {
        return {empty_row, empty_col};
    }

    bool is_solvable() const {
        vector<int> linear;
        for (const auto& row : board) {
            for (int val : row) {
                if (val != 0) linear.push_back(val);
            }
        }
        
        int inversions = 0;
        for (int i = 0; i < linear.size(); i++) {
            for (int j = i + 1; j < linear.size(); j++) {
                if (linear[i] > linear[j]) {
                    inversions++;
                }
            }
        }
        
        // ???????, ????:
        // ????? ???????? ?????? ? ????? ?????? 00 (?????) ????????
        // ????? ???????? ???????? ? ????? ?????? 00 (?????) ??????
        int empty_row_down = SIZE - empty_row;
        return (inversions % 2) != (empty_row_down % 2);
    }

    int manhattan_distance() const {
        int distance = 0;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int value = board[i][j];
                if (value != 0) {
                    int target_row = (value - 1) / SIZE;
                    int target_col = (value - 1) % SIZE;
                    distance += abs(i - target_row) + abs(j - target_col);
                }
            }
        }
        return distance;
    }
};

vector<string> find_solution(unique_ptr<Puzzle> initial_state) {
    if (!initial_state->is_solvable()) {
        return {};
    }
    
    queue<unique_ptr<Puzzle>> states_queue;
    unordered_map<string, string> came_from;
    unordered_map<string, string> move_used;
    
    string initial_hash = initial_state->get_hash();
    states_queue.push(move(initial_state));
    came_from[initial_hash] = "";
    
    int states_visited = 0;
    const int MAX_STATES = 1000000000;
    
    while (!states_queue.empty() && states_visited < MAX_STATES) {
        auto current_state = move(states_queue.front());
        states_queue.pop();
        states_visited++;
        
        string current_hash = current_state->get_hash();
        
        if (current_state->is_target()) {            
            vector<string> path;
            string hash = current_hash;
            
            while (move_used.find(hash) != move_used.end() && !move_used[hash].empty()) {
                path.push_back(move_used[hash]);
                hash = came_from[hash];
            }
            
            reverse(path.begin(), path.end());
            return path;
        }
        
        auto next_states = current_state->get_next_states();
        
        for (auto& [next_state, move_name] : next_states) {
            string next_hash = next_state->get_hash();
            
            if (came_from.find(next_hash) == came_from.end()) {
                came_from[next_hash] = current_hash;
                move_used[next_hash] = move_name;
                states_queue.push(move(next_state));
            }
        }
    }
    
    if (states_visited >= MAX_STATES) {
        cout << "Search limit reached (" << MAX_STATES << " states). Solution may be too complex." << endl;
    } else {
        cout << "Solution not found in " << states_visited << " states!" << endl;
    }
    
    return {};
}

vector<vector<int>> read_board() {
    vector<vector<int>> board(4, vector<int>(4));
    
    cout << "Enter 4 lines with 4 numbers each" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            string cell;
            cin >> cell;
            
            if (cell == "00") {
                board[i][j] = 0;
            } else {
                if (cell.length() == 2 && cell[0] == '0') {
                    cell = cell.substr(1);
                }
                board[i][j] = stoi(cell);
            }
        }
    }
    
    return board;
}

int main() {
    cout << "=== PUZZLE SOLVER ===" << endl;
    cout << "Target state:" << endl;
    cout << "01 02 03 04" << endl;
    cout << "05 06 07 08" << endl;
    cout << "09 10 11 12" << endl;
    cout << "13 14 15 00" << endl;
    cout << endl;
    
    auto initial_board = read_board();
    auto initial_state = make_unique<Puzzle>(initial_board);
    if (!initial_state->is_solvable())
    {
        cout << "Solution doesn`t exist!" << endl;
        return 0;
    }

    auto solution = find_solution(move(initial_state));
    
    if (!solution.empty()) {
        cout << "\n=== SOLUTION FOUND ===" << endl;
        cout << "Number of moves: " << solution.size() << endl;
        cout << "Sequence of empty cell (00) movements:" << endl;
        
        for (int i = 0; i < solution.size(); i++) {
            cout << (i + 1) << ". " << solution[i];
            if (i < solution.size() - 1) {
                cout << " -> ";
            }
            if ((i + 1) % 6 == 0) {
                cout << endl;
            }
        }
        cout << endl;
    }
    
    return 0;
}