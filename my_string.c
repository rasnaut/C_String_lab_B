#include "my_string.h"
#include <stdlib.h>
#include <stdio.h>

#define INITIAL_CAPACITY 16

my_string my_string_create(void) {
    my_string str;
    str.capacity = INITIAL_CAPACITY;
    str.length = 0;
    str.data = (char *)malloc(str.capacity);
    if (str.data != NULL) {
        str.data[0] = '\0';
    }
    return str;
}

my_string my_string_create_with_capacity(size_t initial_capacity)
{
    my_string str;
    str.capacity = initial_capacity;
    str.length = 0;
    str.data = (char *)malloc(str.capacity);
    if (str.data != NULL) {
        str.data[0] = '\0';
    }
    return str;
}

my_string my_string_from_cstr(const char *cstr) {
    my_string str = my_string_create();
    if (cstr != NULL) {
        my_string_append_cstr(&str, cstr);
    }
    return str;
}

void my_string_destroy(my_string *str) {
    if (str != NULL && str->data != NULL) {
        free(str->data);
        str->data = NULL;
        str->length = 0;
        str->capacity = 0;
    }
}

static void my_string_reserve(my_string *str, size_t new_capacity) {
    if (new_capacity > str->capacity) {
        char *new_data = (char *)realloc(str->data, new_capacity);
        if (new_data != NULL) {
            str->data = new_data;
            str->capacity = new_capacity;
        }
    }
}

void my_string_append_char(my_string *str, char c) {
    if (str == NULL || str->data == NULL) {
        return;
    }
    
    if (str->length + 1 >= str->capacity) {
        my_string_reserve(str, str->capacity * 2);
    }
    
    str->data[str->length] = c;
    str->length++;
    str->data[str->length] = '\0';
}

void my_string_append_cstr(my_string *str, const char *cstr) {
    if (str == NULL || str->data == NULL || cstr == NULL) {
        return;
    }

    size_t cstr_len = my_strlen(cstr);
    while (str->length + cstr_len >= str->capacity) {
        my_string_reserve(str, str->capacity * 2);
    }
    my_strcpy(str->data + str->length, cstr);
    str->length += cstr_len;
}

void my_string_append_my_string(my_string *str, const my_string *other)
{
    if (str == NULL || str->data == NULL || other == NULL || other->data == NULL) {
        return;
    }
    
    size_t other_len = other->length;
    while (str->length + other_len >= str->capacity) {
        my_string_reserve(str, str->capacity * 2);
    }

    my_strcpy(str->data + str->length, other->data);
    str->length += other_len;
}

char my_string_at(const my_string *str, size_t index) {
    if (str != NULL && str->data != NULL && index < str->length) {
        return str->data[index];
    }
    return '\0';
}

size_t my_string_length(const my_string *str) {
    if (str != NULL) {
        return str->length;
    }
    return 0;
}

const char *my_string_cstr(const my_string *str) {
    if (str != NULL && str->data != NULL) {
        return str->data;
    }
    return "";
}

void my_string_clear(my_string *str) {
    if (str != NULL && str->data != NULL) {
        str->length = 0;
        str->data[0] = '\0';
    }
}

my_string my_string_copy(const my_string *src) {
    if (src == NULL) {
        return my_string_create();
    }
    return my_string_from_cstr(my_string_cstr(src));
}

void my_string_print(const my_string *str) {
    if (str != NULL && str->data != NULL) {
        printf("%s\n", str->data);
    }
}

size_t my_strlen(const char *cstr)
{
    size_t len = 0;
    if (cstr != NULL) {
        while (cstr[len] != '\0' && cstr[len] != 0) {
            len++;
        }
    }
    return len;
}

int my_strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void my_strcpy(char *dest, const char *src)
{
    while ((*dest++ = *src++) != '\0');
}