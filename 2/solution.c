#include <ctype.h>    //atoi
#include <stdbool.h>  // bool
#include <stdint.h>   // int32_t
#include <stdio.h>    //printf
#include <stdlib.h>   // malloc realloc
#include <string.h>

#define FILENAME "input.txt"
#define IPT_SIZE 1000
#define MAX_LINE_LEN 30

// struct
typedef struct String {
    int16_t len;
    char *buffer;
} String;

// prototypes
bool is_line_level_valid(String line);
int part1();

int main() {
    part1();

    return 0;
}

int part1() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        perror("test");
        return -1;
    };

    String line = (String){0, malloc(sizeof(1) * MAX_LINE_LEN)};

    int level_total = 0;
    for (int i = 0; i < IPT_SIZE; i++) {
        char c;
        for (int j = 0; j < MAX_LINE_LEN; j++) {
            fread(&c, sizeof(char), 1, file);
            // we rached end of line
            if (c == '\n') {
                line.buffer[j] = '\0';
                line.len = j + 1;
                bool validity = is_line_level_valid(line);
                if (validity) level_total++;
                break;
            }

            // fill up line.buffer
            line.buffer[j] = c;
            line.len = j + 1;
        }
    }
    return 1;
}

bool is_line_level_valid(String line) {
    // find out if the rules for a level applies
    bool validity = false;
    char buffer[3];

    int low = 0;
    for (int i = 0; i < line.len; i++) {
        // at space gets the recent num and converts to num
        if (' ' == line.buffer[i] || '\0' == line.buffer[i]) {
            memcpy(buffer, line.buffer + low, i);
            buffer[i - low] = '\0';
            printf("%d ", atoi(buffer));
            low = i + 1;

        }
    }
    // .
    printf("\n");

    return validity;
}

