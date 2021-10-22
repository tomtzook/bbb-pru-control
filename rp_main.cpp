#include <unistd.h>
#include <iostream>
#include <prurp.h>


int main() {
    pru::rp::pru pru(pru::rp::pru0);

    if (pru.is_running()) {
        std::cout << "PRU is running. Stopping..." << std::endl;
        pru.stop();
    }

    std::cout << "Upload software..." << std::endl;
    pru.load_firmware("/tmp/pru_test");

    std::cout << "Starting PRU..." << std::endl;
    pru.start();

    auto pru0_dram = pru.dram<unsigned int>();
    for (int i = 0; i < 10; ++i) {
        std::cout << "READ: " << pru0_dram[0] << std::endl;
        usleep(1000 * 500);
    }

    std::cout << "Done..." << std::endl;
    pru.stop();

    return 0;
}
