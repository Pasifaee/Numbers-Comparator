CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -O2
DEPS=general_definitions.h make_solution.h read_input.h verse_comparison.h word_recognition.h
OBJS=main.o make_solution.o read_input.o verse_comparison.o word_recognition.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

similar_lines: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	@rm -f *.o
	@rm -f main

# some parts of this file were took from: https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
