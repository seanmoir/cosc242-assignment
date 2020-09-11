#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "tree.h"
#include "mylib.h"

static void print_info(int freq, char *word) {
    printf("%-4d %s\n", freq, word);
}

static void print_key(int freq, char *word) {
    printf("%s\n", word);
}

int main(int argc, char *argv[]) {

    const char *optstring = "c:df:orh";
    char option;
    char *input;
    tree t;
    int c_option = 0, d_option = 0, f_option = 0,
        o_option = 0, r_option = 0, h_option = 0;
    int unknown_words;
    FILE *infile;

    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'c':
                /* Safely open file*/
                if (NULL == (infile = fopen(optarg, "r"))) {
                    fprintf(stderr, "Can't find file '%s'\n", optarg);
                    return EXIT_FAILURE;
                }
                c_option = 1;
                printf("%s", optarg);
                break;
            case 'd':
                d_option = 1;
                break;
            case 'f':
                f_option = 1;
                break;
            case 'o':
                o_option = 1;
                break;
            case 'r' :
                r_option = 1;
                break;
            case 'h' :
                h_option = 1;
                break;
            default:
                printf("Invalid option. Please use -h for help\n");
        }
    }
    
    /* Check if tree is a BST or RBT*/
    if (r_option == 0) {
        t = tree_new(BST);
    } else {
        t = tree_new(RBT);
    }

    /* If -c is given, ignore -o and -d */
    if (c_option == 1) {
        d_option = 0;
        o_option = 0;
    }

    /* Read stdin into the tree */
    

    if (h_option == 1) {
        printf("Help message describing how to use the program.\n");
    }

    if (c_option == 1) {
        input = malloc(100 * sizeof input);
        unknown_words = 0;
        
        /**/
        
        
        /* Insert stdin to tree*/
        while (getword(input, 99, stdin) != EOF) {
            t = tree_insert(t, input);
        }

        /* Read each word from filename*/
        while (getword(input, 99, infile) != EOF) {
            if (tree_search(t, input) == 0) {
                fprintf(stdout, "%s\n", input);
                unknown_words++;
            }
        }

        fclose(infile);

        fprintf(stderr, ""); /*fill time and search time*/ 
        fprintf(stderr, "");
        fprintf(stderr, "Unknown words = %d\n", unknown_words);
        
    }

    tree_inorder(t, print_key);
    
    return EXIT_SUCCESS;
}
