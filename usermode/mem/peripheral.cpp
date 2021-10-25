
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "mem/peripheral.h"


namespace bbb {

peripheral::peripheral(size_t address, size_t size) noexcept
    : m_base(map_memory(address, size))
    , m_size(size)
{}

peripheral::~peripheral() {
    if (nullptr != m_base) {
        munmap((void*) m_base, m_size);
    }
}

void* peripheral::map_memory(size_t address, size_t size) {
    int fd = open("/dev/mem", O_RDWR);
    if (fd < 0) {
        return nullptr;
    }

    void* mem = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, address);
    if (MAP_FAILED == mem) {
        close(fd);
        return nullptr;
    }

    close(fd);

    return mem;
}

}
