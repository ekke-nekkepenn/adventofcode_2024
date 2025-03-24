#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 140
#define WORD "XMAS"
#define WORD2 "MAS"

#define LEFT -1
#define RIGHT 1
#define UP -1
#define DOWN 1

void part1(FILE *file);
void part2(FILE *file);

// these all needed for part1
int star_search(char a[SIZE][SIZE], int len, int x, int y);
int search_row(char *row, int len, int x, int dir);
int search_column(char a[SIZE][SIZE], int len, int x, int y, int dir);
int search_diagonally(char a[SIZE][SIZE], int len, int x, int y, int vx, int vy);

int cross_search(char **a, int x, int y, int len, int m);
bool diagonal_search2(char **a, int x, int y, int len, int xdir, int ydir);

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
    else
    {
        return 3;
    }
}

void part1(FILE *file)
{
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

int star_search(char a[SIZE][SIZE], int len, int x, int y)
{
    int matches = 0;

    // enough room for word

    // 0 ... 6 7 8 9
    //       X M A S  x = 6 + len = 4 = 10
    //       ^ ->
    bool room_r = x + len <= SIZE;
    // 0 1 2 3 ... 9
    // S A M X  x = 3 - len = 4 = -1
    //    <- ^
    bool room_l = x - len + 1 >= 0;
    // 6 X <
    // 7 M  |
    // 8 A  v
    // 9 S
    // y = 6, len = 4; 6 + 4 = 10
    bool room_d = y + len <= SIZE;
    // 0 S
    // 1 A  ^
    // 2 M  |
    // 3 X <
    bool room_u = y - len + 1 >= 0;

    // search to the right
    if (room_r)
    {
        matches = matches + search_row(a[y], len, x, RIGHT);
    }
    // search ot the left
    if (room_l)
    {
        matches = matches + search_row(a[y], len, x, LEFT);
    }
    // search downwards
    if (room_d)
    {
        matches = matches + search_column(a, len, x, y, DOWN);
    }
    // search updwards
    if (room_u)
    {
        matches = matches + search_column(a, len, x, y, UP);
    }
    // search up-right
    if (room_r && room_u)
    {
        matches = matches + search_diagonally(a, len, x, y, RIGHT, UP);
    }
    // search down-left
    if (room_l && room_d)
    {
        matches = matches + search_diagonally(a, len, x, y, LEFT, DOWN);
    }
    // search down-right
    if (room_r && room_d)
    {
        matches = matches + search_diagonally(a, len, x, y, RIGHT, DOWN);
    }
    // search up-left
    if (room_l && room_u)
    {
        matches = matches + search_diagonally(a, len, x, y, LEFT, UP);
    }

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

int search_column(char a[SIZE][SIZE], int len, int x, int y, int dir)
{
    for (int i = 1; i < len; ++i)
    {
        if (a[y + (i * dir)][x] != WORD[i])
        {
            return 0;
        }
    }
    return 1;
}

int search_diagonally(char a[SIZE][SIZE], int len, int x, int y, int vx, int vy)
{
    for (int i = 1; i < len; ++i)
    {
        if (a[y + (i * vy)][x + (i * vx)] != WORD[i])
        {
            return 0;
        }
    }
    return 1;
}

void part2(FILE *file)
{
    int total_matches = 0;
    // get file length in # of chars
    fseek(file, 0, SEEK_END);
    int64_t file_len = ftell(file);
    fseek(file, 0, SEEK_SET);

    int size_x = 0;
    int size_y = 0;

    // determine size of x and y
    char c;
    for (int i = 0; i < file_len; ++i)
    {
        fread(&c, sizeof(char), 1, file);
        if (c == '\n')
        {
            size_y++;
            size_x = (size_x == 0) ? i : size_x;
        }
    }
    // reset file position
    fseek(file, 0, SEEK_SET);

    // alloctate mem for 2D array & put chars into it
    char **array = malloc(sizeof(char *) * size_y);
    for (int i = 0; i < size_y; ++i)
    {
        char *str = malloc(sizeof(char) * size_x);
        fread(str, sizeof(char), size_x, file);
        array[i] = str;

        // hop over '\n'
        fseek(file, 1, SEEK_CUR);
    }
    fclose(file);

    // get middle index of WORD2
    int word_len = strlen(WORD2);
    // m is also the length of one of the 4 cross arms
    int m = word_len / 2;
    c = WORD2[m];

    // iter of 3D array and find middle letter of WORD2
    for (int y = 0; y < size_y; ++y)
    {
        for (int x = 0; x < size_x; ++x)
        {
            if (array[y][x] == c)
            {
                // check if x, y leaves enough room to form a cross
                if (x - m < 0 || x + m >= size_x || y - m < 0 || y + m >= size_y)
                {
                    continue;
                }

                total_matches = total_matches + cross_search(array, x, y, word_len, m);
            }
        }
    }
    printf("total matches: %d\n", total_matches);

    // free up step
    for (int i = 0; i < size_y; ++i)
    {
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
}

int cross_search(char **a, int x, int y, int len, int m)
{
    // check if one arm matche
    if (!diagonal_search2(a, x - m, y - m, len, RIGHT, DOWN) && !diagonal_search2(a, x + m, y + m, len, LEFT, UP))
    {
        return 0;
    }

    if (!diagonal_search2(a, x + m, y - m, len, LEFT, DOWN) && !diagonal_search2(a, x - m, y + m, len, RIGHT, UP))
    {
        return 0;
    }
    return 1;
}

bool diagonal_search2(char **a, int x, int y, int len, int xdir, int ydir)
{
    for (int i = 0; i < len; ++i)
    {
        if (a[y + (i * ydir)][x + (i * xdir)] != WORD2[i])
        {
            return false;
        }
    }
    return true;
}
