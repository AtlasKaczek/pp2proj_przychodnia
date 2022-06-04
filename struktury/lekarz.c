#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lekarz.h"
#include "pomocnicze.h"

// Funkcje Operacji Na Liscie Lekarzy

/// Funkcja sprawdzEmail
/**
* Funkcja generuje i sprawdza email, tak aby był unikalny.
* Funkcja zwraca ciag znaków zawierający email dla lekarza.
*
*/
char *sprawdzEmail(struct Lekarz *head, char imie[], char nazwisko[])
{
    char *mail = malloc(40);
    strcpy(mail, generujEmail(imie, nazwisko, "@przychodnia.lekarz.pl"));

    char nazw[40];
    char intos[5];
    int licznik = 0;
    struct Lekarz *node = head;
    do
    {
        if (strcmp(node->email, mail) == 0)
        {
            strcpy(nazw, nazwisko);
            sprintf(intos, "%d", licznik % 10);
            strcat(nazw, intos);
            strcpy(mail, generujEmail(imie, nazw, "@przychodnia.lekarz.pl"));
            licznik++;
            node = head;
        }
        node = node->nastepny;
    } while (node != NULL);
    return mail;
}

/// Funkcja dodajLekarzaNaKoniec
/**
* Funkcja dodaje tworzy lekarza na podstawie podanych argumentów i dodaje ją na koniec listy lekarzy.
* Funkcja nic nie zwraca.
*
*/
void dodajLekarzaNaKoniec(struct Lekarz **glowny, char imie[], char nazwisko[], int dzien, int miesiac, int rok, char pesel[], char adres[], char tel[], int g_roz, int m_roz, int g_zak, int m_zak, char OddzialNFZ[])
{

    struct Lekarz *nowyLekarz = (struct Lekarz *)malloc(sizeof(struct Lekarz));

    strcpy(nowyLekarz->id, generujIDLekarz(*glowny));
    strcpy(nowyLekarz->imie, imie);
    strcpy(nowyLekarz->nazwisko, nazwisko);
    nowyLekarz->dob.dzien = dzien;
    nowyLekarz->dob.miesiac = miesiac;
    nowyLekarz->dob.rok = rok;
    strcpy(nowyLekarz->pesel, pesel);
    strcpy(nowyLekarz->adres, adres);
    strcpy(nowyLekarz->email, sprawdzEmail(*glowny, nowyLekarz->imie, nowyLekarz->nazwisko));
    strcpy(nowyLekarz->tel, tel);
    nowyLekarz->godzRozpoczeciaPracy.godzina = g_roz;
    nowyLekarz->godzRozpoczeciaPracy.minuta = m_roz;
    nowyLekarz->godzZakonczeniaPracy.godzina = g_zak;
    nowyLekarz->godzZakonczeniaPracy.minuta = m_zak;
    strcpy(nowyLekarz->OddzialNFZ, OddzialNFZ);
    nowyLekarz->poprzedni = nowyLekarz->nastepny = NULL;

    struct Lekarz *tmp = *glowny;

    if (*glowny == NULL)
    {
        nowyLekarz->poprzedni = NULL;
        *glowny = nowyLekarz;
        return;
    }

    while (tmp->nastepny != NULL)
    {
        tmp = tmp->nastepny;
    }

    tmp->nastepny = nowyLekarz;
    nowyLekarz->poprzedni = tmp;
}

/// Funkcja usunPierwszego
/**
* Funkcja usuwa pierwszego lekarza z listy lekarzy.
* Funkcja nic nie zwraca.
*
*/
void usunPierwszego(struct Lekarz **glowny)
{

    struct Lekarz *tmp = *glowny;
    if (tmp->nastepny != NULL)
    {
        *glowny = tmp->nastepny;
    }
    else
    {
        *glowny = NULL;
    }
    free(tmp);
}

