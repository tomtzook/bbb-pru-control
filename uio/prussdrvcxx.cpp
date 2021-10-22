
#include <prussdrv.h>

#include "prussdrvcxx.h"


#define CHECK_ERROR(...)     \
    do {                     \
        if (__VA_ARGS__) {   \
            throw exception(); \
        }                    \
    } while(0)

namespace pru::uio {

pru_def pru0 = {_pru0, PRUSS0_PRU0_DATARAM, PRUSS0_PRU0_IRAM};
pru_def pru1 = {_pru1, PRUSS0_PRU1_DATARAM, PRUSS0_PRU1_IRAM};

pru::pru(pru_def pru_def, unsigned int host_interrupt)
    : m_pru_def(pru_def)
    , m_host_interrupt(host_interrupt) {
    CHECK_ERROR(prussdrv_open(host_interrupt));
}

void pru::enable(size_t address) {
    CHECK_ERROR(prussdrv_pru_enable_at(m_pru_def.base.pru_id, address));
}

void pru::disable() {
    CHECK_ERROR(prussdrv_pru_disable(m_pru_def.base.pru_id));
}

void pru::reset() {
    CHECK_ERROR(prussdrv_pru_reset(m_pru_def.base.pru_id));
}

void pru::write_memory(ram ram, size_t offset, const void* buffer, size_t size) {
    CHECK_ERROR(prussdrv_pru_write_memory(ram_id(ram),
                                          offset,
                                          reinterpret_cast<const unsigned int*>(buffer),
                                          size));
}

void* pru::map_memory(ram ram) {
    void* address;
    CHECK_ERROR(prussdrv_map_prumem(ram_id(ram),
                                    &address));
    return address;
}

void pru::send_event(unsigned int event_num) {
    CHECK_ERROR(prussdrv_pru_send_event(event_num));
}

size_t pru::wait_event() {
    return prussdrv_pru_wait_event(m_host_interrupt);
}

size_t pru::wait_event_timeout(int time_us) {
    size_t count = prussdrv_pru_wait_event_timeout(m_host_interrupt, time_us);
    if (-1 == count) {
        throw exception();
    }

    return count;
}

void pru::clear_event(unsigned int sysevent) {
    CHECK_ERROR(prussdrv_pru_clear_event(m_host_interrupt, sysevent));
}

void pru::load_data(const void* buffer, size_t size) {
    CHECK_ERROR(prussdrv_load_data(m_pru_def.base.pru_id,
                                   reinterpret_cast<const unsigned int*>(buffer),
                                   size));
}

void pru::load_data(const char* path) {
    CHECK_ERROR(prussdrv_load_datafile(m_pru_def.base.pru_id, path));
}

void pru::exec_program(const void* buffer, size_t size, size_t address) {
    CHECK_ERROR(prussdrv_exec_code_at(m_pru_def.base.pru_id,
                                      reinterpret_cast<const unsigned int*>(buffer),
                                      size, address));
}

void pru::exec_program(const char* path, size_t address) {
    CHECK_ERROR(prussdrv_exec_program_at(m_pru_def.base.pru_id, path, address));
}

unsigned pru::ram_id(ram ram) {
    switch (ram) {
        case ram::DATA: return m_pru_def.data_ram;
        case ram::IRAM: return m_pru_def.i_ram;
        default: throw exception();
    }
}

}
