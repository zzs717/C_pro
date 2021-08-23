CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -pedantic -std=c90 -Werror
DEBUG= -g3
SDL= -I/usr/include/SDL2 -lSDL2
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS = -lm

interpreter : commandlist.h general.h interp.h polishstack.h neillsdl2.h commandlist.c general.c interp.c polishstack.c testinterp.c neillsdl2.c
	clang interp.c polishstack.c testinterp.c general.c commandlist.c neillsdl2.c -o interpreter $(PRODUCTION) $(LDLIBS) $(SDL)

clean:
	rm -f parser

interp: interpreter
	./interpreter "example1.txt"
	./interpreter "example2.txt"
	./interpreter "example3.txt"
	./interpreter "example4.txt"
