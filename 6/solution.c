<<<<<<< HEAD
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
=======
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    char *start;
    int64_t length;
} String;

// IMPORTANT. Instead of taking input.txt and putting into an actual Char array[][]
// I am treating the whole string from input.txt as a 2D array.
// Pos at string gets turned into x and y coordinates
typedef struct
{
    String content;
    int16_t size_x;
    int16_t size_y;
} Char2DArray;

// Char2DArray.methods
void get_coordinates(Char2DArray *s, int16_t *x, int16_t *y, int64_t pos);
int16_t get_x(int64_t pos, int16_t size_x);
int16_t get_y(int64_t pos, int16_t size_x);
//
int64_t find_size(int16_t *size_x, int16_t *size_y, FILE *file);

//
int64_t part1(FILE *file);
int64_t part2(FILE *file);

int main(int argc, char **argv)
{
    char *filename;
    char part;

    if (argc == 2)
    {
        filename = argv[1];
        printf("%s\n", filename);
        part = '1';
    }
    else if (argc == 3)
    {
        filename = argv[1];
        printf("%s\n", filename);
        part = argv[2][0];
    }
    else
    {
        return 25;
    }

    int64_t result = 0;
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("File could not be opened!\n");
        return 100;
    }

    if (part == '1')
    {
        result = part1(file);
    }
    else if (part == '2')
    {
        result = part1(file);
    }
    else
    {
        fclose(file);
        return 50;
    }
    fclose(file);
    printf("Result of Part %c: %ld", part, result);
>>>>>>> refs/remotes/origin/main
    return 0;
}

int64_t part1(FILE *file)
{
    int64_t result = 0;

<<<<<<< HEAD
    CharTable room = (CharTable){NULL, 0, 0};
    // determine size of CharTable
    measure_size(&room.width, &room.height, file);
    // printf("room width: %d, height: %d\n", room.width, room.height);
    room.start = malloc(sizeof(char *) * room.height);

    // read file data into CharTable
    char *line;
    for (int i = 0; i < room.height; ++i)
    {
        line = malloc(sizeof(char) * room.width);
        fread(line, sizeof(char), room.width, file);
        room.start[i] = line;

        // printf("%d\t%s", i, line);
    }

    IntPair pos; // position of guard
    pos.x = -10;
    pos.y = -10;
    for (int16_t i = 0; i < room.height; ++i)
    {
        for (int16_t j = 0; j < room.width - 1; ++j)
        {
            if (room.start[i][j] == '^')
            {
                pos.x = j;
                pos.y = i;
            }
        }
    }
    IntPair dir = (IntPair){.x = 0, .y = -1}; // guard is facing this way
    // store visited positions
    bool visited[room.height][room.width - 1];
    memset(visited, 0, room.height * (room.width - 1));

    visited[pos.y][pos.x] = true;
    // guard starts patrolling
    int16_t nx, ny;
    while (true)
    {
        nx = pos.x + dir.x;
        ny = pos.y + dir.y;
        // first check if new position is in bounds
        if (nx < 0 || ny < 0 || nx >= room.width || ny >= room.height)
        {
            break;
        }
        // check if new position is occupied by stuff
        if (room.start[ny][nx] != '.')
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
        for (int j = 0; j < room.width; ++j)
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
    int f = 1;
    while (fread(&c, sizeof(char), 1, file))
    {
        if (f)
            ++*w;

        if (c == '\n')
        {
            ++*h;
            f = 0;
        }
    }
    rewind(file);
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
        dir->y = 1;
    }
}
=======
    // first load the data into appropriate data struct
    int16_t size_x = 0;
    int16_t size_y = 0;
    int64_t size_file = find_size(&size_x, &size_y, file);

    String text = (String){malloc(size_file), size_file};
    Char2DArray a = (Char2DArray){text, size_x, size_y};

    // read file into String
    fread(text.start, sizeof(char), size_file, file);

    // find the current position of the guard
    int64_t pos = 0;
    while (text.start[pos] != '^')
    {
        pos++;
    }

    // get x and y of guard
    int16_t pos_x;
    int16_t pos_y;
    get_coordinates(&a, &pos_x, &pos_y, pos);

    // initial direction guard is facing
    int16_t dir_x = 0;
    int16_t dir_y = -1;

    // apply the guard patrol rules
    // remember which positions have been visited
    free(text.start);
    return result;
}

int64_t part2(FILE *file) { return 0; }

int64_t find_size(int16_t *size_x, int16_t *size_y, FILE *file)
{
    char c;
    int64_t i = 0;
    while (fread(&c, sizeof(char), 1, file))
    {
        if (c == '\n')
        {
            if (!(*size_x))
            {
                *size_x = (int16_t)i + 1; // include '\n'
            }
            ++(*size_y);
        }
        ++i;
    }
    // reset file position
    fseek(file, 0, SEEK_SET);

    return i;
}

void get_coordinates(Char2DArray *s, int16_t *pos_x, int16_t *pos_y, int64_t pos)
{
    *pos_x = get_x(pos, s->size_x);
    *pos_y = get_y(pos, s->size_x);
}

int16_t get_x(int64_t pos, int16_t size_x)
{
    return (int16_t)(pos % size_x);
}

int16_t get_y(int64_t pos, int16_t size_x)
{
    if (pos)
    {
        return (int16_t)(pos / size_x);
    }
    return 0;
}
>>>>>>> refs/remotes/origin/main
