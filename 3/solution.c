#include <stdio.h>
#include <regex.h>
#include <stdlib.h>

#define FILENAME "input.txt"
#define LINE_LEN 4000

typedef struct {
    char *ptr;
    int length;
} String;

void part1(void);
void free_string(String s);

int main(void) {
    part1();

    return 0;
}

void part1(void) {
    FILE *file = fopen(FILENAME, "r");
    if (NULL == file) {
        printf("Could not open %s\n", FILENAME);
        return;
    }
    String Line = (String) {malloc(sizeof(char) * LINE_LEN), 0};

    free_string(Line);
    fclose(file);
}


void free_string(String s) {
    free(s.ptr);
}