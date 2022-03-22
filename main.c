#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lekarz
{
    unsigned int id;
    char imie[20];
    char nazwisko[20];
    char pesel[10];
    char adres[40];
    char email[40];
    char tel[9];
    unsigned int waga;
    unsigned int wzrost;
    char OddzialNFZ[60];

    struct Lekarz* nastepny;
    struct Lekarz* poprzedni;
};

void DodajLekarzaNaKoniec(struct Lekarz **glowny, unsigned int id, char imie[], char nazwisko[], char pesel[], char adres[], char email[], char tel[], unsigned int waga, unsigned int wzrost, char OddzialNFZ[]) {
    
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


int main() {
    struct Lekarz *glowny;

    glowny = (struct Lekarz *)malloc(sizeof(struct Lekarz));

    glowny = NULL;

    wyswietlLekarzy(glowny);

    DodajLekarzaNaKoniec(&glowny, 123, "Adam", "Monetka", "0123456789", "Kielce, ul.Jana Pawla II 14", "amonetka@przychodnia.lekarz.pl", "012345678", 78, 178, "NFZ nr 135");
    DodajLekarzaNaKoniec(&glowny, 231, "Radoslaw", "Koscielec", "0123456789", "Kielce, ul.Jana Pawla II 14", "rkoscielec@przychodnia.lekarz.pl", "012345678", 78, 178, "NFZ nr 135");
    DodajLekarzaNaKoniec(&glowny, 321, "Mariusz", "Pudzianowski", "0123456789", "Kielce, ul.Jana Pawla II 14", "mpudzian@przychodnia.lekarz.pl", "012345678", 78, 178, "NFZ nr 135");

    wyswietlLekarzy(glowny);

    DodajLekarzaNaKoniec(&glowny, 213, "Wikary", "Marcepan", "0123456789", "Kielce, ul.Jana Pawla II 14", "wmaecepan@przychodnia.lekarz.pl", "012345678", 78, 178, "NFZ nr 135");

    wyswietlLekarzy(glowny);
    
    return 0;
}