#ifndef POMOC
#define POMOC

/// Struktura Daty
/**
 * Zawiera zmienne dzień, miesiąc i rok.
 * 
*/
struct Date
{
    int dzien;
    int miesiac;
    int rok;
};

/// Struktura Godzina
/**
 * Zawiera zmienne godzina i minuta.
 * 
*/
struct Hour {
    int godzina;
    int minuta;
};

char * generujEmail(char imie[], char nazwisko[], char platforma[]);

#endif