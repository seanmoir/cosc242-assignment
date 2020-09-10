#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "tree.h"
#include "mylib.h"

static void print_key(int freq, char *word)
{
    printf("%-4d %s\n", freq, word);
}

int main(int argc, char **argv)
{
    char word[256];
    char option;
    const char *optstring = "c:df:orh";
    tree t = tree_new(RBT);
    
    while ((option = getopt(argc, argv, optstring)) != EOF)
    {
        switch (option)
        {
        case 'c':
            /* spell checker */
            break;
        case 'd':
            /* print tree depth */
            break;
        case 'f':
            /* do something else */
            break;
        case 'o':
            /* output tree in DOT form */
            break;
        case 'r':
            /* use RBT */
            break;
        case 'h':
            /* help menu */
            break;
        default:
            /* if an unknown option is given */
            break;
        }
    }

    while (getword(word, sizeof word, stdin) != EOF)
    {
        t = tree_insert(t, word);
    }
    return 0;
}
