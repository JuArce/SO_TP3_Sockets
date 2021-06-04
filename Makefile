CFLAGS = -Wall -std=gnu99 -lm
CC = gcc
all: compile

compile:  server.c challenges.c
	$(CC) -o server server.c challenges.c $(CFLAGS)

test: cpp pvs

cpp: $(OUT_CPP)

pvs: clean
	./pvs.sh

%.cpp: %.c
	cppcheck --quiet --enable=all --force --inconclusive $< 2>> output.cppOut

cleanTest:
	rm output.cppOut report.tasks

clean:
	rm -f server

.PHONY:  all clean cleanTest cpp test pvs
