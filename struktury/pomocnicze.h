#ifndef POMOC
#define POMOC

struct Date
{
    int dzien;
    int miesiac;
    int rok;
};

struct Hour {
    int godzina;
    int minuta;
};

char * generujEmail(char imie[], char nazwisko[], char platforma[]);

#endif