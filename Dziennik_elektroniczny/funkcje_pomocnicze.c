#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void usun_biale_znaki(char* s)
{
     int p = -1, q = 0;

     while(s[++p] != '\0')
     {
         if ((s[p] != ' ') && (s[p] != '\n') && (s[p] != '\t'))
         {
             s[q++] = s[p];
         }
     }

     s[q] = '\0';
}

void usun_nowa_linia(char* s)
{
     int p = -1, q = 0;

     while(s[++p] != '\0')
     {
         if (s[p] != '\n')
         {
             s[q++] = s[p];
         }
     }

     s[q] = '\0';
}

void utworz_folder(char *str1, char *str2, char *str3, char *str4, char *str5)
{
    char folder[100]="mkdir ";
    strcat(folder, str1);
    strcat(folder, str2);
    strcat(folder, str3);
    strcat(folder, str4);
    strcat(folder, str5);

    system(folder);
}

int utworz_plik(char *str1, char *str2, char *str3, char *str4, char *str5)
{
    char nazwa_pliku[100];
    strcpy(nazwa_pliku, str1);
    strcat(nazwa_pliku, str2);
    strcat(nazwa_pliku, str3);
    strcat(nazwa_pliku, str4);
    strcat(nazwa_pliku, str5);

    FILE *plik;

    if ((plik=fopen(nazwa_pliku, "r"))==NULL)
    {
        if ((plik=fopen(nazwa_pliku, "w"))==NULL)
        {
             printf ("\n\t\t|OSTRZEZENIE| Nie moge utworzyc pliku %s!\n\n", nazwa_pliku);
             return 0;
        }
    }
    fclose(plik);

    return 0;
}

int usun_plik(char *str1, char *str2, char *str3, char *str4, char *str5)
{
    char nazwa_pliku[100];
    strcpy(nazwa_pliku, str1);
    strcat(nazwa_pliku, str2);
    strcat(nazwa_pliku, str3);
    strcat(nazwa_pliku, str4);
    strcat(nazwa_pliku, str5);

    remove(nazwa_pliku);

    return 0;
}

int obsluga_folder_klasa(char *klasa)
{
    char klasa_odczyt[10];
    char sciezka[50]="Dane_dziennika\\Klasa_";
    char nazwy_przedmiotow[50];

    //otwieranie spisu klas
    FILE *spis_klas;
    if ((spis_klas=fopen("Dane_dziennika\\spis_klas.txt", "r"))==NULL)
    {
         printf("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku spis_klas.txt do odczytu!\n\n");
         return 0;
    }

    //odczyt klas
    while(feof(spis_klas)==0)
    {

        fscanf(spis_klas, "%s", klasa_odczyt);

        //sprawdzenie czy klasa istnieje
        if(!strcmp(klasa_odczyt, klasa))
        {
            return 0; //jesli istnieje to wychodzi
        }

    }
    //tworzenie folderu klasy
    utworz_folder(sciezka, klasa, "", "", "");
    fclose(spis_klas);


    if ((spis_klas=fopen("Dane_dziennika\\spis_klas.txt", "a"))==NULL)
    {
         printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku spis_klas.txt do odczytu!\n\n");
         return 0;
    }

    fprintf(spis_klas,"%s\n",klasa);
    fclose(spis_klas);

    utworz_plik(sciezka, klasa, "\\uczniowie.txt", "", "");
    utworz_folder(sciezka, klasa, "\\Oceny", "", "");

    FILE *przedmioty;
    if ((przedmioty=fopen("Dane_dziennika\\przedmioty.txt", "r"))==NULL)
    {
         printf("\n\t\t|OSTRZEZENIE| Nie mozna otworzyc pliku przedmioty.txt do odczytu!\n\n");
         return 0;
    }

    while(feof(przedmioty)==0)
    {
        fscanf(przedmioty, "%s", nazwy_przedmiotow);
        utworz_plik(sciezka, klasa, "\\Oceny\\", nazwy_przedmiotow, ".txt");
    }
    fclose(przedmioty);

    return 0;
}

void czyszczenie_konsoli(int a)
{
    switch(a)
    {

        case 1:
            printf("\t\tNacisnij ENTER aby powrocic do glownego menu");
            getchar(); getchar(); system("cls");
            break;
        case 2:
            printf("\t\tZly wybor\n\n");
            printf("\t\tNacisnij ENTER aby  tym razem wybrac poprawna opcje\n");
            break;
        case 3:
            printf("\t\tNacisnij ENTER aby powrocic do glownego menu");
            getchar(); getchar(); system("cls");
            break;
        case 4:
            system("cls");
            break;
        case 5:
            getchar(); getchar(); system("cls");
            break;
    }
}
