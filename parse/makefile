CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -Werror
DEBUG= -g3
SDL= -I/usr/include/SDL2 -lSDL2
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS = -lm

parser : commandlist.h general.h parser.h polishstack.h commandlist.c general.c parser.c polishstack.c testparser.c
	$(CC) parser.c polishstack.c testparser.c general.c commandlist.c -o parser $(PRODUCTION) $(LDLIBS)

clean:
	rm -f parser

parse: parser
	./parser "example1.txt"
	./parser "example2.txt"
	./parser "example3.txt"
	./parser "example4.txt"
