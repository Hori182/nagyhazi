#include "menu.h"
#include <stdio.h>
#include <windows.h>
#include <conio.h>

//menu:
//ez a fuggveny irja ki a menupontokat, itt lehet kivalasztani, hogy a felhasznalo mit szeretne csinálni(jatek/dicsosegtabla megtekintese/kilepes)
//a valasztastol fuggoen visszater a bevitt szammal
int menu()
{
    int mvalaszt=0;
    while(mvalaszt!=1 && mvalaszt!=2 && mvalaszt!=3) {
        system("cls");
        printf("1. Uj jatek\n");
        printf("2. Dicsosegtabla\n");
        printf("3. Kilepes\n");
        printf("Valasztott menupont: ");
        scanf(" %d", &mvalaszt);
        if(mvalaszt!=1 && mvalaszt!=2 && mvalaszt!=3) {
            printf("Nincs ilyen menupont, kerlek valasszon ujra!");
            getch();
        }
    }
    return mvalaszt;
}
