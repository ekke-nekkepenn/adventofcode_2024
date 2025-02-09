#include <ctype.h>    // atoi
#include <stdbool.h>  // bool
#include <stdint.h>   // int32_t
#include <stdio.h>    // printf
#include <stdlib.h>   // malloc realloc
#include <string.h>   // memcpy

#define FILENAME "input.txt"
#define IPT_SIZE 1000 // total line amount
#define MAX_LINE_LEN 30  // technically longer than len of any line

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
    for (int i = 0; i < IPT_SIZE; i++) {

        IntArray arr;
        char c;
        for (int j = 0; j < MAX_LINE_LEN; j++) {
            fread(&c, sizeof(char), 1, file);
            line.len = j;
            if (c == '\n') {
                line.buffer[j] = '\0';
                
                IntArray arr = convert(line);
                if (is_safe(arr)) 
                    safety_total++;

                break;
            }

            // fill up line.buffer
            line.buffer[j] = c;
        }
        free(arr.items);
    }

    printf("Total amount of safe lines: %d\n", safety_total);
    return 0;
}

IntArray convert(String line) {
    char buffer[3]; // no number is bigger than 2 digets

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

bool is_safe(IntArray arr) {
    /* this whole function is just garbage jank. I am so sorry*/
    bool v = true;
    int dampner = 0; // this is explained in the problem. 
    bool inc = false; // increase in value?
    bool dec = false; // decrease in value? 
    bool incdec = false; // idk fk this

    for (int i = 0; i < arr.len - 1; i++) {
        int d = arr.items[i + 1] - arr.items[i];

        if (0 == d || d > 3 || d < -3) {
            v = false;
            dampner++;
        }

        if (d > 0) inc = true; 
        if (d < 0) dec = true;

        if(inc == dec && !incdec) { // WTF AM I DOING
            dampner++;
            incdec = true; // this should only be once
        }

                
    }
    if (inc == dec) v = false;
    if (dampner == 1) v = true;
    return v;

}

//bool is_safe(IntArray arr) {
//
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