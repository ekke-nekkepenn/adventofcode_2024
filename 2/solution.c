#include <ctype.h>    // atoi
#include <stdbool.h>  // bool
#include <stdint.h>   // int32_t
#include <stdio.h>    // printf
#include <stdlib.h>   // malloc realloc
#include <string.h>   // memcpy

#define FILENAME "input.txt"
#define IPT_SIZE 1000 // total line amount
#define MAX_LINE_LEN 30  // technically longer than len of any line
#define BUFFER_SIZE 3
#define INTARR_CAPACITY 10

// Struct
typedef struct {
    char *buffer;
    int16_t len;
} String;

typedef struct {
    int16_t *items;
    int16_t len;
    int16_t capacity;
} IntArray;


// Prototypes
IntArray convert(String line); 
bool is_safe(IntArray arr);


int part1() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        perror("test");
        return -1;
    };

    String line = (String) {malloc(sizeof(char) * MAX_LINE_LEN), 0};

    int safety_total = 0;
    IntArray arr;
    for (int i = 0; i < IPT_SIZE; i++) {

        char c;
        for (int j = 0; j < MAX_LINE_LEN; j++) {
            fread(&c, sizeof(char), 1, file);
            line.len = j;
            if (c == '\n') {
                line.buffer[j] = '\0';
                
                arr = convert(line);
                if (is_safe(arr)) 
                    safety_total++;

                break;
            }

            // fill up line.buffer
            line.buffer[j] = c;
        }
        free(arr.items);
    }

    free(line.buffer);
    fclose(file);
    printf("Total amount of safe lines: %d\n", safety_total);
    return 0;
}

IntArray convert(String line) {
    char buffer[BUFFER_SIZE];

    int capacity = INTARR_CAPACITY;
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

bool is_safe(IntArray arr) {
    bool safety = true;
    bool rising = false, falling = false;
    bool life = true;

    for (int i = 0; i < arr.len - 1; i++) {

        int d = arr.items[i + 1] - arr.items[i];

        if (d == 0 || d > 3 || d < -3) {
            if (life) {
                life = false;
                continue;
            }
            safety = false;
        }

        if (d > 0) rising = true;
        if (d < 0) falling = true;

        if (rising && falling) {
            if (life) {
                life = false;
                if (arr.items[i] - arr.items[i - 1] > 0) falling = false;
                else if(arr.items[i] - arr.items[i - 1] < 0) rising = false;
            }
            else safety = false;

        }
    }

    return safety;
}

//bool is_safe(IntArray arr) {
//    // this works part 1
//    bool inc = false; 
//    bool dec = false;
//    for (int i = 0; i < arr.len - 1; i++) {
//        int d = arr.items[i + 1] - arr.items[i];
//        if (0 == d || d < -3 || d > 3) return false;
//
//        if (d > 0) inc = true;
//        if (d < 0) dec = true;
//        if (inc == dec) return false;
//    }
//
//    return true;
//}


int main(void) {
    int s = part1();
    printf("%d\n", s);
    
    
    return 0;
}