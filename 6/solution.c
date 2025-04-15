#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"
typedef struct
{
    int16_t x;
    int16_t y;
} IntPair;

typedef struct
{
    char **start;
    int16_t width;
    int16_t height;
} CharTable;

int64_t part1(FILE *file);
int64_t part2(FILE *file);

void measure_size(int16_t *w, int16_t *h, FILE *file);
void free_table(CharTable *t);
void rotate_clockwise(IntPair *dir);
void get_guard_pos(int16_t *x, int16_t *y, CharTable *room);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        return 1;
    }

    int64_t result = 0;

    FILE *file = fopen(FILENAME, "r");
    if (!file)
    {
        printf("fopen error. FILENAME=%s\n", FILENAME);
        return 20;
    }

    if (argv[1][0] == '1')
    {
        result = part1(file);
    }

    else if (argv[1][0] == '2')
    {
        result = part2(file);
    }

    else
    {
        printf("arg[1] not matching\n");
    }

    printf("Result of Part %c: %ld\n", argv[1][0], result);
    fclose(file);
    return 0;
}

int64_t part1(FILE *file)
{
    int64_t result = 0;

    CharTable room = (CharTable){NULL, 0, 0};
    measure_size(&room.width, &room.height, file);

    // read file data into CharTable
    room.start = malloc(sizeof(char *) * room.height);
    for (int i = 0; i < room.height; ++i)
    {
        char *line = malloc(sizeof(char) * room.width);
        fgets(line, room.width + 1, file);
        room.start[i] = line;
    }

    // guard stats
    IntPair dir = (IntPair){.x = 0, .y = -1}; // guard is facing north
    IntPair pos = (IntPair){.x = 0, .y = 0};
    get_guard_pos(&pos.x, &pos.y, &room);

    // positions to mark when visited
    bool visited[room.height][room.width - 1];
    memset(visited, 0, (room.height * (room.width - 1)));
    visited[pos.y][pos.x] = true;

    // guard starts patrolling
    int16_t nx, ny;
    while (true)
    {
        nx = pos.x + dir.x;
        ny = pos.y + dir.y;
        // first check if new position is in bounds
        if (nx < 0 || ny < 0 || nx >= room.width - 1 || ny >= room.height)
        {
            break;
        }
        // check if new position is occupied by stuff
        if (room.start[ny][nx] == '#')
        {
            rotate_clockwise(&dir);
        }
        // not occupied -> guard moves one step
        else
        {
            pos.x = nx;
            pos.y = ny;
            visited[ny][nx] = true;
        }
    }

    // count the visited positions
    for (int i = 0; i < room.height; ++i)
    {
        for (int j = 0; j < room.width - 1; ++j)
        {
            if (visited[i][j])
            {
                result = result + 1;
            }
        }
    }

    free_table(&room);
    return result;
}

int64_t part2(FILE *file)
{

    return 0;
}

void measure_size(int16_t *w, int16_t *h, FILE *file)
{
    char c;
    int f = -1;
    while (fread(&c, sizeof(char), 1, file))
    {
        if (f != 0)
            ++*w;

        if (c == '\n')
        {
            ++*h;
            f = 0;
        }
    }
    rewind(file);
}

void get_guard_pos(int16_t *x, int16_t *y, CharTable *room)
{

    for (; *y < room->height; ++(*y))
    {
        for (; *x < room->width - 1; ++(*x))
        {
            if (room->start[*y][*x] == '^')
            {
                return;
            }
        }
        *x = 0;
    }
    printf("\nPosition of guard not found!\n");
    return;
}

void free_table(CharTable *t)
{
    for (int i = 0; i < t->height; ++i)
    {
        free(t->start[i]);
        t->start[i] = NULL;
    }
    free(t->start);
    t->start = NULL;
}

void rotate_clockwise(IntPair *dir)
{
    // !TODO find a math function that does this
    if (dir->y == -1)
    {
        dir->x = 1;
        dir->y = 0;
    }
    else if (dir->x == 1)
    {
        dir->x = 0;
        dir->y = 1;
    }
    else if (dir->y == 1)
    {
        dir->x = -1;
        dir->y = 0;
    }
    else if (dir->x == -1)
    {
        dir->x = 0;
        dir->y = -1;
    }
}
