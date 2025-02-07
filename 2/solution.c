#include <ctype.h>    // atoi
#include <stdbool.h>  // bool
#include <stdint.h>   // int32_t
#include <stdio.h>    // printf
#include <stdlib.h>   // malloc realloc
#include <string.h>   // memcpy

#define FILENAME "input.txt"
#define IPT_SIZE 1000
#define MAX_LINE_LEN 30  // technically longer than len of any line

// struct
typedef struct {
    char *buffer;
    int16_t len;
} String;

typedef struct {
    int16_t *items;
    int16_t len;
    int16_t capacity;
} IntArray;

// prototypes
IntArray convert(String line); 
void part1();

int main() {
    part1();

    return 0;
}

void part1() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        perror("test");
        return -1;
    };

    String line = (String) {malloc(sizeof(char) * MAX_LINE_LEN), 0};

    int level_total = 0;
    for (int i = 0; i < IPT_SIZE; i++) {
        char c;
        for (int j = 0; j < MAX_LINE_LEN; j++) {
            fread(&c, sizeof(char), 1, file);
            // we rached end of line
            line.len = j;
            if (c == '\n') {
                line.buffer[j] = '\0';
                
                IntArray arr = convert(line);


                break;
            }

            // fill up line.buffer
            line.buffer[j] = c;
        }
    }

    printf("%d", level_total);
}

IntArray convert(String line) {
    char buffer[3]; // store each num per line

    int capacity = 10;
    IntArray arr = (IntArray) {malloc(sizeof(int) * capacity), 0, capacity};

    for (int i = 0, low = 0; i <= line.len; i++) {
        if (' ' == line.buffer[i] || '\0' == line.buffer[i]) {
            // parse 'NUM' to int NUM. Delimiters [' ', '\0']
            memcpy(buffer, line.buffer + low, i - low);
            buffer[i - low] = '\0';
            low = i + 1;
            arr.items[arr.len] = atoi(buffer);
            arr.len++;
        }
    }

    return arr;
}