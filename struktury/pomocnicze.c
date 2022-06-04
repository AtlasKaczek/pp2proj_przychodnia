#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pomocnicze.h"

///
/** Funkcja generujEmail
 * Zwraca ciąg znaków - email postaci (pierwsza litera imienia)(nazwisko)(platforma).
 * 
*/
char * generujEmail(char imie[], char nazwisko[], char platforma[]) {
    int dlugosc = strlen(nazwisko) + strlen(platforma) + 1 + 1;
    
    char *str = malloc(dlugosc);
    str[0] = imie[0] + 32;
    for (int i = 1; i < strlen(nazwisko) + 1; i++)
    {
        if(nazwisko[i-1] >= 65 && nazwisko[i-1] <= 90) {
            str[i] = nazwisko[i-1] + 32;
        } else {
            str[i] = nazwisko[i-1];
        }
    }
    for (int j = strlen(nazwisko); j < dlugosc - 2; j++)
    {
        str[j + 1] = platforma[j-strlen(nazwisko)];
    }
    str[dlugosc-1] = '\0';
    return str;
}