/// Funkcja usunOstatniego
/**
* Funkcja usuwa ostatniego lekarza z listy lekarzy.
* Funkcja nic nie zwraca.
*
*/
void usunOstatniego(struct Lekarz **glowny)
{
    struct Lekarz *tmp;
    if ((*glowny) == NULL)
    {
        return;
    }
    else if ((*glowny)->nastepny == NULL)
    {
        (*glowny) = NULL;
        free(*glowny);
    }
    else
    {
        tmp = *glowny;
        while (tmp->nastepny != NULL)
        {
            tmp = tmp->nastepny;
        }
        tmp->poprzedni->nastepny = NULL;
        free(tmp);
    }
}

/// Funkcja usunLekarza
/**
* Funkcja usuwa lekarza z listy lekarzy na podstawie drugiego argumentu - ID lekarza postaci L000.
* Funkcja nic nie zwraca.
*
*/
void usunLekarza(struct Lekarz **glowny, char id[])
{
    int liczba = 2;
    if (strcmp(id, (*glowny)->id) == 0 || liczbaLekarzy(*glowny) == 1)
    {
        usunPierwszego(glowny);
    }
    else
    {
        struct Lekarz *node = *glowny;
        struct Lekarz *tmp;

        while (node->nastepny != NULL && strcmp(node->nastepny->id, id) != 0)
        {
            node = node->nastepny;
            liczba++;
        }
        if (liczba == liczbaLekarzy(*glowny))
        {
            usunOstatniego(glowny);
        }
        else
        {
            tmp = node->nastepny;
            node->nastepny = tmp->nastepny;
            tmp->nastepny->poprzedni = node;
            free(tmp);
        }
        printf("Pomyslnie usunieto lekarza.\n\n");
    }
}

