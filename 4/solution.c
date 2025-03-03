#include <stdio.h>

#define FILENAME "small_input.txt"
// small_input has 18 "XMAS" occurences

void part1(FILE* file);
void part2(FILE* file);

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("\"./solution 1\" for part 1 \n.\"/solution 2\" for part 2\n");
        return 1;
    }

    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("File could not be opened\n");
        return 2;
    }

    if (*argv[1] == '1') {
        part1(file);
    } else if (*argv[1] == '2')
        part2(file);
}

void part1(FILE* file)
{
    // load file data into a char 2D array
}

void part2(FILE* file)
{
}