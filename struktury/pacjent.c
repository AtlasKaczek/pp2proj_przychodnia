#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pacjent.h"

void dodajPacjentaNaKoniec(struct Pacjent **glowny, char imie[], char nazwisko[], int dzien, int miesiac, int rok, char pesel[], char adres[], char email[], char tel[], unsigned int waga, unsigned int wzrost) {

    struct Pacjent *nowyPacjent = (struct Pacjent *)malloc(sizeof(struct Pacjent));

    strcpy(nowyPacjent->id, generujIDPacjent(*glowny));
    strcpy(nowyPacjent->imie, imie);
    strcpy(nowyPacjent->nazwisko, nazwisko);
    nowyPacjent->dob.dzien = dzien;
    nowyPacjent->dob.miesiac = miesiac;
    nowyPacjent->dob.rok = rok;
    strcpy(nowyPacjent->pesel, pesel);
    strcpy(nowyPacjent->adres, adres);
    strcpy(nowyPacjent->email, email);
    strcpy(nowyPacjent->tel, tel);
    nowyPacjent->waga = waga;
    nowyPacjent->wzrost = wzrost;
    nowyPacjent->poprzedni = nowyPacjent->nastepny = NULL;

    struct Pacjent *tmp = *glowny;

    if (*glowny == NULL) {
        nowyPacjent->poprzedni = NULL;
        *glowny = nowyPacjent;
        return;
    }

    while (tmp->nastepny != NULL) {
        tmp = tmp->nastepny;
    }

    tmp->nastepny = nowyPacjent;
    nowyPacjent->poprzedni = tmp;
}

void usunPierwszegoPacjenta(struct Pacjent **glowny) {
    
	struct Pacjent *tmp = *glowny;
    if (tmp->nastepny != NULL)
    {
        *glowny = tmp->nastepny;
    } else {
        *glowny = NULL;
    }
    free(tmp);
}

