#include "dialog.h"
#include "string_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

my_string my_readline(void) {
    my_string result = my_string_create();
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    // Читаем строку через scanf с форматом для чтения всей строки до перевода строки
    if (scanf(" %4095[^\n]", buffer) != 1) {
        // Удаляем символ конца строки, если он есть
        size_t len = strlen(buffer);
        printf("Line size: %ld\n", len); // Debug print
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Копируем в my_string
        my_string_append_cstr(&result, buffer);
    }
    return result;
}

void run_dialog(void) {
    printf("Введите строки (Ctrl+D для завершения):\n\n");
    
    while (1) {
        // Читаем входную строку
        my_string input = my_readline();
        
        // Проверяем EOF
        if (feof(stdin)) {
            my_string_destroy(&input);
            break;
        }
        
        // Обрабатываем строку
        my_string output = process_string(&input);
        
        // Выводим входную строку в кавычках
        printf("Входная:  \"%s\"\n", my_string_cstr(&input));
        
        // Выводим выходную строку в кавычках
        printf("Выходная: \"%s\"\n", my_string_cstr(&output));
        printf("\n");
        
        // Освобождаем память
        my_string_destroy(&input);
        my_string_destroy(&output);
    }
    
    printf("Конец ввода.\n");
}