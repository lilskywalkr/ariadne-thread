#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_maze(const char *filename, char ***labirynth);
int solve_maze(char **maze, int x, int y);
void free_maze(char **maze);
void maze_size(char **maze, int *w, int *h);
int path_finding(char **maze, int x, int y, int width, int height);

int main() {
    char *filename = calloc(31, sizeof(char));
    char **maze;
    int n = 0, x = 0, y = 0, end_coords_x = 0, end_coords_y = 0, width = 0, height = 0;

    if (filename == NULL) {
        printf("Failed to allocate memory ");
        return 8;
    }

    printf("Enter filename:");
    scanf("%30[^\n]", filename);

    while (getchar() != '\n');

    n = load_maze(filename, &maze);

    if (n == 2) {
        printf("Couldn't open file");
        free(filename);
        return 4;
    } else if (n == 3) {
        printf("File corrupted");
        free(filename);
        return 6;
    } else if (n == 4) {
        printf("Failed to allocate memory");
        free(filename);
        return 8;
    }

    maze_size(maze, &width, &height);
    for (int i = 0, flg = 1; i < height && flg; i++) {
        for (int j = 0; j < width && flg; j++) {
            if (*(*(maze + i) + j) == 'a') {
                x = j;
                y = i;
                flg = 0;
            }
        }
    }

    for (int i = 0, flg = 1; i < height && flg; i++) {
        for (int j = 0; j < width && flg; j++) {
            if (*(*(maze + i) + j) == 'b') {
                end_coords_x = j;
                end_coords_y = i;
                flg = 0;
            }
        }
    }

    if (!end_coords_x && !end_coords_y) {
        printf("File corrupted");
        free_maze(maze);
        free(filename);
        return 6;
    }

    n = solve_maze(maze, x, y);

    if (n == 0) {
        printf("Couldn't find path\n");
    } else {
        for (int i = 0; i < height; ++i) {
            printf("%s\n", *(maze + i));
        }
    }

    free(filename);
    free_maze(maze);
    return 0;
}

int load_maze(const char *filename, char ***labirynth) {
    if (filename == NULL || labirynth == NULL) {
        return 1;
    }

    int row_length = 0, column_length = 0, first_row_length = 0, start_count = 0, end_count = 0, flag = 0;
    char ch = 0;

    FILE  *f_p = fopen(filename, "r");
    if (f_p == NULL) {
        return 2;
    }

    /*File inspection*/
    while ((ch = (char) fgetc(f_p)) != EOF) {
        if (ch != '\n') {
            first_row_length += (flag ? 0 : 1);
            row_length++;

            if (ch == 'a') start_count++;
            else if (ch == 'b') end_count++;
        } else {
            if (!flag) {
                fseek(f_p, 0, SEEK_SET);
                flag = 1;
            }

            if (row_length != first_row_length || start_count > 1 || end_count > 1) {
                fclose(f_p);
                return 3;
            }

            row_length = 0;
            column_length++;
        }
    }

    if ((row_length == first_row_length && !row_length && !first_row_length)) {
        fclose(f_p);
        return 3;
    }

    /*Maze memory allocation*/
    (*labirynth) = calloc(column_length + 1, sizeof (char *));
    if ((*labirynth) == NULL) {
        fclose(f_p);
        return 4;
    }

    for (int i = 0; i < column_length; i++) {
        *((*labirynth) + i) = calloc(first_row_length + 1, sizeof(char));

        if (*((*labirynth) + i) == NULL) {
            for (int j = 0; j < i; j++) {
                free(*(*labirynth + j));
            }

            free(*labirynth);
            fclose(f_p);
            return 4;
        }
    }

    *((*labirynth) + column_length) = NULL;

    /*Maze loading*/
    fseek(f_p, 0, SEEK_SET);
    for (int i = 0, j = 0; i < column_length && !feof(f_p); ++i) {
        while ((ch = (char) fgetc(f_p)) != '\n' && ch != EOF) {
            *(*((*labirynth) + i ) + j) = ch;
            j++;
        }
        *(*((*labirynth) + i ) + j) = '\0';
        j = 0;
    }

    fclose(f_p);
    return 0;
}

int path_finding(char **maze, int x, int y, int width, int height) {
    switch (*(*(maze + y) + x)) {
        case '*':
        case '#':
            return 0;
        case 'b':
            return 1;
        default:
            break;
    }

    if (*(*(maze + y) + x) != 'a') {
        *(*(maze + y) + x) = '*';
    }


    // Exploring the surroundings
    int right = path_finding(maze, x + 1, y, width, height);
    int down = path_finding(maze, x, y + 1, width, height);
    int left= path_finding(maze, x - 1, y, width, height);
    int up = path_finding(maze, x, y - 1, width, height);

    if (right == 1 || left == 1 || up == 1 || down == 1) {
        return 1;
    } else if (right == -2 || left == -2 || up == -2 || down == -2) {
        return -1;
    }

    if (*(*(maze + y) + x) == ' ' || *(*(maze + y) + x) == '*') {
        *(*(maze + y) + x) = ' ';
    }

    return 0;
}

void maze_size(char **maze, int *w, int *h) {
    if (maze != NULL && w != NULL && h != NULL) {
        int width = (int) strlen(*(maze + 0)), height = 0;

        for (int i = 0; *(maze + i) != NULL; i++) {
            height++;
        }

        *w = width, *h = height;
    }
}

int solve_maze(char **maze, int x, int y) {
    int width = 0, height = 0;
    maze_size(maze, &width, &height);

    if (maze == NULL || x <= 0 || x >= width || y <= 0 || y >= height) {
        return -1;
    }

    return path_finding(maze, x, y, width, height);
}

void free_maze(char **maze) {
    if (maze != NULL) {
        for (int i = 0; *(maze + i) != NULL; i++) {
            free(*(maze + i));
        }

        free(maze);
    }
}
