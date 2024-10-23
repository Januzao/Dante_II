#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include "tested_declarations.h"
#include "rdebug.h"



int create_board(struct board_t **board, int width, int height) {
    if (!board || width <= 0 || height <= 0) {
        return 1;
    }

    *board = (struct board_t *) malloc(sizeof(struct board_t));
    if (*board == NULL) {
        return 2;
    }

    (*board)->width = width;
    (*board)->height = height;
    (*board)->is_init = 0;
    (*board)->move_player_up = move_player_up;
    (*board)->move_player_down = move_player_down;
    (*board)->move_player_left = move_player_left;
    (*board)->move_player_right = move_player_right;

    (*board)->board = (char **) malloc(height * sizeof(char *));
    if ((*board)->board == NULL) {
        free(*board);
        return 2;
    }

    for (int i = 0; i < height; ++i) {
        *((*board)->board + i) = (char *) malloc((width + 1) * sizeof(char));
        if (*((*board)->board + i) == NULL) {
            for (int j = 0; j < i; ++j) {
                free(*((*board)->board + j));
            }
            free((*board)->board);
            free(*board);
            return 2;
        }
        char *row = *((*board)->board + i);
        for (int j = 0; j < width; ++j) {
            *(row + j) = '.';
        }
        *(row + width) = '\0';
    }

    return 0;
}

void display_board(const struct board_t *board) {
    if (board == NULL) {
        return;
    }
    for (int i = 0; i < board->height; ++i) {
        printf("%s\n", *(board->board + i));
    }
}

void free_board(struct board_t *board) {
    if (board == NULL) {
        return;
    }
    for (int i = 0; i < board->height; ++i) {
        free(*(board->board + i));
    }
    free(board->board);
    free(board);
}

int set_player(struct board_t *board, int x, int y) {
    if (!board || !board->board || board->width <= 0 || board->height <= 0 || board->is_init == 1 ||
        x < 0 || y < 0 || x >= board->width || y >= board->height)
        return 1;

    board->player.x = x;
    board->player.y = y;
    *(*(board->board + y) + x) = '@';
    board->is_init = 1;
    return 0;
}

struct board_t *move_player_up(struct board_t *board) {
    if (!board|| !board->board || board->player.x < 0 || board->player.y < 0 ||
        board->player.x >= board->width || board->player.y >= board->height || board->is_init != 1 ||
        board->width <= 0 || board->height <= 0)
        return NULL;
    int new_y = (board->player.y - 1 + board->height) % board->height;
    *(*(board->board + board->player.y) + board->player.x) = '.';
    board->player.y = new_y;
    *(*(board->board + board->player.y) + board->player.x) = '@';
    return board;
}

struct board_t *move_player_down(struct board_t *board) {
    if (!board|| !board->board || board->player.x < 0 || board->player.y < 0 ||
        board->player.x >= board->width || board->player.y >= board->height || board->is_init != 1 ||
        board->width <= 0 || board->height <= 0)
        return NULL;
    int new_y = (board->player.y + 1) % board->height;
    *(*(board->board + board->player.y) + board->player.x) = '.';
    board->player.y = new_y;
    *(*(board->board + board->player.y) + board->player.x) = '@';
    return board;
}

struct board_t *move_player_left(struct board_t *board) {
    if (!board|| !board->board || board->player.x < 0 || board->player.y < 0 ||
        board->player.x >= board->width || board->player.y >= board->height || board->is_init != 1 ||
        board->width <= 0 || board->height <= 0)
        return NULL;
    int new_x = (board->player.x - 1 + board->width) % board->width;
    *(*(board->board + board->player.y) + board->player.x) = '.';
    board->player.x = new_x;
    *(*(board->board + board->player.y) + board->player.x) = '@';
    return board;
}

struct board_t *move_player_right(struct board_t *board) {
    if (!board|| !board->board || board->player.x < 0 || board->player.y < 0 ||
        board->player.x >= board->width || board->player.y >= board->height || board->is_init != 1 ||
        board->width <= 0 || board->height <= 0)
        return NULL;
    int new_x = (board->player.x + 1) % board->width;
    *(*(board->board + board->player.y) + board->player.x) = '.';
    board->player.x = new_x;
    *(*(board->board + board->player.y) + board->player.x) = '@';
    return board;
}

int main(void) {
    struct board_t *board = NULL;
    int width, height, x, y;

    printf("Enter width and height of the board: ");
    if (scanf("%d %d", &width, &height) != 2) {
        printf("Incorrect input\n");
        return 1;
    }
    if (width <= 0 || height <= 0) {
        printf("Incorrect input data\n");
        return 2;
    }

    if (create_board(&board, width, height) != 0) {
        printf("Failed to allocate memory\n");
        return 8;
    }

    printf("Enter player's initial coordinates (x, y): ");
    if (scanf("%d %d", &x, &y) != 2) {
        printf("Incorrect input\n");
        free_board(board);
        return 1;
    }
    if (set_player(board, x, y) != 0) {
        printf("Incorrect input data\n");
        free_board(board);
        return 2;
    }

    display_board(board);

    char action;
    while (1) {
        printf("Choose your action: ");
        if (scanf(" %c", &action) != 1) {
            printf("Incorrect input\n");
            break;
        }
        if (action == 'q') {
            break;
        }
        switch (action) {
            case 'w':
                board->move_player_up(board);
                break;
            case 's':
                board->move_player_down(board);
                break;
            case 'a':
                board->move_player_left(board);
                break;
            case 'd':
                board->move_player_right(board);
                break;
            default:
                printf("Incorrect choice\n");
                continue;
        }
        display_board(board);
    }

    free_board(board);
    return 0;
}


