COMPILER = clang
FLAGS = --std=c99 -pedantic -pedantic-errors -Wall -Wextra -Werror -Wno-unused-parameter -Wno-implicit-fallthrough

all:	
	$(COMPILER) $(FLAGS) httpMediaTypeMatcher.c -o httpMediaTypeMatcher.out

clean:
	rm -f httpMediaTypeMatcher.out
