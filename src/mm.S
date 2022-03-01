.globl memzero
memzero:
    str xzr, [x0], #8
    sub x1, x1, #8
    b.gt memzero
    ret