#ifndef COLOR_H
#define COLOR_H

enum colors {
    RED = 1,
    GREEN,//2
    BLUE,//3
    YELLOW,//4
    UNKNOWN//5
};

struct color_t {
    float r;
    float g;
    float b;
    enum colors c;
};

struct __attribute((packed)) kostyl_t {
    float a;
    float b;
    float c;
    float d;
    float e;
    float f;
    float g;
    float h;
    float k;
    float l;
};
typedef struct kostyl_t k;

typedef struct __attribute((packed))  {
    k a;
    k b;
    k c;
    k d;
    k e;
    k f;
    k g;
    k h;
    k k;
    k l;
} take_this;



#endif