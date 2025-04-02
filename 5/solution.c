#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"
#define LEN_LINE 6
#define LEN_DIGIT 2
#define LEN_LINE_2 70 // 2nd part of input.txt. Max of 69 chars in a line
#define SIZE_TABLE 100 // ik ik some spots in the table are not used idc

typedef struct
{
    bool** table;
    int size; // # rows and columns are the same
} Table;

typedef struct
{
    int* ptr;
    int len; // len is also capicity in this case
} IntArray;

// sub function in main
int part1(FILE* file);
int part2(FILE* file);

// create/modify data structs
void fill_table(Table* t, FILE* file);
void free_table(Table* t);
IntArray convert_update(char* s);
void sort_by_priority(IntArray* a, Table* t);

// misc
bool is_update_valid(IntArray* a, Table* t);
int count_prio(IntArray* a, Table* t, int idx);

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

    else {
        fclose(file);
        return 11;
    }

    printf("result for Part %s: %d\n", argv[1], result);

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

    fill_table(&priority, file);
    // get the next line of "update"
    // iter over it and check if it is valid
    // by checking priority is first num highest prio? Is second num second highest prio? and so on

    // update ha ~ max 90 chars
    char buffer[LEN_LINE_2];
    while (fgets(buffer, LEN_LINE_2, file)) {
        IntArray current_update = convert_update(buffer);
        if (is_update_valid(&current_update, &priority)) {
            int median = current_update.ptr[(current_update.len / 2)];
            total = total + median;
        }
        free(current_update.ptr);
    }

    free_table(&priority);
    return total;
}

int part2(FILE* file)
{
    // for comments look at part 1
    int total = 0;

    Table priority = (Table) { malloc(sizeof(bool*) * SIZE_TABLE), SIZE_TABLE };
    for (int i = 0; i < SIZE_TABLE; ++i) {
        priority.table[i] = calloc(SIZE_TABLE, sizeof(bool));
    }

    fill_table(&priority, file);

    char buffer[LEN_LINE_2];
    while (fgets(buffer, LEN_LINE_2, file)) {
        IntArray current_update = convert_update(buffer);
        if (!is_update_valid(&current_update, &priority)) {
            sort_by_priority(&current_update, &priority);
            int median = current_update.ptr[(current_update.len / 2)];
            total = total + median;
        }
        free(current_update.ptr);
        current_update.ptr = NULL;
    }

    free_table(&priority);
    return total;
}

void fill_table(Table* t, FILE* file)
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
        t->table[numA][numB] = true;
    }

    free(buffer_line);
    free(buffer_num);
}

void free_table(Table* t)
{
    // free table
    for (int i = 0; i < t->size; ++i) {
        free(t->table[i]);
        t->table[i] = NULL;
    }
    free(t->table);
    t->table = NULL;
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

    *p = atoi(buffer);
    a.len++;

    a.ptr = realloc(a.ptr, sizeof(int) * a.len);
    return a;
}

bool is_update_valid(IntArray* a, Table* t)
{
    // iter over each num except last (i)
    int n = a->len - 2;
    for (int i = 0; i < n; ++i) {
        int numA = a->ptr[i];
        // iter over next nums and check if they have prio
        for (int j = 1 + i; j < a->len; ++j) {
            int numB = a->ptr[j];
            // does numB have prio over numA
            if (t->table[numB][numA]) {
                return false;
            }
        }
    }

    return true;
}

int count_prio(IntArray* a, Table* t, int idx)
{
    // count how often element at index idx has prio over every other num in array
    int prio = 0;
    int numA = a->ptr[idx];
    for (int i = 0; i < a->len; ++i) {
        // no need to count itself but even if, [numA][numA] has prio 0;
        if (numA == a->ptr[i])
            continue;
        prio = prio + t->table[numA][a->ptr[i]];
    }
    return prio;
}

void sort_by_priority(IntArray* a, Table* t)
{
    // how do we sort this mess?
    // first we should count each prio N for each number
    // where do we store this?
    // like in a python dictionary for example?
    // key = numA, value = prio N; ??
    // IK IK Not really a dictionary. There is no hash here and we have to iter. IDC
    typedef struct {
        int key;
        int value;
    } KeyValue;

    KeyValue* dict = malloc(sizeof(KeyValue) * a->len);

    // fill pseudo dictionary
    for (int i = 0; i < a->len; ++i) {
        KeyValue kv = (KeyValue) { a->ptr[i], count_prio(a, t, i) };
        dict[i] = kv;
    }
    // sort the pseudo dictionary (Bubble sort)
    for (int i = 0; i < a->len - 1; ++i) {
        for (int j = 0; j < a->len - i - 1; ++j) {
            if (dict[j].value > dict[j + 1].value) {
                KeyValue tmp = dict[j];
                dict[j] = dict[j + 1];
                dict[j + 1] = tmp;
            }
        }
    }

    // copy the order of the peusdo dictionary to the IntArray
    for (int i = 0; i < a->len; ++i) {
        a->ptr[i] = dict[i].key;
        printf("key: %d value: %d\n", a->ptr[i], dict[i].value);
    }
    printf("\n");

    free(dict);
}