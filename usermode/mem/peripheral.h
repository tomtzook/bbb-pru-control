#pragma once

#include <cstddef>
#include <exception>


namespace bbb {

class module_access_exception : std::exception {

};

template<size_t offset, typename type>
struct reg {
    static constexpr size_t OFFSET = offset;
    using TYPE = type;
};

template<typename T>
struct is_reg : std::false_type {};

template<size_t offset, typename type>
struct is_reg<reg<offset, type>> : std::true_type {};

class peripheral {
public:
    peripheral(size_t address, size_t size) noexcept;
    virtual ~peripheral();

    template<typename T>
    volatile T* raw(size_t offset=0) {
        if (nullptr == m_base) {
            throw module_access_exception();
        }

        return reinterpret_cast<volatile T*>(
                reinterpret_cast<volatile char*>(m_base) + offset);
    }

    template<typename T>
    const volatile T* raw(size_t offset=0) const {
        if (nullptr == m_base) {
            throw module_access_exception();
        }

        return reinterpret_cast<const volatile T*>(
                reinterpret_cast<const volatile char*>(m_base) + offset);
    }

    template<
            typename T,
            typename std::enable_if<
                    is_reg<T>::value,
                    bool>::type = 0
    >
    volatile typename T::TYPE* data(size_t offset=0) {
        return raw<typename T::TYPE>(T::OFFSET);
    }

    template<
            typename T,
            typename std::enable_if<
                    is_reg<T>::value,
                    bool>::type = 0
    >
    const volatile typename T::TYPE* data(size_t offset=0) const {
        return raw<typename T::TYPE>(T::OFFSET);
    }

    template<typename T>
    T read(size_t offset=0) const {
        return *raw<T>(offset);
    }

    template<typename T>
    inline void write(T value, size_t offset=0) {
        *raw<T>(offset) = value;
    }

    template<
            typename T,
            typename std::enable_if<
                    is_reg<T>::value,
                    bool>::type = 0
    >
    inline typename T::TYPE read_reg() const {
        return read<typename T::TYPE>(T::OFFSET);
    }

    template<
            typename T,
            typename std::enable_if<
                    is_reg<T>::value,
                    bool>::type = 0
    >
    inline void write_reg(typename T::TYPE value) {
        write(value, T::OFFSET);
    }

private:
    static void* map_memory(size_t address, size_t size);

    volatile void* const m_base;
    size_t m_size;
};

}
