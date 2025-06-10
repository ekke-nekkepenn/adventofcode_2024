#include <stdio.h>
#include <stdint.h>

// StringView Lib from tsoding https://github.com/tsoding/sv
#define SV_IMPLEMENTATION
#include "../sv.h"

#define FILENAME "input.txt"
#define CAP 20

// ARRAY STUFF
typedef struct Int64Array
{
    int64_t *start;
    int len;
    int cap;
} Int64Array;

// array methods
bool append_int64(Int64Array *a, int64_t v);

typedef struct Node
{
    int64_t value;
    struct Node *left;  // add
    struct Node *right; // multiply
} Node;

typedef struct Context
{
    const int64_t value;
    bool found;
} Context;

// Node methods
void populate_tree(Node *current, int level, Int64Array *line);
void free_nodes(Node *current_node);
void compare_leaf_nodes(Node *current_node, Context *context);

int64_t part1(String_View *sv);
int64_t part2(String_View *sv);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        return 1;
    }

    FILE *file = fopen(FILENAME, "r");
    if (!file)
        return 20;

    // get count of chars in file
    fseek(file, 0, SEEK_END);
    int64_t count = ftell(file);
    rewind(file);

    // we need "data" because we cannot fread or free sv.data it's a "const char*"
    char *data = malloc(sizeof(char) * count); // free THIS later
    fread(data, sizeof(char), count, file);

    String_View sv = (String_View){.data = data, .count = count};
    fclose(file);

    int64_t result = 0;

    if (argv[1][0] == '1')
    {
        result = part1(&sv);
    }

    else if (argv[1][0] == '2')
    {
        result = part2(&sv);
    }

    else
    {
        printf("Usage: ./<progname.c> [1, 2]");
    }

    // DONT FORGET THIS
    free(data);

    printf("Result of Part %c: %ld\n", argv[1][0], result);
    return 0;
}

int64_t part1(String_View *sv)
{
    int64_t result = 0;

    Int64Array line = (Int64Array){
        .start = malloc(sizeof(int64_t) * CAP),
        .len = 0,
        .cap = CAP};

    // Iterate over each line until no more chars left
    while (sv->count > 0)
    {
        String_View sv_line = sv_chop_by_delim(sv, '\n');
        int64_t test_value = sv_to_u64(sv_chop_by_delim(&sv_line, ' ')); // NOT to be confused with var "result"
        // printf(SV_Fmt "\n", SV_Arg(sv_line));

        // put nums into a array
        while (sv_line.count > 0)
        {
            int64_t num = (int64_t)sv_to_u64(sv_chop_by_delim(&sv_line, ' '));
            append_int64(&line, num);
        }

        // how do we populate our tree?
        Node *root = malloc(sizeof(Node));
        root->value = line.start[0];
        root->left = NULL;
        root->right = NULL;

        populate_tree(root, 0, &line);
        Context cxt = (Context){.value = test_value, .found = false};
        compare_leaf_nodes(root, &cxt);

        if (cxt.found)
            result = result + test_value;

        free_nodes(root);
        line.len = 0; // reset
    }

    // Free Int64Array
    free(line.start);
    line.start = NULL;
    return result;
}

int64_t part2(String_View *sv)
{
    int64_t result = 0;
    // solution here
    return result;
}

bool append_int64(Int64Array *a, int64_t v)
{
    if (a->len < (a->cap))
    {
        a->start[a->len] = v;
        a->len++;
        return true;
    }
    printf("No more room in array");
    return false;
}

void populate_tree(Node *current, int level, Int64Array *line)
{
    ++level;
    if (level == line->len)
    {
        return;
    }

    current->left = malloc(sizeof(Node));
    current->right = malloc(sizeof(Node));
    if (!current->left || !current->right)
    {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }

    current->left->value = current->value + line->start[level];
    current->left->left = NULL;
    current->left->right = NULL;

    current->right->value = current->value * line->start[level];
    current->right->left = NULL;
    current->right->right = NULL;

    // printf("line len: %d\n", line->len);
    // printf("level: %d\n", level);
    // printf("left: %ld | right: %ld\n", current->left->value, current->right->value);

    populate_tree(current->left, level, line);
    populate_tree(current->right, level, line);
}

void free_nodes(Node *current_node)
{
    // Check if we reached a leaf node
    if (current_node == NULL)
    {
        return;
    }

    free_nodes(current_node->left);
    free_nodes(current_node->right);

    free(current_node);
    current_node = NULL;

    // recursive call
    // post order
}

void compare_leaf_nodes(Node *current_node, Context *context)
{

    if (current_node == NULL)
        return;

    compare_leaf_nodes(current_node->left, context);
    compare_leaf_nodes(current_node->right, context);

    // printf("%ld\n", current_node->value);

    if (context->found == false && current_node->value == context->value)
    {
        // printf("\tFound matching value: %ld (%ld)\n", current_node->value, context->value);
        context->found = true;
    }
}