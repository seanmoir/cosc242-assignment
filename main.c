#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <time.h>
#include <string.h>

#include "tree.h"
#include "mylib.h"

int main(int argc, char *argv[]) {

    const char *optstring = "c:df:orh";
    char option;
    char *input;
    char *f_filename = "";
    tree t;
    int c_option = 0, d_option = 0, f_option = 0,
        o_option = 0, r_option = 0, h_option = 0;
    int unknown_words;
    FILE *c_file = NULL;
    FILE *o_file;
    clock_t fill_start, fill_end, search_start, search_end;

    while ((option = getopt(argc, argv, optstring)) != EOF) {
        switch (option) {
            case 'c':
                c_file = open_file(optarg, "r");
                c_option = 1;
                break;
            case 'd':
                d_option = 1;
                break;
            case 'f':
                f_filename = emalloc((strlen(optarg) + 1) * sizeof f_filename);
                strcpy(f_filename, optarg);
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

    /* Read stdin into the tree */
    input = emalloc(100 * sizeof input);
    fill_start = clock();
    while (getword(input, 99, stdin) != EOF) {
        t = tree_insert(t, input);
    }
    fill_end = clock();

    /* option c*/
    if (c_option == 1) {      
        unknown_words = 0;

        search_start = clock();
        while (getword(input, 99, c_file) != EOF) {
            if (tree_search(t, input) == 0) {
                fprintf(stdout, "%s\n", input);
                unknown_words++;
            }
        }
        search_end = clock();

        fclose(c_file);

        fprintf(stderr, "Fill time\t: %f\n",
                (fill_end - fill_start) / (double)CLOCKS_PER_SEC);
        fprintf(stderr, "Search time\t: %f\n",
                (search_end - search_start) / (double)CLOCKS_PER_SEC);
        fprintf(stderr, "Unknown words = %d\n", unknown_words);

        /* If -c is given, ignore -d and -o*/
        d_option = 0;
        o_option = 0;        
    }

    if (d_option == 1) {
        printf("%d\n", tree_depth(t));
        o_option = 0;
        r_option = 0;
        h_option = 0;
    }

    if (o_option == 1) {
        if (f_option == 0) {
            f_filename = "tree-view.dot";
        }
        o_file = open_file(f_filename, "w");
        printf("Creating dot file '%s'\n", f_filename);
        tree_output_dot(t, o_file);
        fclose(o_file);
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

    free(input);
    tree_free(t);
    
    return EXIT_SUCCESS;
}
