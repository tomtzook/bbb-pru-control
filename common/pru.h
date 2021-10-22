#pragma once

#include <exception>

namespace pru {

class exception : public std::exception {
};

class mem_exception : public exception {

};

struct _pru_def {
    const unsigned pru_id;

    const size_t dram_offset;
    const size_t sharedmem_offset;
};

extern _pru_def _pru0;
extern _pru_def _pru1;

class pru_memory {
public:
    pru_memory();
    ~pru_memory();

    template<typename T>
    T* memory() {
        return reinterpret_cast<T*>(m_memory);
    }

private:
    static constexpr off_t PRU_MEM_ADDR = 0x4A300000;
    static constexpr size_t PRU_MEM_LEN = 0x80000;

    void* m_memory;
};

}
