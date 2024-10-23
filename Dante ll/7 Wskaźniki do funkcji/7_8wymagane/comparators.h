#ifndef UNTITLED1_COMPARATORS_H
#define UNTITLED1_COMPARATORS_H

#include <stddef.h>

struct point_t
{
    double x;
    double y;
};


int sort(void *base, size_t elements, size_t size, int (*comparator)(const void*, const void*));

int comp_int(const void* a, const void* b);
int comp_double(const void* a, const void* b);
int comp_point(const void* a, const void* b);

#endif //UNTITLED1_COMPARATORS_H
