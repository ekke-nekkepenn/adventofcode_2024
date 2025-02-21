#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define FILENAME    "input.txt"
#define LINE_LEN    22000

typedef struct {
    char    *ptr; // beginning of string
    int     length;
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
    
    regex_t     regex;
    regmatch_t  pmatch[3]; // match stored here

    char *pattern = "mul\\(([0-9]+),([0-9]+)\\)";
    int regc = regcomp(&regex, pattern, REG_EXTENDED); // regc = 0 successful
    // REG_EXTENDED flag, link below for more info
    // https://en.wikibooks.org/wiki/Regular_Expressions/POSIX-Extended_Regular_Expressions 

    if (regc) {
        free_string(Text);
        fclose(file);
    }

    int start = 0;    
    int end = 0;
    char *ptr = Text.ptr + end; // need to use *ptr or else we get a warning idk

    char num_buffer[10]; // here we atoi our string number 
    int total = 0;
    int64_t num;
    while (1) {
        regc = regexec(&regex, ptr, 3, pmatch, 0);
        if (regc != 0) {
            break;
        }
        // first num
        int start = pmatch[1].rm_so;
        int end = pmatch[1].rm_eo;

        memcpy(num_buffer, ptr + start, end - start);
        num_buffer[end-start] = '\0';
        num = atoi(num_buffer);

        start = pmatch[2].rm_so;
        end = pmatch[2].rm_eo;

        memcpy(num_buffer, ptr + start, end - start);
        num_buffer[end-start] = '\0';
        total += num * atoi(num_buffer);

        //start = pmatch[2].rm_so;
        //end = pmatch[2].rm_eo;

        //for (int i = start; i < end; i++) {
        //    printf("%c", *(ptr + i));
        //}
        //printf("  ");






        ptr = ptr + end;
    }
    printf("\n");
    printf("%d\n", total);


    
    regfree(&regex); // used after regexec() not if regcomp failed
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