/// Funkcja edytujLekarzaMenu
/**
* Funkcja stworzona z myślą o użytkowniku. Pozwala wybrać lekarza i jego konkretne pole, a następnie edytować je.
* Funkcja nic nie zwraca.
*/
void edytujLekarzaMenu(struct Lekarz **glowny)
{

    char id[5];
    printf("\nWybierz lekarza, ktorego chcesz edytowac (id): ");
    scanf("%s", id);

    int opcja = -1;

    if (strcmp(id, (*glowny)->id) == 0)
    {
        while (opcja != 0)
        {
            wyswietlLekarza(*glowny);
            printf("0. Zatwierdz");
            printf("Wybierz pole do edycji: ");
            scanf(" %d", &opcja);
            edytujLekarza(glowny, opcja);
        }
    }
    else
    {
        struct Lekarz *node = *glowny;

        while (node->nastepny != NULL && strcmp(node->nastepny->id, id) != 0)
        {
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

/// Funkcja edytujLekarza
/**
* Funkcja pozwala edytować dane pole lekarza.
* Funkcja nic nie zwraca.
*/
void edytujLekarza(struct Lekarz **glowny, int opcja)
{
    int data;
    int dob;
    switch (opcja)
    {
    case 1:
        printf("ID: %s -> ", (*glowny)->id);
        char id[5];
        scanf(" %4[^\n]%*c", id);
        while (strlen(id) != 4 || id[0] != 'L')
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
        printf("Data urodzenia: %d/%d/%d -> \n", (*glowny)->dob.dzien, (*glowny)->dob.miesiac, (*glowny)->dob.rok);
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
            while (dob < 1 || dob > 12)
            {
                printf("Bledne dane!\nMiesiac: ");
                scanf(" %d", &dob);
            }
            (*glowny)->dob.miesiac = dob;
            if (dob == 1 || dob == 3 || dob == 5 || dob == 7 || dob == 8 || dob == 10 || dob == 12)
            {
                printf("Dzien: ");
                scanf(" %d", &dob);
                while (dob < 1 || dob > 31)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &dob);
                }
                (*glowny)->dob.dzien = dob;

            }
            else if (dob == 2)
            {
                printf("Dzien: ");
                scanf(" %d", &dob);
                while (dob < 1 || dob > 29)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &dob);
                }
                (*glowny)->dob.dzien = dob;

            }
            else if (dob == 4 || dob == 6 || dob == 9 || dob == 11)
            {
                printf("Dzien: ");
                scanf(" %d", &dob);
                while (dob < 1 || dob > 30)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &dob);
                }
                (*glowny)->dob.dzien = dob;
            }
        }
        else
        {
            printf("Miesiac: ");
            scanf(" %d", &dob);
            while (dob < 1 || dob > 12)
            {
                printf("Bledne dane!\nMiesiac: ");
                scanf(" %d", &dob);
            }
            (*glowny)->dob.miesiac = dob;
            if (dob == 1 || dob == 3 || dob == 5 || dob == 7 || dob == 8 || dob == 10 || dob == 12)
            {
                printf("Dzien: ");
                scanf(" %d", &dob);
                while (dob < 1 || dob > 31)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &dob);
                }
                (*glowny)->dob.dzien = dob;
            }
            else if (dob == 2)
            {
                printf("Dzien: ");
                scanf(" %d", &dob);
                while (dob < 1 || dob > 28)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &dob);
                }
                (*glowny)->dob.dzien = dob;
            }
            else if (dob == 4 || dob == 6 || dob == 9 || dob == 11)
            {
                printf("Dzien: ");
                scanf(" %d", &dob);
                while (dob < 1 || dob > 30)
                {
                    printf("Bledne dane!\nDzien: ");
                    scanf(" %d", &dob);
                }
                (*glowny)->dob.dzien = dob;
            }
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
        printf("Czas rozpoczecia pracy: %d:%d -> \n", (*glowny)->godzRozpoczeciaPracy.godzina, (*glowny)->godzRozpoczeciaPracy.minuta);
        printf("Godzina: ");
        scanf(" %d", &data);
        while (data < 0 || data > 23)
        {
            printf("Bledne dane!\nGodzina: ");
            scanf(" %d", &data);
        }
        (*glowny)->godzRozpoczeciaPracy.godzina = data;
        printf("Minuta: ");
        scanf(" %d", &data);
        while (data < 0 || data > 59)
        {
            printf("Bledne dane!\nMinuta: ");
            scanf(" %d", &data);
        }
        (*glowny)->godzRozpoczeciaPracy.minuta = data;
        break;

    case 10:
        printf("Czas zakonczenia pracy: %d:%d -> \n", (*glowny)->godzZakonczeniaPracy.godzina, (*glowny)->godzZakonczeniaPracy.minuta);
        printf("Godzina: ");
        scanf(" %d", &data);
        while (data < 0 || data > 23)
        {
            printf("Bledne dane!\nGodzina: ");
            scanf(" %d", &data);
        }
        (*glowny)->godzZakonczeniaPracy.godzina = data;
        printf("Minuta: ");
        scanf(" %d", &data);
        while (data < 0 || data > 59)
        {
            printf("Bledne dane!\nMinuta: ");
            scanf(" %d", &data);
        }
        (*glowny)->godzZakonczeniaPracy.minuta = data;
        break;

    case 11:
        printf("Oddzial NFZ: %s -> ", (*glowny)->OddzialNFZ);
        char nfz[40];
        scanf(" %39[^\n]%*c", nfz);
        strcpy((*glowny)->OddzialNFZ, nfz);
        break;

    default:
        break;
    }
    printf("\n");
}
/// Funkcja dodajLekarza
/**
* Funkcja stworzona z myślą o użytkowniku. Pozwala stworzyć lekarza po wprowadzeniu przez użytkownika danych.
* Funkcja nic nie zwraca.
*/
void dodajLekarza(struct Lekarz **glowny)
{
    printf("\nDodaj lekarza:\n");
    char imie[20];
    printf("Imie: ");
    scanf(" %19[^\n]%*c", imie);
    char nazwisko[21];
    printf("Nazwisko: ");
    scanf(" %19[^\n]%*c", nazwisko);
    int d, m, r;
    printf("Rok urodzenia: ");
    scanf(" %d", &r);
    while (r < 1900 || r > 2020)
    {
        printf("Bledne dane!\nRok: ");
        scanf(" %d", &r);
    }
    if ((r % 4 == 0 && r % 100 != 0) || r % 400 == 0)
    {
        printf("Miesiac urodzenia: ");
        scanf(" %d", &m);
        while (m < 1 || m > 12)
        {
            printf("Bledne dane!\nMiesiac: ");
            scanf(" %d", &m);
        }
        if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        {
            printf("Dzien urodzenia: ");
            scanf(" %d", &d);
            while (d < 1 || d > 31)
            {
                printf("Bledne dane!\nDzien: ");
                scanf(" %d", &d);
            }
        }
        else if (m == 2)
        {
            printf("Dzien urodzenia: ");
            scanf(" %d", &d);
            while (d < 1 || d > 29)
            {
                printf("Bledne dane!\nDzien: ");
                scanf(" %d", &d);
            }
        }
        else if (m == 4 || m == 6 || m == 9 || m == 11)
        {
            printf("Dzien: ");
            scanf(" %d", &d);
            while (d < 1 || d > 30)
            {
                printf("Bledne dane!\nDzien: ");
                scanf(" %d", &d);
            }
        }
    }
    else
    {
        printf("Miesiac urodzenia: ");
        scanf(" %d", &m);
        while (m < 1 || m > 12)
        {
            printf("Bledne dane!\nMiesiac: ");
            scanf(" %d", &m);
        }
        if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        {
            printf("Dzien urodzenia: ");
            scanf(" %d", &d);
            while (d < 1 || d > 31)
            {
                printf("Bledne dane!\nDzien: ");
                scanf(" %d", &d);
            }
        }
        else if (m == 2)
        {
            printf("Dzien urodzenia: ");
            scanf(" %d", &d);
            while (d < 1 || d > 28)
            {
                printf("Bledne dane!\nDzien: ");
                scanf(" %d", &d);
            }
        }
        else if (m == 4 || m == 6 || m == 9 || m == 11)
        {
            printf("Dzien urodzenia: ");
            scanf(" %d", &d);
            while (d < 1 || d > 30)
            {
                printf("Bledne dane!\nDzien: ");
                scanf(" %d", &d);
            }
        }
    }
    char pesel[12];
    printf("PESEL: ");
    scanf(" %11[^\n]%*c", pesel);
    char adres[40];
    printf("Adres: ");
    scanf(" %39[^\n]%*c", adres);
    char tel[40];
    printf("Telefon: ");
    scanf(" %9[^\n]%*c", tel);
    int g_roz, m_roz, g_zak, m_zak;
    printf("Czas rozpoczecia pracy:\n");
    printf("Godzina: ");
    scanf(" %d", &g_roz);
    while (g_roz < 0 || g_roz > 23)
    {
        printf("Bledne dane!\nGodzina: ");
        scanf(" %d", &g_roz);
    }
    printf("Minuta: ");
    scanf(" %d", &m_roz);
    while (m_roz < 0 || m_roz > 59)
    {
        printf("Bledne dane!\nMinuta: ");
        scanf(" %d", &m_roz);
    }
    printf("Czas zakonczenia pracy:\n");
    printf("Godzina: ");
    scanf(" %d", &g_zak);
    while (g_zak < 0 || g_zak > 23)
    {
        printf("Bledne dane!\nGodzina: ");
        scanf(" %d", &g_zak);
    }
    printf("Minuta: ");
    scanf(" %d", &m_zak);
    while (m_zak < 0 || m_zak > 59)
    {
        printf("Bledne dane!\nMinuta: ");
        scanf(" %d", &m_zak);
    }
    char NFZ[40];
    printf("Oddzial NFZ: ");
    scanf(" %39[^\n]%*c", NFZ);

    printf("\nNowy lekarz:\n%s %s %d/%d/%d %s %s %s %d:%d %d:%d %s", imie, nazwisko, d, m, r, pesel, adres, tel, g_roz, m_roz, g_zak, m_zak, NFZ);

    dodajLekarzaNaKoniec(glowny, imie, nazwisko, d, m, r, pesel, adres, tel, g_roz, m_roz, g_zak, m_zak, NFZ);

    printf("\n");
}

