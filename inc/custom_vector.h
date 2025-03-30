#include <cstdint>
#include <memory>
#include <stdexcept>

template <typename T, class Allocator = std::allocator<T>>
class CustomVector
{
    std::size_t current_size;
    std::size_t current_capacity;
    T *pool;

    const size_t koef;
    Allocator allocator;

    inline bool need_resize() noexcept(true)
    {
        return current_size + 1 >= current_capacity;
    }

public:
    using value = T;
    using const_value = const T;
    using reference = T &;
    using const_reference = const T &;

    CustomVector() : current_size(0),
                     current_capacity(1),
                     pool(nullptr),
                     koef(2) {

                     };

    CustomVector(const CustomVector &)
    {
    }

    CustomVector(CustomVector &&)
    {
    }

    void push(const T &value)
    {
        if (need_resize)
        {
            reserve(capacity * koef);
        }

        allocator.construct(pool + current_size, value);
        ++current_size;
    }

    void push(T &&value)
    {

        if (need_resize())
        {
            reserve(current_capacity * koef);
        }

        allocator.construct(pool + current_size, std::move(value));
        ++current_size;
    }

    void erase(const size_t &index)
    {
        if (index >= current_size)
        {
            throw std::out_of_range("index is larger than size");
        }

        allocator.destroy(pool + index);

        for (size_t i = index; i < current_size - 1; ++i)
        {
            *(pool + i) = *(pool + i + 1);
        }

        --current_size;
    }

    const_reference at(const size_t &index) const
    {
        if (index >= current_size)
        {
            throw std::out_of_range("index is larger than size");
        }
        return pool[index];
    }

    reference at(const size_t &index)
    {
        if (index >= current_size)
        {
            throw std::out_of_range("index is larger than size");
        }
        return pool[index];
    }

    void reserve(const size_t &new_capacity)
    {
        if (new_capacity == 0)
        {
            for (size_t i = 0; i < current_size; ++i)
            {
                allocator.destroy(pool + i);
            }

            if (pool)
                allocator.deallocate(pool, current_capacity);

            pool = nullptr;
            current_capacity = 0;
            current_capacity = 1;
        }
        else
        {

            T *tmp = allocator.allocate(new_capacity);
            size_t size = 0;

            for (size_t i = 0; i < current_size; ++i)
            {
                if (i < new_capacity)
                {
                    *(tmp + i) = *(pool + i);
                    ++size;
                }
                allocator.destroy(pool + i);
            }

            if (pool)
                allocator.deallocate(pool, current_capacity);

            pool = tmp;
            current_size = size;
            current_capacity = new_capacity;
        }
    }

    const_reference operator[](const size_t &index) const noexcept(true)
    {
        return pool[index];
    }

    reference operator[](const size_t &index) noexcept(true)
    {
        return pool[index];
    }

    std::size_t size()
    {
        return current_size;
    }

    std::size_t capacity()
    {
        return current_capacity;
    }

    ~CustomVector()
    {
        allocator.deallocate(pool, current_capacity);
    }
};