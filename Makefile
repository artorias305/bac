bac: bac.c
	gcc -g bac.c -o bac -lm

run:
	gcc -g bac.c -o bac -lm && ./bac