// Funkcje Dodatkowe Dla Listy Lekarzy

/// Funkcja strFormat
/**
* Funkcja tworzy i zwraca ciąg znaków zawierający dane konkretnego lekarza.
* Funkcja wykorzystywana podczas wyświetlania listy lekarzy.
*
*/
char *strFormat(struct Lekarz *glowny)
{
    int dlugosc = 200;
    char *str = malloc(dlugosc);

    strcpy(str, glowny->id);
    strcat(str, "   ");
    strcat(str, glowny->imie);
    for (int i = 0; i < 12 - strlen(glowny->imie); i++)
    {
        strcat(str, " ");
    }
    strcat(str, glowny->nazwisko);
    for (int i = 0; i < 15 - strlen(glowny->nazwisko); i++)
    {
        strcat(str, " ");
    }
    char intos[5];
    if (glowny->dob.dzien < 10)
    {
        strcat(str, "0");
    }
    sprintf(intos, "%d", glowny->dob.dzien);
    strcat(str, intos);
    strcat(str, "/");
    if (glowny->dob.miesiac < 10)
    {
        strcat(str, "0");
    }
    sprintf(intos, "%d", glowny->dob.miesiac);
    strcat(str, intos);
    strcat(str, "/");
    sprintf(intos, "%d", glowny->dob.rok);
    strcat(str, intos);
    strcat(str, "      ");
    strcat(str, glowny->pesel);
    strcat(str, "  ");
    strcat(str, glowny->adres);
    for (int i = 0; i < 40 - strlen(glowny->adres); i++)
    {
        strcat(str, " ");
    }
    strcat(str, glowny->email);
    for (int i = 0; i < 40 - strlen(glowny->email); i++)
    {
        strcat(str, " ");
    }
    strcat(str, glowny->tel);
    for (int i = 0; i < 13 - strlen(glowny->tel); i++)
    {
        strcat(str, " ");
    }
    if (glowny->godzRozpoczeciaPracy.godzina < 10)
    {
        sprintf(intos, "%d", 0);
        strcat(str, intos);
    }
    sprintf(intos, "%d", glowny->godzRozpoczeciaPracy.godzina);
    strcat(str, intos);
    strcat(str, ":");
    if (glowny->godzRozpoczeciaPracy.minuta < 10)
    {
        sprintf(intos, "%d", 0);
        strcat(str, intos);
    }
    sprintf(intos, "%d", glowny->godzRozpoczeciaPracy.minuta);
    strcat(str, intos);
    strcat(str, "       ");
    if (glowny->godzZakonczeniaPracy.godzina < 10)
    {
        sprintf(intos, "%d", 0);
        strcat(str, intos);
    }
    sprintf(intos, "%d", glowny->godzZakonczeniaPracy.godzina);
    strcat(str, intos);
    strcat(str, ":");
    if (glowny->godzZakonczeniaPracy.minuta < 10)
    {
        sprintf(intos, "%d", 0);
        strcat(str, intos);
    }
    sprintf(intos, "%d", glowny->godzZakonczeniaPracy.minuta);
    strcat(str, intos);
    strcat(str, "       ");
    strcat(str, glowny->OddzialNFZ);
    if (str[strlen(str) - 1] == '\n')
    {
        str[strlen(str) - 1] = '\0';
    }

    return str;
}

