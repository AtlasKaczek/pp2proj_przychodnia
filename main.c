#include <stdio.h>
#include <stdlib.h>
#include "struktury/lekarz.h"

int main() {
    struct Lekarz *glowny;

    glowny = (struct Lekarz *)malloc(sizeof(struct Lekarz));

    glowny = NULL;

    wyswietlLekarzy(glowny);

    dodajLekarzaNaKoniec(&glowny, 123, "Adam", "Monetka", "0123456789", "Kielce, ul.Jana Pawla II 14", "amonetka@przychodnia.lekarz.pl", "012345678", 78, 178, "NFZ nr 135");
    dodajLekarzaNaKoniec(&glowny, 231, "Radoslaw", "Koscielec", "0123456789", "Kielce, ul.Jana Pawla II 14", "rkoscielec@przychodnia.lekarz.pl", "012345678", 78, 178, "NFZ nr 135");
    dodajLekarzaNaKoniec(&glowny, 321, "Mariusz", "Pudzianowski", "0123456789", "Kielce, ul.Jana Pawla II 14", "mpudzian@przychodnia.lekarz.pl", "012345678", 78, 178, "NFZ nr 135");

    wyswietlLekarzy(glowny);

    dodajLekarzaNaKoniec(&glowny, 213, "Wikary", "Marcepan", "0123456789", "Kielce, ul.Jana Pawla II 14", "wmaecepan@przychodnia.lekarz.pl", "012345678", 78, 178, "NFZ nr 135");

    wyswietlLekarzy(glowny);
    
    return 0;
}