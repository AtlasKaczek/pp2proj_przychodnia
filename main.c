#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struktury/lekarz.h"
#include "struktury/pacjent.h"
#include "struktury/wizyty.h"

///
/** Funkcja main
 * Zawiera wszystkie parametry potrzebne do prawidłowego działania programu.
 * W tej funkcji znajduję się menu dla użytkownika.
 *
 */
int main() {

    struct Lekarz *g_lekarz;
    g_lekarz = NULL;

    struct Pacjent *g_pacjent;
    g_pacjent = NULL;

    struct Wizyta *g_wizyta;
    g_wizyta = NULL;

    FILE *plik;
    
    OdczytajLekarzy(plik, &g_lekarz);
    OdczytajPacjentow(plik, &g_pacjent);
    OdczytajWizyty(plik, &g_wizyta, g_lekarz, g_pacjent);

    
    char id[5];

    int opcja = -1;
    while (opcja != 0)
    {
        printf("\n 1. Lista lekarzy\n 2. Lista pacjentow\n 3. Lista wizyt\n 0. Wyjdz");
        printf("\nWybierz opcje: ");
        scanf(" %d", &opcja);
        switch (opcja)
        {
        case 0:
            opcja = -1;
            while (opcja != 0)
            {
                printf("\nCzy chesz zapisac zmiany i wyjsc?\n 1. Tak\n 0. Nie\nWybierz: ");
                scanf(" %d", &opcja);
                switch (opcja)
                {
                case 0:
                    printf("\nZamykanie...\n");
                    break;
                case 1:
                    ZapiszLekarzy(plik, g_lekarz);
                    ZapiszPacjentow(plik, g_pacjent);
                    ZapiszWizyty(plik, g_wizyta);
                    printf("\nZamykanie...\n");
                    opcja = 0;
                    break;
                default:
                    break;
                }
            }
            
            break;

        case 1: // Lista lekarzy
            while (opcja != 0)
            {
                printf("\n 1. Wyswietl liste lekarzy\n 2. Dodaj lekarza\n 3. Edytuj lekarza\n 4. Usun lekarza\n 5. Zapisz liste\n 6. Liczba lekarzy\n 0. Powrot");
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
                    printf("\nZapisywanie...\n");
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
                printf("\n 1. Wyswietl liste pacjentow\n 2. Dodaj pacjenta\n 3. Edytuj pacjenta\n 4. Usun pacjenta\n 5. Zapisz liste\n 6. Liczba pacjentow\n 0. Powrot");
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
                    printf("\nZapisywanie...\n");
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
                printf("\n 1. Wyswietl wizyty\n 2. Dodaj wizyte\n 3. Edytuj wizyte\n 4. Usun wizyte\n 5. Zapisz wizyte\n 6. Wyswietl konkretna wizyte\n 7. Liczba wizyt\n 0. Powrot");
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
                    printf("\nZapisywanie...\n");
                    ZapiszWizyty(plik, g_wizyta);
                    break;
                
                case 6: // Liczba lekarzy
                    printf("\nPodaj ID pacjenta ( np. L001 ): ");
                    scanf(" %4[^\n]%*c", id);
                    wyswietlWizyte(wybranaWizyta(g_wizyta, id));
                    break;

                case 7: // Liczba lekarzy
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

    return 0;
}