#ifndef MY_STRING_H
#define MY_STRING_H

#include <stddef.h>

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} my_string;

/**
 * Создает новую пустую строку
 */
my_string my_string_create(void);

my_string my_string_create_with_capacity(size_t initial_capacity);

/**
 * Создает строку из С-строки
 */
my_string my_string_from_cstr(const char *cstr);

/**
 * Освобождает память, выделенную для строки
 */
void my_string_destroy(my_string *str);

/**
 * Добавляет символ в конец строки
 */
void my_string_append_char(my_string *str, char c);

/**
 * Добавляет С-строку в конец строки
 */
void my_string_append_cstr(my_string *str, const char *cstr);

/**
 * Добавляет одну строку в другую строку в конец строки
 */
void my_string_append_my_string(my_string *str, const my_string *other);

/**
 * Возвращает символ по индексу
 */
char my_string_at(const my_string *str, size_t index);

/**
 * Возвращает длину строки
 */
size_t my_string_length(const my_string *str);

/**
 * Возвращает указатель на данные строки (как C-строка)
 */
const char *my_string_cstr(const my_string *str);

/**
 * Очищает содержимое строки, но сохраняет выделенную память
 */
void my_string_clear(my_string *str);

/**
 * Копирует одну строку в другую
 */
my_string my_string_copy(const my_string *src);

void my_string_print(const my_string *str);


size_t my_strlen(const char *cstr);
int my_strcmp(const char *str1, const char *str2);
void my_strcpy(char *dest, const char *src);

#endif // MY_STRING_H