void usunOstatniegoPacjenta(struct Pacjent **glowny) {
    struct Pacjent *tmp;
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

void usunPacjenta (struct Pacjent **glowny, char id[]) {
    int liczba = 2;
    if (strcmp( id, (*glowny)->id) == 0 || liczbaPacjentow(*glowny) == 1)
    {
        usunPierwszegoPacjenta(glowny);
    } else {
        struct Pacjent *node = *glowny;
        struct Pacjent *tmp;

        while (node->nastepny != NULL && strcmp( node->nastepny->id, id) != 0) {
            node = node->nastepny;
            liczba++;
        }
        if (liczba == liczbaPacjentow(*glowny))
        {
            usunOstatniegoPacjenta(glowny);
        } else {
            tmp=node->nastepny;
            node->nastepny = tmp->nastepny;
            tmp->nastepny->poprzedni = node;
            free(tmp);
        }
        printf("Pomyslnie usunieto pacjenta.\n\n");
    }

}

void edytujPacjenta(struct Pacjent **glowny, int opcja) {
    
    switch (opcja)
    {
    case 1:
        printf("ID: %s -> ", (*glowny)->id);
        char id[5];
        scanf(" %4[^\n]%*c", id);
        while (strlen(id) != 4 || id[0] != 'P')
        {
            printf("Nie poprawna forma !\n");
            printf("ID: %s -> ", (*glowny)->id);
            scanf(" %4[^\n]%*c", id);
        }
        strcpy((*glowny)->id, id);
        break;
    
    case 2:
        printf("Imie: %s -> ", (*glowny)->imie);
        char imie[20];
        scanf(" %19[^\n]%*c", imie);
        strcpy((*glowny)->imie, imie);
        break;
    
    case 3:
        printf("Nazwisko: %s -> ", (*glowny)->nazwisko);
        char naz[20];
        scanf(" %19[^\n]%*c", naz);
        strcpy((*glowny)->nazwisko, naz);
        break;
    
    case 4:
        int dob;
        printf("Data urodzenia: %d/%d/%d -> \n", (*glowny)->dob.dzien), (*glowny)->dob.miesiac, (*glowny)->dob.rok);
        printf("Rok: ");
        scanf(" %d", &dob);
        while (dob < 1900 || dob > 2020)
        {
            printf("Bledne dane!\nRok: ");
            scanf(" %d", &dob);
        }
        (*glowny)->dob.rok = dob;
	    if((dob%4==0 && dob%100!=0) || dob%400==0)
        {
            printf("Miesiac: ");
            scanf(" %d", &dob);
            while (dob < 0 || dob > 12)
            {
                printf("Bledne dane!\nMiesiac: ");
                scanf(" %d", &dob);
            }
            (*glowny)->dob.miesiac = dob;
            if (dob == 1 || dob == 3 || dob == 5 || dob == 7 || dob == 8 || dob == 10 || dob == 12)
            {
                printf("Dzien: ");
                scanf(" %d", &dob);
                while (dob < 0 || dob > 31)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &dob);
                }
                (*glowny)->dob.dzien = dob;

            }
            else if (miesiac == 2)
            {
                printf("Dzien: ");
                scanf(" %d", &dob);
                while (dob < 0 || dob > 29)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &dob);
                }
                (*glowny)->dob.dzien = dob;

            }
            else
            {
                printf("Dzien: ");
                scanf(" %d", &dob);
                while (dob < 0 || dob > 30)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &dob);
                }
                (*glowny)->dob.dzien = dob;
        }
	    else
        {
            printf("Miesiac: ");
            scanf(" %d", &dob);
            while (dob < 0 || dob > 12)
            {
                printf("Bledne dane!\nMiesiac: ");
                scanf(" %d", &dob);
            }
            (*glowny)->dob.miesiac = dob;
            if (dob == 1 || dob == 3 || dob == 5 || dob == 7 || dob == 8 || dob == 10 || dob == 12)
            {
                printf("Dzien: ");
                scanf(" %d", &dob);
                while (dob < 0 || dob > 31)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &dob);
                }
                (*glowny)->dob.dzien = dob;
            }
            else if (miesiac == 2)
            {
                printf("Dzien: ");
                scanf(" %d", &dob);
                while (dob < 0 || dob > 28)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &dob);
                }
                (*glowny)->dob.dzien = dob;
        }
        break;
    
    case 5:
        printf("Pesel: %s -> ", (*glowny)->pesel);
        char pesel[12];
        scanf(" %11[^\n]%*c", pesel);
        strcpy((*glowny)->pesel, pesel);
        break;
    
    case 6:
        printf("Miejsce zamieszkania: %s -> ", (*glowny)->adres);
        char adr[40];
        scanf(" %39[^\n]%*c", adr);
        strcpy((*glowny)->nazwisko, adr);
        break;
    
    case 7:
        printf("Email: %s -> ", (*glowny)->email);
        char email[40];
        scanf(" %39[^\n]%*c", email);
        strcpy((*glowny)->email, email);
        break;
    
    case 8:
        printf("Nr.Telefonu: %s -> ", (*glowny)->tel);
        char tel[10];
        scanf(" %9[^\n]%*c", tel);
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
    
    default:
        break;
    }
    printf("\n");
}

