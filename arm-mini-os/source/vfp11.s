#ifndef ASSEMBLY
#define ASSEMBLY 1
#endif

#include <arch/assembler.h>

armVfp11Mvfr0:
    FMRX    R0, MVFR0
    BX      LR

armVfp11HwInit:
    /* NSACR: Non-secure Access Control Register                            */
    MRC     p15, 0, R0, c1, c1, 2       /* R0 = NSACR                       */
    ORR     R0, R0, #(0x3 << 10)        /* Enable full access for cp10,cp11 */
    MCR     p15, 0, R0, c1, c1, 2       /* NSACR = R0                       */
                                       
    /* CPACR: Coprocessor Access Control Register                           */
    MRC     p15, 0, R0, c1, c0, 2       /* R0 = CPACR                       */
    ORR     R0, R0, #(0xf << 20)        /* Enable full access for cp10,cp11 */
    MCR     p15, 0, R0, c1, c0, 2       /* CPACR = R0                       */

    MOV     R0, #0
    MCR     p15, 0, R0, c7, c5, 4       /* Flush prefetch buffer            */

    BX      LR
