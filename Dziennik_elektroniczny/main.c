#include <windows.h>

#include "dodaj_usun_przedmiot.h"
#include "dodaj_usun_ucznia.h"
#include "funkcje_pomocnicze.h"
#include "funkcje_pomocnicze_uczen.h"
#include "menu.h"
#include "srednia_i_oceny.h"
#include "wyswietlanie.h"

int main()
{
    system("mkdir Dane_dziennika");
    utworz_plik("Dane_dziennika\\spis_klas.txt", "", "", "", "");
    utworz_plik("Dane_dziennika\\przedmioty.txt", "", "", "", "");

    while(menu_czesc_glowna());

    return 0;
}
