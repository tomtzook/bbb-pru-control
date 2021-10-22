#pragma once

#include <string>
#include <fstream>


namespace pru::rp {

class channel_exception : std::exception {

};

class channel {
public:
    explicit channel(std::string dev);
    explicit channel(unsigned dev);
    ~channel();

    channel& operator<<(std::string& msg);
    channel& operator>>(std::string& buf);

private:
    static constexpr const char* DEFAULT_DEV = "/dev/rpmsg_pru%u";
    static constexpr size_t MAX_MESSAGE_SIZE = 512;

    static std::string dev_path(unsigned dev);

    int m_fd;
};

}
