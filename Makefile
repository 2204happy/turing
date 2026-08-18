all:
	mkdir build
	gcc src/* -I include/ -o build/turing

clean:
	rm - r build/
