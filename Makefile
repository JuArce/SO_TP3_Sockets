CFLAGS = -Wall -std=gnu99 -pedantic -fsanitize=address -lm
CC = gcc

all: server client

server:  server.c challenges.c
	$(CC) -o server server.c challenges.c $(CFLAGS)

client: client.c
	$(CC) -o client client.c $(CFLAGS)

test: clean
	./pvs.sh; valgrind --leak-check=full -v ./server 2>> results.valgrind; valgrind --leak-check=full -v ./client 2>> results.valgrind; cppcheck --quiet --enable=all --force --inconclusive server.c levels.c client.c 2>> output.cppOut

cleanTest:
	rm -rf output.cppOut report.tasks results.valgrind

clean:
	rm -f server
	rm -f client

.PHONY:  all clean test cleanTest server client
