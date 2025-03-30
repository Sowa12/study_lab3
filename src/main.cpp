#include <custom_allocator.h>
#include <custom_vector.h>
#include <vector>
#include <map>
#include <iostream>

int main()
{
    try
    {
        const size_t TEST_SIZE = 10;

        std::vector<int, CustomAllocator<int>> v;
        v.reserve(TEST_SIZE);

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            v.push_back(i);
            std::cout << "value: " << v[i] << std::endl;
        }

        CustomVector<int, CustomAllocator<int>> v1;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            v1.push(i);
        }

        for (size_t i = 0; i < v1.size(); ++i)
        {
            std::cout << "index: " << i << " value: " << v1[i] << std::endl;
        }

        std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>>> m_int;

        for (size_t i = 0; i < TEST_SIZE; ++i)
        {
            m_int.insert(std::make_pair(i, 1));
        }

        for (auto &i : m_int)
        {
            std::cout << "m_int key: " << i.first << " value: " << i.second << std::endl;
        }
    }
    catch (const std::exception &ec)
    {
        std::cout << ec.what() << std::endl;
    }
    return EXIT_SUCCESS;
}