#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lekarz.h"
#include "pacjent.h"
#include "wizyty.h"

/// Funkcja dodajWizyteNaKoniec
/**
* Funkcja dodaje tworzy wizytę na podstawie podanych argumentów i dodaje ją na koniec listy wizyt.
* Funkcja nic nie zwraca.
*
*/
void dodajWizyteNaKoniec(struct Wizyta **head, struct Lekarz *head_lekarz, struct Pacjent *head_pacjent, int dzien, int miesiac, int rok, int godzina, int minuta, char lekarz[5], char pacjent[5]) {
    
    struct Wizyta *nowa = (struct Wizyta *)malloc(sizeof(struct Wizyta));
    strcpy(nowa->id, generujIDWizyta(*head));
    nowa->data.dzien = dzien;
    nowa->data.miesiac = miesiac;
    nowa->data.rok = rok;
    nowa->time.godzina = godzina;
    nowa->time.minuta = minuta;
    nowa->lekarz = wybranyLekarz(head_lekarz, lekarz);
    nowa->pacjent = wybranyPacjent(head_pacjent , pacjent);
    nowa->nastepny = NULL;
    nowa->poprzedni = NULL;

    if ((*head) == NULL)
    {
        *head = nowa;
        wyswietlWizyte((*head));
        return;
    } else {
        struct Wizyta *tmp = *head;
        while (tmp->nastepny!=NULL)
        {
            tmp=tmp->nastepny;
        }

        tmp->nastepny = nowa;
        nowa->poprzedni = tmp;
    }
    
}

/// Funkcja usunPierwszaWizyte
/**
* Funkcja usuwa pierwszą wizytę z listy wizyt.
* Funkcja nic nie zwraca.
*
*/
void usunPierwszaWizyte(struct Wizyta **glowny) {
    
	struct Wizyta *tmp = *glowny;
    if (tmp->nastepny != NULL)
    {
        *glowny = tmp->nastepny;
    } else {
        *glowny = NULL;
    }
    free(tmp);
}

/// Funkcja usunOstatniaWizyte
/**
* Funkcja usuwa ostatnią wizytę z listy wizyt.
* Funkcja nic nie zwraca.
*
*/
void usunOstatniaWizyte(struct Wizyta **glowny) {
    struct Wizyta *tmp;
    if ((*glowny) == NULL)
    {
        return;
    } else if ((*glowny)->nastepny==NULL) {
        (*glowny)=NULL;
        free(*glowny);
    } else {
        tmp=*glowny;
        while (tmp->nastepny != NULL) {
            tmp=tmp->nastepny;
        }
        tmp->poprzedni->nastepny=NULL;
        free(tmp);
    }
}

/// Funkcja usunWizyte
/**
* Funkcja usuwa daną wizytę z listy wizyt na podstawie drugiego argumentu - ID wizyty postaci 'W000'.
* Funkcja nic nie zwraca.
*
*/
void usunWizyte(struct Wizyta **glowny, char id[]) {
    
    if (strcmp( id, (*glowny)->id) == 0 || liczbaWizyt(*glowny) == 1)
    {
        usunPierwszaWizyte(glowny);
    } else {
        struct Wizyta *node = *glowny;
        struct Wizyta *tmp;

        while (node->nastepny != NULL && strcmp( node->nastepny->id, id) != 0) {
            node = node->nastepny;
        }
        if (strcmp( node->nastepny->id, id) == 0)
        {
            usunOstatniaWizyte(glowny);
        } else {
            tmp=node->nastepny;
            node->nastepny = tmp->nastepny;
            tmp->nastepny->poprzedni = node;
            free(tmp);
        }
        printf("Pomyslnie usunieto Wizyte.\n\n");
    }
    
}

/// Funkcja liczbaWizyt
/**
* Funkcja zlicza aktualną liczbę wizyt w liście wizyt i zwraca tą liczbę.
*
*
*/
int liczbaWizyt(struct Wizyta *glowny) {
    int liczba = 0;
    if (glowny == NULL) return 0;
    else {
        while(glowny != NULL) {
            liczba++;
            glowny = glowny->nastepny;
        }
    }
    return liczba;
}

