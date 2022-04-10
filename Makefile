
default: run

build:
	gcc -o main.out main.c struktury/lekarz.c struktury/pomocnicze.c

run: build
	./main.out