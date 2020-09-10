#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

static void print_key(int freq, char *word)
{
    printf("%-4d %s\n", freq, word);

}

int main()
{
    tree b = tree_new(RBT);
    char s[256];
    while (1 == scanf("%255s", s))
    {
        b = tree_insert(b, s);
    }
    printf("INORDER\n");
    tree_inorder(b, print_key);
    printf("\n\n");
    printf("PREORDER\n");
    tree_preorder(b, print_key);
    printf("\nTREE DEPTH====\n%d\n", tree_depth(b));

    tree_free(b);
    return 0;
}