/// Funkcja strFormatWizyta
/**
* Funkcja tworzy i zwraca ciąg znaków zawierający dane konkretnej wizyty.
* Funkcja wykorzystywana podczas wyświetlania listy wizyt.
*
*/
char * strFormatWizyta(struct Wizyta *glowny) {
    int dlugosc = 200;
    char * str = malloc(dlugosc);

    

    strcpy(str, glowny->id);
    strcat(str, "   ");
    char intos[5];
    if(glowny->data.dzien < 10) {
        strcat(str, "0");
    }
    sprintf( intos, "%d", glowny->data.dzien);
    strcat(str, intos);
    strcat(str, "/");
    if(glowny->data.miesiac < 10) {
        strcat(str, "0");
    }
    sprintf( intos, "%d", glowny->data.miesiac);
    strcat(str, intos);
    strcat(str, "/");
    sprintf( intos, "%d", glowny->data.rok);
    strcat(str, intos);
    strcat(str, "      ");
    if(glowny->time.godzina < 10) {
        strcat(str, "0");
    }
    sprintf( intos, "%d", glowny->time.godzina);
    strcat(str, intos);
    strcat(str, ":");
    if(glowny->time.minuta < 10) {
        strcat(str, "0");
    }
    sprintf( intos, "%d", glowny->time.minuta);
    strcat(str, intos);
    strcat(str, "      ");
    strcat(str, glowny->lekarz->imie);
    strcat(str, " ");
    strcat(str, glowny->lekarz->nazwisko);
    strcat(str, " (");
    strcat(str, glowny->lekarz->id);
    strcat(str, ") / ");
    strcat(str, glowny->pacjent->imie);
    strcat(str, " ");
    strcat(str, glowny->pacjent->nazwisko);
    strcat(str, " (");
    strcat(str, glowny->pacjent->id);
    strcat(str, ")");


    if (str[strlen(str)-1] == '\n')
    {
        str[strlen(str)-1] = '\0';
    }
    
    return str;
}

/// Funkcja wyswietlWizyty
/**
* Funkcja wyświetla listę wizyt.
* Funkcja nic nie zwraca.
*/
void wyswietlWizyty(struct Wizyta *glowny) {

    if (glowny == NULL) { printf("\nLista wizyt jest pusta.\n"); }
    else {
        printf("\nID     DATA            GODZINA    LEKARZ / PACJENT\n");
        while(glowny != NULL) {
            printf("%s\n", strFormatWizyta(glowny));
            glowny = glowny->nastepny;
        }
    }

}

/// Funkcja wyswietlWizyty
/**
* Funkcja wyświetla konkretną wizyt.
* Funkcja nic nie zwraca.
*/
void wyswietlWizyte(struct Wizyta *glowny) {
    printf("1. ID: %s\n2. Data: %d/%d/%d\n3. Godzina: %d:%d\n4. Lekarz: %s %s (%s) \n5. Pacjent: %s %s (%s)\n", glowny->id, glowny->data.dzien, glowny->data.miesiac, glowny->data.rok, glowny->time.godzina, glowny->time.minuta, glowny->lekarz->imie, glowny->lekarz->nazwisko, glowny->lekarz->id, glowny->pacjent->imie, glowny->pacjent->nazwisko, glowny->pacjent->id);
}

