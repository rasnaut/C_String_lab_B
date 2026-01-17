CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g 
TARGET = main
TEST_MY_STRING = test_my_string
TEST_STRING_PROCESSING = test_string_processing

# Object files
OBJS = my_string.o reorder_words.o string_processing.o dialog.o

# Source files
SOURCES = my_string.c reorder_words.c string_processing.c dialog.c 
HEADERS = my_string.h reorder_words.h string_processing.h dialog.h

.PHONY: all clean test run

all: $(TARGET)

$(TARGET): $(OBJS) main.c $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) main.c -o $(TARGET) -lreadline

my_string.o: my_string.c my_string.h
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o

string_processing.o: string_processing.c string_processing.h my_string.h
	$(CC) $(CFLAGS) -c string_processing.c -o string_processing.o

dialog.o: dialog.c dialog.h my_string.h string_processing.h
	$(CC) $(CFLAGS) -c dialog.c -o dialog.o

test_my_string: my_string.o my_string_test_main.c
	$(CC) $(CFLAGS) my_string.o my_string_test_main.c -o $(TEST_MY_STRING)

test_string_processing: my_string.o string_processing.o string_processing_test_main.c
	$(CC) $(CFLAGS) my_string.o string_processing.o string_processing_test_main.c -o $(TEST_STRING_PROCESSING)

test: test_my_string test_string_processing
	@echo "Running my_string tests..."
	./$(TEST_MY_STRING)
	@echo ""
	@echo "Running string_processing tests..."
	./$(TEST_STRING_PROCESSING)

run: $(TARGET)
	./$(TARGET)

valgrind: main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

valgrind_test_my_string: test_my_string
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_MY_STRING)

valgrind_test_string_processing: test_string_processing
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_STRING_PROCESSING)

clean:
	rm -f *.o $(TARGET) $(TEST_MY_STRING) $(TEST_STRING_PROCESSING)

help:
	@echo "Available targets:"
	@echo "  all                    - Build main program (default)"
	@echo "  test                   - Run all tests"
	@echo "  test_my_string         - Build and run my_string tests"
	@echo "  test_string_processing - Build and run string_processing tests"
	@echo "  run                    - Build and run main program"
	@echo "  clean                  - Remove compiled files"
	@echo "  help                   - Show this help message"