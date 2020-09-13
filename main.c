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
 *
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

/**
 * Free's all resources used by the main program, called before returning from
 * main
 *
 * @param c_file -c arguement file pointer
 * @param o_file -o arguement file pointer
 * @param t tree ADT
 * @param f_filename -f arguement filename
 */
void free_resources(FILE *c_file, FILE *o_file, tree t, char *f_filename)
{
    if (c_file != NULL)
    {
        fclose(c_file);
    }
    if (o_file != NULL)
    {
        fclose(o_file);
    }
    if (strcmp(f_filename, "") != 0 && f_filename)
    {
        free(f_filename);
    }
    if (t != NULL)
    {
        tree_free(t);
    }
}

int main(int argc, char *argv[])
{
    const char *optstring = "c:df:orh";
    char option, input[255], *f_filename = "";
    int c_option, d_option, f_option, o_option, r_option, h_option;
    int unknown_words;
    FILE *c_file = NULL, *o_file = NULL;
    clock_t fill, search;
    tree t = NULL;

    while ((option = getopt(argc, argv, optstring)) != EOF)
    {
        switch (option)
        {
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
        printf("Help - A list of options and the actions they perform\n\n");

        printf("-c\t<filename>\tCheck the spelling of words in filename ");
        printf("using words read from stdin as the dictionary.\n");

        printf("-d\t\t\tDisplay the height of the tree after insertion\n");

        printf("-f\t<filename>\toutput dot notation of tree to <filename> ");
        printf("used in combination with -o\n");

        printf("-o\t\t\toutput dot notation of tree to ./tree-view.dot ");
        printf("unless specified otherwise by -f\n");

        printf("-r\t\t\tUse RBT for data over BST \n");
        printf("-h\t\t\tHelp menu\n");

        /* dont create tree or add any values as help menu was invoked, print
         * help menu, free any resources and terminate
         */
        free_resources(c_file, o_file, t, f_filename);
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
    if(r_option == 1)
    {
        t = set_black_root(t);
    }
    fill = clock() - fill;

    /* option c*/
    if (c_option == 1)
    {
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

        fprintf(stderr, "Fill time\t: %f\n", (fill) / (double)CLOCKS_PER_SEC);

        fprintf(stderr, "Search time\t: %f\n",
                (search) / (double)CLOCKS_PER_SEC);

        fprintf(stderr, "Unknown words = %d\n", unknown_words);

        /*
         * ignore option d, o, f and operate in dictionary mode, free resoucrces
         * as program is terminating before EOF
         */
        free_resources(c_file, o_file, t, f_filename);
        return EXIT_SUCCESS;
    }

    /* option d*/
    if (d_option == 1)
    {
        printf("%d\n", tree_depth(t));

        /* only perform tree depth, free resources as terminating before EOF */
        free_resources(c_file, o_file, t, f_filename);
        return EXIT_SUCCESS;
    }

    /* option o & f*/
    if (o_option == 1)
    {
        if (f_option == 0)
        {
            f_filename = "tree-view.dot";
        }
        o_file = open_file(f_filename, "w");
        printf("Creating dot file '%s'\n", f_filename);
        tree_output_dot(t, o_file);
    }

    /*
     * perform normal operation aka (no -h, -c, -d), print tree preorder with
     * frequencies for nodes, free resources and terminate
     */
    tree_preorder(t, print_info);
    free_resources(c_file, o_file, t, f_filename);
    return EXIT_SUCCESS;
}
