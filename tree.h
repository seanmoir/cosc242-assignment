#ifndef TREE_H_
#define TREE_H_
#include <stdio.h>

/**
 * Tree header file
 * 
 * @author Sean Moir
 * @author Jakbo Harvey
 */

typedef struct tree_node *tree;

/**
 * @enum tree colour
 */
typedef enum { 
    RED, /* Red node */
    BLACK /* Black node */
} tree_colour;

/**
 * @enum tree type
 */
typedef enum tree_e { 
    BST, /* BST */
    RBT  /* RBT */
} tree_t;

extern tree tree_new(tree_t type);
extern tree tree_free(tree b);
extern tree tree_insert(tree b, char *key);
extern tree set_black_root(tree t);
extern int tree_search(tree b, char *key);
extern void tree_inorder(tree b, void f(char *s));
extern void tree_preorder(tree b, void f(int freq, char *word));
extern void tree_output_dot(tree t, FILE *out);
extern int tree_depth(tree b);

#endif
