#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lekarz.h"
#include "pomocnicze.h"

// Funkcje Operacji Na Liscie Lekarzy

void dodajLekarzaNaKoniec(struct Lekarz **glowny, char imie[], char nazwisko[], char pesel[], char adres[], char tel[], unsigned int waga, unsigned int wzrost, char OddzialNFZ[]) {
        
    struct Lekarz *nowyLekarz = (struct Lekarz *)malloc(sizeof(struct Lekarz));

    strcpy(nowyLekarz->id, generujIDLekarz(*glowny));
    strcpy(nowyLekarz->imie, imie);
    strcpy(nowyLekarz->nazwisko, nazwisko);
    strcpy(nowyLekarz->pesel, pesel);
    strcpy(nowyLekarz->adres, adres);
    strcpy(nowyLekarz->email, generujEmail(imie, nazwisko, "@przychodnia.lekarz.pl"));
    strcpy(nowyLekarz->tel, tel);
    nowyLekarz->waga = waga;
    nowyLekarz->wzrost = wzrost;
    strcpy(nowyLekarz->OddzialNFZ, OddzialNFZ);
    nowyLekarz->poprzedni = nowyLekarz->nastepny = NULL;

    struct Lekarz *tmp = *glowny;

    if (*glowny == NULL) {
        nowyLekarz->poprzedni = NULL;
        *glowny = nowyLekarz;
        return;
    }

    while (tmp->nastepny != NULL) {
        tmp = tmp->nastepny;
    }

    tmp->nastepny = nowyLekarz;
    nowyLekarz->poprzedni = tmp;
}

void usunPierwszego(struct Lekarz **glowny) {
    
	struct Lekarz *tmp = *glowny;
    if (tmp->nastepny != NULL)
    {
        *glowny = tmp->nastepny;
    }
    free(tmp);
}

void usunLekarza(struct Lekarz **glowny, char id[]) {

    if (strcmp( id, (*glowny)->id) == 0)
    {
        usunPierwszego(glowny);
    } else {
        struct Lekarz *node = *glowny;
        struct Lekarz *tmp;

        while (node->nastepny != NULL && strcmp( node->nastepny->id, id) != 0) {
            node = node->nastepny;
        }
        
        tmp=node->nastepny;
        node->nastepny = tmp->nastepny;
        tmp->nastepny->poprzedni = node;
        free(tmp);
        printf("Pomyslnie usunieto lekarza.\n\n");
    }
    
}

// Funkcje Dodatkowe Dla Listy Lekarzy

char * strFormat(struct Lekarz *glowny) {
    int dlugosc = 200;
    char *str = malloc(dlugosc);

    strcat(str, glowny->id);
    strcat(str, "   ");
    strcat(str, glowny->imie);
    for (int i = 0; i < 12 - strlen(glowny->imie) ; i++) {
        strcat(str, " ");
    }
    strcat(str, glowny->nazwisko);
    for (int i = 0; i < 15 - strlen(glowny->nazwisko) ; i++) {
        strcat(str, " ");
    }
    strcat(str, glowny->pesel);
    strcat(str, "   ");
    strcat(str, glowny->adres);
    for (int i = 0; i < 40 - strlen(glowny->adres) ; i++) {
        strcat(str, " ");
    }
    strcat(str, glowny->email);
    for (int i = 0; i < 40 - strlen(glowny->email) ; i++) {
        strcat(str, " ");
    }
    strcat(str, glowny->tel);
    for (int i = 0; i < 13 - strlen(glowny->tel) ; i++) {
        strcat(str, " ");
    }
    char intos[3];
    sprintf( intos, "%d", glowny->waga);
    strcat(str, intos);
    for (int i = 0; i < 6 - strlen(intos) ; i++) {
        strcat(str, " ");
    }
    sprintf( intos, "%d", glowny->wzrost);
    strcat(str, intos);
    for (int i = 0; i < 8 - strlen(intos) ; i++) {
        strcat(str, " ");
    }
    strcat(str, glowny->OddzialNFZ);

    return str;
}

void wyswietlLekarzy(struct Lekarz *glowny) {

    if (glowny == NULL) printf("\nLista lekarzy jest pusta.\n");
    else {
        printf("\nID     IMIE        NAZWISKO       PESEL        ADRES ZAMIESZKANIA                      EMAIL                                   TELEFON      WAGA  WZROST  ODDZIAL NFZ\n");
        while(glowny != NULL) {
            printf("%s\n", strFormat(glowny));
            glowny = glowny->nastepny;
        }
    }

}

int liczbaLekarzy(struct Lekarz *glowny) {
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

char * generujIDLekarz(struct Lekarz *glowny) {
    char *str = malloc(5);
    str[0] = 'L';
    str[1] = '0';
    str[2] = '0';
    str[3] = '0';
    str[4] = '\0';
    if (liczbaLekarzy(glowny) == 0) {
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

int sprawdzID(struct Lekarz *glowny, char id[5]) {
    int czastkowa = 0;
    struct Lekarz *node = glowny;
    do {
        if( strcmp(node->id, id) == 0) {
            return 1;
        }
        node = node->nastepny;
    } while (node != NULL);
    
    return 0;
}

// Funkcje Zapisu I Odczytu Listy Lekarzy

void ZapiszLekarzy(FILE *file, struct Lekarz *glowny) {
    if ((file = fopen("dane/lista_lekarzy.txt", "w")) == NULL) {
        printf ("Nie mogę otworzyć pliku lista_lekarzy.txt do zapisu !\n");
        return;
    }
    if (glowny == NULL) printf("Lista lekarzy jest pusta.\n");
    else {
        while(glowny != NULL) {
            fwrite(&glowny, sizeof(struct Lekarz), 1, file);
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

struct Lekarz *OdczytajLekarzy(FILE *file, struct Lekarz **glowny) {
    if ((file = fopen("dane/lista_lekarzy.txt", "r")) == NULL) {
        printf ("Nie mogę otworzyć pliku lista_lekarzy.txt do zapisu !\n");
        return;
    }
    struct Lekarz *tmp = *glowny;
    while (fread(&tmp, sizeof(struct Lekarz), 1, file)) {
        printf("%s\n", tmp->id);
    }
    fclose(file);
    return tmp;
}
