build:
	clang main.c -o bin/jdif

binary: build
	sudo cp bin/jdif /usr/local/bin

example: binary
	cat example.ldif | jdif | jq