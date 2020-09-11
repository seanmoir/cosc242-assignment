#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <time.h>

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
    FILE *c_file;
    FILE *f_file;
    clock_t fill_start, fill_end, search_start, search_end;

    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'c':
                /* Safely open file*/
                if (NULL == (c_file = fopen(optarg, "r"))) {
                    fprintf(stderr, "Can't find file '%s'\n", optarg);
                    return EXIT_FAILURE;
                }
                c_option = 1;
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
        input = emalloc(100 * sizeof input);
        unknown_words = 0;

        /* Insert stdin to tree*/
        fill_start = clock();
        while (getword(input, 99, stdin) != EOF) {
            t = tree_insert(t, input);
        }
        fill_end = clock();

        /* Read each word from filename*/
        search_start = clock();
        while (getword(input, 99, c_file) != EOF) {
            if (tree_search(t, input) == 0) {
                fprintf(stdout, "%s\n", input);
                unknown_words++;
            }
        }
        search_end = clock();

        fclose(c_file);
        free(input);

        fprintf(stderr, "Fill time\t: %f\n",
                (fill_end - fill_start) / (double)CLOCKS_PER_SEC);
        fprintf(stderr, "Search time\t: %f\n",
                (search_end - search_start) / (double)CLOCKS_PER_SEC);
        fprintf(stderr, "Unknown words = %d\n", unknown_words);
        
    }

    if (d_option == 1) {
        printf("%d\n", tree_depth(t));
        o_option = 0;
        r_option = 0;
        h_option = 0;
    }

    if (o_option == 1) {
        /*do dot stuff*/
        if (f_option == 1) {           
        } else {
        }
    }

    if (h_option == 1) {
        printf("Help - A list of options and the actions they perform\n");
        printf("-c filename : Check the spelling of words in filename using words read from stdin as the dictionary.\n");
        printf("-d\n");
        printf("-f filename\n");
        printf("-o\n");
        printf("-r\n");
        printf("-h\n");
    }

    tree_free(t);
    
    return EXIT_SUCCESS;
}
