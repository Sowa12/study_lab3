#pragma once
#include <cstdlib>
#include <cstdint>
#include <utility>

template <typename T>
class CustomAllocator
{
public:
    using value_type = T;

    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;

    CustomAllocator() noexcept(true)
    {
        size = 100 * sizeof(T);
        pool = reinterpret_cast<uint8_t *>(::operator new[](size));
        pos = 0;
    }

    ~CustomAllocator() noexcept(true)
    {
    }

    template <typename U>
    CustomAllocator(const CustomAllocator<U> &) noexcept(true)
    {
    }

    T *allocate(size_t n)
    {
        if (pos + n > size)
        {

            size = n * sizeof(T);
            pool = reinterpret_cast<uint8_t *>(::operator new(size));
            pos = 0;
        }
        size_t cur = pos;
        pos += n;
        return reinterpret_cast<pointer>(pool) + cur;
    }

    void deallocate(pointer , std::size_t )
    {
        //
    }

    template <typename U, class... Args>
    void construct(U *p, Args &&...args)
    {
        ::new (p) U(std::forward<Args>(args)...);
    }

    template <class U>
    void destroy(U *p)
    {
        p->~U();
    }

    template <class U>
    struct rebind
    {
        using other = CustomAllocator<U>;
    };

private:
    size_t pos;
    size_t size;
    uint8_t *pool;
};

template <class T, class U>
constexpr bool operator==(const CustomAllocator<T> &a1, const CustomAllocator<U> &a2) noexcept
{
    return true;
};
template <class T, class U>
constexpr bool operator!=(const CustomAllocator<T> &a1, const CustomAllocator<U> &a2) noexcept
{
    return false;
};