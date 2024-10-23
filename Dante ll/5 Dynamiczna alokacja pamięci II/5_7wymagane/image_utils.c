#include "image_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tested_declarations.h"
#include "rdebug.h"

int check_ferror_or_feof(FILE *fp) {
    if (ferror(fp) != 0 || feof(fp) != 0) {
        return 1;
    }
    return 0;
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int **create_array_2d(int width, int height) {
    if (width <= 0 || height <= 0) {
        return NULL;
    }
    int **tablica = (int **)malloc(height * sizeof(int *));
    if (tablica == NULL) {
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        *(tablica + i) = (int *)malloc(width * sizeof(int));
        if (*(tablica + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(tablica + j));
            }
            free(tablica);
            return NULL;
        }
    }
    return tablica;
}

void destroy_array_2d(int **ptr, int height) {
    if (ptr != NULL && height > 0) {
        for (int i = 0; i < height; i++) {
            free(*(ptr + i));
        }
        free(ptr);
    }
}


struct image_t* load_image_t(const char *filename, int *err_code) {
    if (err_code != NULL) *err_code = 0;
    if (filename == NULL) {
        if (err_code != NULL) *err_code = 1;
        return NULL;
    }
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        if (err_code != NULL) *err_code = 2;
        return NULL;
    }
    struct image_t *image = calloc(1, sizeof(struct image_t));
    if (image == NULL) {
        if (err_code != NULL) *err_code = 4;
        fclose(file);
        return NULL;
    }
    fscanf(file, "%2s", image->type);
    if (check_ferror_or_feof(file)) {
        if (err_code != NULL) *err_code = 3;
        fclose(file);
        free(image);
        return NULL;
    }
    if (strcmp("P2", image->type) != 0) {
        if (err_code != NULL) *err_code = 3;
        fclose(file);
        free(image);
        return NULL;
    }
    int c = fgetc(file);
    if (c != '\n') {
        if (err_code != NULL) *err_code = 3;
        fclose(file);
        free(image);
        return NULL;
    } else {
        ungetc(c, file);
    }
    int array;
    fscanf(file, "%d %d\n%d", &image->width, &image->height, &array);
    if (check_ferror_or_feof(file)) {
        if (err_code != NULL) *err_code = 3;
        fclose(file);
        free(image);
        return NULL;
    }
    if (image->height <= 0 || image->width <= 0) {
        if (err_code != NULL) *err_code = 3;
        fclose(file);
        free(image);
        return NULL;
    }
    image->ptr = create_array_2d(image->width, image->height);
    if (image->ptr == NULL) {
        if (err_code != NULL) *err_code = 4;
        fclose(file);
        free(image);
        return NULL;
    }
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            fscanf(file, "%d", &array);
            if (check_ferror_or_feof(file) || array < 0) {
                if (err_code != NULL) *err_code = 3;
                fclose(file);
                destroy_array_2d(image->ptr, image->height);
                free(image);
                return NULL;
            }
            *(*(image->ptr + i) + j) = array;
        }
    }
    fclose(file);
    return image;
}


int save_image_t(const char * filename, const struct image_t *m1) {
    if (filename == NULL || m1 == NULL || m1->ptr == NULL || m1->height <= 0 || m1->width <= 0) {
        return 1;
    }

    FILE* fout = fopen(filename, "w");
    if (fout == NULL) {
        return 2;
    }

    fprintf(fout, "P2\n%d %d\n255\n", m1->width, m1->height);
    for (int i = 0; i < m1->height; i++) {
        for (int j = 0; j < m1->width; j++)
            fprintf(fout, "%d ", *(*(m1->ptr + i) + j));
        fprintf(fout, "\n");
        int a = ferror(fout);
        if (a != 0) {
            fclose(fout);
            return 3;
        }
    }
    fclose(fout);
    return 0;
}

void destroy_image(struct image_t **m) {
    if (m != NULL) {
        struct image_t *m1 = *m;
        if ((m1)->ptr != NULL) {
            for (int i = 0; i < (m1->height); i++) {
                if ((m1->ptr + i) != NULL)
                    free(*((*m)->ptr + i));
            }
            free(m1->ptr);
            free(*m);
            *m = NULL;
            m = NULL;
        }
    }
}

