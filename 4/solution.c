#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10
#define WORD "XMAS"

#define LEFT -1
#define RIGHT 1

typedef struct
{
    char *ptr;
    int64_t length;
} String;

void part1(FILE *file);
void part2(FILE *file);

// star_search just bundles all the other searches
int star_search(char a[SIZE][SIZE], int len, int x, int y);
// directional searches
int search_row(char *row, int len, int x, int dir);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return 1;
    }

    char *fp = argv[2];

    FILE *file = fopen(fp, "r");
    if (file == NULL)
    {
        printf("File could not be opened\n");
        return 2;
    }

    if (*argv[1] == '1')
    {
        part1(file);
    }
    else if (*argv[1] == '2')
        part2(file);
}

void part1(FILE *file)
{
    // load file into a String and close it
    fseek(file, 0, SEEK_END);
    int64_t file_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char a[SIZE][SIZE];
    int x = 0;
    int y = 0;

    char c;
    while (fread(&c, sizeof(char), 1, file))
    {
        if (c == '\n')
        {
            x = 0;
            y++;
            continue;
        }
        // printf("x: %d, y: %d\n", x, y);
        a[y][x] = c;
        x++;
    }

    int word_len = strlen(WORD);

    // total matches of WORD
    int64_t total_matches = 0;
    for (y = 0; y < SIZE; y++)
    {
        for (x = 0; x < SIZE; x++)
        {
            // start search when first letter of WORD is found
            if (a[y][x] == WORD[0])
            {
                // word_len -1 because we already found first letter
                total_matches = total_matches + star_search(a, word_len, x, y);
            }
        }
    }

    printf("Total found matches of %s: %ld\n", WORD, total_matches);
}

void part2(FILE *file)
{
}

int star_search(char a[SIZE][SIZE], int len, int x, int y)
{
    int matches = 0;
    int i, nx, ny;

    // search to the right
    // 0 ... 6 7 8 9
    //       X M A S  x = 6 + len = 4 = 10
    if (x + len <= SIZE)
    {
        matches = matches + search_row(a[y], len, x, RIGHT);
    }

    // search to the left
    // 0 1 2 3 ... 9
    // S A M X  x = 3 - len = 4 = -1
    if (x - len + 1 >= 0)
    {
        matches = matches + search_row(a[y], len, x, LEFT);
    }

    // search down
    if (y + len <= SIZE)
    {
    }
    // Search upwards
    // Search downwards
    // Diagonal Search
    // Up Right
    // Up Left
    // Down Right
    // Down Left

    return matches;
}

int search_row(char *row, int len, int x, int dir)
{
    for (int i = 1; i < len; ++i)
    {
        if (row[x + (i * dir)] != WORD[i])
        {
            return 0;
        }
    }
    return 1;
}