/// Funkcja edytujWizyteMenu
/**
* Funkcja stworzona z myślą o użytkowniku. Pozwala wybrać wizytę i jej konkretne pole, a następnie edytować je.
* Funkcja nic nie zwraca.
*/
void edytujWizyteMenu(struct Wizyta **glowny, struct Lekarz *g_lekarz, struct Pacjent *g_pacjent) {
    
    char id[5];
    printf("\nWybierz wizyte, ktora chcesz edytowac (id): ");
    scanf("%s", id);

    int opcja = -1;

    if (strcmp( id, (*glowny)->id) == 0)
    {
        while (opcja != 0)
        {
            wyswietlWizyte(*glowny);
            printf("0. Zatwierdz");
            printf("Wybierz pole do edycji: ");
            scanf(" %d", &opcja);
            edytujWizyte(glowny, g_lekarz, g_pacjent, opcja);
        }
        
    } else {
        struct Wizyta *node = *glowny;

        while (node->nastepny != NULL && strcmp( node->nastepny->id, id) != 0) {
            node = node->nastepny;
        }
        
        while (opcja != 0)
        {
            wyswietlWizyte(node->nastepny);
            printf("0. Zatwierdz\n\n");
            printf("Wybierz pole do edycji: ");
            scanf(" %d", &opcja);
            edytujWizyte(&(node->nastepny), g_lekarz, g_pacjent, opcja);
        }
    }
    
    printf("Pomyslnie edytowano wizyte .\n");
}

/// Funkcja edytujWizyte
/**
* Funkcja pozwala edytować dane pole wizyty.
* Funkcja nic nie zwraca.
*/
void edytujWizyte(struct Wizyta **glowny, struct Lekarz *g_lekarz, struct Pacjent *g_pacjent, int opcja) {
    char id[5];
    int data = 0;
    switch (opcja)
    {
    case 1:
        printf("ID: %s -> ", (*glowny)->id);
        scanf(" %4[^\n]%*c", id);
        strcpy((*glowny)->id, id);
        break;
    
    case 2:
        printf("Data wizyty: %d/%d/%d -> \n", (*glowny)->data.dzien, (*glowny)->data.miesiac, (*glowny)->data.rok);
        printf("Rok: ");
        scanf(" %d", &data);
        while (data < 2021)
        {
            printf("Bledne dane!\nRok: ");
            scanf(" %d", &data);
        }
        (*glowny)->data.rok = data;
	    if((data%4==0 && data%100!=0) || data%400==0)
        {
            printf("Miesiac: ");
            scanf(" %d", &data);
            while (data < 0 || data > 12)
            {
                printf("Bledne dane!\nMiesiac: ");
                scanf(" %d", &data);
            }
            (*glowny)->data.miesiac = data;
            if (data == 1 || data == 3 || data == 5 || data == 7 || data == 8 || data == 10 || data == 12)
            {
                printf("Dzien: ");
                scanf(" %d", &data);
                while (data < 0 || data > 31)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &data);
                }
                (*glowny)->data.dzien = data;

            }
            else if (data == 2)
            {
                printf("Dzien: ");
                scanf(" %d", &data);
                while (data < 0 || data > 29)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &data);
                }
                (*glowny)->data.dzien = data;

            }
            else if (data == 4 || data == 6 || data == 9 || data == 11)
            {
                printf("Dzien: ");
                scanf(" %d", &data);
                while (data < 0 || data > 30)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &data);
                }
                (*glowny)->data.dzien = data;
            }
        }
        else
        {
            printf("Miesiac: ");
            scanf(" %d", &data);
            while (data < 0 || data > 12)
            {
                printf("Bledne dane!\nMiesiac: ");
                scanf(" %d", &data);
            }
            (*glowny)->data.miesiac = data;
            if (data == 1 || data == 3 || data == 5 || data == 7 || data == 8 || data == 10 || data == 12)
            {
                printf("Dzien: ");
                scanf(" %d", &data);
                while (data < 0 || data > 31)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &data);
                }
                (*glowny)->data.dzien = data;
            }
            else if (data == 2)
            {
                printf("Dzien: ");
                scanf(" %d", &data);
                while (data < 0 || data > 28)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &data);
                }
                (*glowny)->data.dzien = data;
            }
            else if (data == 4 || data == 6 || data == 9 || data == 11)
            {
                printf("Dzien: ");
                scanf(" %d", &data);
                while (data < 0 || data > 30)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &data);
                }
                (*glowny)->data.dzien = data;
            }
        }
        break;
    
    case 3:
        printf("Czas: %d:%d -> \n", (*glowny)->time.godzina, (*glowny)->time.minuta);
        do
        {
            printf("Godzina: ");
            scanf(" %d", &data);
            while (data < 0 || data > 23)
            {
                printf("Bledne dane!\nGodzina: ");
                scanf(" %d", &data);
            }
            (*glowny)->time.godzina = data;
            printf("Minuta: ");
            scanf(" %d", &data);
            while (data < 0 || data > 59)
            {
                printf("Bledne dane!\nMinuta: ");
                scanf(" %d", &data);
            }
            (*glowny)->time.minuta = data;
        } while (((*glowny)->time.godzina > (*glowny)->lekarz->godzZakonczeniaPracy.godzina || (*glowny)->time.godzina < (*glowny)->lekarz->godzRozpoczeciaPracy.godzina));

        break;

    case 4:
        printf("Lekarz: %s %s (%s) -> ID: ", (*glowny)->lekarz->imie, (*glowny)->lekarz->nazwisko, (*glowny)->lekarz->id);
        scanf(" %4[^\n]%*c", id);
        do
        {
            while (strlen(id) != 4 || id[0] != 'L')
            {
                printf("Nie poprawna forma !\n");
                printf("Lekarz: %s %s (%s) -> ID: ", (*glowny)->lekarz->imie, (*glowny)->lekarz->nazwisko, (*glowny)->lekarz->id);
                scanf(" %4[^\n]%*c", id);
            }
        } while (sprawdzIDLekarz(g_lekarz, id) == 0);
        (*glowny)->lekarz = wybranyLekarz(g_lekarz, id);
        break;
    
    case 5:
        printf("Pacjent: %s %s (%s) ->  ID: ", (*glowny)->pacjent->imie, (*glowny)->pacjent->nazwisko, (*glowny)->pacjent->id);
        scanf(" %4[^\n]%*c", id);
        do
        {
            while (strlen(id) != 4 || id[0] != 'P')
            {
                printf("Nie poprawna forma !\n");
                printf("Pacjent: %s %s (%s) ->  ID: ", (*glowny)->pacjent->imie, (*glowny)->pacjent->nazwisko, (*glowny)->pacjent->id);
                scanf(" %4[^\n]%*c", id);
            }
        } while (sprawdzIDPacjent(g_pacjent, id) == 0);
        (*glowny)->pacjent = wybranyPacjent(g_pacjent, id);
        break;
    
    default:
        break;
    }
    printf("\n");
}

