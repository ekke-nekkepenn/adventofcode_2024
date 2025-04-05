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
    return 0;
}

int64_t part1(FILE *file)
{
    int64_t result = 0;

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