#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int dodaj_przedmiot()
{
    char przedmiot_odczyt[20]="";
    char przedmiot_linia[20]="", przedmiot[20]="";
    char klasa[20]="";
    char sciezka[50]="Dane_dziennika\\Klasa_";
    char imie[20]="", nazwisko[20]="", pesel[20]="";
    char oceny[20]="";

    utworz_plik("Dane_dziennika\\przedmioty.txt", "", "", "", "");

    FILE *przedmioty;
    if ((przedmioty=fopen("Dane_dziennika\\przedmioty.txt", "r"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku przedmioty.txt do odczytu!\n\n");
         return 0;
    }

    printf("\t\t>> Podaj przedmiot, ktory chcesz dodac: ");
    scanf("%s", przedmiot);
    strcpy(przedmiot_linia,przedmiot);
    strcat(przedmiot_linia, "\n");

    while( fgets(przedmiot_odczyt, 20, przedmioty) != NULL )
    {
      if(!strcmp(przedmiot_odczyt, przedmiot_linia))
      {
            printf("\n\n\t\t|KOMUNIKAT| Podany przedmiot jest juz w bazie danych.\n\n");
            return 0;
      }
    }
    fclose(przedmioty);

    if ((przedmioty=fopen("Dane_dziennika\\przedmioty.txt", "a"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku przedmioty.txt do zapisu!\n\n");
         return 0;
    }
    fprintf(przedmioty, "%s", przedmiot_linia);
    printf("\n\t\t*** Dodales nowy przedmiot. ***\n\n");
    fclose(przedmioty);

    FILE *spis_klas;
    if ((spis_klas=fopen("Dane_dziennika\\spis_klas.txt", "r"))==NULL)
    {
         printf("\n\t\t|OSTRZEZENIE| Nie mozna otworzyc pliku spis_klas.txt do odczytu!\n\n");
         return 0;
    }

    FILE *uczniowie;

    while(feof(spis_klas)==0)
    {
        fscanf(spis_klas, "%s", klasa);
        usun_biale_znaki(klasa);

        if(strcmp(klasa,""))
        {
           strcpy(sciezka,"Dane_dziennika\\Klasa_");
           utworz_plik(sciezka, klasa, "\\Oceny\\", przedmiot, ".txt");
           strcat(sciezka,klasa);
           strcat(sciezka,"\\uczniowie.txt");
           if ((uczniowie=fopen(sciezka, "r"))==NULL)
           {
             printf("\n\t\t|OSTRZEZENIE| Nie mozna otworzyc pliku uczniowie.txt do odczytu!\n\n");
             return 0;
           }
           while(feof(uczniowie)==0)
           {
               fscanf(uczniowie,"%s",imie);
               fscanf(uczniowie,"%s",nazwisko);
               fscanf(uczniowie,"%s",pesel);
               if(fgets(oceny,20,uczniowie)==0)
                break;
               wpisz_uczniow(klasa,przedmiot,imie,nazwisko,pesel);
           }

           fclose(uczniowie);
        }

       fgets(klasa,20,spis_klas);
    }

    fclose(spis_klas);

    return 0;
}

int usun_przedmiot()
{
    int czy_usun=0;
    char nazwa_odczyt[20]="";
    char klasa[20]="";
    char sciezka[50]="Dane_dziennika\\Klasa_";
    char przedmiot_linia[20]="", przedmiot[20]="";

    FILE *przedmioty, *pomocniczy;
    if ((przedmioty=fopen("Dane_dziennika\\przedmioty.txt", "r"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku przedmioty.txt do odczytu!\n\n");
         return 0;
    }
    if ((pomocniczy=fopen("Dane_dziennika\\pomocniczy.txt", "w"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku pomocniczy.txt do zapisu!\n\n");
         return 0;
    }

    printf("\t\t>> Podaj przedmiot, ktory chcesz usunac: ");
    scanf("%s", przedmiot);
    strcpy(przedmiot_linia,przedmiot);
    strcat(przedmiot_linia, "\n");

    while( fgets(nazwa_odczyt, 20, przedmioty) != NULL )
    {
      if( strcmp(nazwa_odczyt, przedmiot_linia) != 0 )
      {
          fputs(nazwa_odczyt, pomocniczy);
      }
      else
      {
            czy_usun=1;
            printf("\n\t\t *** Podany przedmiot zostal usuniety. *** \n\n");
      }

    }

    if(!czy_usun)
    {
        printf("\n\t\t|KOMUNIKAT| Podany przedmiot nie zostal znaleziony.\n\n");
    }

    fclose(przedmioty);
    fclose(pomocniczy);

    if( remove("Dane_dziennika\\przedmioty.txt") != 0 )
        printf("\n\t\t|OSTRZEZENIE| Nie mozna usunac pliku przedmioty.txt!\n\n");
    else if( rename( "Dane_dziennika\\pomocniczy.txt", "Dane_dziennika\\przedmioty.txt" ) != 0 )
        printf("\n\t\t|OSTRZEZENIE| Nie mozna zmienic nazwy pliku pomocniczy.txt!\n\n");


    FILE *spis_klas;
    if ((spis_klas=fopen("Dane_dziennika\\spis_klas.txt", "r"))==NULL)
    {
         printf("\n\t\t|OSTRZEZENIE| Nie mozna otworzyc pliku spis_klas.txt do odczytu!\n\n");
         return 0;
    }

    while(feof(spis_klas)==0)
    {
        fscanf(spis_klas, "%s", klasa);
        usun_biale_znaki(klasa);

        if(strcmp(klasa,""))
        {
           usun_plik(sciezka, klasa, "\\Oceny\\", przedmiot, ".txt");
        }

        fgets(klasa,20,spis_klas);
    }
    fclose(spis_klas);


    return 0;

}
