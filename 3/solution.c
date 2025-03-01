#include <regex.h> // regex_t regmatch_t regexec() regcomp()
#include <stdbool.h>
#include <stdint.h> // int64_t
#include <stdio.h> // fseek() ftell() printf() fread() FILE
#include <stdlib.h> // atoi()
#include <string.h> // memcpy()

#define FILENAME "input.txt"
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

int64_t find_muls(char* string, int64_t offset_start, int64_t offset_end, regex_t* regex_mul, regmatch_t* match_mul);

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

    // determine length of file
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
        printf("File could not be opened.");
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
        || regcomp(&regex_do, PATTERN_DO, REG_EXTENDED)) {
        printf("Regex compiliation failed.\n");
        free_string(Text);
        return;
    }

    regmatch_t match_mul[3]; // [3] coz 2 additional subexpr matches
    regmatch_t match_dont[1];
    regmatch_t match_do[1];

    int64_t s_start = 0; // slice start
    int64_t s_end = 0; // slice end

    int64_t total = 0;
    while (s_end < Text.length) {
        if (regexec(&regex_dont, Text.ptr + s_start, 1, match_dont, 0) != 0) {
            // failed to find a dont()
            s_end = Text.length;
        } else {
            // if regexec was successful
            s_end = s_start + match_dont[0].rm_eo;
        }

        // string "slice" s_start to s_end
        char tmp = Text.ptr[s_end];
        Text.ptr[s_end] = '\0'; // insert so regexec knows at s_end to stop
        total = total + find_muls(Text.ptr, s_start, s_end, &regex_mul, match_mul);
        Text.ptr[s_end] = tmp;

        // now we find update start with offset end of next do()
        if (regexec(&regex_do, Text.ptr + s_end, 1, match_do, 0) != 0) {
            // no do() found so all remaining mul() invalid
            break;
        }
        s_start = s_end + match_do[0].rm_eo;
    }

    printf("%ld\n", total);

    // free things
    free_string(Text);
    regfree(&regex_mul);
    regfree(&regex_dont);
    regfree(&regex_do);
}

int64_t find_muls(char* string, int64_t offset_start, int64_t offset_end, regex_t* regex_mul, regmatch_t* match_mul)
{
    char buffer[MAX_DIGIT];

    int64_t total = 0;
    while (offset_start < offset_end) {
        if (regexec(regex_mul, string + offset_start, 3, match_mul, 0) != 0) {
            break;
        }

        int s;
        int e;
        int num = 1;
        // gets the 2 subexpressions in match_mul[i] and multiplies them both
        for (int i = 1; i < 3; ++i) {
            s = match_mul[i].rm_so;
            e = match_mul[i].rm_eo;
            memcpy(buffer, string + offset_start + s, e - s);
            buffer[e - s] = '\0'; // if previous write to buffer is still there
            num = num * atoi(buffer);
        }
        total += num;
        offset_start += e; // advance start pos of slice
    }

    return total;
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