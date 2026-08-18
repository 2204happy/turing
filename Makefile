all:
	mkdir build
	gcc src/* -I include/ -Wall -Wextra -Wno-char-subscripts -o build/turing

clean:
	rm -r build/
