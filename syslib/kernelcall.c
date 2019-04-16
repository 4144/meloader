//
// Created by pbx on 15/04/19.
//

#include <stdint.h>
#include "printf.h"
#include "meloader.h"

typedef struct {
    const char *name;
    int size;
    int (*impl)(void *);
} kernelcall_table;

kernelcall_table kctable[] = {
        {
            .name = "sys_snowball_read",
            .size = 16,
            .impl = snowball_read
        }
};

int kernelcall(uint8_t call_id, uint16_t par_sz, void *par) {
    if ( call_id > ( sizeof kctable / sizeof(kernelcall_table))) {
        mel_printf("[libc] syscall( %i, %i, 0x%08x) not impl\n", call_id, par_sz, par);
        return 0;
    }
    if ( par_sz != kctable[call_id].size ){
        mel_printf("[libc] syscall( %i, %i, 0x%08x) wrong size\n", call_id, par_sz, par);
        return 0;
    }
    return kctable[call_id].impl(par);
}