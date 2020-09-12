#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mylib.h"
#include "tree.h"

/**
 * Main program file, managing command line arguments and interfacing with Tree
 * ADT
 * @author Sean Moir
 * @author Jakob Harbey
 * @author Fin Mountford
 */

/**
 * Prints the frequency and value of a node given to it
 * @param freq: frequency of node
 * @param word: value of node
 */
static void print_info(int freq, char *word)
{
    printf("%-4d %s\n", freq, word);
}

int main(int argc, char *argv[])
{
    const char *optstring = "c:df:orh";
    char option, input[255], *f_filename;
    int c_option, d_option, f_option, o_option, r_option, h_option;
    int unknown_words;
    FILE *c_file, *o_file;
    clock_t fill, search;
    tree t;

    while ((option = getopt(argc, argv, optstring)) != EOF)
    {
        switch (option)
        {
        case 'c':
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
        case 'r':
            r_option = 1;
            break;
        default:
            h_option = 1;
        }
    }

    /* option h */
    if (h_option == 1)
    {
        printf("Help - A list of options and the actions they perform\n");

        printf("-c filename : Check the spelling of words in filename using ");
        printf("words read from stdin as the dictionary.\n");

        printf("-d\n");
        printf("-f filename\n");
        printf("-o\n");
        printf("-r\n");
        printf("-h\n");

        /* dont create tree or add any values as help menu was invoked, print
         * help menu and terminate 
         */
        return EXIT_SUCCESS;
    }

    /* Check if want a BST or RBT*/
    t = r_option == 0 ? tree_new(BST) : tree_new(RBT);

    /* Read stdin into the tree */
    fill = clock();
    while (getword(input, sizeof input, stdin) != EOF)
    {
        t = tree_insert(t, input);
    }
    fill = clock() - fill;

    /* option c*/
    if (c_option == 1)
    {
        c_file = open_file(optarg, "r");
        unknown_words = 0;

        search = clock();
        while (getword(input, sizeof input, c_file) != EOF)
        {
            if (tree_search(t, input) == 0)
            {
                fprintf(stdout, "%s\n", input);
                unknown_words++;
            }
        }
        search = clock() - search;

        fclose(c_file);
        fprintf(stderr, "Fill time\t: %f\n", (fill) / (double)CLOCKS_PER_SEC);

        fprintf(stderr, "Search time\t: %f\n",
                (search) / (double)CLOCKS_PER_SEC);

        fprintf(stderr, "Unknown words = %d\n", unknown_words);

        /*
         * ignore option d, o, f and operate in dictionary mode, free tree as
         * program is terminating before EOF
         */
        tree_free(t);
        return EXIT_SUCCESS;
    }

    /* option d*/
    if (d_option == 1)
    {
        printf("%d\n", tree_depth(t));

        /* only perform tree depth, free tree as terminating before EOF */
        tree_free(t);
        return EXIT_SUCCESS;
    }

    /* option o & f*/
    if (o_option == 1)
    {
        if (f_option == 0)
        {
            f_filename = "tree-view.dot";
        }
        else
        {
            f_filename = emalloc((strlen(optarg) + 1) * sizeof f_filename);
            strcpy(f_filename, optarg);
        }

        o_file = open_file(f_filename, "w");
        printf("Creating dot file '%s'\n", f_filename);
        tree_output_dot(t, o_file);
        fclose(o_file);
        free(f_filename);
    }

    /*
     * perform normal operation aka (no -h, -c, -d), print tree preorder with
     * frequencies for nodes, free tree and terminate
     */
    tree_preorder(t, print_info);
    tree_free(t);
    return EXIT_SUCCESS;
}
