#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "pru.h"


namespace pru {

_pru_def _pru0 = {0, 0x00000, 0x10000};
_pru_def _pru1 = {1, 0x02000, 0x10000};

pru_memory::pru_memory() {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        throw mem_exception();
    }

    void* pru_memory = mmap(0,
                            PRU_MEM_LEN,
                            PROT_READ | PROT_WRITE,
                            MAP_SHARED,
                            fd,
                            PRU_MEM_ADDR);
    if (MAP_FAILED == pru_memory) {
        close(fd);
        throw mem_exception();
    }

    m_memory = pru_memory;
    close(fd);
}

pru_memory::~pru_memory() {
    munmap(m_memory, PRU_MEM_LEN);
}

}
