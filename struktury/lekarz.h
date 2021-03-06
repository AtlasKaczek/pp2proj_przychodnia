#ifndef LEKARZ
#define LEKARZ

#include "pomocnicze.h"

// Lista Lekarzy i odpowiednie funkcje

/// Struktura listy lekarzy
/** 
 * Zawiera wszystkie potrzebne zmienne do zaimplementowania listy dwukierunkowej i wszystkie dane lekarza.
 * 
*/
struct Lekarz {
    char id[5];
    char imie[20];
    char nazwisko[20];
    struct Date dob;
    char pesel[12];
    char adres[40];
    char email[40];
    char tel[10];
    struct Hour godzRozpoczeciaPracy;
    struct Hour godzZakonczeniaPracy;
    char OddzialNFZ[60];

    struct Lekarz* nastepny;
    struct Lekarz* poprzedni;
};

// Funkcje Operacji Na Liscie Lekarzy

void dodajLekarzaNaKoniec(struct Lekarz **glowny, char imie[], char nazwisko[], int dzien, int miesiac, int rok, char pesel[], char adres[], char tel[], int g_roz, int m_roz, int g_zak, int m_zak, char OddzialNFZ[]);
void usunPierwszego(struct Lekarz **glowny);
void usunOstatniego(struct Lekarz **glowny);
void usunLekarza(struct Lekarz **glowny, char id[]);
void edytujLekarzaMenu(struct Lekarz **glowny);
void edytujLekarza(struct Lekarz **glowny, int opcja);
void dodajLekarza(struct Lekarz **glowny);

// Funkcje Dodatkowe Dla Listy Lekarzy

void wyswietlLekarzy(struct Lekarz *glowny);
void wyswietlLekarza(struct Lekarz *glowny);
int liczbaLekarzy(struct Lekarz *glowny);
char * generujIDLekarz(struct Lekarz *glowny);
int sprawdzIDLekarz(struct Lekarz *glowny, char id[5]);
struct Lekarz * wybranyLekarz(struct Lekarz *head, char lekarz[5]);

// Funkcje Zapisu I Odczytu Listy Lekarzy

char * strFFileLekarz(struct Lekarz *glowny);
void ZapiszLekarzy(FILE *file, struct Lekarz *glowny);
void OdczytajLekarzy(FILE *file, struct Lekarz **glowny);

#endif