/// Funkcja dodajWizyte
/**
* Funkcja stworzona z myślą o użytkowniku. Pozwala stworzyć wizytę po wprowadzeniu przez użytkownika danych.
* Funkcja nic nie zwraca.
*/
void dodajWizyte(struct Wizyta **glowny, struct Lekarz *g_lekarz, struct Pacjent *g_pacjent) {
    printf("\nDodaj wizyte:\n");
    int d, m, r;
    printf("Dzien wizyty\nDzien: ");
    scanf(" %d", &d);
    while (d < 0 || d > 31)
    {
        printf("Bledne dane!\nDzien: ");
        scanf(" %d", &d);
    }   
    printf("Miesiac: ");
    scanf(" %d", &m);
    while (m < 1 || m > 12)
    {
        printf("Bledne dane!\nMiesiac: ");
        scanf(" %d", &m);
    } 
    printf("Rok: ");
    scanf(" %d", &r);
    while (r < 2022 || r > 3000)
    {
        printf("Bledne dane!\nRok: ");
        scanf(" %d", &r);
    } 
    char id_l[5];
    printf("Lekarz (ID np. L001): ");
    scanf(" %4[^\n]%*c", id_l);
    while ((strlen(id_l) != 4 || id_l[0] != 'L') || (sprawdzIDLekarz( g_lekarz, id_l) == 0))
    {
        printf("Nie poprawna forma !\n");
        printf("Lekarz (ID np. L001): ");
        scanf(" %4[^\n]%*c", id_l);
    }
    char id_p[5];
    printf("Pacjent (ID np. P001): ");
    scanf(" %4[^\n]%*c", id_p);
    while ((strlen(id_p) != 4 || id_p[0] != 'P') || (sprawdzIDPacjent(g_pacjent, id_p) == 0))
    {
        printf("Nie poprawna forma !\n");
        printf("Pacjent (ID np. P001): ");
        scanf(" %4[^\n]%*c", id_p);
    }
    double czas_rozpoczecia_pracy = (double)wybranyLekarz(g_lekarz, id_l)->godzRozpoczeciaPracy.godzina + (double)wybranyLekarz(g_lekarz, id_l)->godzRozpoczeciaPracy.minuta/100;
    double czas_zakonczenia_pracy = (double)wybranyLekarz(g_lekarz, id_l)->godzZakonczeniaPracy.godzina + (double)wybranyLekarz(g_lekarz, id_l)->godzZakonczeniaPracy.minuta/100;
    double czas_wizyty = 0;

    int godz, min;
    do {
    if (czas_wizyty != 0)
    {
        printf("Czas wizyty poza godzinami pracy lekarza !\n");
    }
    
    printf("Godzina wizyty\nGodzina: ");
    scanf(" %d", &godz);
    while (godz < 0 || godz > 24)
    {
        printf("Bledne dane!\nGodzina: ");
        scanf(" %d", &godz);
    }  
    printf("Minuta: ");
    scanf(" %d", &min);
    while (min < 0 || min > 59)
    {
        printf("Bledne dane!\nMinuta: ");
        scanf(" %d", &min);
    }
    czas_wizyty = (double)godz + (double)min/100;
    } while (czas_wizyty > czas_zakonczenia_pracy || czas_wizyty < czas_rozpoczecia_pracy);

    
    dodajWizyteNaKoniec(glowny, g_lekarz, g_pacjent, d, m, r, godz, min, id_l, id_p);
    printf("\n");
}

