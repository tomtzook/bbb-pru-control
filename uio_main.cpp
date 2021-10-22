#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <prussdrv.h>
#include <pruss_intc_mapping.h>
#include <cerrno>

#include "prussdrvcxx.h"


int main() {
    tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

    prussdrv_init();

    pru::uio::pru pru(pru::uio::pru0, PRU_EVTOUT0);
    prussdrv_pruintc_init(&pruss_intc_initdata);

    pru.enable();
    try {
        pru.load_data("/tmp/data.bin");
        pru.exec_program("/tmp/text.bin");

        auto memory = pru.map_memory<unsigned int>(pru::uio::ram::DATA);
        for(int i = 0; i < 5; i++){
            printf("Read: %u\n", memory[0]);
            usleep(500000);
            fflush(stdout);
        }

        printf("Waiting event\n");
        pru.wait_event();
        pru.clear_event(PRU0_ARM_INTERRUPT);
        printf("Done\n");
    } catch (const std::exception&) {
        fprintf(stderr, "ERROR\n");
    }
    pru.disable();

    prussdrv_exit();
    return 0;
}


/*static int example() {
    int j;
    unsigned int read_result;

    void* map_address;
    prussdrv_map_prumem(PRUSS0_PRU0_DATARAM, &map_address);

    for(j=0; j<1000; j++){
        read_result = *((unsigned int*) map_address);
        printf("Read: %u\n", read_result);
        usleep(500000);
        fflush(stdout);
    }

    return 0;
}

int main() {
    int ret;
    tpruss_intc_initdata pruss_intc_initdata = PRUSS_INTC_INITDATA;

    prussdrv_init();
    ret = prussdrv_open(PRU_EVTOUT_0);
    if (ret) {
        printf("prussdrv_open open failed\n");
        return ret;
    }

    prussdrv_pruintc_init(&pruss_intc_initdata);

    if(prussdrv_load_datafile(PRU_NUM, "/tmp/data.bin")) {
        fprintf(stderr, "ERROR: Could not load data file\n");
        return 1;
    }

    printf("\tINFO: Executing example.\r\n");
    if(prussdrv_exec_program(PRU_NUM, "/tmp/text.bin")) {
        fprintf(stderr, "ERROR: Could not load code file\n");
        return 1;
    }

    example();

    prussdrv_pru_disable(PRU_NUM);
    prussdrv_exit ();

    return 0;
}*/
