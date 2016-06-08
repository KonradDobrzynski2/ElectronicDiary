#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int dodaj_ucznia()
{
    char imie[20]="", nazwisko[20]="", pesel[20]="", klasa[20]="";
    char imie_odczyt[20]="", nazwisko_odczyt[20]="", pesel_odczyt[20]="", klasa_odczyt[20]="";
    char sciezka[50]="Dane_dziennika\\Klasa_";
    char przedmiot[20]="";

    FILE *uczniowie;

    printf("\t\t>> Podaj Imie ucznia: ");
    scanf("%s",imie);
    printf("\t\t>> Podaj Nazwisko ucznia: ");
    scanf("%s",nazwisko);
    printf("\t\t>> Podaj PESEL ucznia: ");
    scanf("%s",pesel);
    printf("\t\t>> Podaj klase do ktorej nalezy uczen: ");
    scanf("%s",klasa);

    obsluga_folder_klasa(klasa);

    strcat(sciezka,klasa);
    strcat(sciezka,"\\uczniowie.txt");

    if ((uczniowie=fopen(sciezka,"r"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku uczniowie.txt do odczytu!\n\n");
         return 0;
    }

    while(feof(uczniowie) == 0)
    {
        fscanf(uczniowie,"%s",imie_odczyt);
        fscanf(uczniowie,"%s",nazwisko_odczyt);
        fscanf(uczniowie,"%s",pesel_odczyt);
        fgets(klasa_odczyt,20,uczniowie);

        if(!strcmp(pesel_odczyt, pesel))
        {
            printf("\n\t\t |KOMUNIKAT| Uczen o podanym PESELu juz istnieje.\n\n");
            return 0;
        }
    }

    fclose(uczniowie);

    if ((uczniowie=fopen(sciezka,"a"))==NULL)
    {
         printf ("Nie moge otworzyc pliku uczniowie.txt do zapisu!\n");
         return 0;
    }
    fprintf(uczniowie, "%-20s %-20s %s\n", imie,nazwisko,pesel);
    printf("\n\t\t *** Dodales nowego ucznia. ***\n\n");
    fclose(uczniowie);

    FILE *przedmioty;

    if ((przedmioty=fopen("Dane_dziennika\\przedmioty.txt","r"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku przedmioty.txt do odczytu!\n\n");
         return 0;
    }

    while(feof(przedmioty) == 0)
    {
        fscanf(przedmioty,"%s",przedmiot);

        usun_biale_znaki(przedmiot);

        if(strcmp(przedmiot,""))
        {
            wpisz_uczniow(klasa,przedmiot,imie,nazwisko,pesel);
        }

        fgets(przedmiot,20,przedmioty);
    }

    fclose(przedmioty);

    return 0;
}

int usun_ucznia()
{
    int czy_usun=0;
    char pesel[20]="";
    char klasa[20]="";
    char imie_odczyt[20]="", nazwisko_odczyt[20]="", pesel_odczyt[20]="", nowa_linia[20]="";
    char sciezka[50]="Dane_dziennika\\Klasa_";
    char sciezka2[50]="Dane_dziennika\\Klasa_";
    char przedmiot[20]="";
    char oceny[50]="";


    FILE *uczniowie, *pomocniczy;

    printf("\t\t >> Podaj klase do ktorej nalezy uczen: ");
    scanf("%s", klasa);

    printf("\t\t >> Podaj PESEL ucznia ktorego chcesz usunac: ");
    scanf("%s", pesel);

    strcat(sciezka,klasa);
    strcat(sciezka,"\\uczniowie.txt");

    strcat(sciezka2,klasa);
    strcat(sciezka2,"\\pomocniczy.txt");


    if ((uczniowie=fopen(sciezka, "r"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku uczniowie.txt do odczytu!\n\n");
         return 0;
    }
    if ((pomocniczy=fopen(sciezka2, "w"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku pomocniczy.txt do zapisu!\n\n");
         return 0;
    }

    while(feof(uczniowie) == 0)
    {
        fscanf(uczniowie, "%s", imie_odczyt);
        fscanf(uczniowie, "%s", nazwisko_odczyt);
        fscanf(uczniowie, "%s", pesel_odczyt);
        if(fgets(nowa_linia, 2, uczniowie)==NULL)
        {
            break;
        }

        if( strcmp(pesel_odczyt, pesel) != 0 )
        {
            fprintf(pomocniczy, "%-20s %-20s %-20s\n", imie_odczyt, nazwisko_odczyt, pesel_odczyt);
        }
        else
        {
            czy_usun=1;
        }

    }

    fclose(uczniowie);
    fclose(pomocniczy);

    if( remove(sciezka) != 0 )
        printf("\n\t\t|OSTRZEZENIE| Nie mozna usunac pliku uczniowie.txt!\n\n");
    else if( rename(sciezka2,sciezka) != 0 )
        printf("\n\t\t|OSTRZEZENIE| Nie mozna zmienic nazwy pliku pomocniczy.txt!\n\n");

    FILE *przedmioty;

    if ((przedmioty=fopen("Dane_dziennika\\przedmioty.txt","r"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku przedmioty.txt do odczytu!\n\n");
         return 0;
    }

    FILE *plik_przedmiot;


    while(feof(przedmioty) == 0)
    {
        fscanf(przedmioty,"%s",przedmiot);

        usun_biale_znaki(przedmiot);

        if(strcmp(przedmiot,""))
        {
            strcpy(sciezka,"Dane_dziennika\\Klasa_");
            strcat(sciezka,klasa);
            strcat(sciezka,"\\Oceny\\");
            strcat(sciezka,przedmiot);
            strcat(sciezka,".txt");



            if ((plik_przedmiot=fopen(sciezka, "r"))==NULL)
            {
                printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku %s.txt do odczytu!\n\n",przedmiot);
                return 0;
            }

            if ((pomocniczy=fopen(sciezka2, "w"))==NULL)
            {
                 printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku pomocniczy.txt do zapisu!\n\n");
                 return 0;
            }

            while(feof(plik_przedmiot) == 0)
            {
                fscanf(plik_przedmiot, "%s", imie_odczyt);
                fscanf(plik_przedmiot, "%s", nazwisko_odczyt);
                fscanf(plik_przedmiot, "%s", pesel_odczyt);
                if(fgets(oceny,50,plik_przedmiot)==NULL)
                {
                    break;
                }

                if( strcmp(pesel_odczyt, pesel) != 0 )
                {
                    fprintf(pomocniczy, "%-20s %-20s %-20s", imie_odczyt, nazwisko_odczyt, pesel_odczyt);
                    fputs(oceny,pomocniczy);
                }
                else
                {
                    czy_usun=1;
                }

            }

            fclose(plik_przedmiot);
            fclose(pomocniczy);

            if( remove(sciezka) != 0 )
                printf("\n\t\t|OSTRZEZENIE| Nie mozna usunac pliku uczniowie.txt!\n\n");
            else if( rename(sciezka2,sciezka) != 0 )
                printf("\n\t\t|OSTRZEZENIE| Nie mozna zmienic nazwy pliku pomocniczy.txt!\n\n");
        }

        fgets(przedmiot,20,przedmioty);
    }

    if(!czy_usun)
    {
        printf("\n\t\t|KOMUNIKAT| Uczen o podanym PESELu nie zostal znaleziony.\n");
    }
    else
    {
        printf("\n\t\t*** Uczen o podanym PESELu zostal usuniety. ***\n\n");
    }

    fclose(przedmioty);

    return 0;

}
