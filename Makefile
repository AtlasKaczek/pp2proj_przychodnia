
default: run

build:
	gcc -o main.out main.c struktury/lekarz.c struktury/pomocnicze.c struktury/pacjent.c struktury/wizyty.c

run: build
	./main.out