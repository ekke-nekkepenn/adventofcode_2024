#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"
#define LEN_LINE 6 // each number has 2 digits, so range is 10-99
#define LEN_DIGIT 2 // first part of input.txt
#define LEN_LINE_2 70 // 2nd part of input.txt. Max of 69 chars in a line
#define SIZE_TABLE 100

typedef struct {
    bool** table;
    // size is for rows and columns
    int size;
} Table;

typedef struct {
    int* ptr;
    int len;
} IntArray;

// sub main function
int part1(FILE* file);
int part2(FILE* file);

void fill_table(Table t, FILE* file);
void free_table(Table t);

IntArray convert_update(char* s);

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
    int total = 0;

    Table priority = (Table) { malloc(sizeof(bool*) * SIZE_TABLE), SIZE_TABLE };
    for (int i = 0; i < SIZE_TABLE; ++i) {
        priority.table[i] = calloc(SIZE_TABLE, sizeof(bool));
    }

    fill_table(priority, file);
    // get the next line of "update"
    // iter over it and check if it is valid
    // by checking priority is first num highest prio? Is second num second highest prio? and so on

    // update ha ~ max 90 chars
    char buffer[LEN_LINE_2];
    while (fgets(buffer, LEN_LINE_2, file)) {
        IntArray current_update = convert_update(buffer);
        int l = current_update.len - 1; // -1 coz last num has no later nums to check
        bool check = true;

        for (int i = 0; i < l; ++i) {
            int numA = *(current_update.ptr + i);
            for (int j = 1 + i; j < current_update.len; j++) {
                int numB = *(current_update.ptr + j);
                if (!priority.table[numA][numB]) {
                    check = false;
                    break;
                }
            }
            // if inner for loop breaks, outer should too. Invalid update
            if (!check) {
                break;
            }
        }
        // find middle num and add to total
        if (check) {
            total = total + current_update.ptr[(current_update.len / 2)];
        }
    }

    free_table(priority);
    return total;
}

int part2(FILE* file)
{
    return 0;
}

void fill_table(Table t, FILE* file)
{
    char* buffer_line = calloc(LEN_LINE + 1, sizeof(char));
    char* buffer_num = calloc(LEN_DIGIT + 1, sizeof(char));

    // read line for line
    while (fgets(buffer_line, LEN_LINE + 1, file)) {
        // stop at newline because we only need first half of input here
        if (buffer_line[0] == '\n') {
            break;
        }

        // copy nums from line into
        memcpy(buffer_num, buffer_line, LEN_DIGIT);
        int numA = atoi(buffer_num);
        memcpy(buffer_num, (buffer_line + LEN_DIGIT + 1), LEN_DIGIT);
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

IntArray convert_update(char* s)
{

    // line has max 23 numbers per line (I estimated)
    IntArray a = { calloc(LEN_LINE_2, sizeof(int)), 0 };
    int* p = a.ptr;

    char buffer[LEN_DIGIT + 1] = { 0 }; // there are only 2 digit nums
    char* b = buffer;
    char c;

    // turn "53, 32, 12, 56\n" -> int [53, 32, 12, 56] as a IntArray
    while ((c = *s++) != '\n') {
        // end of number
        if (c == ',') {
            *p++ = atoi(buffer);
            a.len++;
            // reset buffer index
            b = &buffer[0];
        }
        // write into buffer
        else {
            *b++ = c;
        }
    }
    a.ptr = realloc(a.ptr, sizeof(int) * a.len);
    return a;
}