void dodajPacjenta(struct Pacjent **glowny) {
    printf("\nDodaj pacjenta:\n");
            char imie[20];
            printf("Imie: ");
            scanf(" %19[^\n]%*c", imie);
            char nazwisko[21];
            printf("Nazwisko: ");
            scanf(" %19[^\n]%*c", nazwisko);
            int d, m, r;
            printf("Dzien urodzenia\nDzien: ");
            scanf(" %d", &d);
            while (d < 0 || d > 31)
            {
                printf("Bledne dane!\nDzien: ");
                scanf(" %d", &d);
            }   
            printf("Miesiac: ");
            scanf(" %d", &m);
            while (m < 0 || m > 12)
            {
                printf("Bledne dane!\nMiesiac: ");
                scanf(" %d", &m);
            } 
            printf("Rok: ");
            scanf(" %d", &r);
            while (r < 1900 || r > 2020)
            {
                printf("Bledne dane!\nRok: ");
                scanf(" %d", &r);
            } 
            char pesel[12];
            printf("PESEL: ");
            scanf(" %11[^\n]%*c", pesel);
            char adres[40];
            printf("Adres: ");
            scanf(" %39[^\n]%*c", adres);
            char email[40];
            printf("Email: ");
            scanf(" %39[^\n]%*s", email);
            char tel[40];
            printf("Telefon: ");
            scanf(" %9[^\n]%*c", tel);
            int waga, wzost;
            printf("Waga: ");
            scanf(" %d", &waga);
            printf("Wzrost: ");
            scanf(" %d", &wzost);


            printf("\nNowy pacjent:\n%s %s %d/%d/%d %s %s %s %s %d %d ", imie, nazwisko, d, m, r, pesel, adres, email, tel, waga, wzost);

            dodajPacjentaNaKoniec(glowny, imie, nazwisko, d, m, r, pesel, adres, email, tel, waga, wzost);

            printf("\n");
}

char * strFormatPacjent(struct Pacjent *glowny) {
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
    strcat(str, "  ");
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
    
    return str;
}

void wyswietlPacjentow(struct Pacjent *glowny) {

    if (glowny == NULL) printf("\nLista pacjentow jest pusta.\n");
    else {
        printf("\nID     IMIE        NAZWISKO       DZIEN URODZIN   PESEL        ADRES ZAMIESZKANIA                      EMAIL                                   TELEFON      WAGA  WZROST \n");
        while(glowny != NULL) {
            printf("%s\n", strFormatPacjent(glowny));
            glowny = glowny->nastepny;
        }
    }

}

void wyswietlPacjenta(struct Pacjent *glowny) {
    printf("1. ID: %s\n2. Imie: %s\n3. Nazwisko: %s\n4. Dzien urodzenia: %d/%d/%d\n5. PESEL: %s\n6. Adres zamieszkania: %s\n7. Email: %s\n8. Telefon: %s\n9. Waga: %d\n10. Wzrost: %d\n\n", glowny->id, glowny->imie, glowny->nazwisko, glowny->dob.dzien, glowny->dob.miesiac, glowny->dob.rok, glowny->pesel, glowny->adres, glowny->email, glowny->tel, glowny->waga, glowny->wzrost);
}

void edytujPacjentaMenu(struct Pacjent **glowny) {
    
    char id[5];
    printf("\nWybierz pacjenta, ktorego chcesz edytowac (id): ");
    scanf("%s", id);

    int opcja = -1;

    if (strcmp( id, (*glowny)->id) == 0)
    {
        while (opcja != 0)
        {
            wyswietlPacjenta(*glowny);
            printf("0. Zatwierdz");
            printf("Wybierz pole do edycji: ");
            scanf(" %d", &opcja);
            edytujPacjenta(glowny, opcja);
        }
        
    } else {
        struct Pacjent *node = *glowny;

        while (node->nastepny != NULL && strcmp( node->nastepny->id, id) != 0) {
            node = node->nastepny;
        }
        
        while (opcja != 0)
        {
            wyswietlPacjenta(node->nastepny);
            printf("0. Zatwierdz\n\n");
            printf("Wybierz pole do edycji: ");
            scanf(" %d", &opcja);
            edytujPacjenta(&(node->nastepny), opcja);
        }
    }
    
    printf("Pomyslnie edytowano pacjenta .\n");
}

