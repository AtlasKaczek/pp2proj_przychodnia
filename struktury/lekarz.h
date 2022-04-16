// Lista Lekarzy i odpowiednie funkcje

struct Date
{
    int dzien;
    int miesiac;
    int rok;
};


struct Lekarz {
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
    char OddzialNFZ[60];

    struct Lekarz* nastepny;
    struct Lekarz* poprzedni;
};

// Funkcje Operacji Na Liscie Lekarzy

void dodajLekarzaNaKoniec(struct Lekarz **glowny, char imie[], char nazwisko[], int dzien, int miesiac, int rok, char pesel[], char adres[], char tel[], unsigned int waga, unsigned int wzrost, char OddzialNFZ[]);
void usunPierwszego(struct Lekarz **glowny);
void usunOstatniego(struct Lekarz **glowny);
void usunLekarza(struct Lekarz **glowny, char id[]);
void edytujLekarzaMenu(struct Lekarz **glowny);
void edytujLekarza(struct Lekarz **glowny, int opcja);

// Funkcje Dodatkowe Dla Listy Lekarzy

void wyswietlLekarzy(struct Lekarz *glowny);
void wyswietlLekarza(struct Lekarz *glowny);
int liczbaLekarzy(struct Lekarz *glowny);
char * generujIDLekarz(struct Lekarz *glowny);
int sprawdzID(struct Lekarz *glowny, char id[5]);

// Funkcje Zapisu I Odczytu Listy Lekarzy

char * strFFile(struct Lekarz *glowny);
void ZapiszLekarzy(FILE *file, struct Lekarz *glowny);
void OdczytajLekarzy(FILE *file, struct Lekarz **glowny);