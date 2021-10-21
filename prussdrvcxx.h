#pragma once

#include <cstddef>
#include <exception>


namespace prussdrv {

class exception : std::exception {

};

enum class ram {
    DATA,
    IRAM
};

class pru {
public:
    explicit pru(unsigned pru_num, unsigned int host_interrupt);

    void enable(size_t address=0);
    void disable();

    void reset();

    void write_memory(ram ram, size_t offset, const void* buffer, size_t size);
    void* map_memory(ram ram);

    void send_event(unsigned int event_num);
    size_t wait_event();
    size_t wait_event_timeout(int time_us=0);
    void clear_event(unsigned int sysevent);

    void load_data(const void* buffer, size_t size);
    void load_data(const char* path);

    void exec_program(const void* buffer, size_t size, size_t address=0);
    void exec_program(const char* path, size_t address=0);

private:
    unsigned m_pru_num;
    unsigned int m_host_interrupt;
};

}
