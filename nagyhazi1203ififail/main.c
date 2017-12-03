#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include "jatek.h"
#include "menu.h"
#include "ranglista.h"
#include "seged.h"

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#endif

struct SOR
{
    char kerdes[200];
    char a[30];
    char b[30];
    char c[30];
    char d[30];
    char jo;
    int nehezseg;
    char kategoria[20];
    struct SOR *kov;
};

//struktura a jatekos nevehez/idejehez/pontszamahoz
struct RANGLISTA
{
    int helyezes;
    char nev[20];
    int pont;
    double ido;
};

int main()
{

#if defined(WIN32) || defined(_WIN32)
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
#endif

    srand(time(0));

    RANGLISTA jatekos;

    SOR *eleje;
    RANGLISTA top[3];
    ranglista_beolvas(top);
    eleje=beolvas();

    int valaszt;

    while (1)
    {
        valaszt=menu();
        switch (valaszt)
        {
        //uj jatek inditasa
        case  1:
            jatek(jatekos, eleje, top);
            break;
        //ranglista megtekintese
        case 2:
            ranglista(top);
            break;
        //kilepes
        case 3:
            kilepes(top,eleje);
            break;
        default:
            printf("Nincs ilyen lehetoseg, kerlek valassz ujra.");
            break;
        }
    }

    return 0;
}
