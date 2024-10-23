#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"

#define Z 0

int cor(char **maze, int path, int path1) {
    if(*(*(maze + path1) + path) == ' ') {
        return 1;
    }
    return Z;
}

int pathhhhhh(char **maze, int path, int path1) {
    if(*(*(maze + path1) + path) == '*') {
        return 1;
    }
    return Z;
}

int ex(char **maze, int path, int path1) {
    if(*(*(maze + path1) + path) == 'b'){
        return 1;
    }
    return Z;
}

int ban(char **maze, int path, int path1) {
    if(*(*(maze + path1) + path) == 'c'){
        return 1;
    }
    return Z;
}

int maze_width = Z;
int maze_height = Z;

int load_maze(const char *filename, char ***labirynth) {
    if (!filename || !labirynth) return 1;
    FILE *chinazes = fopen(filename, "r");
    if (chinazes == NULL) return 2;

    int kolum = Z;
    char hashtag = '#';

    for (;;) {
        fscanf(chinazes, "%c", &hashtag);
        if (hashtag == '\n' || feof(chinazes))
            break;
        kolum++;
    }
    if (kolum <= 2) {
        fclose(chinazes);
        return 3;
    }

    fseek(chinazes, Z, SEEK_SET);

    int wiersz = Z;
    int k = Z;

    for (;;) {
        if (feof(chinazes)) {
            if (k - 1 != kolum) {
                fclose(chinazes);
                return 3;
            }
            wiersz++;
            break;
        }
        fscanf(chinazes, "%c", &hashtag);
        if (hashtag == '\n') {
            k = 0;
            wiersz++;
            continue;
        }
        k++;
    }
    if (wiersz <= 2) {
        fclose(chinazes);
        return 3;
    }

    maze_width = kolum;
    maze_height = wiersz;

    *labirynth = (char **)calloc(wiersz + 1, sizeof(char *));
    if (!*labirynth) {
        fclose(chinazes);
        return 4;
    }

    for (int i = 0; i < wiersz; i++) {
        *((*labirynth) + i) = (char *)calloc(kolum + 1, sizeof(char));
        if (!*((*labirynth) + i)) {
            for (int j = i - 1; j >= Z; j--) {
                free(*((*labirynth) + j));
            }
            free(*labirynth);
            fclose(chinazes);
            return 4;
        }
    }

    *((*labirynth) + wiersz) = NULL;
    fseek(chinazes, Z, SEEK_SET);
    int j;

    for (int i = Z; i < wiersz; i++) {
        j = Z;
        while (j < kolum + 1) {
            fscanf(chinazes, "%c", &hashtag);
            if (feof(chinazes) || hashtag == '\n') {
                *(*((*labirynth) + i) + j) = '\0';
                break;
            }
            *(*((*labirynth) + i) + j) = hashtag;
            j++;
        }
    }

    fclose(chinazes);
    return 0;
}

void free_maze(char **maze) {
    if (!maze) return;
    int i = Z;
    while (*(maze + i)) {
        free(*(maze + i));
        i++;
    }
    free(maze);
}

/*
 * int is_safe(char **maze, int x, int y, char **visited) {
    return *(*(maze + x) + y) == ' ' || *(*(maze + x) + y) == 'a' ||
           (*(*(maze + x) + y) == 'b' && !*(*(visited + x) + y));
}

int solve_maze_util(char **maze, char **visited, int x, int y) {
    if (*(*(maze + x) + y) == 'b') return 1;
    if (!is_safe(maze, x, y, visited)) return 0;

    *(*(visited + x) + y) = 1;

    char original = *(*(maze + x) + y);
    if (original != 'a') *(*(maze + x) + y) = '*';


    if ((*(*(maze + x + 1) + y) != '#' && solve_maze_util(maze, visited, x + 1, y)) ||
        (*(*(maze + x - 1) + y) != '#' && solve_maze_util(maze, visited, x - 1, y)) ||
        (*(*(maze + x) + y + 1) != '#' && solve_maze_util(maze, visited, x, y + 1)) ||
        (*(*(maze + x) + y - 1) != '#' && solve_maze_util(maze, visited, x, y - 1))) {
        return 1;
    }

    if (original != 'a') *(*(maze + x) + y) = original;
    return 0;
}
 */

