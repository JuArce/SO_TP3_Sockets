CFLAGS = -Wall -std=gnu99 -pedantic -fsanitize=address -lm
CC = gcc

all: server client

server:  src/server.c src/challenges.c src/socketsApi.c
	$(CC) -o server src/server.c src/challenges.c src/socketsApi.c $(CFLAGS)

client: src/client.c src/socketsApi.c
	$(CC) -o client src/client.c src/socketsApi.c $(CFLAGS)

test: clean
	mkdir tests; ./pvs.sh; valgrind --leak-check=full -v ./server 2>> tests/results.valgrind; valgrind --leak-check=full -v ./client 2>> tests/results.valgrind; cppcheck --quiet --enable=all --force --inconclusive src/server.c src/challenges.c src/client.c 2>> tests/output.cppOut

cleanTest:
	rm -rf tests/output.cppOut tests/report.tasks tests/results.valgrind tests

clean:
	rm -f server
	rm -f client

.PHONY:  all clean test cleanTest server client