/// Funkcja wyswietlLekarzy
/**
* Funkcja wyświetla listę lekarzy.
* Funkcja nic nie zwraca.
*/
void wyswietlLekarzy(struct Lekarz *glowny)
{

    if (glowny == NULL)
        printf("\nLista lekarzy jest pusta.\n");
    else
    {
        printf("\nID     IMIE        NAZWISKO       DZIEN URODZIN   PESEL        ADRES ZAMIESZKANIA                      EMAIL                                   TELEFON      GODZ. ROZ.  GODZ. ZAK.  ODDZIAL NFZ\n");
        while (glowny != NULL)
        {
            printf("%s\n", strFormat(glowny));
            glowny = glowny->nastepny;
        }
    }
}

/// Funkcja wyswietlLekarza
/**
* Funkcja wyświetla konkretngo lekarza.
* Funkcja nic nie zwraca.
*/
void wyswietlLekarza(struct Lekarz *glowny)
{
    printf("1. ID: %s\n2. Imie: %s\n3. Nazwisko: %s\n4. Dzien urodzenia: %d/%d/%d\n5. PESEL: %s\n6. Adres zamieszkania: %s\n7. Email: %s\n8. Telefon: %s\n9. Godz. rozpoczecia pracy: %d:%d\n10. Godz. zakonczenia pracy: %d:%d\n11. Oddzial NFZ: %s\n\n", glowny->id, glowny->imie, glowny->nazwisko, glowny->dob.dzien, glowny->dob.miesiac, glowny->dob.rok, glowny->pesel, glowny->adres, glowny->email, glowny->tel, glowny->godzRozpoczeciaPracy.godzina, glowny->godzRozpoczeciaPracy.minuta, glowny->godzZakonczeniaPracy.godzina, glowny->godzZakonczeniaPracy.minuta, glowny->OddzialNFZ);
}

