CC = clang
CFLAGS = -Wall -Werror -Wpedantic -Wextra
LFLAGS = -lm

all: sorting

sorting: sorting.o bubble.o shell.o quick.o stack.o queue.o set.o
	$(CC) -o sorting $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *.c *.h
