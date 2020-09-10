#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define IS_BLACK(x) ((NULL == (x)) || (BLACK == (x)->colour))
#define IS_RED(x) ((NULL != (x)) && (RED == (x)->colour))

/*
 * key: value
 * left: pointer to left child node
 * right: pointer to right child node
 * rbt_colour: colour of node (RED, BLACK) enum
 */
struct tree_node
{
    char *key;
    tree left;
    tree right;
    rbt_colour colour;
    int frequency;
};

static tree_t tree_type;

static tree right_rotate(tree r)
{
    tree temp = r->left;
    r->left = temp->right;
    temp->right = r;
    return temp;
}

static tree left_rotate(tree r)
{
    tree temp = r->right;
    r->right = temp->left;
    temp->left = r;
    return temp;
}

static tree rbt_fix(tree r)
{
    if (IS_RED(r->left) && IS_RED(r->left->left))
    {

        if (IS_RED(r->right))
        {
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        }
        else
        {
            r = right_rotate(r);
            r->colour = BLACK;
            r->right->colour = RED;
        }
    }
    else if (IS_RED(r->left) && IS_RED(r->left->right))
    {

        if (IS_RED(r->right))
        {
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        }
        else
        {
            r->left = left_rotate(r->left);
            r = right_rotate(r);
            r->colour = BLACK;
            r->right->colour = RED;
        }
    }
    else if (IS_RED(r->right) && IS_RED(r->right->left))
    {

        if (IS_RED(r->left))
        {
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        }
        else
        {
            r->right = right_rotate(r->right);
            r = left_rotate(r);
            r->colour = BLACK;
            r->left->colour = RED;
        }
    }
    else if (IS_RED(r->right) && IS_RED(r->right->right))
    {

        if (IS_RED(r->left))
        {
            r->colour = RED;
            r->left->colour = BLACK;
            r->right->colour = BLACK;
        }
        else
        {
            r = left_rotate(r);
            r->colour = BLACK;
            r->left->colour = RED;
        }
    }
    return r;
}

/*returns null node to represent empty new tree*/
tree tree_new(tree_t type)
{
    tree_type = type;
    return NULL;
}

/*
 * search for node based on value
 *
 * param b: (sub)tree to start at
 * param key: value to search for
 *
 * return: returns 0 if not found, 1 if found
 */
int tree_search(tree b, char *key)
{
    /*
     * if leaf is reached and key is not found, then must not be in tree, thus
     * return 0 for false
     */
    if (b == NULL)
    {
        return 0;
    }

    /* 
     * if current nodes value is more than value being searched, then search left
     * subtree
     *
     * else if nodes value is less than value being searched, then search right
     * subtree
     */
    if (strcmp(b->key, key) > 0)
    {
        return tree_search(b->left, key);
    }
    else if (strcmp(b->key, key) < 0)
    {
        return tree_search(b->right, key);
    }

    /* value found, return 1 for true */
    return 1;
}

/*
 * insert function 
 *
 * b: (sub)tree to insert into
 * key: value to insert
 *
 * return: the modified tree
 */
tree tree_insert(tree b, char *key)
{
    static int count = 0;

    /*if leaf is found allocate new node and insert value into node */
    if (b == NULL)
    {
        b = malloc(sizeof *b);
        b->left = NULL;
        b->right = NULL;
        b->key = malloc((strlen(key) + 1) * sizeof key[0]);
        b->key = strcpy(b->key, key);
        b->frequency = 1;
        b->colour = count == 0 ? BLACK : RED;
        count++;
        if (tree_type == RBT)
        {
            return rbt_fix(b);
        }
        return b;
    }

    /* 
     * if current nodes value is more than value being inserted, then insert
     * into  left subtree, 
     *
     * else if nodes value is less than value being inserted, then insert into
     * right subtree
     */
    if (strcmp(b->key, key) > 0)
    {
        b->left = tree_insert(b->left, key);
    }
    else if (strcmp(b->key, key) < 0)
    {
        b->right = tree_insert(b->right, key);
    }
    else
    {
        b->frequency++;
    }

    /* return modified tree */
    if (tree_type == RBT)
    {
        return rbt_fix(b);
    }
    return b;
}

/*
 * print function for inorder printing
 *
 * b: (sub)tree to print
 * f: print function used
 */
void tree_inorder(tree b, void f(char *s))
{
    char *tmp;
    /* if leaf then return to stack */
    if (b == NULL)
    {
        return;
    }

    /* call self on left subtree recursively */
    tree_inorder(b->left, f);

    /* call print method on current node */
    tmp = malloc(strlen(b->key) + 20 * sizeof tmp[0]);
    if (tree_type == RBT)
    {
        strcpy(tmp, IS_BLACK(b) ? "black:\t" : "red:\t");
        strcat(tmp, b->key);
        f(tmp);
        free(tmp);
    }
    /* Maybe we do this instead of assigning memory to a string and concatenating them?
    if (tree_type == RBT) {
        if (IS_RED(b)) {
            printf("red: ");
        } else {
        printf("black: ");
        }
    }
    f(b->key);
    */
    else
    {
        f(b->key);
    }

    /* call self on right subtree recursively */
    tree_inorder(b->right, f);
}

/*
 * print function for preorder printing
 *
 * b: (sub)tree to print
 * f: print function used
 */
void tree_preorder(tree b, void f(char *s))
{
    char *tmp;
    /* if leaf then return to stack */
    if (b == NULL)
    {
        return;
    }

    /* call print method on current node */
    tmp = malloc(strlen(b->key) + 20 * sizeof tmp[0]);
    if (tree_type == RBT)
    {
        strcpy(tmp, IS_BLACK(b) ? "black:\t" : "red:\t");
        strcat(tmp, b->key);
        f(tmp);
        free(tmp);
    }
    else
    {
        f(b->key);
    }

    /* call self on left subtree recursively */
    tree_preorder(b->left, f);

    /* call self on right subtree recursively */
    tree_preorder(b->right, f);
}

/*
 * tree destruction function
 * frees nodes and nodes key recursively
 *
 * b: node to free
 *
 * return: null pointer - for checking purposes (could be void function otherwise)
 */
tree tree_free(tree b)
{
    /* if leaf met return to stack */
    if (b == NULL)
    {
        return b;
    }

    /* free left and right subtrees recursively */
    tree_free(b->left);
    tree_free(b->right);

    /* free node and it's key */
    free(b->key);
    free(b);
    return b;
}
