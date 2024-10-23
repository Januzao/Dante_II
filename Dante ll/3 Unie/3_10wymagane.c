#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

struct point_t {
    int x;
    int y;
};

struct rectangle_t {
    struct point_t p;
    int width;
    int height;
};

struct circle_t {
    struct point_t c;
    float r;
};

struct triangle_t {
    struct point_t p1;
    struct point_t p2;
    struct point_t p3;
};

enum figure_types {
    TRIANGLE = 1,
    RECTANGLE,
    CIRCLE
};

struct figure_t {
    union {
        struct rectangle_t rectangle;
        struct circle_t circ;
        struct triangle_t triangle;
    };
    enum figure_types type;
};
float area_triangle(const struct triangle_t *t) {
    if (t == NULL){
        return -1.0f;
    }

    float a = hypotf(t->p1.x - t->p2.x, t->p1.y - t->p2.y);
    float b = hypotf(t->p2.x - t->p3.x, t->p2.y - t->p3.y);
    float c = hypotf(t->p3.x - t->p1.x, t->p3.y - t->p1.y);
    float s = (a + b + c) / 2;

    if (a + b <= c || a + c <= b || b + c <= a) {
        return -1.0f;
    }

    float areaSq = s * (s - a) * (s - b) * (s - c);
    if (areaSq < 0) {
        return -1.0f;
    }

    return sqrtf(areaSq);
}


float area_rectangle(const struct rectangle_t *r) {
    if (r == NULL || r->width <= 0 || r->height <= 0) {
        return -1.0f;
    }
    else {
        return (float)(r->width) * (float)(r->height);
    }
}

float area_circle(const struct circle_t *c) {
    if (c == NULL || c->r <= 0) {
        return -1.0f;
    }
    return M_PI * c->r * c->r;
}


float area_figure(const struct figure_t *f) {
    if (f == NULL){
        return -1.0f;
    }
    switch (f->type) {
        case TRIANGLE:
            return area_triangle(&f->triangle);
        case RECTANGLE:
            return area_rectangle(&f->rectangle);
        case CIRCLE:
            return area_circle(&f->circ);
        default:
            return -1;
    }
}

void display_rectangle(const struct rectangle_t *rect) {
    printf("Rectangle (%d, %d), width = %d, height = %d", rect->p.x, rect->p.y, rect->width, rect->height);
}

void display_triangle(const struct triangle_t *t) {
    printf("Triangle p1(%d, %d), p2(%d, %d), p3(%d, %d)", t->p1.x, t->p1.y, t->p2.x, t->p2.y, t->p3.x, t->p3.y);
}

void display_circle(const struct circle_t *circ) {
    printf("Circle (%d, %d), radius = %.6f", circ->c.x, circ->c.y, circ->r);
}

void display_figure(struct figure_t *f) {
    if (f == NULL){
        return;
    }
    switch (f->type) {
        case RECTANGLE:
            display_rectangle(&f->rectangle);
            break;
        case TRIANGLE:
            display_triangle(&f->triangle);
            break;
        case CIRCLE:
            display_circle(&f->circ);
            break;
        default:
            break;
    }
}

int compare_figures(const void *a, const void *b) {
    if (a == NULL || b == NULL){
        return -1;
    }
    const struct figure_t *fa = *(const struct figure_t **)a;
    const struct figure_t *fb = *(const struct figure_t **)b;

    float area_a = area_figure(fa);
    float area_b = area_figure(fb);

    return (area_b - area_a) > 0 ? 1 : (area_b - area_a) < 0 ? -1 : 0;
}

int sort_by_area(struct figure_t **figures, int size) {
    if (figures == NULL || size <= 0) return 1;

    for (int i = 0; i < size; i++) {
        float area = area_figure(*(figures + i));
        if (*(figures + i) == NULL){
            return 1;
        }
        if (area < 0) {
            return 1;
        }
    }

    qsort(figures, size, sizeof(struct figure_t *), compare_figures);
    return 0;
}

int main() {
    struct figure_t *figure[50];
    struct figure_t pFigure[50];
    struct figure_t structfigure;
    int burger, przypadek, s = 0;
    while (s < 50) {
        printf("Enter figure's type:");
        burger = scanf("%d", &przypadek);
        if (burger != 1) {
            printf("Incorrect input");
            return 1;
        }

        switch (przypadek) {
            case 1:
                structfigure.type = 1;
                printf("Enter triangle points (x1 y1 x2 y2 x3 y3):");
                burger = scanf("%d %d %d %d %d %d", &structfigure.triangle.p1.x, &structfigure.triangle.p1.y, &structfigure.triangle.p2.x, &structfigure.triangle.p2.y, &structfigure.triangle.p3.x, &structfigure.triangle.p3.y);
                if (burger != 6) {
                    printf("Incorrect input");
                    return 1;
                }
                while (getchar() != '\n');
                break;

            case 2:
                structfigure.type = 2;
                printf("Enter rectangle top-left corner, width, and height (x y width height):");
                burger = scanf("%d %d %d %d", &structfigure.rectangle.p.x, &structfigure.rectangle.p.y, &structfigure.rectangle.width, &structfigure.rectangle.height);
                if (burger != 4) {
                    printf("Incorrect input");
                    return 1;
                }
                while (getchar() != '\n');
                break;

            case 3:
                structfigure.type = 3;
                printf("Enter circle center and radius (x y radius):");
                burger = scanf("%d %d %figure", &structfigure.circ.c.x, &structfigure.circ.c.y, &structfigure.circ.r);
                if (burger != 3) {
                    printf("Incorrect input");
                    return 1;
                }
                while (getchar() != '\n');
                break;

            case 0:
                goto end_loop;

            default:
                printf("Incorrect input data");
                return 2;
        }

        *(pFigure + s) = structfigure;
        *(figure + s) = pFigure + s;
        s++;
    }

    end_loop:
    burger = sort_by_area(figure, s);
    if (burger == 1) {
        printf("Incorrect input data");
        return 2;
    }

    for (int i = 0; i < s; i++) {
        display_figure(*(figure + i));
        printf("\n");
    }

    return 0;
}