int solve_maze(char **maze, int x, int y) {
    if(!maze || x < Z || y < Z) {
        return -1;
    }

    int wiersz = Z;
    for(int i = Z; *(*(maze) + i) != '\0'; i++) {
        wiersz = i;
    }
    wiersz++;

    int row = Z, col;

    for (; *(maze + row) != NULL; row++) {
        int temp_width = Z;
        for (int i = Z; *(*(maze + row) + i) != '\0'; i++) {
            temp_width = i + 1;
        }

        if (temp_width != wiersz) {
            return -1;
        }
    }
    if(x >= wiersz) {
        return -1;
    }
    int kolum = Z;

    for (char **row_ptr = maze; *row_ptr != NULL; row_ptr++) {
        kolum++;
    }


    if(y >= kolum) {
        return -1;
    }

    while(*(*(maze + y) + x) != 'b') {
        if (ex(maze, x + 1, y) || ex(maze, x - 1, y) || ex(maze, x, y + 1) ||
            ex(maze, x, y - 1)) {
            row = Z, col = Z;
            while(*(maze + row) != NULL) {
                if(*(*(maze + row) + col) == 'c') *(*(maze + row) + col) = ' ';
                col++;
                if(col == wiersz) {
                    col = Z;
                    row++;
                }
            }
            return 1;
        }
        else if (cor(maze, x, y - 1) && !ban(maze, x, y - 1)) {
            y--;
            *(*(maze + y) + x) = '*';
        }
        else if (cor(maze, x, y + 1) && !ban(maze, x, y + 1)) {
            y++;
            *(*(maze + y) + x) = '*';
        }
        else if (cor(maze, x + 1, y) && !ban(maze, x + 1, y)) {
            x++;
            *(*(maze + y) + x) = '*';
        }
        else if (cor(maze, x - 1, y) && !ban(maze, x - 1, y)) {
            x--;
            *(*(maze + y) + x) = '*';
        }
        else if (cor(maze, x, y - 1) && !ban(maze, x, y - 1)) {
            y--;
            *(*(maze + y) + x) = '*';
        }
        else if (cor(maze, x, y + 1) && !ban(maze, x, y + 1)) {
            y++;
            *(*(maze + y) + x) = '*';
        }
        else {
            *(*(maze + y) + x) = 'c';
            if (pathhhhhh(maze, x - 1, y)) {
                x--;
                continue;
            }
            else if (pathhhhhh(maze, x + 1, y)) {
                x++;
                continue;
            }
            else if (pathhhhhh(maze, x, y - 1)) {
                y--;
                continue;
            }
            else if (pathhhhhh(maze, x, y + 1)) {
                y++;
                continue;
            }
            else return 0;
        };
    }

    return 0;
}


int main() {
    char **maze;
    char *filename = malloc(31 * sizeof(char));
    if (filename == NULL) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Please input filename:");
    scanf("%30[^\n]", filename);
    while (getchar() != '\n') {}

    int res = load_maze(filename, &maze);
    free(filename);

    if (res == 4) {
        printf("Failed to allocate memory\n");
        return 8;
    } else if (res == 2) {
        printf("Couldn't open file\n");
        return 4;
    } else if (res == 3) {
        printf("File corrupted\n");
        return 6;
    }


    int x = -1, y = -1;
    int a_counter = Z, b_counter = Z;
    char **row_ptr = maze;
    char *cell_ptr;

    while (*row_ptr) {
        cell_ptr = *row_ptr;
        int col = Z;
        while (*cell_ptr) {
            if (*cell_ptr == 'a') {
                if (cell_ptr == *row_ptr || *(cell_ptr + 1) == '\0') {
                    printf("File corrupted\n");
                    free_maze(maze);
                    return 6;
                }
                x = col, y = row_ptr - maze;
                a_counter++;
            } else if (*cell_ptr == 'b') {
                if (cell_ptr == *row_ptr || *(cell_ptr + 1) == '\0') {
                    printf("File corrupted\n");
                    free_maze(maze);
                    return 6;
                }
                b_counter++;
            }
            cell_ptr++;
            col++;
        }
        row_ptr++;
    }

    if (x == -1 || y == -1 || a_counter != 1 || b_counter != 1) {
        printf("File corrupted\n");
        free_maze(maze);
        return 6;
    }

    res = solve_maze(maze, x, y);

    if (res == Z) {
        printf("Couldn't find path\n");
    } else if (res == 1) {
        row_ptr = maze;
        while (*row_ptr) {
            printf("%s\n", *row_ptr);
            row_ptr++;
        }
    }

    free_maze(maze);
    return 0;
}





