CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -Werror
DEBUG= -g3
SDL= -I/usr/include/SDL2 -lSDL2
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS = -lm

extra : commandlist.h general.h extension.h polishstack.h neillsdl2.h commandlist.c general.c extension.c polishstack.c testextension.c neillsdl2.c
	clang extension.c polishstack.c testextension.c general.c commandlist.c neillsdl2.c -o extension $(PRODUCTION) $(LDLIBS) $(SDL)

clean:
	rm -f parser

extension: extension
	./extra "example1.txt"
	./extra "example2.txt"
	./extra "example3.txt"
	./extra "example4.txt"
	./extra "example5.txt"
