#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lekarz.h"
#include "pomocnicze.h"

// Funkcje Operacji Na Liscie Lekarzy

void dodajLekarzaNaKoniec(struct Lekarz **glowny, char imie[], char nazwisko[], int dzien, int miesiac, int rok, char pesel[], char adres[], char tel[], unsigned int waga, unsigned int wzrost, char OddzialNFZ[]) {
        
    struct Lekarz *nowyLekarz = (struct Lekarz *)malloc(sizeof(struct Lekarz));

    strcpy(nowyLekarz->id, generujIDLekarz(*glowny));
    strcpy(nowyLekarz->imie, imie);
    strcpy(nowyLekarz->nazwisko, nazwisko);
    nowyLekarz->dob.dzien = dzien;
    nowyLekarz->dob.miesiac = miesiac;
    nowyLekarz->dob.rok = rok;
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

void usunOstatniego(struct Lekarz **glowny) {
    struct Lekarz *tmp;
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
        if (strcmp( node->nastepny->id, id) == 0)
        {
            usunOstatniego(glowny);
        } else {
            tmp=node->nastepny;
            node->nastepny = tmp->nastepny;
            tmp->nastepny->poprzedni = node;
            free(tmp);
        }
        printf("Pomyslnie usunieto lekarza.\n\n");
    }
    
}

void edytujLekarzaMenu(struct Lekarz **glowny) {
    
    char id[5];
    printf("\nWybierz lekarza, ktorego chcesz edytowac (id): ");
    scanf("%s", id);

    int opcja = -1;

    if (strcmp( id, (*glowny)->id) == 0)
    {
        while (opcja != 0)
        {
            wyswietlLekarza(*glowny);
            printf("0. Zatwierdz");
            printf("Wybierz pole do edycji: ");
            scanf(" %d", &opcja);
            edytujLekarza(glowny, opcja);
        }
        
    } else {
        struct Lekarz *node = *glowny;

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
    
    printf("Pomyslnie edytowano lekarza .\n");
}

void edytujLekarza(struct Lekarz **glowny, int opcja) {
    
    switch (opcja)
    {
    case 1:
        printf("ID: %s -> ", (*glowny)->id);
        char id[5];
        scanf("%s", id);
        strcpy((*glowny)->id, id);
        break;
    
    case 2:
        printf("Imie: %s -> ", (*glowny)->imie);
        char imie[20];
        scanf("%s", imie);
        strcpy((*glowny)->imie, imie);
        break;
    
    case 3:
        printf("Nazwisko: %s -> ", (*glowny)->nazwisko);
        char naz[20];
        scanf("%s", naz);
        strcpy((*glowny)->nazwisko, naz);
        break;
    
    case 4:
        printf("Data urodzenia: %d/%d/%d -> \n", (*glowny)->dob.dzien, (*glowny)->dob.miesiac, (*glowny)->dob.rok);
        int dob;
        printf("Dzien: ");
        scanf(" %d", &dob);
        (*glowny)->dob.dzien = dob;
        printf("Miesiac: ");
        scanf(" %d", &dob);
        (*glowny)->dob.miesiac = dob;
        printf("Rok: ");
        scanf(" %d", &dob);
        (*glowny)->dob.rok = dob;
        break;
    
    case 5:
        printf("Pesel: %s -> ", (*glowny)->pesel);
        char pesel[11];
        scanf("%s", pesel);
        strcpy((*glowny)->pesel, pesel);
        break;
    
    case 6:
        printf("Miejsce zamieszkania: %s -> ", (*glowny)->adres);
        char adr[40];
        scanf("%s", adr);
        strcpy((*glowny)->nazwisko, adr);
        break;
    
    case 7:
        printf("Email: %s -> ", (*glowny)->email);
        char email[40];
        scanf("%s", email);
        strcpy((*glowny)->email, email);
        break;
    
    case 8:
        printf("Nr.Telefonu: %s -> ", (*glowny)->tel);
        char tel[10];
        scanf("%s", tel);
        strcpy((*glowny)->tel, tel);
        break;
    
    case 9:
        printf("Waga: %d -> ", (*glowny)->waga);
        int waga;
        scanf(" %d", &waga);
        (*glowny)->waga = waga;
        break;
    
    case 10:
        printf("Wzrost: %d -> ", (*glowny)->wzrost);
        int wzrost;
        scanf(" %d", &wzrost);
        (*glowny)->wzrost = wzrost;
        break;
    
    case 11:
        printf("Oddzial NFZ: %s -> ", (*glowny)->OddzialNFZ);
        char nfz[40];
        scanf("%s", nfz);
        strcpy((*glowny)->OddzialNFZ, nfz);
        break;
    
    default:
        break;
    }
    printf("\n");
}

// Funkcje Dodatkowe Dla Listy Lekarzy

char * strFormat(struct Lekarz *glowny) {
    int dlugosc = 200;
    char * str = malloc(dlugosc);

    

    strcpy(str, glowny->id);
    strcat(str, "   ");
    strcat(str, glowny->imie);
    for (int i = 0; i < 12 - strlen(glowny->imie) ; i++) {
        strcat(str, " ");
    }
    strcat(str, glowny->nazwisko);
    for (int i = 0; i < 15 - strlen(glowny->nazwisko) ; i++) {
        strcat(str, " ");
    }
    char intos[5];
    if(glowny->dob.dzien < 10) {
        strcat(str, "0");
    }
    sprintf( intos, "%d", glowny->dob.dzien);
    strcat(str, intos);
    strcat(str, "/");
    if(glowny->dob.miesiac < 10) {
        strcat(str, "0");
    }
    sprintf( intos, "%d", glowny->dob.miesiac);
    strcat(str, intos);
    strcat(str, "/");
    sprintf( intos, "%d", glowny->dob.rok);
    strcat(str, intos);
    strcat(str, "      ");
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
        printf("\nID     IMIE        NAZWISKO       DZIEN URODZIN   PESEL        ADRES ZAMIESZKANIA                      EMAIL                                   TELEFON      WAGA  WZROST  ODDZIAL NFZ\n");
        while(glowny != NULL) {
            printf("%s\n", strFormat(glowny));
            glowny = glowny->nastepny;
        }
    }

}

