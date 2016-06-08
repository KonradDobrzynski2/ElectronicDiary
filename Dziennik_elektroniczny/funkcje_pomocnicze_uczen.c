#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int wpisz_uczniow(char *klasa, char *przedmiot, char *imie, char *nazwisko, char *pesel)
{
    char sciezka[50] = "Dane_dziennika\\Klasa_";

    strcat(sciezka,klasa);
    strcat(sciezka,"\\Oceny\\");
    strcat(sciezka,przedmiot);
    strcat(sciezka,".txt");


    FILE *otwierany_przedmiot;
    if ((otwierany_przedmiot=fopen(sciezka, "a"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku %s.txt do odczytu!\n\n",przedmiot);
         return 0;
    }

    fprintf(otwierany_przedmiot,"%-20s %-20s %-20s\n",imie,nazwisko,pesel);

    fclose(otwierany_przedmiot);

    return 0;
}

int znajdz_ucznia(const char *sciezka, const char *pesel, char *imie, char *nazwisko, char *oceny)
{
    char pesel_odczyt[20]="";
    int linia=0;
    FILE *uczniowie;

    if ((uczniowie=fopen(sciezka,"r"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku uczniowie.txt do odczytu!\n\n");
         return 0;
    }

    while(feof(uczniowie) == 0)
    {
        fscanf(uczniowie,"%s",imie);
        fscanf(uczniowie,"%s",nazwisko);
        fscanf(uczniowie,"%s",pesel_odczyt);
        fgets(oceny,50,uczniowie);
        linia++;

        if(!strcmp(pesel_odczyt, pesel))
        {
            return linia;
        }
    }

    fclose(uczniowie);
    return 0;
}
