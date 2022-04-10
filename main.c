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

    usunPierwszego(glowny);
    //usunLekarza(&glowny, "L000");

    wyswietlLekarzy(&glowny);

    printf("\nLiczba lekarzy: %d\n", liczbaLekarzy(glowny));
    
    dodajLekarzaNaKoniec(&glowny, "Maciej", "Kalwin", "0123456789", "Kielce, ul.Jana Pawla II 14", "112233445", 78, 178, "NFZ nr 133");

    printf("\nLiczba lekarzy: %d\n", liczbaLekarzy(glowny));
    return 0;
}