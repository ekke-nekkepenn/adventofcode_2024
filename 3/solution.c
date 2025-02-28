#include <regex.h> // regex_t regmatch_t regexec() regcomp()
#include <stdbool.h>
#include <stdint.h> // int64_t
#include <stdio.h> // fseek() ftell() printf() fread() FILE
#include <stdlib.h> // atoi()
#include <string.h> // memcpy()

#define FILENAME "input.txt"
#define LINE_LEN 22000 // used for part1 not needed for part2
#define MAX_DIGIT 10

#define PATTERN_MUL "mul\\(([0-9]+),([0-9]+)\\)"
#define PATTERN_DONT "don't\\(\\)"
#define PATTERN_DO "do\\(\\)"

typedef struct {
    char* ptr; // beginning of string
    int length;
} String;

// PROTOTYPES
void part1(void);
void part2(void);

int64_t find_muls(char* s, int64_t* oS, int64_t* oE, regex_t* regex_mul, regmatch_t* match_mul);

void free_string(String s);
void print_string(String s);

int main(void)
{
    // part1();
    part2();

    return 0;
}

void part1(void)
{
    FILE* file = fopen(FILENAME, "r");
    if (NULL == file) {
        printf("Could not open %s\n", FILENAME);
        return;
    }

    fseek(file, 0, SEEK_END); // go to the end pos of file
    int64_t file_length = ftell(file); // returns current pos which is the length
    fseek(file, 0, SEEK_SET);
    String Text = (String) { malloc(sizeof(char) * file_length), file_length };

    fread(Text.ptr, 1, file_length, file);
    Text.ptr[Text.length] = '\0';

    regex_t regex;
    regmatch_t pmatch[3]; // match stored here

    int regc = regcomp(&regex, PATTERN_MUL, REG_EXTENDED); // regc = 0 successful
    // REG_EXTENDED flag, link below for more info
    // https://en.wikibooks.org/wiki/Regular_Expressions/POSIX-Extended_Regular_Expressions

    if (regc) {
        free_string(Text);
        fclose(file);
    }

    char* ptr = Text.ptr; // we wanna override ptr and not lose Text.ptr

    char num_buffer[10]; // here we atoi our string number 10 is just randomly
                         // chosen
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
        num_buffer[end - start] = '\0';
        num = atoi(num_buffer);

        start = pmatch[2].rm_so;
        end = pmatch[2].rm_eo;

        memcpy(num_buffer, ptr + start, end - start);
        num_buffer[end - start] = '\0';
        total += num * atoi(num_buffer);

        ptr = ptr + end;
    }
    printf("\n");
    printf("%d\n", total);

    regfree(&regex); // used after regexec() not if regcomp failed
    free_string(Text);
    fclose(file);
}

void part2(void)
{

    // open file
    FILE* file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("File could not opened.");
        return;
    }

    // determine length of file
    fseek(file, 0, SEEK_END); // go to the end pos of file
    int64_t file_length = ftell(file); // returns current pos which is the length
    fseek(file, 0, SEEK_SET); // reset pos

    // load file into String and close it
    String Text = (String) { malloc(sizeof(char) * file_length), file_length };
    fread(Text.ptr, sizeof(char), Text.length, file);
    Text.ptr[Text.length] = '\0';
    fclose(file);

    // compile regex
    regex_t regex_mul;
    regex_t regex_dont;
    regex_t regex_do;

    if (regcomp(&regex_mul, PATTERN_MUL, REG_EXTENDED) || regcomp(&regex_dont, PATTERN_DONT, REG_EXTENDED)
        || regcomp(&regex_do, PATTERN_DONT, REG_EXTENDED)) {
        printf("Regex compiliation failed.\n");
        free_string(Text);
        return;
    }

    regmatch_t match_mul[3]; // [3] coz 2 additional subexpr matches
    regmatch_t match_dont[1];
    regmatch_t match_do[1];

    int64_t offset_start = 0;
    int64_t offset_end = 0;

    bool donts = true;

    int64_t total = 0;
    while (true) {
    }

    char tmp;
    char num_buffer[MAX_DIGIT];

    // free things
    free_string(Text);
    regfree(&regex_mul);
    regfree(&regex_dont);
    regfree(&regex_do);
}

int64_t find_muls(char* s, int64_t* offset_start, int64_t* offset_end, regex_t* regex_mul, regmatch_t* match_mul)
{
    // modify s so it ends at *oE with a '\0' so regexec() knows where to stop
    char tmp = s[*offset_end];
    s[*offset_end] = '\0';

    int64_t num = 0;

    while (true) {
        if (regexec(regex_mul, s + *offset_start, 3, match_mul, 0) != 0) {
            break;
        }

        *offset_start = *offset_start + match_mul[0].rm_eo;
    }
    s[*offset_end] = tmp;
    return num;
}

void print_string(String s)
{
    for (int i = 0; i < s.length; i++) {
        printf("%c", s.ptr[i]);
    }
}

void free_string(String s)
{
    // printf("(free_string) address ptr: %p\n\n", s.ptr);
    free(s.ptr);
}