/// Funkcja generujIDWizyta
/**
* Funkcja generuje i zwraca orginalne ID wizyty.
* 
*/
char * generujIDWizyta(struct Wizyta *glowny) {
    char *str = malloc(5);
    str[0] = 'W';
    str[1] = '0';
    str[2] = '0';
    str[3] = '0';
    str[4] = '\0';
    if (liczbaWizyt(glowny) == 0) {
        return str;
    }
    int licznik_id = 0;
    while(sprawdzIDWizyta(glowny, str) == 1) {
        str[1] = 48 + licznik_id%1000 - licznik_id%100;
        str[2] = 48 + licznik_id%100 - licznik_id%10;
        str[3] = 48 + licznik_id%10;
        licznik_id++;
    }

    return str;
}

/// Funkcja sprawdzIDWizyta
/**
* Funkcja sprawdza, czy ID wizyty jest orginalne.
* Funkcja zwraca 1 (Fałsz) lub 0 (Prawda).
*/
int sprawdzIDWizyta(struct Wizyta *glowny, char id[5]) {
    int czastkowa = 0;
    struct Wizyta *node = glowny;
    do {
        if( strcmp(node->id, id) == 0) {
            return 1;
        }
        node = node->nastepny;
    } while (node != NULL);
    
    return 0;
}

/// Funkcja wybranaWizyta
/**
* Funkcja zwraca wizytę o podanym w drugim argumencie ID.
* 
*/
struct Wizyta * wybranaWizyta(struct Wizyta *head, char wizyta[5]) {
    struct Wizyta *tmp = head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->id, wizyta) == 0)
        {
            return tmp;
        }
        
        tmp = tmp->nastepny;
    }

    return NULL;
}

// Funkcje Zapisu I Odczytu Listy Lekarzy


    // Funkcja formatujaca dane lekarza
