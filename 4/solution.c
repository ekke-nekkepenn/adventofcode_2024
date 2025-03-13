#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// small_input.txt has 18 "XMAS" occurences

#define SEARCH_TARGET "XMAS"

typedef struct {
    int x;
    int y;
} IntPair;

void part1(FILE* file);
void part2(FILE* file);

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
        printf("File could not be opened\n");
        return 2;
    }

    if (argv[1][0] == '1') { // argv[1][0] same as *argv[1] which expands to *(argv[1] + 0) which expands to *(*(argv + 1) + 0)
        part1(file);
    } else if (argv[1][0] == '2')
        part2(file);
    else {
        return 3;
    }
}

void part1(FILE* file)
{

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
            }
        }
    }

    // print result
    printf("Found matches: %d\n", total_matches);

    // free inside StringArray
    for (int i = 0; i < size.y; ++i) {
        free(StringArray[i]);
        StringArray[i] = NULL;
    }
    free(StringArray);
    StringArray = NULL;
}

void part2(FILE* file)
{
}

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
