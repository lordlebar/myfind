CC = gcc
CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra

BIN = myfind
OBJS = src/$(BIN).o src/main.o src/is_dir.o src/is_file.o

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $(OBJS) -g

check: $(OBJS)
	./tests/tests.sh

clean:
	$(RM) $(BIN) $(OBJS)