/// Funkcja strFFileWizyta
/**
* Funkcja tworzy i zwraca ciag znaków z danymi wizyty, w formacie odpowiednim do zapisu do pliku.
* 
*/
char * strFFileWizyta(struct Wizyta *glowny) {
    int dlugosc = 200;
    char *str = malloc(dlugosc);

    strcpy(str, glowny->id);
    strcat(str, "|");
    
    char intos[5];
    sprintf( intos, "%d", glowny->data.dzien);
    strcat(str, intos);
    strcat(str, "|");
    sprintf( intos, "%d", glowny->data.miesiac);
    strcat(str, intos);
    strcat(str, "|");
    sprintf( intos, "%d", glowny->data.rok);
    strcat(str, intos);
    strcat(str, "|");
    sprintf( intos, "%d", glowny->time.godzina);
    strcat(str, intos);
    strcat(str, "|");
    sprintf( intos, "%d", glowny->time.minuta);
    strcat(str, intos);
    strcat(str, "|");
    strcat(str, glowny->lekarz->id);
    strcat(str, "|");
    strcat(str, glowny->pacjent->id);
    strcat(str, "\n");
    return str;
}

    // Funkcja zapisu do pliku
/// Funkcja ZapiszWizyty
/**
* Funkcja zapisuje listę wizyt do pliku "lista_wizyt.txt" w folderze "dane".
* 
*/
void ZapiszWizyty(FILE *file, struct Wizyta *glowny) {
    if ((file = fopen("dane/lista_wizyt.txt", "w")) == NULL) {
        printf ("Nie mogę otworzyć pliku lista_wizyt.txt do zapisu !\n");
        return;
    }
    if (glowny == NULL) printf("Lista wizyt jest pusta.\n");
    else {
        while(glowny != NULL) {
            fprintf(file, "%s", strFFileWizyta(glowny));
            glowny = glowny->nastepny;
        }
        if (fwrite != 0) {
            printf("Lista zostala pomyslnie zapisana do pliku !\n");
        } else {
            printf("Blad zapisu do pliku !\n");
        }
    }
    fclose(file);
}

    // Funkcja odczytu z pliku
/// Funkcja OdczytajWizyty
/**
* Funkcja odczytuje listę wizyt z pliku "lista_wizyt.txt" w folderze "dane".
* 
*/
void OdczytajWizyty(FILE *file, struct Wizyta **glowny, struct Lekarz *head_lekarz, struct Pacjent *head_pacjent) {
    if ((file = fopen("dane/lista_wizyt.txt", "r")) == NULL) {
        printf ("Nie mogę otworzyć pliku lista_wizyt.txt do odczytu !\n");
        return;
    }

    char *linia = NULL;
    size_t len = 0;

    while (getline(&linia, &len, file) != -1) {
        
        char korektor[] = "|";
        char * schowek;
        char dane[8][5];
        int i = 0;
        schowek = strtok( linia, korektor );
        while( schowek != NULL )
        {
            strcpy(dane[i], schowek);
            i++;
            schowek = strtok( NULL, korektor );
        }

        struct Wizyta *nowaWizyta = (struct Wizyta *)malloc(sizeof(struct Wizyta));

        strcpy(nowaWizyta->id, dane[0]);
        
        nowaWizyta->data.dzien = atoi(dane[1]);
        nowaWizyta->data.miesiac = atoi(dane[2]);
        nowaWizyta->data.rok = atoi(dane[3]);
        nowaWizyta->time.godzina = atoi(dane[4]);
        nowaWizyta->time.minuta = atoi(dane[5]);
        nowaWizyta->lekarz = wybranyLekarz(head_lekarz, dane[6]);
        char id_p[5];
        for (int j = 0; j < 4; j++)
        {
            id_p[j] = dane[7][j];
        }
        id_p[5] = '\0';
        
        nowaWizyta->pacjent = wybranyPacjent(head_pacjent, id_p);
        nowaWizyta->poprzedni = nowaWizyta->nastepny = NULL;

        struct Wizyta *tmp = *glowny;

        if (*glowny == NULL) {
            nowaWizyta->poprzedni = NULL;
            *glowny = nowaWizyta;
        } else {
            while (tmp->nastepny != NULL) {
            tmp = tmp->nastepny;
            }

            tmp->nastepny = nowaWizyta;
            nowaWizyta->poprzedni = tmp;
        }
    }

    if (linia)
            free(linia);

    fclose(file);
}