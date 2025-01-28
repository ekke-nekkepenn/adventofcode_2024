#include <stdio.h> //printf
#include <stdlib.h> // malloc realloc
#include <ctype.h>  //atoi
#include <stdint.h> 

#define FILENAME "input.txt"
#define IPT_SIZE 1000
#define MAX_LINE_LENGTH 25


// structs
typedef struct String {
    char *text;
    int32_t len;
} String;

// prototypes
char String_GET(String string, int i);
void free_line(String string);
int part1();

int main() {
    part1();

    return 0;
}

int part1() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        return -1;
    };

    // int line_num = 0;
    // read line
    // i is line number
    String line = (String) {NULL, 0};
    line.text = malloc(sizeof(char) * (uint64_t) (line.len * 1));

   for (int i = 0; i < IPT_SIZE; i++) {

        char c = ' ';
        // load line 
        while (fread(&c, sizeof(char), 1, file)) {
            if (c == '\n') {
                printf("breaking out of for-loop\n");
                break;
            }
            line.text = realloc(line.text, sizeof(char) * (uint64_t) line.len + 1);
            line.text[line.len] = c;
            line.len++;
        }

        line.text[line.len] = '\n';
        printf("%s", line.text);
        break;

    }
    free_line(line);
    return 1;
}

char String_GET(String string, int32_t i) {
    if (i > string.len || i < 0 ) {
        printf("error");
    }
    return string.text[i];
}

void free_line(String string) {
    free(string.text);
}