/// Funkcja liczbaLekarzy
/**
* Funkcja zlicza aktualną liczbę lekarzy w liście lekarzy i zwraca tą liczbę.
*
*
*/
int liczbaLekarzy(struct Lekarz *glowny)
{
    int liczba = 0;
    if (glowny == NULL)
        return 0;
    else
    {
        while (glowny != NULL)
        {
            liczba++;
            glowny = glowny->nastepny;
        }
    }
    return liczba;
}

/// Funkcja generujIDLekarz
/**
* Funkcja generuje i zwraca orginalne ID lekarza.
* 
*/
char *generujIDLekarz(struct Lekarz *glowny)
{
    char *str = malloc(5);
    str[0] = 'L';
    str[1] = '0';
    str[2] = '0';
    str[3] = '0';
    str[4] = '\0';
    if (liczbaLekarzy(glowny) == 0)
    {
        return str;
    }
    int licznik_id = 0;
    while (sprawdzIDLekarz(glowny, str) == 1)
    {
        str[1] = 48 + licznik_id % 1000 - licznik_id % 100;
        str[2] = 48 + licznik_id % 100 - licznik_id % 10;
        str[3] = 48 + licznik_id % 10;
        licznik_id++;
    }

    return str;
}

/// Funkcja sprawdzIDWizyta
/**
* Funkcja sprawdza, czy ID lekarza jest orginalne.
* Funkcja zwraca 1 (Fałsz) lub 0 (Prawda).
*/
int sprawdzIDLekarz(struct Lekarz *glowny, char id[5])
{
    struct Lekarz *node = glowny;
    do
    {
        if (strcmp(node->id, id) == 0)
        {
            return 1;
        }
        node = node->nastepny;
    } while (node != NULL);

    return 0;
}

/// Funkcja wybranyLekarz
/**
* Funkcja zwraca lekarza o podanym w drugim argumencie ID.
* 
*/
struct Lekarz *wybranyLekarz(struct Lekarz *head, char lekarz[5])
{
    struct Lekarz *tmp = head;
    while (tmp != NULL)
    {
        if (strcmp(tmp->id, lekarz) == 0)
        {
            return tmp;
        }

        tmp = tmp->nastepny;
    }

    return NULL;
}

// Funkcje Zapisu I Odczytu Listy Lekarzy

// Funkcja formatujaca dane lekarza

