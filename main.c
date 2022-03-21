#include <stdio.h>
#include <stdlib.h>

struct Lekarz
{
    int id;
    char imie[20];
    char nazwisko[20];
    struct Lekarz* nastepny;
    struct Lekarz* poprzedni;
};

void DodajLekarzaNaKoniec(struct Lekarz **glowny, int id, char imie[], char nazwisko[]) {
    
    struct Lekarz *nowyLekarz = NULL;
    
    nowyLekarz = (struct Lekarz *)malloc(sizeof(struct Lekarz));

    nowyLekarz->id = id;
    strcpy(nowyLekarz->imie, imie);
    strcpy(nowyLekarz->nazwisko, nazwisko);

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
            printf("%d %s %s\n", ten->id, ten->imie, ten->nazwisko);
            ten = ten->nastepny;
        } while (ten != NULL);
    }
}


int main() {
    struct Lekarz *glowny;

    glowny = (struct Lekarz *)malloc(sizeof(struct Lekarz));

    glowny = NULL;

    wyswietlLekarzy(glowny);

    DodajLekarzaNaKoniec(&glowny, 123, "Adam", "Monetka");
    DodajLekarzaNaKoniec(&glowny, 231, "Radoslaw", "Koscielec");
    DodajLekarzaNaKoniec(&glowny, 321, "Mariusz", "Pudzianowski");

    wyswietlLekarzy(glowny);

    DodajLekarzaNaKoniec(&glowny, 213, "Wikary", "Marcepan");

    wyswietlLekarzy(glowny);
    
    return 0;
}