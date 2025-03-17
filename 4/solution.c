#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

<<<<<<< HEAD
// small_input.txt has 18 "XMAS" occurences

#define SEARCH_TARGET "XMAS"

typedef struct {
    int x;
    int y;
} IntPair;
=======
#define SIZE 10
#define WORD "XMAS"
>>>>>>> refs/remotes/origin/main

#define LEFT -1
#define RIGHT 1

<<<<<<< HEAD
void find_dimensions(IntPair* size, FILE* file);
int star_search(char** const StringArray, IntPair size, IntPair pos, const char* __WORDSIZE_TIME64_COMPAT32);

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("Please provide valid arguements:\n\"./solution 1 file_name.txt\" or \"./solution 2 file_name.txt\"\n");
        return 1;
    }

    char* filename = argv[2];

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
=======
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
>>>>>>> refs/remotes/origin/main
        printf("File could not be opened\n");
        return 2;
    }

<<<<<<< HEAD
    if (argv[1][0] == '1') { // argv[1][0] same as *argv[1] which expands to *(argv[1] + 0) which expands to *(*(argv + 1) + 0)
        part1(file);
    } else if (argv[1][0] == '2')
=======
    if (*argv[1] == '1')
    {
        part1(file);
    }
    else if (*argv[1] == '2')
>>>>>>> refs/remotes/origin/main
        part2(file);
    else {
        return 3;
    }
}

void part1(FILE *file)
{
<<<<<<< HEAD

    IntPair size = { .x = 0, .y = 0 };
    find_dimensions(&size, file);

    // Reset file position
    int64_t file_pos = 0;
    fseek(file, file_pos, SEEK_SET);

    // Allocate mem for StringArray
    char** StringArray = malloc(sizeof(char*) * size.y);
    // Read data in a String and store in StringArray
    for (int i = 0; i < size.y; ++i) {
        char* line = malloc(sizeof(char) * size.x);
        // write into line. find_dimension guaranteers width excludes '\n'
        if (!fgets(line, size.x, file)) {
            printf("ERROR fgets()");
        }
        file_pos = ftell(file);
        fseek(file, file_pos + 2, SEEK_SET); // go 1 pos over '\n'
        StringArray[i] = line;
    }
    // close file no need anymore
    fclose(file);

    // SEARCH
    int total_matches = 0;
    // loop over indices to find first element of SEARCH_TARGET
    for (int y = 0; y < size.y; ++y) {
        for (int x = 0; x < size.x; ++x) {
            if (StringArray[y][x] == SEARCH_TARGET[0]) {
                total_matches = star_search(StringArray, size, (IntPair) { .x = x, .y = y }, SEARCH_TARGET);
=======
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
>>>>>>> refs/remotes/origin/main
            }
        }
    }

<<<<<<< HEAD
    // print result
    printf("Found matches: %d\n", total_matches);

    // free inside StringArray
    for (int i = 0; i < size.y; ++i) {
        free(StringArray[i]);
        StringArray[i] = NULL;
    }
    free(StringArray);
    StringArray = NULL;
=======
    printf("Total found matches of %s: %ld\n", WORD, total_matches);
>>>>>>> refs/remotes/origin/main
}

void part2(FILE *file)
{
}

<<<<<<< HEAD
void find_dimensions(IntPair* size, FILE* file)
{
    // Find out x and y dimensions of input size.
    // x = up to first '\n' so x = pos('\n') - 1
    char c;
    bool f = true; // only count x length once so disable after '\n' found
    while ((fread(&c, 1, 1, file)) != 0) {
        if (f && (c != '\n')) {
            (size->x)++;
        }
        if (c == '\n') {
            (size->y)++;
            f = false;
        }
    }
}

int star_search(char** const StringArray, IntPair size, IntPair pos, const char* word)
{
    int len = strlen(word) int dx;

    // TO THE RIGHT
    // first check if there is even room for word
    if ((dx = size.x - pos.x) < len) {
    }

    return 1;
}
=======
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
>>>>>>> refs/remotes/origin/main
