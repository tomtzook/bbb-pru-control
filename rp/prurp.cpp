#include <cstdio>
#include <climits>
#include <unistd.h>

#include <iostream>
#include <fstream>

#include "prurp.h"


namespace pru::rp {

pru_def pru0 = {_pru0, 1};
pru_def pru1 = {_pru1, 2};

pru::pru(pru_def pru_def)
    : m_pru_def(pru_def) {
}

void pru::start() {
    write_state("start");
}

void pru::stop() {
    write_state("stop");
}

bool pru::is_running() {
    std::string state = read_state();
    return state == "running";
}

void pru::load_firmware(std::string path) {
    std::string firmware_path = read_firmware_path();

    if (0 == access(firmware_path.c_str(), F_OK)) {
        // exists
        unlink(firmware_path.c_str());
    }

    std::ifstream src;
    src.open(path, std::ios::binary);
    std::ofstream dst;
    dst.open(firmware_path, std::ios::binary);

    dst << src.rdbuf();

    src.close();
    dst.close();
}

void pru::write_state(std::string state) {
    char state_file_path[PATH_MAX] = {0};
    sprintf(state_file_path, STATE_FILE, m_pru_def.remoteproc_id);

    std::ofstream stream;
    stream.open(state_file_path);
    stream << state;
}

std::string pru::read_state() {
    char state_file_path[PATH_MAX] = {0};
    sprintf(state_file_path, STATE_FILE, m_pru_def.remoteproc_id);

    std::ifstream stream;
    stream.open(state_file_path);
    std::string state;
    stream >> state;

    return state;
}

std::string pru::read_firmware_path() {
    char firmware_file_path[PATH_MAX] = {0};
    sprintf(firmware_file_path, FIRMWARE_FILE, m_pru_def.remoteproc_id);

    std::ifstream stream;
    stream.open(firmware_file_path);
    std::string path;
    stream >> path;

    sprintf(firmware_file_path, "%s/%s", FIRMWARE_DIR, path.c_str());

    return {firmware_file_path};
}

}
