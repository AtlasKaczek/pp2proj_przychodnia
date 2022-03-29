// Lista Lekarzy i odpowiednie funkcje
struct Lekarz {
    unsigned int id;
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

void dodajLekarzaNaKoniec(struct Lekarz **glowny, unsigned int id, char imie[], char nazwisko[], char pesel[], char adres[], char email[], char tel[], unsigned int waga, unsigned int wzrost, char OddzialNFZ[]);
void wyswietlLekarzy(struct Lekarz *glowny);
