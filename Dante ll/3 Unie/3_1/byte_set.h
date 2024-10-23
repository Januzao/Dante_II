#ifndef BYTE_SET_H
#define BYTE_SET_H

union byte_set {
    int value;
    unsigned char bytes[sizeof(int)];
};

#endif
