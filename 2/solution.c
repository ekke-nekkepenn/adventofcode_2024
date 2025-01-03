#include <stdio.h> // printf scanf fopen
#include <string.h>
#include <stdlib.h> // atoi()

#define IPT_SIZE 1000
#define MAX_LINE_LEN 25

// prototypes

/*
typedef struct node {
    int num;
    struct node *next;
} node;
*/

int main(void) {
    FILE *file = fopen("input", "r");
    if (!file) {
        return -1;
    }

    // first we need to convert our input

    int sim_score = 0;

    char line[MAX_LINE_LEN];
    char *ptr_chr;
    char *token;
    char delim[] = " ";
    for (int i = 0; i < IPT_SIZE; i++) {
        ptr_chr = fgets(line, MAX_LINE_LEN, file);


        token = strtok(line, delim);

        while (token != NULL) {
            
            printf("%s ", token);
            token = strtok(NULL, delim); // Use NULL when calling strtok again on same str

        }


    }
    return 0;
}