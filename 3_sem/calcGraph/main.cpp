#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>
#include <iostream>

class Vertex 
{ 
public: 
    // virtual ~Vertex(); 
    virtual int num_inputs() const = 0; 
    virtual void set_input(int inp_idx, double inp_val) = 0; 
    virtual int num_outputs() const = 0; 
    virtual double get_output(int out_idx) = 0; 
    virtual void calc_value() = 0; 
}; 

struct Edge 
{ 
    int out_vertex_id; 
    int out_port_id; 
    int inp_vertex_id; 
    int inp_port_id; 
}; 

class PlusOperator : public Vertex 
{ 
    double m_out_val = 0;
    double m_inp_val[2] = {0}; 
     
public:

    int num_inputs() const override
    { 
        return 2; 
    } 
    void set_input(int inp_idx, double inp_val) override 
    { 
        if(inp_idx < 0 || inp_idx >= 2) 
            throw std::out_of_range("Bad inp_idx in the PlusOperator::set_input"); 
        m_inp_val[inp_idx] = inp_val; 
    } 
    void calc_value() override 
    { 
        m_out_val = m_inp_val[0] + m_inp_val[1]; 
    } 
    int num_outputs() const override 
    { 
        return 1; 
    } 
    double get_output(int out_idx) override 
    { 
        return m_out_val; 
    } 
};

class CalcGraph : public Vertex 
{ 
public:
    int num_inputs() const override
    {
        int result = 0;
        for (std::pair<int, int> p : input_vertexes)
        {
            result += vertex[p.first]->num_inputs() - p.second;
        }
        return result;
    }

    void set_input(int inp_idx, double inp_val) override
    {
        auto input_vertex = std::find_if(input_vertexes.begin(), input_vertexes.end(),
                                        [&](std::pair<int, int> p) -> bool { return p.first == inp_idx; });
        if (input_vertex == input_vertexes.end() || inp_idx < 0 || inp_idx > num_inputs() || (*input_vertex).second == vertex[inp_idx]->num_inputs())
            throw std::out_of_range("Bad inp_idx in the CalcGraph::set_input");
        vertex[inp_idx]->set_input((*input_vertex).second, inp_val);
        (*input_vertex).second += 1;
    }

    int num_outputs() const override
    {
        int result = 0;
        for (std::pair<int, int> p : output_vertexes)
        {
            result += vertex[p.first]->num_outputs();
        }
        return result;
    } 

    double get_output(int out_idx) override
    {
        auto output_vertex = std::find_if(output_vertexes.begin(), output_vertexes.end(),
                                        [&](std::pair<int, int> p) -> bool { return p.first == out_idx; });
        if (output_vertex == output_vertexes.end() || out_idx < 0 || out_idx > num_outputs())
            throw std::out_of_range("Bad out_idx in the CalcGraph::get_output");
        return vertex[out_idx]->get_output((*output_vertex).second);
    }

    void calc_value() override
    {
        std::vector<bool> visited(graph.size(), false);
        std::function<void(int)> dfs = [&](int v)
        {
            visited[v] = true;
            vertex[v]->calc_value();
            for(int u : graph[v])
            {
                if(!visited[u])
                {
                    auto edge = std::find_if(edges.begin(), edges.end(),
                                [&](Edge e) -> bool { return e.out_vertex_id == v && e.inp_vertex_id == u; });
                    vertex[u]->set_input(edge->inp_port_id, vertex[v]->get_output(edge->out_port_id));
                    vertex[u]->calc_value();
                    dfs(u);
                }
            }
        };

        std::vector<int> sorted = topological_sort();
        for(int v : sorted)
        {
            if (!visited[v])
                dfs(v);
        }
    }

    void set_data(const std::vector<Vertex*> &vertex, const std::vector<Edge> &edges)
    {
        this->vertex = vertex;
        this->edges = edges;

        for (int i = 0; i < vertex.size(); ++i)
        {
            graph.push_back(std::vector<int>());
        }

        for (Edge e : edges)
        {
            graph[e.out_vertex_id].push_back(e.inp_vertex_id);
        }

        for (int i = 0; i < graph.size(); ++i)
        {
            int nums = 0;
            for (int j = 0; j < graph.size(); ++j)
            {
                if (std::find(graph[j].begin(), graph[j].end(), i) != graph[j].end())
                    ++nums;
            }
            if (vertex[i]->num_inputs() > nums)
            {
                input_vertexes.push_back(std::pair<int, int> (i, nums));
            }

            if (vertex[i]->num_outputs() > graph[i].size())
                output_vertexes.push_back(std::pair<int, int> (i, graph[i].size()));
        }
    } 

private:
    std::vector<std::vector<int>> graph;
    std::vector<Vertex*> vertex;
    std::vector<Edge> edges;

    std::vector<std::pair<int, int>> input_vertexes; // vertex_id, port_id
    std::vector<std::pair<int, int>> output_vertexes; // vertex_id, port_id

    std::vector<int> topological_sort()
    {
        std::vector<bool> visited(graph.size());
        std::vector<int> sorted;
        std::function<void(int)> dfs = [&](int v)
        {
            visited[v] = true;
            for(int u : graph[v])
                if(!visited[u])
                    dfs(u);
            sorted.push_back(v);
        };
        for(int v = 0; v < graph.size() ; ++v)
            if(!visited[v])
                dfs(v);
        std::reverse(sorted.begin(), sorted.end());
        return sorted;
    }
};

int main()
{
    CalcGraph cg; 
    std::vector< Vertex* > vertex; 
    std::vector< Edge > edges; 
    vertex.push_back(new PlusOperator);//vertex_id = 0 
    vertex.push_back(new PlusOperator);//vertex_id = 1 
    edges.push_back(Edge{1,0,0,0});//First output to second inp0 
    cg.set_data(vertex,edges); 
    std::cout << cg.num_inputs() << std::endl;//3 
    std::cout << cg.num_outputs() << std::endl;//1 
    cg.set_input(0,1.0); 
    cg.set_input(1,2.0); 
    cg.set_input(1,3.0); 
    cg.calc_value(); 
    std::cout << cg.get_output(0) << std::endl;//1.0 + 2.0 + 3.0 = 6
}