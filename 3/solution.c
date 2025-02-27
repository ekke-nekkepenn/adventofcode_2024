#include <stdio.h> // fseek() ftell() printf() fread() FILE
#include <regex.h> // regex_t regmatch_t regexec() regcomp()
#include <stdlib.h> // atoi()
#include <string.h> // memcpy()
#include <stdint.h> // int64_t
#include <stdbool.h>

#define FILENAME    "input.txt"
#define LINE_LEN    22000

typedef struct {
    char    *ptr; // beginning of string
    int     length;
} String;

// PROTOTYPES
void part1(void);
void part2(void);

void free_string(String s);
void print_string(String s);

int main(void) {
    //part1();
    part2();

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


    char *ptr = Text.ptr; // we wanna override ptr and not lose Text.ptr

    char num_buffer[10]; // here we atoi our string number 
    int total = 0;
    int64_t num;
    while (1) {
        regc = regexec(&regex, ptr, 3, pmatch, 0);
        if (regc != 0) {
            break;
        }
        // pmatch[0] is the whole match
        // every other element in pmatch is a subexpression 
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

        ptr = ptr + end;
    }
    printf("\n");
    printf("%d\n", total);


    
    regfree(&regex); // used after regexec() not if regcomp failed
    free_string(Text);
    fclose(file);
}

void part2(void) {
    // open file
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("File could not opened.");
        return;
    }

    // determine length of file
    fseek(file, 0, SEEK_END);   // go to the end pos of file
    int64_t file_length = ftell(file);  // returns current pos which is the length
    fseek(file, 0, SEEK_SET); // reset pos 

    // alloc mem for String and read file into 
    String Text = (String) {malloc(sizeof(char) * file_length), file_length};
    fread(Text.ptr, sizeof(char), Text.length, file);
    Text.ptr[Text.length] = '\0';  
    
    // file not needed anymore
    fclose(file);

    // init vars for regcmp() & regexec()
    regex_t mul_regex;
    regex_t dont_regex;
    regex_t do_regex;

    regmatch_t mul_match[3]; // [3] coz 2 additional subexpr matches
    regmatch_t dont_match[1];
    regmatch_t do_match[1];

    char *mul_pattern = "mul\\(([0-9]+),([0-9]+)\\)";
    char *dont_pattern = "don't\\(\\)";
    char *do_pattern = "do\\(\\)";

    int regc = regcomp(&mul_regex, mul_pattern, REG_EXTENDED);
    int regc1 = regcomp(&dont_regex, dont_pattern, REG_EXTENDED);
    int regc2 = regcomp(&do_regex, do_pattern, REG_EXTENDED);
    
    // check for SUCCESS which is 0
    if (regc || regc1 || regc2) {
        printf("Regec compiliation failed.\n");
        free_string(Text);
        return;
    }

    // init vars for finding all mul(...) 
    int start = 0;
    int end = 0;
    int regc;
    char *copy_textptr = Text.ptr; // we wanna change the copy & free old

    // we start start to next "dont()"

    regc = regexec(&dont_regex, copy_textptr, 1, dont_match, 0);
    end = dont_match[0].rm_so;

    // what we could do is store value in Text.ptr[rm_so] in sep var
    // then put a '\0' into that position 
    // regexec over it until no matches happen 
    // then replace '\0' with the old value







        



    

    // free things
    free_string(Text);    
    regfree(&dont_regex);
}

String create_slice(String s, int64_t start, int64_t end) {

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