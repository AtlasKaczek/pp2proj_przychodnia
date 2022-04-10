#include <stdio.h>
#include <stdlib.h>
#include "struktury/lekarz.h"

int main() {
    struct Lekarz *glowny;

    glowny = (struct Lekarz *)malloc(sizeof(struct Lekarz));

    glowny = NULL;

    wyswietlLekarzy(glowny);

    dodajLekarzaNaKoniec(&glowny, "Adam", "Monetka", "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");
    dodajLekarzaNaKoniec(&glowny, "Radoslaw", "Koscielec", "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");
    dodajLekarzaNaKoniec(&glowny, "Mariusz", "Pudzianowski", "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");

    wyswietlLekarzy(glowny);

    dodajLekarzaNaKoniec(&glowny, "Wikary", "Marcepan", "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");

    wyswietlLekarzy(glowny);
    
    return 0;
}