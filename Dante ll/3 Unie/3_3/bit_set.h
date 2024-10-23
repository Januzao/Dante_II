#ifndef BIT_SET_H
#define BIT_SET_H

union bit_set {
    unsigned char byte;
    struct {
        unsigned bit0 : 1;
        unsigned bit1 : 1;
        unsigned bit2 : 1;
        unsigned bit3 : 1;
        unsigned bit4 : 1;
        unsigned bit5 : 1;
        unsigned bit6 : 1;
        unsigned bit7 : 1;
    } __attribute__((packed)) bits;
};

#endif
