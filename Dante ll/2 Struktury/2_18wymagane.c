#include <stdio.h>
#include <string.h>
#include "tested_declarations.h"
#include "rdebug.h"
#include <sys/stat.h>

#define MAX_FILENAME_LENGTH 31
#define MAX_TEXT_LENGTH 1000
#define MAX_FILES 5

struct file_t
{
    FILE *f;
    int size;
};

int open_file(struct file_t* f, const char *filename){
    if (f == NULL || filename == NULL) {
        return 1;
    }
    f->f = fopen(filename, "a");
    if (f->f == NULL) {
        f->f = fopen(filename, "w");
        if (f->f == NULL){
            return 2;
        }
        f->size = 0;
        return 0;
    }

    struct stat st;
    if (stat(filename, &st) != 0){
        fclose(f->f);
        return 2;
    }
    f->size = st.st_size;
    return 0;
}

struct file_t* find_min(const struct file_t* files, int size){
    if (files == NULL || size <= 0){
        return NULL;
    }
    const struct file_t* min_file = NULL;
    long min_size = -1;

    for (const struct file_t* current_file = files; current_file < files + size; ++current_file) {
        if (current_file->size >= 0 && (min_file == NULL || current_file->size < min_size)) {
            min_file = current_file;
            min_size = current_file->size;
        }
    }
    return (struct file_t*)min_file;
}

void close_file(struct file_t* f){
    if (f != NULL && f->f != NULL){
        fclose(f->f);
        f->f = NULL;
    }
}

int file_size_from_file(FILE *f) {
    if (f == NULL) { return -2; }
    int start_pos = (int)ftell(f);
    fseek(f, 0, SEEK_END);
    int len = (int)ftell(f);
    fseek(f, start_pos, SEEK_SET);
    return len;
}
//int main(){
//    struct file_t files[MAX_FILES];
//    int num_files = 0;
//    int empty_lines_count = 0;
//
//    printf("Podaj nazwy plikow:");
//    char filename[MAX_FILENAME_LENGTH];
//
//
//    while (num_files < MAX_FILES) {
//        int Temp = scanf("%[^\n]", filename);
//        clearBuffer();
//        if (Temp == 1){
//            int result = open_file((files+num_files), filename);
//            if (result != 0){
//                printf("Couldn't open file\n");
//                for (int i = 0; i < num_files; ++i) {
//                    close_file(files + i);
//                }
//                return 4;
//            }
//            num_files++;
//        } else {
//            break;
//        }
//    }
//
//    for (int num = 0; num < ; ++num) {
//
//    }
//
//    if (num_files == 0){
//        printf("Couldn't open file\n");
//        return 4;
//    }
//
//    printf("Podaj teksty:\n");
//    char text[MAX_TEXT_LENGTH];
//
//    while (1) {
//        if (scanf("%[^\n]", text) == 1) {
//            empty_lines_count = 0;
//            char* token = strtok(text, "\n");
//            while (token != NULL) {
//                struct file_t* min_file = find_min(files, num_files);
//                if (min_file != NULL) {
//                    fprintf(min_file->f, "%s\n", token);
//                    fflush(min_file->f);
//                    min_file->size += strlen(token) + 1;
//                } else {
//                    printf("Couldn't open file\n");
//                    return 4;
//                }
//                token = strtok(NULL, "\n");
//            }
//        } else {
//            empty_lines_count++;
//            if (empty_lines_count == 2) {
//                break;
//            }
//        }
//    }
//
//    printf("Files saved\n");
//    for (int i = 0; i < num_files; i++) {
//        close_file((files+i));
//    }
//
//    return 0;
//}
int main(){
    printf("Podaj nazwy plikow:");
    char filename[31];
    int files_opened = 0;
    struct file_t files[5];
    while (1) {
        char c; int count = 0;
        do {
            c = getchar();
            *(filename + count) = c;
            if (c == '\n') break;
            count++;
        } while (c != EOF);
        if (*filename == '\n') break;
        *(filename + count) = '\0';
        if (files_opened < 5) {
            int res = open_file((files + files_opened), filename);
            if (res == 0) files_opened++;
        }
    }
    int status = (files_opened == 0) ? 1 : 0;

    switch (status) {
        case 1:
            printf("Couldn't open file\n");
            return 4;
        default:
            break;
    }
    printf("Podaj teksty:");
    char txt[999];
    while (1) {
        char asd; int count = 0;

        do {
            asd = getchar();
            *(txt + count) = asd;
            if (asd == '\n') break;
            count++;
        } while (asd != EOF && count < 998);
        if (*txt == '\n') break;
        *(txt + (++count)) = '\0';

        struct file_t *findMin = find_min(files, files_opened);
        fprintf(findMin->f, "%s", txt);
        findMin->size = file_size_from_file(findMin->f);
    }

    for (int i = 0; i < files_opened; ++i) {
        close_file((files + i));
    }

    printf("Files saved");
    return 0;
}
