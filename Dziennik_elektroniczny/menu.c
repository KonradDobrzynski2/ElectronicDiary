#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int menu_czesc_glowna()
{
    int wybor;

    wyswietlanie_menu();
    scanf("%d",&wybor);
    printf("\n\t\tWybrana opcja to: %d\n",wybor);

    switch(wybor)
    {
        case 1: printf("\a"); menu_case_1(wybor);
        break;
        case 2: printf("\a"); menu_case_2(wybor);
        break;
        case 3: printf("\a"); menu_case_3();
        break;
        case 4: printf("\a"); menu_case_4(wybor);
        break;
        case 5: printf("\a"); menu_case_5();
        break;
        case 6: printf("\a"); menu_case_6();
        break;
        case 0: printf("\a\a\a"); exit(0);
        default: printf("\a\a"); defaullt();
        break;
    }

    return wybor;
}

void wyswietlanie_menu()
{
    printf("\n\t\tWybierz jedna z ponizszych opcji:\n\n");
    printf("\t\t1. Dodaj/usun przedmiot\n\n");
    printf("\t\t2. Dodaj/usun ucznia\n\n");
    printf("\t\t3. Dodaj oceny do konkretnego ucznia\n\n");
    printf("\t\t4. Wyswietl srednia\n\n");
    printf("\t\t5. Wyswietl liste przedmiotow\n\n");
    printf("\t\t6. Wyswietl liste uczniow\n\n");
    printf("\t\t7. Nacisnij 0 aby wyjsc z programu\n\n");
}

void menu_case_1(int wybor)
{
    do
            {
                if((wybor!=1) && (wybor!=2) && (wybor!=3))
                {
                    czyszczenie_konsoli(5);
                    wyswietlanie_menu();

                }

                printf("\n\t\t1. Dodaj przedmiot\n\n");
                printf("\t\t2. Usun przedmiot\n\n");
                printf("\t\t3. Powrot do glownego menu\n\n");
                scanf("%d",&wybor);

                switch(wybor)
                {
                    case 1: printf("\a"); dodaj_przedmiot(); czyszczenie_konsoli(1);
                    break;
                    case 2: printf("\a"); usun_przedmiot(); czyszczenie_konsoli(1);
                    break;
                    case 3: printf("\a"); czyszczenie_konsoli(4);
                    break;
                    default: printf("\a\a"); czyszczenie_konsoli(2);
                    break;
                }
            }
            while((wybor!=1) && (wybor!=2) && (wybor!=3));
}

void menu_case_2(int wybor)
{
    do
    {
        if((wybor!=1) && (wybor!=2) && (wybor!=3))
        {
            czyszczenie_konsoli(5);
            wyswietlanie_menu();
        }

        printf("\n\t\t1. Dodaj ucznia\n\n");
        printf("\t\t2. Usun ucznia\n\n");
        printf("\t\t3. Powrot do glownego menu\n\n");
        scanf("%d",&wybor);

        switch(wybor)
        {
            case 1: printf("\a"); dodaj_ucznia(); czyszczenie_konsoli(1);
            break;
            case 2: printf("\a"); usun_ucznia(); czyszczenie_konsoli(1);
            break;
            case 3: printf("\a"); czyszczenie_konsoli(4);
            break;
            default: printf("\a\a"); czyszczenie_konsoli(2);
            break;
        }

    }
    while((wybor!=1) && (wybor!=2) && (wybor!=3));
}

void menu_case_3()
{
    dodaj_ocene();
    czyszczenie_konsoli(3);
}

void menu_case_4(int wybor)
{
    do
            {
                if((wybor!=1) && (wybor!=2) && (wybor!=3) && (wybor!=4))
                {
                    czyszczenie_konsoli(5);
                    wyswietlanie_menu();

                }

                printf("\n\t\t1. Wyswietl srednia danego ucznia \n\n");
                printf("\t\t2. Wyswietl srednia danej klasy\n\n");
                printf("\t\t3. Wyswietl srednia danego przedmiotu\n\n");
                printf("\t\t4. Powrot do glownego menu\n\n");
                scanf("%d",&wybor);

                switch(wybor)
                {
                    case 1: printf("\a"); wyswietl_srednia_ucznia(); czyszczenie_konsoli(1);
                    break;
                    case 2: printf("\a"); wyswietl_srednia_klasy(); czyszczenie_konsoli(1);
                    break;
                    case 3: printf("\a"); wyswietl_srednia_przedmiotu(); czyszczenie_konsoli(1);
                    break;
                    case 4: printf("\a"); czyszczenie_konsoli(4);
                    break;
                    default: printf("\a\a");czyszczenie_konsoli(2);
                    break;
                }
            }
            while((wybor!=1) && (wybor!=2) && (wybor!=3) && (wybor!=4));
}

void menu_case_5()
{
    wyswietlanie_przedmiotow();
    czyszczenie_konsoli(1);
}

void menu_case_6()
{
    wyswietlanie_listy_uczniow_w_klasie();
    czyszczenie_konsoli(1);
}

void defaullt()
{
    printf("\t\tBledny wybor. Dostepne klawisze: 1 do 7 lub 0.\n\n");
    czyszczenie_konsoli(1);
}
