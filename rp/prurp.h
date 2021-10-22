#pragma once

#include <string>
#include <pru.h>

namespace pru::rp {

struct pru_def {
    _pru_def base;

    const unsigned remoteproc_id;
};

extern pru_def pru0;
extern pru_def pru1;

class pru {
public:
    explicit pru(pru_def pru_def);

    void start();
    void stop();
    bool is_running();

    void load_firmware(std::string path);

    template<typename T>
    T* dram() {
        return reinterpret_cast<T*>(m_memory.memory<char>() + m_pru_def.base.dram_offset);
    }
    template<typename T>
    T* shared_mem() {
        return reinterpret_cast<T*>(m_memory.memory<char>() + m_pru_def.base.sharedmem_offset);
    }

private:
    static constexpr const char* STATE_FILE = "/sys/class/remoteproc/remoteproc%d/state";
    static constexpr const char* FIRMWARE_FILE = "/sys/class/remoteproc/remoteproc%d/firmware";
    static constexpr const char* FIRMWARE_DIR = "/lib/firmware";

    void write_state(std::string state);
    std::string read_state();
    std::string read_firmware_path();

    pru_def m_pru_def;
    pru_memory m_memory;
};

}
