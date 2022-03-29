#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lekarz.h"

// struct Lekarz
// {
//     unsigned int id;
//     char imie[20];
//     char nazwisko[20];
//     char pesel[10];
//     char adres[40];
//     char email[40];
//     char tel[9];
//     unsigned int waga;
//     unsigned int wzrost;
//     char OddzialNFZ[60];

//     struct Lekarz* nastepny;
//     struct Lekarz* poprzedni;
// };

void dodajLekarzaNaKoniec(struct Lekarz **glowny, unsigned int id, char imie[], char nazwisko[], char pesel[], char adres[], char email[], char tel[], unsigned int waga, unsigned int wzrost, char OddzialNFZ[]) {
    
    struct Lekarz *nowyLekarz = NULL;
    
    nowyLekarz = (struct Lekarz *)malloc(sizeof(struct Lekarz));

    nowyLekarz->id = id;
    strcpy(nowyLekarz->imie, imie);
    strcpy(nowyLekarz->nazwisko, nazwisko);
    strcpy(nowyLekarz->pesel, pesel);
    strcpy(nowyLekarz->adres, adres);
    strcpy(nowyLekarz->email, email);
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
            printf("%d %s %s %s %s %s %s %d %d %s\n", ten->id, ten->imie, ten->nazwisko, ten->pesel, ten->adres, ten->email, ten->tel, ten->waga, ten->wzrost, ten->OddzialNFZ);
            ten = ten->nastepny;
        } while (ten != NULL);
    }
}
