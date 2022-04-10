#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lekarz.h"
#include "pomocnicze.h"

void dodajLekarzaNaKoniec(struct Lekarz **glowny, char imie[], char nazwisko[], char pesel[], char adres[], char tel[], unsigned int waga, unsigned int wzrost, char OddzialNFZ[]) {
    
    struct Lekarz *nowyLekarz = NULL;
    
    nowyLekarz = (struct Lekarz *)malloc(sizeof(struct Lekarz));

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

    struct Lekarz *temp = *glowny;

    if (*glowny == NULL) {
        nowyLekarz->poprzedni = NULL;
        *glowny = nowyLekarz;
        return;
    }

    while (temp->nastepny != NULL) {
        temp = temp->nastepny;
    }

    temp->nastepny = nowyLekarz;

    nowyLekarz->poprzedni = temp;
}

void wyswietlLekarzy(struct Lekarz *glowny) {
    
    printf("\n");

    if (glowny == NULL) printf("Lista lekarzy jest pusta.\n");
    else {
        struct Lekarz *ten = glowny;
        do {
            printf("%s %s %s %s %s %s %s %d %d %s\n", ten->id, ten->imie, ten->nazwisko, ten->pesel, ten->adres, ten->email, ten->tel, ten->waga, ten->wzrost, ten->OddzialNFZ);
            ten = ten->nastepny;
        } while (ten != NULL);
    }
}

int liczbaLekarzy(struct Lekarz *glowny) {
    int liczba = 0;
    if (glowny == NULL) return 0;
    else {
        struct Lekarz *ten = glowny;
        do {
            liczba++;
            ten = ten->nastepny;
        } while (ten != NULL);
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
    struct Lekarz *ten = glowny;
    do {
        for (int i = 1; i < 4; i++)
        {
            if (ten->id[i] == id[i])
            {
                czastkowa++;
            }
            
        }
        if (czastkowa == 3)
        {
            return 1;
        }
        czastkowa = 0;
        ten = ten->nastepny;
    } while (ten != NULL);
    
    return 0;
}