#ifndef STR_H
#define STR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    char *str;
    size_t len;
} Str;

#define NULLSTR (Str) { NULL, 0 }
#define str_print(x) puts(x.str);
#define strndup _strndup

size_t _strnlen(const char *str, size_t maxlen)
{
    for (size_t len = 0; len < maxlen; ++len)
    {
        if (str[len] == '\0')
            return len;
    }
    return maxlen;
}

char *_strndup(const char *s, size_t n)
{
    size_t minlen = _strnlen(s, n);
    char *dup = malloc((minlen+1)*sizeof(char));
    if (dup != NULL)
        strncpy(dup, s, minlen+1);
    return dup;
}

Str str_init(char *str)
{
    size_t len = strlen(str);
    char *new = strndup(str, len);
    return (Str) { new, len };
}

Str str_num_init(char *str, size_t len)
{
    char *new = strndup(str, len);
    return (Str) { new, len };
}

void str_add(Str *dest, Str src)
{
    if (dest->str == NULL) return;
    size_t new_len = dest->len+src.len;
    dest->str = realloc(dest->str, new_len+1);
    if (dest->str == NULL) return;
    char *end = &dest->str[dest->len];
    strcpy(end, src.str);

    dest->len = new_len;
}

void str_fmt_add(Str *dest, const char *format, ...)
{
    va_list vlist;
    va_start(vlist, format);
    int fmtlen = vsnprintf(NULL, 0, format, vlist);
    va_end(vlist);

    if (fmtlen < 0) fmtlen = 0;
    size_t newlen = fmtlen+dest->len;
    dest->str = realloc(dest->str, newlen+1);
    if (dest->str == NULL) return;

    va_start(vlist, format);
    vsprintf(&dest->str[dest->len], format, vlist);
    va_end(vlist);

    dest->len = newlen;
}

void str_cat(Str *dest, char *src)
{
    if (dest->str == NULL) return;
    size_t new_len = dest->len+strlen(src);
    dest->str = realloc(dest->str, new_len+1);
    if (dest->str == NULL) return;
    char *end = &dest->str[dest->len];
    strcpy(end, src);

    dest->len = new_len;
}

Str str_substr(Str str, size_t start, size_t end)
{
    size_t len = end-start;
    char *new = malloc((len+1)*sizeof(char));

    if (new == NULL || str.str == NULL)
        return NULLSTR;

    char *sta = &str.str[start];
    strncpy(new, sta, len);
    return (Str) { new, len };
}

int32_t str_index(Str str, char *idx)
{
    if (str.str == NULL) return -1;
    size_t idxlen = strlen(idx);
    for (int i = 0; i < str.len; i++)
    {
        for (int j = 0; j < idxlen; j++)
        {
            if (str.str[i] == idx[j])
                return i;
        }
    }
    return -1;
}

void str_reverse(Str *str)
{
    if (str->str == NULL) return;
    char *tmp = strndup(str->str, str->len);
    if (tmp == NULL) return;
    for (int i = 0; i < str->len; i++)
    {
        str->str[i] = tmp[str->len-1-i];
    }
    free(tmp);
}

bool str_eq(Str left, Str right)
{
    if (left.str == NULL || right.str == NULL)
        return false;
    return !strcmp(left.str, right.str);
}

void str_destroy(Str *str)
{
    if (str->str == NULL) return;
    free(str->str);
    str->len = 0;
}

#undef strndup

#endif /* STR_H */
