#include <stdio.h>
#include <time.h>
#include "string_processing.h"
#include "my_string.h"
#include "reorder_words.h"
#include <string.h>


void big_string_benchmark_test(void) {
    const char *pattern =
        "alpha   beta\t\tgamma   delta   almanac   meta   "
        "omega   alfa   kolobok   abrakadabra   allegro   opera   allegretto   "
        "alchemy   beta   alpaca   panorama   al   ";

    // Собираем сырую строку в обычный C‑буфер
    char raw[1200]; // с запасом
    size_t len = 0;

    // Префиксные пробелы/табы
    for (int i = 0; i < 20 && len + 1 < sizeof(raw); ++i) {
        raw[len++] = (i % 3 == 0) ? '\t' : ' ';
    }

    // Повторяем pattern, пока не доберёмся примерно до 1000 символов
    size_t pat_len = strlen(pattern);
    while (len + pat_len < 10000 && len + pat_len + 1 < sizeof(raw)) {
        memcpy(raw + len, pattern, pat_len);
        len += pat_len;
    }

    // Немного лишних пробелов/табов в конце
    for (int i = 0; i < 30 && len + 1 < sizeof(raw); ++i) {
        raw[len++] = (i % 4 == 0) ? '\t' : ' ';
    }

    raw[len] = '\0';

    printf("Raw length: %zu\n", len);
    my_string input = my_string_from_cstr(raw);

    printf("=== BIG STRING TEST ===\n");
    
    // 1. Нормализация строки (удаление лишних пробелов/табов, trim)
    clock_t start_proc = clock();
    my_string output = process_string(&input);
    clock_t end_proc = clock();
    long double time_proc =
        (long double)(end_proc - start_proc) * 1e6L / CLOCKS_PER_SEC;

    printf("process_string time: %.3Lf microseconds\n\n", time_proc);

    // 2. Перестановка слов
    clock_t start_reorder = clock();
    reorder_words(&output);
    clock_t end_reorder = clock();
    long double time_reorder =
        (long double)(end_reorder - start_reorder) * 1e6L / CLOCKS_PER_SEC;

    
    printf("reorder_words time: %.3Lf microseconds\n", time_reorder);

    my_string_destroy(&input);
    my_string_destroy(&output);
}

int main(void) {
    big_string_benchmark_test();
    return 0;
}