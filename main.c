#include <stdio.h>
#include <stdlib.h>
#include "struktury/lekarz.h"

int main() {
    struct Lekarz *glowny;

    glowny = (struct Lekarz *)malloc(sizeof(struct Lekarz));

    glowny = NULL;
    /*
    wyswietlLekarzy(glowny);
    
    dodajLekarzaNaKoniec(&glowny, "Adam", "Monetka", 12, 6, 1986, "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");
    dodajLekarzaNaKoniec(&glowny, "Radoslaw", "Koscielec", 4, 12, 1992, "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");
    dodajLekarzaNaKoniec(&glowny, "Mariusz", "Pudzianowski", 27, 3, 1978, "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");

    wyswietlLekarzy(glowny);
    
    dodajLekarzaNaKoniec(&glowny, "Wikary", "Marcepan", "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");

    wyswietlLekarzy(glowny);

    usunLekarza(&glowny, "L000");

    wyswietlLekarzy(glowny);
    
    dodajLekarzaNaKoniec(&glowny, "Maciej", "Kalwin", "0123456789", "Kielce, ul.Jana Pawla II 14", "112233445", 78, 178, "NFZ nr 133");

    wyswietlLekarzy(glowny);
    */
    FILE *plik;
    
    //ZapiszLekarzy(plik, glowny);

    OdczytajLekarzy(plik, &glowny);

    wyswietlLekarzy(glowny);

    //usunOstatniego(&glowny);
    edytujLekarzaMenu(&glowny);

    wyswietlLekarzy(glowny);

    return 0;
}