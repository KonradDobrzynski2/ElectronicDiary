#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void liczenie_sredniej(const char *oceny, int *out_suma, int *out_ilosc)
{
    int i=0;

    while(oceny[i])
    {
        if((oceny[i] >= '0') && (oceny[i] <= '9'))
        {
            (*out_suma) = (*out_suma) + oceny[i] - '0';
            (*out_ilosc)++;
        }
        i++;

        if(i==50)
        {
            break;
        }
    }
}

int dodaj_ocene()
{
    char klasa[20]="", pesel[20]="", przedmiot[20]="";
    char imie_odczyt[20], nazwisko_odczyt[20], pesel_odczyt[20]="";
    char oceny[50]="";
    char sciezka[50]="";
    char sciezka2[50]="pomocniczy.txt";
    int ocena;

    printf("\t\t>> Poda klase do ktorej nalezy uczen:");
    scanf("%s",klasa);
    printf("\t\t>> Podaj PESEL ucznia:");
    scanf("%s",pesel);
    printf("\t\t>> Podaj przedmiot do ktorego chcesz dodac ocene:");
    scanf("%s",przedmiot);
    printf("\t\t>> Podaj ocene:");
    scanf("%d",&ocena);

    strcpy(sciezka,"Dane_dziennika\\Klasa_");
            strcat(sciezka,klasa);
            strcat(sciezka,"\\Oceny\\");
            strcat(sciezka,przedmiot);
            strcat(sciezka,".txt");


    FILE *plik_przedmiot;
    FILE *pomocniczy;

            if ((plik_przedmiot=fopen(sciezka, "r"))==NULL)
            {
                printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku %s.txt do odczytu!\n",przedmiot);
                return 0;
            }

            if ((pomocniczy=fopen(sciezka2, "w"))==NULL)
            {
                 printf ("\n\t\t|OSTRZEZENIE| Nie moge otworzyc pliku pomocniczy.txt do zapisu!\n");
                 return 0;
            }

            while(feof(plik_przedmiot) == 0)
            {
                fscanf(plik_przedmiot, "%s", imie_odczyt);
                fscanf(plik_przedmiot, "%s", nazwisko_odczyt);
                fscanf(plik_przedmiot, "%s", pesel_odczyt);
                if(fgets(oceny, 40, plik_przedmiot)==NULL)
                {
                    break;
                }

                if( strcmp(pesel_odczyt, pesel) != 0 )
                {
                    fprintf(pomocniczy, "%-20s %-20s %s", imie_odczyt, nazwisko_odczyt, pesel_odczyt);
                    fputs(oceny,pomocniczy);
                }
                else
                {
                    fprintf(pomocniczy, "%-20s %-20s %s", imie_odczyt, nazwisko_odczyt, pesel_odczyt);
                    usun_nowa_linia(oceny);
                    fputs(oceny,pomocniczy);
                    fprintf(pomocniczy," %d\n",ocena);
                }

            }

            fclose(plik_przedmiot);
            fclose(pomocniczy);

            if( remove(sciezka) != 0 )
                printf("\n\t\t|OSTRZEZENIE| Nie mozna usunac pliku %s\n",sciezka);
            else if( rename(sciezka2,sciezka) != 0 )
                printf("\n\t\t|OSTRZEZENIE| Nie mozna zmienic nazwy pliku pomocniczy.txt\n");

    printf("\n\t\tWlasnie dodales ocene uczniowi o numerze PESEL:%s\n\n",pesel);

    return 0;
}
