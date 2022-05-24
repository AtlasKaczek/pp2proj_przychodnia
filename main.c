#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struktury/lekarz.h"
#include "struktury/pacjent.h"
#include "struktury/wizyty.h"

int main() {

    struct Lekarz *g_lekarz;
    //g_lekarz = (struct Lekarz *)malloc(sizeof(struct Lekarz));
    g_lekarz = NULL;

    struct Pacjent *g_pacjent;
    //g_pacjent = (struct Pacjent *)malloc(sizeof(struct Pacjent));
    g_pacjent = NULL;

    struct Wizyta *g_wizyta;
    //g_wizyta = (struct Wizyta *)malloc(sizeof(struct Wizyta));
    g_wizyta = NULL;

    FILE *plik;
    
    OdczytajLekarzy(plik, &g_lekarz);
    OdczytajPacjentow(plik, &g_pacjent);
    OdczytajWizyty(plik, &g_wizyta, g_lekarz, g_pacjent);

    char id[5];

    int opcja = -1;
    while (opcja != 0)
    {
        printf("\n1. Lista lekarzy   2. Lista pacjentow   3. Lista wizyt   0. Wyjdz");
        printf("\nWybierz opcje: ");
        scanf(" %d", &opcja);
        switch (opcja)
        {
        case 0:
            printf("\nZamykanie...\n");
            break;

        case 1: // Lista lekarzy
            while (opcja != 0)
            {
                printf("\n1. Wyswietl liste lekarzy   2. Dodaj lekarza   3. Edytuj lekarza   4. Usun lekarza   5. Zapisz liste   6. Liczba lekarzy   0. Powrot");
                printf("\nWybierz opcje: ");
                scanf(" %d", &opcja);
                switch (opcja)
                {
                case 0: // Wyjdz
                    printf("\nCofanie...\n");
                    break;
                
                case 1: // Wyswietl liste lekarzy
                    wyswietlLekarzy(g_lekarz);
                    break;
                
                case 2: // Dodaj lekarza
                    dodajLekarza(&g_lekarz);
                    break;
                
                case 3: // Edytuj lekarza
                    edytujLekarzaMenu(&g_lekarz);
                    break;

                case 4: // Usun lekarza
                    
                    printf("\nPodaj ID lekarza ( np. L001 ): ");
                    scanf(" %4[^\n]%*c", id);
                    usunLekarza(&g_lekarz, id);
                    break;

                case 5: // Zapisz liste lekarzy
                    printf("\nZapisywanie...");
                    ZapiszLekarzy(plik, g_lekarz);
                    break;

                case 6: // Liczba lekarzy
                    printf("\nLiczba lekarzy: %d\n",liczbaLekarzy(g_lekarz));
                    break;


                default:
                    break;
                }
            }
            opcja = -1;
            break;
        
        case 2: // Lista pacjentow
            while (opcja != 0)
            {
                printf("\n1. Wyswietl liste pacjentow   2. Dodaj pacjenta   3. Edytuj pacjenta   4. Usun pacjenta   5. Zapisz liste   6. Liczba pacjentow   0. Powrot");
                printf("\nWybierz opcje: ");
                scanf(" %d", &opcja);
                switch (opcja)
                {
                case 0: // Wyjdz
                    printf("\nCofanie...\n");
                    break;
                
                case 1: // Wyswietl liste pacjentow
                    wyswietlPacjentow(g_pacjent);
                    break;
                
                case 2: // Dodaj pacjenta
                    dodajPacjenta(&g_pacjent);
                    break;
                
                case 3: // Edytuj pacjenta
                    edytujPacjentaMenu(&g_pacjent);
                    break;

                case 4: // Usun pacjenta
                    
                    printf("\nPodaj ID pacjenta ( np. L001 ): ");
                    scanf(" %4[^\n]%*c", id);
                    usunPacjenta(&g_pacjent, id);
                    break;

                case 5: // Zapisz liste pacjentow
                    printf("\nZapisywanie...");
                    ZapiszPacjentow(plik, g_pacjent);
                    break;

                case 6: // Liczba lekarzy
                    printf("\nLiczba pacjentow: %d\n",liczbaPacjentow(g_pacjent));
                    break;


                default:
                    break;
                }
            }
            opcja = -1;
            break;
        
        case 3: // Lista wizyt
            while (opcja != 0)
            {
                printf("\n1. Wyswietl wizyty   2. Dodaj wizyte   3. Edytuj wizyte   4. Usun wizyte   5. Zapisz wizyte   6. Liczba wizyt   0. Powrot");
                printf("\nWybierz opcje: ");
                scanf(" %d", &opcja);
                switch (opcja)
                {
                case 0: // Wyjdz
                    printf("\nCofanie...\n");
                    break;
                
                case 1: // Wyswietl liste pacjentow
                    wyswietlWizyty(g_wizyta);
                    break;
                
                case 2: // Dodaj pacjenta
                    dodajWizyte(&g_wizyta, g_lekarz, g_pacjent);
                    break;
                
                case 3: // Edytuj pacjenta
                    edytujWizyteMenu(&g_wizyta, g_lekarz, g_pacjent);
                    break;

                case 4: // Usun pacjenta
                    
                    printf("\nPodaj ID pacjenta ( np. L001 ): ");
                    scanf(" %4[^\n]%*c", id);
                    usunWizyte(&g_wizyta, id);
                    break;

                case 5: // Zapisz liste pacjentow
                    printf("\nZapisywanie...");
                    ZapiszWizyty(plik, g_wizyta);
                    break;

                case 6: // Liczba lekarzy
                    printf("\nLiczba pacjentow: %d\n",liczbaPacjentow(g_pacjent));
                    break;


                default:
                    break;
                }
            }
            opcja = -1;
            break;

        
        default:
            break;
        }
    }

    
    /*
    dodajLekarzaNaKoniec(&g_lekarz, "Adam", "Monetka", 12, 6, 1986, "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");
    dodajLekarzaNaKoniec(&g_lekarz, "Radoslaw", "Koscielec", 4, 12, 1992, "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");
    dodajLekarzaNaKoniec(&g_lekarz, "Mariusz", "Pudzianowski", 27, 3, 1978, "0123456789", "Kielce, ul.Jana Pawla II 14", "012345678", 78, 178, "NFZ nr 135");
    */
    return 0;
}