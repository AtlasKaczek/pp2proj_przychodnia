#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lekarz.h"
#include "pacjent.h"
#include "wizyty.h"

void dodajWizyteNaKoniec(struct Wizyta **head, struct Lekarz *head_lekarz, struct Pacjent *head_pacjent, char id[5], int dzien, int miesiac, int rok, int godzina, int minuta, char lekarz[5], char pacjent[5]) {
    
    struct Wizyta *nowa = (struct Wizyta *)malloc(sizeof(struct Wizyta));
    strcpy(nowa->id, id);
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

char * generujIDWizyta(struct Wizyta *glowny) {
    char *str = malloc(5);
    str[0] = 'L';
    str[1] = '0';
    str[2] = '0';
    str[3] = '0';
    str[4] = '\0';
    if (liczbaWizyt(glowny) == 0) {
        return str;
    }
    int licznik_id = 0;
    while(sprawdzID(glowny, str) == 1) {
        str[1] = 48 + licznik_id%1000 - licznik_id%100;
        str[2] = 48 + licznik_id%100 - licznik_id%10;
        str[3] = 48 + licznik_id%10;
        licznik_id++;
    }

    return str;
}

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
    strcat(str, glowny->lekarz->id);
    strcat(str, "      ");
    strcat(str, glowny->pacjent->id);


    if (str[strlen(str)-1] == '\n')
    {
        str[strlen(str)-1] = '\0';
    }
    
    return str;
}

void wyswietlWizyty(struct Wizyta *glowny) {

    if (glowny == NULL) printf("\nLista wizyt jest pusta.\n");
    else {
        printf("\nID     DATA   GODZINA     LEKARZ  PACJENT\n");
        while(glowny != NULL) {
            printf("%s\n", strFormatWizyta(glowny));
            glowny = glowny->nastepny;
        }
    }

}

void wyswietlWizyte(struct Wizyta *glowny) {
    printf("1. ID: %s\n2. Data: %d/%d/%d\n3. Godzina: %d:%d\n4. Lekarz: %s %s (%s) \n5. Pacjent: %s %s (%s)\n", glowny->id, glowny->data.dzien, glowny->data.miesiac, glowny->data.rok, glowny->time.godzina, glowny->time.minuta, glowny->lekarz->imie, glowny->lekarz->nazwisko, glowny->lekarz->id, glowny->pacjent->imie, glowny->pacjent->nazwisko, glowny->pacjent->id);
}

void edytujWizyteMenu(struct Wizyta **glowny) {
    
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
            edytujLekarza(glowny, opcja);
        }
        
    } else {
        struct Wizyta *node = *glowny;

        while (node->nastepny != NULL && strcmp( node->nastepny->id, id) != 0) {
            node = node->nastepny;
        }
        
        while (opcja != 0)
        {
            wyswietlLekarza(node->nastepny);
            printf("0. Zatwierdz\n\n");
            printf("Wybierz pole do edycji: ");
            scanf(" %d", &opcja);
            edytujLekarza(&(node->nastepny), opcja);
        }
    }
    
    printf("Pomyslnie edytowano wizyte .\n");
}

void edytujWizyte(struct Wizyta **glowny, int opcja) {
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
        printf("Data: %d/%d/%d -> \n", (*glowny)->data.dzien, (*glowny)->data.miesiac, (*glowny)->data.rok);
        printf("Dzien: ");
        scanf(" %d", &data);
        (*glowny)->data.dzien = data;
        printf("Miesiac: ");
        scanf(" %d", &data);
        (*glowny)->data.miesiac = data;
        printf("Rok: ");
        scanf(" %d", &data);
        (*glowny)->data.rok = data;
        break;
    
    case 3:
        printf("Czas: %d:%d -> \n", (*glowny)->time.godzina, (*glowny)->time.minuta);
        printf("Godzina: ");
        scanf(" %d", &data);
        (*glowny)->time.godzina = data;
        printf("Minuta: ");
        scanf(" %d", &data);
        (*glowny)->time.minuta = data;
        break;
    
    case 4:
        printf("Lekarz: %s %s (%s) -> ID: ", (*glowny)->lekarz->imie, (*glowny)->lekarz->nazwisko, (*glowny)->lekarz->id);
        scanf(" %4[^\n]%*c", id);
        strcpy((*glowny)->lekarz->id, id);
        break;
    
    case 5:
        printf("Pacjent: %s %s (%s) ->  ID: ", (*glowny)->pacjent->imie, (*glowny)->pacjent->nazwisko, (*glowny)->pacjent->id);
        scanf(" %4[^\n]%*c", id);
        strcpy((*glowny)->pacjent->id, id);
        break;
    
    default:
        break;
    }
    printf("\n");
}

// Funkcje Zapisu I Odczytu Listy Lekarzy


    // Funkcja formatujaca dane lekarza
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

    return str;
}

    // Funkcja zapisu do pliku
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
        char dane[13][40];
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
        nowaWizyta->pacjent = wybranyPacjent(head_pacjent, dane[7]);
        
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
