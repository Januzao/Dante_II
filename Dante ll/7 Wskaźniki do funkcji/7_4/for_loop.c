#include "for_loop.h"
#include <stdio.h>
#include <math.h>
#include "tested_declarations.h"
#include "rdebug.h"

void print_value(double x){
    printf("%f ", x);
}
void print_accumulated(double x){
    static double sum = 0;
    sum += x;
    printf("%f ", sum);
}
void print_square(double x){
    printf("%f ", x * x);
}
void print_abs(double x){
    printf("%f ", fabs(x));
}


void for_loop(double start, double step, double end, void(*iter_func)(double)) {
    if ((step > 0 && start > end) || (step < 0 && start < end) || step == 0) {
        return;
    } else if (iter_func == NULL) {
        return;
    }

    iter_func(start);
    if ((step > 0 && start + step <= end) || (step < 0 && start + step >= end)) {
        for_loop(start + step, step, end, iter_func);
    }
}


int main(void){
    double start, step, end;
    int operation;
    void (*funcs[])(double) = {print_value, print_accumulated, print_square, print_abs};

    printf("Podaj poczatek, krok i koniec przedzialu:");
    if (scanf("%lf %lf %lf", &start, &step, &end) != 3){
        printf("Incorrect input");
        return 1;
    }

    if (step == 0 || (step > 0 && start > end) || (step < 0 && start < end)){
        printf("Incorrect input data");
        return 2;
    }

    printf("Podaj rodzaj operacji:");
    if (scanf("%d", &operation) != 1){
        printf("Incorrect input");
        return 1;
    }

    if (operation < 0 || operation > 3){
        printf("Incorrect input data");
        return 2;
    }

    for_loop(start, step, end, *(funcs + operation));
    return 0;
}


