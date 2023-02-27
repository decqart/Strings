#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct {
    char *str;
    size_t len;
} Str;

#define str_print(x) puts(x.str);

Str str_init(char *str)
{
    Str string;
    string.str = strdup(str);
    string.len = strlen(str);
    return string;
}

void str_add(Str *dest, Str src)
{
    if (dest->str == NULL) return;
    size_t new_len = dest->len+src.len;
    dest->str = realloc(dest->str, new_len+1);
    char *end = &dest->str[dest->len];
    strcpy(end, src.str);

    dest->str[new_len+1] = '\0';
}

void str_cat(Str *dest, char *src)
{
    if (dest->str == NULL) return;
    size_t new_len = dest->len+strlen(src);
    dest->str = realloc(dest->str, new_len+1);
    char *end = &dest->str[dest->len];
    strcpy(end, src);

    dest->str[new_len+1] = '\0';
}

void str_destroy(Str *str)
{
    if (str->str == NULL) return;
    free(str->str);
    str->len = 0;
}

#endif /* STR_H */