/// Funkcja strFFileLekarz
/**
* Funkcja tworzy i zwraca ciag znaków z danymi lekarza, w formacie odpowiednim do zapisu do pliku.
* 
*/
char *strFFileLekarz(struct Lekarz *glowny)
{
    int dlugosc = 200;
    char *str = malloc(dlugosc);

    strcpy(str, glowny->id);
    strcat(str, "|");
    strcat(str, glowny->imie);
    strcat(str, "|");
    strcat(str, glowny->nazwisko);
    strcat(str, "|");
    char intos[5];
    sprintf(intos, "%d", glowny->dob.dzien);
    strcat(str, intos);
    strcat(str, "|");
    sprintf(intos, "%d", glowny->dob.miesiac);
    strcat(str, intos);
    strcat(str, "|");
    sprintf(intos, "%d", glowny->dob.rok);
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
    sprintf(intos, "%d", glowny->godzRozpoczeciaPracy.godzina);
    strcat(str, intos);
    strcat(str, "|");
    sprintf(intos, "%d", glowny->godzRozpoczeciaPracy.minuta);
    strcat(str, intos);
    strcat(str, "|");
    sprintf(intos, "%d", glowny->godzZakonczeniaPracy.godzina);
    strcat(str, intos);
    strcat(str, "|");
    sprintf(intos, "%d", glowny->godzZakonczeniaPracy.minuta);
    strcat(str, intos);
    strcat(str, "|");
    strcat(str, glowny->OddzialNFZ);

    return str;
}

// Funkcja zapisu do pliku

/// Funkcja ZapiszLekarzy
/**
* Funkcja zapisuje listę lekarzy do pliku "lista_lekarzy.txt" w folderze "dane".
* 
*/
void ZapiszLekarzy(FILE *file, struct Lekarz *glowny)
{
    if ((file = fopen("dane/lista_lekarzy.txt", "w")) == NULL)
    {
        printf("Nie mogę otworzyć pliku lista_lekarzy.txt do zapisu !\n");
        return;
    }
    if (glowny == NULL)
        printf("Lista lekarzy jest pusta.\n");
    else
    {
        while (glowny != NULL)
        {
            fprintf(file, "%s", strFFileLekarz(glowny));
            glowny = glowny->nastepny;
        }
        if (fwrite != 0)
        {
            printf("Lista zostala pomyslnie zapisana do pliku !\n");
        }
        else
        {
            printf("Blad zapisu do pliku !\n");
        }
    }
    fclose(file);
}

// Funkcja odczytu z pliku

/// Funkcja OdczytajLekarzy
/**
* Funkcja odczytuje listę lekarzy z pliku "lista_lekarzy.txt" w folderze "dane".
* 
*/
void OdczytajLekarzy(FILE *file, struct Lekarz **glowny)
{
    if ((file = fopen("dane/lista_lekarzy.txt", "r")) == NULL)
    {
        printf("Nie mogę otworzyć pliku lista_lekarzy.txt do odczytu !\n");
        return;
    }

    char *linia = NULL;
    size_t len = 0;

    while (getline(&linia, &len, file) != -1)
    {

        char korektor[] = "|";
        char *schowek;
        char dane[15][40];
        int i = 0;
        schowek = strtok(linia, korektor);
        while (schowek != NULL)
        {
            strcpy(dane[i], schowek);
            i++;
            schowek = strtok(NULL, korektor);
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
        nowyLekarz->godzRozpoczeciaPracy.godzina = atoi(dane[10]);
        nowyLekarz->godzRozpoczeciaPracy.minuta = atoi(dane[11]);
        nowyLekarz->godzZakonczeniaPracy.godzina = atoi(dane[12]);
        nowyLekarz->godzZakonczeniaPracy.minuta = atoi(dane[13]);
        strcpy(nowyLekarz->OddzialNFZ, dane[14]);
        nowyLekarz->poprzedni = nowyLekarz->nastepny = NULL;

        struct Lekarz *tmp = *glowny;

        if (*glowny == NULL)
        {
            nowyLekarz->poprzedni = NULL;
            *glowny = nowyLekarz;
        }
        else
        {
            while (tmp->nastepny != NULL)
            {
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
