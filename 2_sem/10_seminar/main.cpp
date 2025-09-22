#include <iostream>
#include <vector>
#include <functional>

void counting_sort(std::vector<int>& vec, int rank)
{
    std::vector<int> count(rank);
    for (int v : vec)
        ++count[v];
    
    int k = 0;
    for (int i = 0; i < rank; ++i)
    {
        for (int j = 0; j < count[i]; ++j)
            vec[k++] = i;
    }
}

using uint=unsigned int;

inline int get_byte(uint v, int byte_pos)
{
    return (v >> (8 * byte_pos)) & 0xFF;
};

void LSD(std::vector<uint> &vec)
{
    std::vector<uint> buf(vec.size());

    for (int byte_pos = 0; byte_pos < 4; ++byte_pos)
    {
        int count[256] = {0};
        for (uint v : a)
            ++count[get_byte(v, byte_pos)];

        int packet[256] = {0};
        for (int i = 1; i < 256; ++i)
            packet[i] = packet[i - 1] + count[i - 1];
    
        for (uint v : vec)
            buf[packet[get_byte(v, byte_pos)]++] = v;
        vec.swap(buf);
    }
}

void MSD(std::vector<uint> &vec, int packet_beg, int packet_end)
{
    std::vector<uint> buf(vec.size());
    std::function<void(int, int, int)> MSD_rec = [&](int packet_beg, int packet_end, int byte_pos)
    {
        int count[256] = {0};
        for (int i = packet_beg; i < packet_end; ++i)
            ++count[get_byte(vec[i], byte_pos)];

        int packet[256] = {0};
        packet[0] = packet_beg;
        for (int i = 1; i < 256; ++i)
            packet[i] = packet[i - 1] + count[i - 1];
    
        for (int i = packet_beg; i < packet_end; ++i)
            buf[packet[get_byte(a[i], byte_pos)]++] = vec[i];

        for (int i = packet_beg; i < packet_end; ++i)
            vec[i] = buf[i];

        packet[0] = packet_beg;
        for (int i = 1; i < 256; ++i)
            packet[i] = packet[i - 1] + count[i - 1];
        if (byte_pos == 0)
            return;
        for (int i = 0; i < 256; ++i)
            if (count[i] != 0)
                MSD_rec(packet[i], packet[i] + count[i], byte_pos - 1);
    };

    MSD_rec(0, vec.size(), 3);
}

void packet_sort(std::vector<int>& vec, int rank)
{
    std::vector<int> count(rank);
    for (int v : vec)
        ++count[v];
    
    std::vector<int> packet(rank);
    for (int i = 1; i < rank; ++i)
        packet[i] = packet[i - 1] + count[i - 1];
    std::vector<int> buf(vec.size());

    for (int v : vec)
        buf[packet[v]++] = v;
    vec.swap(buf);
}

std::ostream& operator<< (std::ostream& os, std::vector<int>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
        os << vec[i] << " ";
    return os;
}

int main()
{
    std::vector<int> a = {8, 0, 8, 1, 3, 2, 1, 3};
    std::cout << a << std::endl;
    counting_sort(a, 9);
    std::cout << a << std::endl;
    
}