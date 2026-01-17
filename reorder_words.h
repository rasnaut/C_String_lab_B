#include "my_string.h"
/**
 * Находит индекс начала последнего слова в строке
 * @param str Исходная строка
 * @return Индекс первого символа последнего слова
 */
int find_last_word_start(const my_string *str);

/**
 * Проверяет, оканчивается ли слово нужным символом
 * @param word Слово (не обязательно null-terminated)
 * @param word_len Длина слова
 * @param target_char Символ для проверки
 * @return 1 если совпадает, 0 иначе
 */
int ends_with_char(const char *word, int word_len, char target_char);
/**
 * Добавляет слово в буфер с пробелом если нужно
 * @param buffer Целевой буфер
 * @param word Слово для добавления
 * @param word_len Длина слова
 */
void append_word(my_string *buffer, const char *word);

/**
 * Собирает слова из исходной строки в две категории
 * @param str Исходная строка
 * @param end_pos Позиция, до которой собирать слова (не включает последнее слово)
 * @param target_char Символ для поиска
 * @param words_to_move Буфер для слов, заканчивающихся target_char
 * @param remaining Буфер для остальных слов
 */
void collect_words(const my_string *str, char target_char, 
                   my_string *words_to_move, my_string *remaining);

/**
 * Перемещает в начало строки все слова, оканчивающиеся символом,
 * с которого начинается последнее слово в строке.
 * 
 * @param str Исходная строка (будет модифицирована!)
 */
void reorder_words(my_string *str);