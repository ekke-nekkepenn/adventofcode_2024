#include <stdio.h>
#include <stdint.h>

#define FILENAME "input.txt"

// PROTOTYPES

int64_t part1(FILE *file);
int64_t part2(FILE *file);

int main(int argc, char**argv)
{
    if (argc != 2)
    {
        return 1;
    }

    FILE *file = fopen(FILENAME, "r");
    if (!file)
    {
        printf("fopen error. FILENAME=%s\n", FILENAME);
        return 20;
    }

    int64_t result = 0;   

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
        printf("Usage: ./<progname.c> [1, 2]");
    }

    printf("Result of Part %c: %ld\n", argv[1][0], result);
    fclose(file);
    return 0;

}


int64_t part1(FILE *file) 
{
    int64_t result = 0;
    // solution here 
    return result;
}

int64_t part2(FILE *file) 
{
    int64_t result = 0;
    // solution here
    return result;
}