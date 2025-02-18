#include <stdio.h>
#include <regex.h>
#include <stdlib.h>

#define FILENAME "input.txt"
#define LINE_LEN 22000

typedef struct {
    char *ptr; // beginning of string
    int length;
} String;



void print_string(String s);
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
    String Text = (String) {malloc(sizeof(char) * LINE_LEN), 0};

    char c;
    while (fread(&c, sizeof(char), 1, file)) {
        Text.ptr[Text.length] = c;
        Text.length++;
    }
    
    print_string(Text);
    printf("\n\n\n");

    regex_t regex;
    while (1) {
        char msgbuf[100];
        char *pattern = "mul\\(+\\d,+\\d\\)";
        int regc = regcomp(&regex, pattern, 0);
        if (regc) {
            break;
        }

        regc = regexec(&regex, Text.ptr, 0, NULL, 0);
        if (!regc) {
            printf("Match");
        }
        else if (regc == REG_NOMATCH) {
            printf("No Match");
        }
        else {
            regerror(regc, &regex, msgbuf, sizeof(msgbuf));
            break;
        }
        break;
    }
    for (int i = 0; i < Text.length; i++)


    regfree(&regex);
    free_string(Text);

    fclose(file);
}

void print_string(String s) {
    for (int i = 0; i < s.length; i++) {
        printf("%c", s.ptr[i]);
    }
}

void free_string(String s) {
    //printf("(free_string) address ptr: %p\n\n", s.ptr);
    free(s.ptr);
}