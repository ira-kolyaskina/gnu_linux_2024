#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 6
#define HEIGHT 6
#define MAZE_WIDTH (WIDTH * 2 + 1)
#define MAZE_HEIGHT (HEIGHT * 2 + 1)

#define WALL '#'
#define PATH '.'

typedef struct {
    char grid[MAZE_HEIGHT][MAZE_WIDTH];
} Maze;

void initMaze(Maze *maze) {
    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            if (i % 2 == 0 || j % 2 == 0) {
                maze->grid[i][j] = WALL;
            } else {
                maze->grid[i][j] = PATH;
            }
        }
    }
}


void dfs(int x, int y, int** visited, Maze *maze) {
    visited[x][y] = 1;

    int directions[4][2] = {
        {0, -1}, // вверх
        {0, 1},  // вниз
        {-1, 0}, // влево
        {1, 0}   // вправо
    };

    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        int temp[2] = {directions[i][0], directions[i][1]};
        directions[i][0] = directions[j][0];
        directions[i][1] = directions[j][1];
        directions[j][0] = temp[0];
        directions[j][1] = temp[1];
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];

        if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT && !visited[nx][ny]) {
            int wx = 1 + x * 2 + directions[i][0];
            int wy = 1 + y * 2 + directions[i][1];
            maze->grid[wy][wx] = PATH;

            dfs(nx, ny, visited, maze);
        }
    }
}


void generateMaze(Maze *maze) {
    int** visited = malloc(WIDTH * sizeof(int*));
    for (int i = 0; i < WIDTH; ++i) {
        visited[i] = malloc(HEIGHT * sizeof(int));
        for (int j = 0; j < HEIGHT; ++j) {
            visited[i][j] = 0;
        }
    }

    dfs(rand() % WIDTH, rand() % HEIGHT, visited, maze);

    for (int i = 0; i < HEIGHT; ++i) {
        free(visited[i]);
    }
    free(visited);
}

void printMaze(Maze *maze) {
    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            printf("%c", maze->grid[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Maze maze;
    initMaze(&maze);
    generateMaze(&maze);

    printMaze(&maze);

    return 0;
}
