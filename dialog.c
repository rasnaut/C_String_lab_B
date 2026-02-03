#include "dialog.h"
#include "string_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reorder_words.h"
#include <time.h>

#define BUFFER_SIZE 4096

my_string my_readline(void) {
    my_string result = my_string_create();
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    // Читаем строку через scanf с форматом для чтения всей строки до перевода строки
    if (scanf(" %4095[^\n]", buffer) != 0) {
        // Удаляем символ конца строки, если он есть
        size_t len = my_strlen(buffer);
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

    while (1) {
        printf("Введите строки (Ctrl + D для завершения):\n\n");
        // Читаем входную строку
        my_string input = my_readline();
        //my_string input = my_string_from_cstr(readline("Введите строку: "));
        if (input.length == 0 || feof(stdin)) {
            // Пустая строка или ошибка чтения
            my_string_destroy(&input);
            break;
        }
        
        clock_t t0 = clock();
        my_string output = process_string(&input);
        clock_t t1 = clock();
        
        printf("Входная:  \"%s\"\n", my_string_cstr(&input));
        printf("Выходная: \"%s\"\n", my_string_cstr(&output));
        clock_t t3 = clock();
        reorder_words(&output);
        clock_t t4 = clock();
        printf("Преобразованная: \"%s\"", my_string_cstr(&output));
        double time_spent = (double)(t1 - t0) / CLOCKS_PER_SEC;
        double time_spent_reorder = (double)(t4 - t3) / CLOCKS_PER_SEC;
        printf("\nВремя обработки: %.6f секунд\n", time_spent);
        printf("Время перестановки слов: %.6f секунд\n", time_spent_reorder);
        printf("\n");
        
        my_string_destroy(&input);
        my_string_destroy(&output);
    }
    
    printf("Конец ввода.\n");
}