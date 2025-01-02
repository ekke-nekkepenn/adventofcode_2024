// https://adventofcode.com/2024/day/
#include <stdio.h> // fread() fclose() printf()
#include <stdlib.h> // atoi() malloc() free()
#include <string.h> // memcpy

#define FILENAME "input"
// structure of our input 1000 lines each 14 chars and 2 numbers digit size 5
#define IPT_SIZE 1000 
#define LINE_LEN 15
#define DIGIT_LEN 5


// prototypes
void part1(FILE *file);
void part2(FILE *file);
void fill_lists(int left[], int right[], FILE *file);
void bubble_sort_asc(int array[], int len);

// vars
char num[DIGIT_LEN + 1];
char line[LINE_LEN];

typedef struct node {
    int num;
    struct node *next;
} node;
  

int main() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        return 1;
    }

    num[DIGIT_LEN] = '\0'; // needed for atoi()
    int select = 0;

    select ? part1(file) : part2(file);
}


void part1(FILE *file) {
    int left[IPT_SIZE];
    int right[IPT_SIZE];
    
    fill_lists(left, right, file);

    bubble_sort_asc(left, IPT_SIZE);
    bubble_sort_asc(right, IPT_SIZE);

    int distance = 0;
    int l, r;

    for (int i = 0; i < IPT_SIZE; i++) {
        l = left[i];
        r = right[i];

        if (l > r) distance += l - r;
        else distance += r - l;

    }

    printf("%d\n", distance);
    return;
}

void part2(FILE *file) {
    int left[IPT_SIZE];
    int right[IPT_SIZE];

    fill_lists(left, right, file);

    int similarity_score = 0;
    for (int i = 0; i < IPT_SIZE; ++i) {

        int occurence = 0;
        for (int j = 0; j < IPT_SIZE; ++j) {
            if (left[i] == right[j]) {
                ++occurence;
            }
        }
        similarity_score += (occurence * left[i]); 
    }

    printf("%d\n", similarity_score);

    return;
}

void fill_lists(int left[], int right[], FILE *file) {
    for (int i=0; i < IPT_SIZE; i++) {
        fgets(line, LINE_LEN, file);
        memcpy(num, line, DIGIT_LEN);
        left[i] = atoi(num);
        memcpy(num, (line + DIGIT_LEN + 3), DIGIT_LEN); // the next number starts at index digit_len + 3
        right[i] = atoi(num);
    }
}

void bubble_sort_asc(int array[], int len) {
    int tmp;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j + i < len - 1; j++) {
            if (array[j] > array[j+1]) {
                tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
            }
        }
    }
}




