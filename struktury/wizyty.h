
#include "lekarz.h"
#include "pacjent.h"

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

struct Wizyta {
    
    char id[5];
    struct Date data;
    struct Hour time;
    struct Lekarz *lekarz;
    struct Pacjent *pacjent;

    struct Wizyta* nastepny;
    struct Wizyta* poprzedni;
};

void dodajWizyteNaKoniec(struct Wizyta **head, struct Lekarz *head_lekarz, struct Pacjent *head_pacjent, char id[5], int dzien, int miesiac, int rok, int godzina, int minuta, char lekarz[5], char pacjent[5]);
void usunPierwszaWizyte(struct Wizyta **glowny);
void usunOstatniaWizyte(struct Wizyta **glowny);
void usunWizyte(struct Wizyta **glowny, char id[]);
void edytujWizyte(struct Wizyta **glowny, int opcja);
void edytujWizyteMenu(struct Wizyta **glowny);

void wyswietlWizyty(struct Wizyta *glowny);
void wyswietlWizyte(struct Wizyta *glowny);
int sprawdzIDWizyta(struct Wizyta *glowny, char id[5]);
char * generujIDWizyta(struct Wizyta *glowny);
int liczbaWizyt(struct Wizyta *glowny);

char * strFFileWizyta(struct Wizyta *glowny);
void ZapiszWizyty(FILE *file, struct Wizyta *glowny);
void OdczytajWizyty(FILE *file, struct Wizyta **glowny, struct Lekarz *head_lekarz, struct Pacjent *head_pacjent);