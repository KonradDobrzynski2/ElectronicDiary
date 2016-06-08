#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int wyswietlanie_przedmiotow()
{
    char sciezka[50]="Dane_dziennika\\przedmioty.txt";
    char przedmiot[20]="";
    int i=1;


    FILE *przedmioty;

    if ((przedmioty=fopen(sciezka,"r"))==NULL)
    {
         printf ("\n\t\t|KOMUNIKAT| Nie moge otworzyc pliku przedmioty.txt do odczytu!\n\n");
         return 0;
    }

    printf("\n\t\tOto lista przedmiotow widniejacych w naszej bazie danych:\n");

    while(feof(przedmioty) == 0)
    {
        fscanf(przedmioty,"%s",przedmiot);

        usun_biale_znaki(przedmiot);

        if(strcmp(przedmiot,""))
        {
            printf("\n");
            printf("\t\t%d. %s\n",i,przedmiot);
        }

        fgets(przedmiot,20,przedmioty);

        i++;
    }

    printf("\n");

    fclose(przedmioty);

    return 0;
}

int wyswietlanie_listy_uczniow_w_klasie()
{
    char sciezka[50]="Dane_dziennika\\Klasa_";
    char imie[20]="", nazwisko[20]="", pesel[20]="";
    char klasa[10]="";

    int i=1;

    printf("\n\t\t>> Podaj klase z ktorej chcesz wyswietlic liste uczniow\n\n\t\t>> Klasa:");
    scanf("%s",klasa);
    printf("\n");

    strcat(sciezka,klasa);
    strcat(sciezka,"\\uczniowie.txt");

    FILE *lista;

    if ((lista=fopen(sciezka,"r"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie mozna otworzyc pliku uczniowie.txt do odczytu (klasa_%s)!\n\n",klasa);
         return 0;
    }

    printf("\n\t\tOto lista uczniow zapisanych do klasy %s:\n",klasa);

    printf("\n\t\tImie                   Nazwisko            PESEL\n\n");

    while(feof(lista) == 0)
    {
        fscanf(lista,"%s",imie);
        fscanf(lista,"%s",nazwisko);
        fscanf(lista,"%s",pesel);
        usun_biale_znaki(pesel);
        if(strcmp(pesel,""))
        {
            printf("\t\t%d. %-20s",i,imie);
            printf("%-20s",nazwisko);
            printf("%-20s\n",pesel);
        }

        if(fgets(pesel,10,lista)==0)
            break;

        i++;
    }

    printf("\n");

    fclose(lista);

    return 0;
}

int wyswietl_srednia_ucznia()
{
    char klasa[20]="";
    char pesel[20]="", imie[20]="", nazwisko[20]="";
    char przedmiot[20]="";
    char sciezka[50] = "Dane_dziennika\\Klasa_";
    char oceny[100]="";
    int suma_ocen=0;
    int ilosc_ocen=0;
    float srednia_ocen=0;

    printf("\t\t>> Podaj klase do ktorej nalezy uczen: ");
    scanf("%s",klasa);
    printf("\t\t>> Podaj PESEL ucznia: ");
    scanf("%s",pesel);

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
            strcpy(sciezka,"Dane_dziennika\\Klasa_");
            strcat(sciezka,klasa);
            strcat(sciezka,"\\Oceny\\");
            strcat(sciezka,przedmiot);
            strcat(sciezka,".txt");
            znajdz_ucznia(sciezka,pesel,imie,nazwisko,oceny);
            liczenie_sredniej(oceny,&suma_ocen,&ilosc_ocen);
        }

        fgets(przedmiot,20,przedmioty);
    }

    fclose(przedmioty);

    srednia_ocen= (float)suma_ocen/ilosc_ocen;

    printf("\n\t\t>>> Srednia ocen ucznia o podanym PESELu wynosi: %.2f\n\n",srednia_ocen);

    return 0;
}

int wyswietl_srednia_klasy()
{
    char klasa[20]="";
    char pesel[20]="", imie[20]="", nazwisko[20]="";
    char przedmiot[20]="";
    char sciezka[50] = "Dane_dziennika\\Klasa_";
    char oceny[100]="";
    int suma_ocen=0;
    int ilosc_ocen=0;
    float srednia_ocen=0;

    printf("\t\t>> Podaj klase ktorej chcesz wyswietlic srednia ocen: ");
    scanf("%s",klasa);

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
            strcpy(sciezka,"Dane_dziennika\\Klasa_");
            strcat(sciezka,klasa);
            strcat(sciezka,"\\Oceny\\");
            strcat(sciezka,przedmiot);
            strcat(sciezka,".txt");

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
                fscanf(uczniowie,"%s",pesel);
                if(fgets(oceny,50,uczniowie)==NULL)
                {
                    break;
                }

                liczenie_sredniej(oceny,&suma_ocen,&ilosc_ocen);
            }

            fclose(uczniowie);
        }

        fgets(przedmiot,20,przedmioty);
    }

    fclose(przedmioty);

    srednia_ocen= (float)suma_ocen/ilosc_ocen;

    printf("\n\t\t>>> Srednia ocen danej klasy wynosi: %.2f\n\n",srednia_ocen);

    return 0;
}

int wyswietl_srednia_przedmiotu()
{
    char klasa[20]="";
    char pesel[20]="", imie[20]="", nazwisko[20]="";
    char przedmiot[20]="";
    char sciezka[50] = "Dane_dziennika\\Klasa_";
    char oceny[100]="";
    int suma_ocen=0;
    int ilosc_ocen=0;
    float srednia_ocen=0;

    printf("\t\t>> Podaj przedmiot dla ktorego chcesz wyswietlic srednia ocen: ");
    scanf("%s",przedmiot);

    FILE *spis_klas;

    if ((spis_klas=fopen("Dane_dziennika\\spis_klas.txt","r"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku spis_klas.txt do odczytu!\n\n");
         return 0;
    }

    while(feof(spis_klas) == 0)
    {
        fscanf(spis_klas,"%s",klasa);

        usun_biale_znaki(klasa);

        if(strcmp(klasa,""))
        {
            strcpy(sciezka,"Dane_dziennika\\Klasa_");
            strcat(sciezka,klasa);
            strcat(sciezka,"\\Oceny\\");
            strcat(sciezka,przedmiot);
            strcat(sciezka,".txt");

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
                fscanf(uczniowie,"%s",pesel);
                if(fgets(oceny,50,uczniowie)==NULL)
                {
                    break;
                }

                liczenie_sredniej(oceny,&suma_ocen,&ilosc_ocen);
            }

            fclose(uczniowie);
        }

        fgets(klasa,20,spis_klas);
    }

    fclose(spis_klas);

    srednia_ocen= (float)suma_ocen/ilosc_ocen;

    printf("\n\t\t>>> Srednia ocen z podanego przedmiotu wynosi: %.2f\n\n",srednia_ocen);

    return 0;
}
