#include "reorder_words.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int find_last_word_start(const my_string *str) {
    int len = str->length;
    int i = len - 1;
    
    while (i > 0 && str->data[i - 1] != ' ') {
        i--;
    }
    
    return i;
}

int ends_with_char(const char *word, int word_len, char target_char) {
    return word_len > 0 && word[word_len - 1] == target_char;
}

void append_word(my_string *buffer, const char *word) {
    if (buffer->length > 0) {
        my_string_append_char(buffer, ' ');
    }
    char *ptr = (char *)word;
    while (*ptr != '\0' && *ptr != ' ') {
        my_string_append_char(buffer, *ptr);
        ptr++;
    }
}

void collect_words(const my_string *str, char target_char, 
                   my_string *words_to_move, my_string *remaining) {
    size_t i = 0;
    while (i < str->length) {
        // Пропускаем пробелы
        while (i < str->length && str->data[i] == ' ') {
            i++;
        }
        
        if (i >= str->length) break;
        
        // Находим конец слова
        int word_start = i;
        while (i < str->length && str->data[i] != ' ') {
            i++;
        }
        
        int word_len = i - word_start;
        
        // Сортируем слово по категориям
        if (ends_with_char(&str->data[word_start], word_len, target_char)) {
            append_word(words_to_move, &str->data[word_start]);
        } else {
            append_word(remaining, &str->data[word_start]);
        }
    }
}

void reorder_words(my_string *str) {
    if (!str || str->length == 0) return;
    
    int last_word_start = find_last_word_start(str);
    char first_char_of_last = str->data[last_word_start];
    
    // Буферы для слов
    my_string words_to_move = my_string_create_with_capacity(str->length);
    my_string remaining = my_string_create_with_capacity(str->length);
    
    // Собираем слова в соответствующие буферы
    collect_words(str, first_char_of_last, &words_to_move, &remaining);
    
    my_string* result_string_ptr = &words_to_move;
    if (my_string_length(result_string_ptr) > 0) {
        if(my_string_length(&remaining) > 0) {
            my_string_append_cstr(&words_to_move, " ");
            my_string_append_my_string(&words_to_move, &remaining);
        }
    } else {
        result_string_ptr = &remaining;
    }
       
    strcpy(str->data, result_string_ptr->data);
    
    my_string_destroy(&words_to_move);
    my_string_destroy(&remaining);
}

