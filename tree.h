#ifndef TREE_H_
#define TREE_H_

typedef struct tree_node *tree;
typedef enum { RED, BLACK} rbt_colour;
typedef enum { BST, RBT } tree_t;

extern tree tree_new(tree_t type);
extern tree tree_free(tree b);
extern tree tree_insert(tree b, char *key);
extern int tree_search(tree b, char *key);
extern void tree_inorder(tree b, void f(char *s));
extern void tree_preorder(tree b, void f(char *s));

#endif
