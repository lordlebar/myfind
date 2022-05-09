CC = gcc
CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra

BIN = myfind
OBJS = src/$(BIN).o src/main.o

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) -o $(BIN) $(OBJS)

check: $(OBJS)
	./tests/tests.sh

clean:
	$(RM) $(BIN) $(OBJS)