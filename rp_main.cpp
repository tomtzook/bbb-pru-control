#include <unistd.h>
#include <iostream>

#include <prurp.h>
#include <rpmsg.h>


struct message {
    unsigned int count;
    bool overflow;
};

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

    try {
        auto pru0_dram = pru.dram<unsigned int>();
        pru::rp::channel channel(pru0_dram[0]);

        for (int i = 0; i < 10; ++i) {
            std::cout << "Sending message" << std::endl;

            std::string msg = "hello";
            channel << msg;

            channel >> msg;

            auto m = reinterpret_cast<const message*>(msg.c_str());
            std::cout << "Received message: " << m->count
                << " (overflow " << m->overflow << ")"
                << std::endl;
        }

    } catch (...) {
        std::cerr << "ERROR:"
            << " is_running=" << pru.is_running()
            << " "
            << std::endl;
    }

    std::cout << "Done..." << std::endl;
    pru.stop();

    return 0;
}
