// Lista Lekarzy i odpowiednie funkcje
struct Lekarz {
    char id[5];
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

void dodajLekarzaNaKoniec(struct Lekarz **glowny, char imie[], char nazwisko[], char pesel[], char adres[], char tel[], unsigned int waga, unsigned int wzrost, char OddzialNFZ[]);
void usunPierwszego(struct Lekarz **glowny);
void usunLekarza(struct Lekarz **glowny, char id[]);
void wyswietlLekarzy(struct Lekarz *glowny);
int liczbaLekarzy(struct Lekarz *glowny);
char * generujIDLekarz(struct Lekarz *glowny);
int sprawdzID(struct Lekarz *glowny, char id[5]);