void wyswietlLekarza(struct Lekarz *glowny) {
    printf("1. ID: %s\n2. Imie: %s\n3. Nazwisko: %s\n4. Dzien urodzenia: %d/%d/%d\n5. PESEL: %s\n6. Adres zamieszkania: %s\n7. Email: %s\n8. Telefon: %s\n9. Waga: %d\n10. Wzrost: %d\n11. Oddzial NFZ: %s\n\n", glowny->id, glowny->imie, glowny->nazwisko, glowny->dob.dzien, glowny->dob.miesiac, glowny->dob.rok, glowny->pesel, glowny->adres, glowny->email, glowny->tel, glowny->waga, glowny->wzrost, glowny->OddzialNFZ);
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


    // Funkcja formatujaca dane lekarza
char * strFFile(struct Lekarz *glowny) {
    int dlugosc = 200;
    char *str = malloc(dlugosc);

    strcat(str, glowny->id);
    strcat(str, "|");
    strcat(str, glowny->imie);
    strcat(str, "|");
    strcat(str, glowny->nazwisko);
    strcat(str, "|");
    char intos[5];
    sprintf( intos, "%d", glowny->dob.dzien);
    strcat(str, intos);
    strcat(str, "|");
    sprintf( intos, "%d", glowny->dob.miesiac);
    strcat(str, intos);
    strcat(str, "|");
    sprintf( intos, "%d", glowny->dob.rok);
    strcat(str, intos);
    strcat(str, "|");
    strcat(str, glowny->pesel);
    strcat(str, "|");
    strcat(str, glowny->adres);
    strcat(str, "|");
    strcat(str, glowny->email);
    strcat(str, "|");
    strcat(str, glowny->tel);
    strcat(str, "|");
    sprintf( intos, "%d", glowny->waga);
    strcat(str, intos);
    strcat(str, "|");
    sprintf( intos, "%d", glowny->wzrost);
    strcat(str, intos);
    strcat(str, "|");
    strcat(str, glowny->OddzialNFZ);

    return str;
}

    // Funkcja zapisu do pliku
void ZapiszLekarzy(FILE *file, struct Lekarz *glowny) {
    if ((file = fopen("dane/lista_lekarzy.txt", "wb+")) == NULL) {
        printf ("Nie mogę otworzyć pliku lista_lekarzy.txt do zapisu !\n");
        return;
    }
    if (glowny == NULL) printf("Lista lekarzy jest pusta.\n");
    else {
        while(glowny != NULL) {
            fprintf(file, "%s\n", strFFile(glowny));
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
void OdczytajLekarzy(FILE *file, struct Lekarz **glowny) {
    if ((file = fopen("dane/lista_lekarzy.txt", "r")) == NULL) {
        printf ("Nie mogę otworzyć pliku lista_lekarzy.txt do zapisu !\n");
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

        struct Lekarz *nowyLekarz = (struct Lekarz *)malloc(sizeof(struct Lekarz));

        strcpy(nowyLekarz->id, dane[0]);
        strcpy(nowyLekarz->imie, dane[1]);
        strcpy(nowyLekarz->nazwisko, dane[2]);
        nowyLekarz->dob.dzien = atoi(dane[3]);
        nowyLekarz->dob.miesiac = atoi(dane[4]);
        nowyLekarz->dob.rok = atoi(dane[5]);
        strcpy(nowyLekarz->pesel, dane[6]);
        strcpy(nowyLekarz->adres, dane[7]);
        strcpy(nowyLekarz->email, dane[8]);
        strcpy(nowyLekarz->tel, dane[9]);
        nowyLekarz->waga = atoi(dane[10]);
        nowyLekarz->wzrost = atoi(dane[11]);
        strcpy(nowyLekarz->OddzialNFZ, dane[12]);
        nowyLekarz->poprzedni = nowyLekarz->nastepny = NULL;

        struct Lekarz *tmp = *glowny;

        if (*glowny == NULL) {
            nowyLekarz->poprzedni = NULL;
            *glowny = nowyLekarz;
        } else {
            while (tmp->nastepny != NULL) {
            tmp = tmp->nastepny;
            }

            tmp->nastepny = nowyLekarz;
            nowyLekarz->poprzedni = tmp;
        }
    }

    if (linia)
            free(linia);

    fclose(file);
}
