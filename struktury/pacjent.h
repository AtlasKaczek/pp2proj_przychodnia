#ifndef PACJENT
#define PACJENT

#include "pomocnicze.h"

struct Pacjent {
    char id[5];
    char imie[20];
    char nazwisko[20];
    struct Date dob;
    char pesel[11];
    char adres[40];
    char email[40];
    char tel[10];
    unsigned int waga;
    unsigned int wzrost;

    struct Pacjent* nastepny;
    struct Pacjent* poprzedni;
};

void dodajPacjentaNaKoniec(struct Pacjent **glowny, char imie[], char nazwisko[], int dzien, int miesiac, int rok, char pesel[], char adres[], char email[], char tel[], unsigned int waga, unsigned int wzrost);
void usunPierwszegoPacjenta(struct Pacjent **glowny);
void usunOstatniegoPacjenta(struct Pacjent **glowny);
void usunPacjenta(struct Pacjent **glowny, char id[]);
void edytujPacjentaMenu(struct Pacjent **glowny);
void edytujPacjenta(struct Pacjent **glowny, int opcja);
void dodajPacjenta(struct Pacjent **glowny);

char * strFormatPacjent(struct Pacjent *glowny);
void wyswietlPacjentow(struct Pacjent *glowny);
void wyswietlPacjenta(struct Pacjent *glowny);
int liczbaPacjentow(struct Pacjent *glowny);
char * generujIDPacjent(struct Pacjent *glowny);
int sprawdzIDPacjent(struct Pacjent *glowny, char id[5]);
struct Pacjent *wybranyPacjent(struct Pacjent *head, char pacjent[5]);

char * strFFilePacjent(struct Pacjent *glowny);
void ZapiszPacjentow(FILE *file, struct Pacjent *glowny);
void OdczytajPacjentow(FILE *file, struct Pacjent **glowny);

#endif