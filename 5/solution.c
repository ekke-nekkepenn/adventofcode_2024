#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"
// each number has 2 digits, so range is 10-99
// size of priority chart
#define SIZE_TABLE 100

typedef struct {
    bool** table;
    // size is for rows and columns
    int size;
} Table;

// sub main function
int part1(FILE* file);
int part2(FILE* file);

void fill_table(Table t, FILE* file);
void free_table(Table t);

int main(int argc, char** argv)
{

    if (argc != 2)
        return 10;

    int result = 0;

    FILE* file = fopen(FILENAME, "r");
    if (!file)
        return 20;

    if (argv[1][0] == '1') {
        result = part1(file);
    } else if (argv[1][0] == '2') {
        result = part2(file);
    }
    // wrong cmd param provided
    else {
        fclose(file);
        return 11;
    }

    printf("result for Part %c: %d\n", argv[1][0], result);

    fclose(file);
    return 0;
}

int part1(FILE* file)
{

    Table priority = (Table) { malloc(sizeof(bool*) * SIZE_TABLE), SIZE_TABLE };
    for (int i = 0; i < SIZE_TABLE; ++i) {
        priority.table[i] = calloc(SIZE_TABLE, sizeof(bool));
    }

    fill_table(priority, file);
    printf(".");

    free_table(priority);
    return 0;
}

int part2(FILE* file)
{
    return 0;
}

void fill_table(Table t, FILE* file)
{
    int l = 6; // 6 chars per line incl newline
    int n = 3; // size for 2 digit nums

    char* buffer_line = calloc(l, sizeof(char));
    char* buffer_num = calloc(n, sizeof(char));

    // read line for line
    while (fread(buffer_line, sizeof(char), l, file)) {

        // stop at newline because we only need first half of input here
        if (buffer_line[0] == '\n') {
            break;
        }

        // copy nums from line into
        memcpy(buffer_num, buffer_line, 2);
        int numA = atoi(buffer_num);
        memcpy(buffer_num, buffer_line + 3, 2);
        int numB = atoi(buffer_num);
        // numA has prio over numB
        t.table[numA][numB] = true;
    }

    free(buffer_line);
    free(buffer_num);
}

void free_table(Table t)
{
    // free table
    for (int i = 0; i < t.size; ++i) {
        free(t.table[i]);
        t.table[i] = NULL;
    }
    free(t.table);
}