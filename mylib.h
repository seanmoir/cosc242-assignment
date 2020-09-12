#ifndef mylib_h
#define mylib_h

extern void *emalloc(size_t);
extern void *erealloc(void *, size_t);
extern unsigned int word_to_int(char *word);
extern int getword(char *s, int limit, FILE *stream);
extern FILE *open_file(char *filename, char *arg);

#endif