const int *image_get_pixel(const struct image_t *img, int x, int y) {
    if (img == NULL || img->height <= 0 || img->width <= 0 || img->ptr == NULL || strcmp(img->type, "P2") != 0 ||
        x < 0 || y < 0 || x >= img->width || y >= img->height) {
        return NULL;
    }
    return (*(img->ptr + y) + x);
}

int *image_set_pixel(struct image_t *img, int x, int y) {
    if (img == NULL || img->height <= 0 || img->width <= 0 || img->ptr == NULL || strcmp(img->type, "P2") != 0 ||
        x < 0 || y < 0 || x >= img->width || y >= img->height) {
        return NULL;
    }
    *(*(img->ptr + y) + x) = 0;
    return (*(img->ptr + y) + x);
}

int draw_image(struct image_t *img, const struct image_t *src, int destx, int desty) {
    if (img == NULL || src == NULL) {
        return 1;
    }

    if (img->ptr == NULL || src->ptr == NULL) {
        return 1;
    }

    if (img->width <= 0 || img->height <= 0 || src->width <= 0 || src->height <= 0) {
        return 1;
    }

    if (destx < 0 || desty < 0 || destx + src->width > img->width || desty + src->height > img->height) {
        return 1;
    }

    for (int y = 0; y < src->height; y++) {
        for (int x = 0; x < src->width; x++) {
            int pixel = *(*(src->ptr + y) + x);

            *(*(img->ptr + (desty + y)) + (destx + x)) = pixel;
        }
    }

    return 0;
}


int main() {
    char *filename = calloc(40, sizeof(char));
    if (!filename) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Enter destination image file name:");
    scanf("%30s", filename);
    int err;
    struct image_t *image = load_image_t(filename, &err);
    if (err) {
        switch (err) {
            case 2:
                printf("Couldn't open file\n");
                free(filename);
                return 4;
            case 3:
                printf("File corrupted\n");
                free(filename);
                return 6;
            case 4:
                printf("Failed to allocate memory\n");
                free(filename);
                return 8;
        }
        free(filename);
        return err + 2;
    }

    clear_input_buffer();

    int count;
    printf("How many subimages you want to draw:");
    if (scanf("%d", &count) != 1) {
        printf("Incorrect input\n");
        free(filename);
        destroy_image(&image);
        return 1;
    } else if (count <= 0){
        printf("Incorrect input data\n");
        free(filename);
        destroy_image(&image);
        return 2;
    }

    for (int i = 0; i < count; ++i) {
        char *name = calloc(40, sizeof(char));
        if (!name) {
            printf("Failed to allocate memory\n");
            free(filename);
            destroy_image(&image);
            return 8;
        }

        printf("Enter a name of a subimage:");
        scanf("%39s", name);
        struct image_t *src = load_image_t(name, &err);
        free(name);

        if (err) {
            if (err == 4) {
                printf("Failed to allocate memory\n");
                free(filename);
                destroy_image(&image);
                return 8;
            }
            printf(err == 3 ? "File corrupted\n" : "Couldn't open file\n");
            continue;
        }

        int destx, desty;
        printf("Enter coordinates (x, y):");
        if (scanf("%d %d", &destx, &desty) != 2) {
            printf("Incorrect input\n");
            free(filename);
            destroy_image(&image);
            destroy_image(&src);
            return 1;
        }

        if (draw_image(image, src, destx, desty) != 0) {
            printf("Incorrect input data\n");
        }
        destroy_image(&src);
    }

    char *output_name = malloc(strlen(filename) + strlen("_modified") + 1);
    if (!output_name) {
        printf("Failed to allocate memory\n");
        free(filename);
        destroy_image(&image);
        return 8;
    }

    int file_last_dot = strrchr(filename, '.') - filename;
    if (file_last_dot < 0) {
        sprintf(output_name, "%s_modified", filename);
    } else {
        strncpy(output_name, filename, file_last_dot);
        sprintf(output_name + file_last_dot, "_modified.%s", filename + file_last_dot + 1);
    }

    if (save_image_t(output_name, image) != 0) {
        printf("Couldn't create file\n");
        free(output_name);
        free(filename);
        destroy_image(&image);
        return 5;
    }

    printf("File saved\n");
    free(output_name);
    free(filename);
    destroy_image(&image);
    return 0;
}