int liczbaPacjentow(struct Pacjent *glowny) {
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

char * generujIDPacjent(struct Pacjent *glowny) {
    char *str = malloc(5);
    str[0] = 'P';
    str[1] = '0';
    str[2] = '0';
    str[3] = '0';
    str[4] = '\0';
    if (liczbaPacjentow(glowny) == 0) {
        return str;
    }
    int licznik_id = 0;
    while(sprawdzIDPacjent(glowny, str) == 1) {
        str[1] = 48 + licznik_id%1000 - licznik_id%100;
        str[2] = 48 + licznik_id%100 - licznik_id%10;
        str[3] = 48 + licznik_id%10;
        licznik_id++;
    }

    return str;
}

int sprawdzIDPacjent(struct Pacjent *glowny, char id[5]) {
    int czastkowa = 0;
    struct Pacjent *node = glowny;
    do {
        if( strcmp(node->id, id) == 0) {
            return 1;
        }
        node = node->nastepny;
    } while (node != NULL);
    
    return 0;
}

struct Pacjent * wybranyPacjent(struct Pacjent *head, char pacjent[5]) {
    struct Pacjent *tmp = head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->id, pacjent) == 0)
        {
            return tmp;
        }
        
        tmp = tmp->nastepny;
    }

    return NULL;
}

char * strFFilePacjent(struct Pacjent *glowny) {
    int dlugosc = 200;
    char *str = malloc(dlugosc);

    strcpy(str, glowny->id);
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
    strcat(str, "\n");

    return str;
}

void ZapiszPacjentow(FILE *file, struct Pacjent *glowny) {
    if ((file = fopen("dane/lista_pacjentow.txt", "w")) == NULL) {
        printf ("Nie mogę otworzyć pliku lista_pacjentow.txt do zapisu !\n");
        return;
    }
    if (glowny == NULL) printf("Lista pacjentow jest pusta.\n");
    else {
        while(glowny != NULL) {
            fprintf(file, "%s", strFFilePacjent(glowny));
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

void OdczytajPacjentow(FILE *file, struct Pacjent **glowny) {
    if ((file = fopen("dane/lista_pacjentow.txt", "r")) == NULL) {
        printf ("Nie mogę otworzyć pliku lista_pacjentow.txt do odczytu !\n");
        return;
    }

    char *linia = NULL;
    size_t len = 0;

    while (getline(&linia, &len, file) != -1) {
        
        char korektor[] = "|";
        char * schowek;
        char dane[12][40];
        int i = 0;
        schowek = strtok( linia, korektor );
        while( schowek != NULL )
        {
            strcpy(dane[i], schowek);
            i++;
            schowek = strtok( NULL, korektor );
        }

        struct Pacjent *nowyPacjent = (struct Pacjent *)malloc(sizeof(struct Pacjent));

        strcpy(nowyPacjent->id, dane[0]);
        strcpy(nowyPacjent->imie, dane[1]);
        strcpy(nowyPacjent->nazwisko, dane[2]);
        nowyPacjent->dob.dzien = atoi(dane[3]);
        nowyPacjent->dob.miesiac = atoi(dane[4]);
        nowyPacjent->dob.rok = atoi(dane[5]);
        strcpy(nowyPacjent->pesel, dane[6]);
        strcpy(nowyPacjent->adres, dane[7]);
        strcpy(nowyPacjent->email, dane[8]);
        strcpy(nowyPacjent->tel, dane[9]);
        nowyPacjent->waga = atoi(dane[10]);
        nowyPacjent->wzrost = atoi(dane[11]);
        nowyPacjent->poprzedni = nowyPacjent->nastepny = NULL;

        struct Pacjent *tmp = *glowny;

        if (*glowny == NULL) {
            nowyPacjent->poprzedni = NULL;
            *glowny = nowyPacjent;
        } else {
            while (tmp->nastepny != NULL) {
            tmp = tmp->nastepny;
            }

            tmp->nastepny = nowyPacjent;
            nowyPacjent->poprzedni = tmp;
        }
    }

    if (linia)
            free(linia);

    fclose(file);
}
