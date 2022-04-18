#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struktury/lekarz.h"

int main() {
    struct Lekarz *glowny;

    glowny = (struct Lekarz *)malloc(sizeof(struct Lekarz));

    glowny = NULL;

    FILE *plik;
    
    OdczytajLekarzy(plik, &glowny);

    char id[5];

    int opcja = -1;
    while (opcja != 0)
    {
        printf("\n1. Wyswietl liste lekarzy   2. Dodaj lekarza   3. Edytuj lekarza   4. Usun lekarza   5. Zapisz liste   6. Liczba lekarzy   0. Wyjdz");
        printf("\nWybierz opcje: ");
        scanf(" %d", &opcja);
        switch (opcja)
        {
        case 0: // Wyjdz
            printf("\nZamykanie...\n");
            break;
        
        case 1: // Wyswietl liste lekarzy
            wyswietlLekarzy(glowny);
            break;
        
        case 2: // Dodaj lekarza
            dodajLekarza(&glowny);
            break;
        
        case 3: // Edytuj lekarza
            edytujLekarzaMenu(&glowny);
            break;

        case 4: // Usun lekarza
            
            printf("\nPodaj ID lekarza ( np. L001 ): ");
            scanf(" %4[^\n]%*c", id);
            usunLekarza(&glowny, id);
            break;

        case 5: // Zapisz liste lekarzy
            printf("\nZapisywanie...");
            ZapiszLekarzy(plik, glowny);
            break;

        case 6: // Liczba lekarzy
            printf("\nLiczba lekarzy: %d\n",liczbaLekarzy(glowny));
            break;


        default:
            break;
        }
    }
    
    /*
    dodajLekarzaNaKoniec(&glowny, "Adam", "Monetka", 12, 6, 1986, "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");
    dodajLekarzaNaKoniec(&glowny, "Radoslaw", "Koscielec", 4, 12, 1992, "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");
    dodajLekarzaNaKoniec(&glowny, "Mariusz", "Pudzianowski", 27, 3, 1978, "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");
    */
    return 0;
}