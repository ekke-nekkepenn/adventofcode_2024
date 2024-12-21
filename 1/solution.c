// https://adventofcode.com/2024/day/1
#include <ctype.h>
#include <stdio.h> // fread() fclose() printf()
#include <stdlib.h> // atoi() malloc() free()
#include <string.h>
#define FILENAME "input"
#define IPT_SIZE 1000
#define LINE_LEN 15
#define DIGIT_LEN 5

// prototypes
void bubble_sort_asc(int array[], int len);

int main(void) {

    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        return 1;
    }
    int left[IPT_SIZE];
    int right[IPT_SIZE];

    char num[DIGIT_LEN + 1]; // all numbers are 5 digits
    num[DIGIT_LEN] = '\0';

    char line[LINE_LEN];
    for (int i=0; i < IPT_SIZE; i++) {
        fgets(line, LINE_LEN, file);
        memcpy(num, line, DIGIT_LEN);
        left[i] = atoi(num);
        memcpy(num, line+8, DIGIT_LEN); // +8 because right number starts at index 8
        right[i] = atoi(num);
    }
    

    bubble_sort_asc(left, IPT_SIZE);
    bubble_sort_asc(right, IPT_SIZE);

//    for (int i = 0; i < 50; i++) {
//        printf("%d , %d\n", left[i], right[i]);
//    }

    // now find the distance btw elements
    int distance = 0;
    int l, r;

    for (int i = 0; i < IPT_SIZE; i++) {
        l = left[i];
        r = right[i];

        if (l > r) {
            distance += l - r;
        }

        else {
            distance += r - l;
        }

    }

    printf("%d\n", distance);

    return 0;
}


void bubble_sort_asc(int array[], int len) {
    // bubble sort
    int flag = 1;
    int i, j, temp, switched;
    while (flag) {
        switched = 0;
        i = 0;
        j = 1;
        for (;i < IPT_SIZE-1; i++, j++) {
            if (array[i] > array[j]) {
                // switches places
                temp = array[j];
                array[j] = array[i];
                array[i] = temp;

                // mark that switch happened
                if (switched == 0) {
                    switched = 1;
                }
            }
        }

        // end loop
        if (switched == 0) {
            flag = 0;
        }
    }

    return;
}

