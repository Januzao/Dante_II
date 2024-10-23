#ifndef COMPARATORS_H
#define COMPARATORS_H

int comp_min(const int *ptr1, const int *ptr2, int width);
int comp_max(const int *ptr1, const int *ptr2, int width);
int comp_sum(const int *ptr1, const int *ptr2, int width);
int sort_rows(int **matrix, int width, int height, int (*comp)(const int *, const int *, int));

#endif // COMPARATORS_H
