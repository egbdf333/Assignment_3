all: test1

test1: a3_talkLookupSystem.c a3_talklib.c
	gcc -Wall -std=c99 -o test1 a3_talkLookupSystem.c a3_talklib.c

clean:
	rm -f test1
