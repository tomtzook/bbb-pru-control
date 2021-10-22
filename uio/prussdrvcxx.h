#pragma once

#include <cstddef>
#include <exception>

#include <prussdrv.h>
#include <pru.h>


namespace pru::uio {

class exception : std::exception {

};

enum class ram {
    DATA,
    IRAM
};

struct pru_def {
    _pru_def base;

    const unsigned data_ram;
    const unsigned i_ram;
};

extern pru_def pru0;
extern pru_def pru1;

class pru {
public:
    explicit pru(pru_def pru_def, unsigned int host_interrupt);

    void enable(size_t address=0);
    void disable();
    void reset();

    void write_memory(ram ram, size_t offset, const void* buffer, size_t size);

    void* map_memory(ram ram);
    template<typename T>
    T* map_memory(ram ram) {
        return reinterpret_cast<T*>(map_memory(ram));
    }

    void send_event(unsigned int event_num);
    size_t wait_event();
    size_t wait_event_timeout(int time_us=0);
    void clear_event(unsigned int sysevent);

    void load_data(const void* buffer, size_t size);
    void load_data(const char* path);

    void exec_program(const void* buffer, size_t size, size_t address=0);
    void exec_program(const char* path, size_t address=0);
    
private:
    unsigned ram_id(ram ram);

    pru_def m_pru_def;
    unsigned int m_host_interrupt;
};

}
