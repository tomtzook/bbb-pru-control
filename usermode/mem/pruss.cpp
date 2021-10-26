
#include <fstream>
#include <vector>
#include <elf.h>
#include <cstring>

#include "pruss.h"


namespace bbb::pruss {

static std::vector<char> load_file(const std::string& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    file.exceptions(std::ios::failbit);

    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(file_size);
    file.read(buffer.data(), file_size);

    return buffer;
}

#ifdef MEM_GLOBAL_REGS
module_peripheral _global_modules[] = {
        module_peripheral(pruicss::ADDRESS)
};
#endif

module_peripheral::module_peripheral(size_t address) noexcept
        : peripheral(address, MODULE_CTRL_SIZE)
{ }


pru::pru(module_peripheral& module, unsigned num)
    : m_module(module)
    , m_num(num) {
}

void pru::enable() {
    auto reg = ctrl_reg();
    reg->ctrl.data = 0;
    reg->ctrl.bits.en = 1;
}

void pru::disable() {
    auto reg = ctrl_reg();
    reg->ctrl.bits.en = 0;
}

void pru::load_from_elf(const std::string& path) {
    auto buffer = load_file(path);

    size_t code_idx = 0;
    size_t data_idx = 0;

    elf::image image(buffer.data());

    for (auto program : image.programs()) {
        if (program.flags().bits.execute) {
            memcpy((void*) (iram<char>() + code_idx), program.data<char>(), program.size());
            code_idx += program.size();
        } else if (program.flags().bits.read || program.flags().bits.write) {
            memcpy((void*) (dram<char>() + data_idx), program.data<char>(), program.size());
            data_idx += program.size();
        }
    }
}

volatile pru_ctrl* pru::ctrl_reg() {
    switch (m_num) {
        case 0: return m_module.data<module_peripheral::register_pru0ctrl>();
        case 1: return m_module.data<module_peripheral::register_pru1ctrl>();
        default: return nullptr;
    }
}

}
