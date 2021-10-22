#include <unistd.h>
#include <fcntl.h>
#include <climits>
#include <iostream>

#include "rpmsg.h"


namespace pru::rp {

channel::channel(std::string dev)
    : m_fd(-1) {
    int fd = open(dev.c_str(), O_RDWR);
    if (fd < 0) {
        throw channel_exception();
    }

    m_fd = fd;
}

channel::channel(unsigned dev)
    : channel(dev_path(dev)){
}

channel::~channel() {
    if (m_fd >= 0) {
        close(m_fd);
        m_fd = -1;
    }
}

channel& channel::operator<<(std::string& msg) {
    if (m_fd < 0) {
        throw channel_exception();
    }

    if (write(m_fd, msg.c_str(), msg.size()) < 0) {
        throw channel_exception();
    }

    return *this;
}

channel& channel::operator>>(std::string& buf) {
    if (m_fd < 0) {
        throw channel_exception();
    }

    char buffer[MAX_MESSAGE_SIZE] = {0};
    ssize_t bytes = read(m_fd, buffer, sizeof(buffer) - 1);
    if (bytes < 0) {
        throw channel_exception();
    }

    buf.operator=(buffer);

    return *this;
}

std::string channel::dev_path(unsigned dev) {
    char dev_path[PATH_MAX] = {0};
    sprintf(dev_path, DEFAULT_DEV, dev);

    return dev_path;
}

}
