#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "mylib.h"

/**
 * Containers helper functions used in main program and ADT
 *
 * @author Jakob Harvey
 */

/**
 * Error checking memory allocation function
 *
 * @param s size of contiguous memory needed
 * @return pointer to location in memory
 */
void *emalloc(size_t s) {
    void *result = malloc(s);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * Error checking memory reallocation function
 *
 * @param s size of contiguous memory needed
 * @param p original memory pointer
 *
 * @return pointer to new location in memory
 */
void *erealloc(void *p, size_t s) {
    void *result = realloc(p, s);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * Provided function, reads in words
 *
 * @param s output string
 * @param limit string limit
 * @param stream input stream/file
 *
 * @return number words read
 */
int getword(char *s, int limit, FILE *stream) {
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);
    /* skip to the start of the word */
    while (!isalnum(c = getc(stream)) && EOF != c)
        ;
    if (EOF == c) {
        return EOF;
    } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
        *w++ = tolower(c);
    }
    while (--limit > 0) {
        if (isalnum(c = getc(stream))) {
            *w++ = tolower(c);
        } else if ('\'' == c) {
            limit++;
        } else {
            break;
        }
    }
    *w = '\0';
    return w - s;
}

/**
 * Error checking file read/write function
 *
 * @param filename name of file
 * @arg read/write argument
 *
 * @return file pointer
 */
FILE *open_file(char *filename, char *arg) {
    FILE *result;
    if (NULL == (result = fopen(filename, arg))) {
        fprintf(stderr, "Can't find file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }
    return result;
}
