build:
	clang main.c -o jdif

example:
	cat example.ldif | ./jdif | jq