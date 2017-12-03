#include "jatek.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>


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

//struktura a jelenlegi jatekos nevehez/idejehez/pontszamahoz
struct RANGLISTA
{
    int helyezes;
    char nev[20];
    int pont;
    double ido;
};

//ez a fuggveny a jatekert felel, kiirja a kerdest es bekeri a felasznalotol a valaszt
//ez addig fut, mig a felhasznalo helyes valaszokat ad
void jatek(RANGLISTA jatekos, SOR *eleje, RANGLISTA *top)
{
    system("cls");

    printf("Add meg a neved: ");

    jatekos.pont=0;
    int hozzaad=25000;
    int db=0;

    scanf("%s", jatekos.nev);

    clock_t start = clock();
    bool game=true;

    char kivesz[2];
    int dbf=0,dbk=0;

    int n=listahossz(eleje);
    int volte[n];
    int x=0;
    bool van;
    int j;
    int hanyadik;

    while(game)
    {
        system("cls");
        do
        {
            hanyadik=rand()%listahossz(eleje);
            van = false;
            for (j = 0; j < x; j += 1)
            {
                if (volte[j] == hanyadik)
                {
                    van = true;
                }
            }
        }
        while(van);

        volte[x]=hanyadik;
        x++;

        SOR *mozgo;
        int i;
        for (mozgo = eleje, i=0; mozgo != NULL && i<hanyadik; mozgo = mozgo->kov, i++)
        {
            ;
        }

        char valasz;
        int szazalek[4];

        jatek_kiir(mozgo,dbf,dbk, jatekos);

        scanf(" %c", &valasz);

        if((valasz=='F' || valasz=='f') && dbf==0)
        {
            dbf++;
            felezes(kivesz, mozgo);

            system("cls");
            printf("%s\n\n", mozgo->kerdes);

            if(kivesz[0]-65!=0 && kivesz[1]-65!=0)
            {
                printf("A: %s\n", mozgo->a);
            }
            if(kivesz[0]-65!=1 && kivesz[1]-65!=1)
            {
                printf("B: %s\n", mozgo->b);
            }
            if(kivesz[0]-65!=2 && kivesz[1]-65!=2)
            {
                printf("C: %s\n", mozgo->c);
            }
            if(kivesz[0]-65!=3 && kivesz[1]-65!=3)
            {
                printf("D: %s\n\n", mozgo->d);
            }

            printf("Jelenlegi penzosszeg: %d Ft\n", jatekos.pont);

            printf("Valasz: ");
            scanf(" %c", &valasz);
        }

        if((valasz=='K' || valasz=='k' ) && dbk==0)
        {
            dbk++;
            kozonseg(szazalek, mozgo->jo);

            system("cls");

            printf("%s\n\n", mozgo->kerdes);

            printf("A: %s->%d%%\n", mozgo->a, szazalek[0]);
            printf("B: %s->%d%%\n", mozgo->b, szazalek[1]);
            printf("C: %s->%d%%\n", mozgo->c, szazalek[2]);
            printf("D: %s->%d%%\n\n", mozgo->d, szazalek[3]);

            printf("Jelenlegi penzosszeg: %d Ft\n", jatekos.pont);

            printf("Valasz: ");
            scanf(" %c", &valasz);
        }

        while((valasz=='K' || valasz=='F') && (dbf!=0 || dbk!=0))
        {
            scanf(" %c", &valasz);
        }
        if(mozgo->jo!=valasz && tolower(mozgo->jo)!=valasz)
        {
            game=false;
            system("cls");
            printf("Game over!\n");
            printf("Nyomjon meg egy gombot a menube valo visszatereshez...");
            getch();
        }
        else
        {
            printf("Helyes valasz!");
            getch();
            if(db!=0 && db%4==0)
            {
                hozzaad*=2;
            }
            jatekos.pont+=hozzaad;
            db++;
        }
    }
    clock_t end = clock();
    jatekos.ido = (double)(end - start) / 1000;

    tope(top, jatekos.nev, jatekos.pont, jatekos.ido);
}

void jatek_kiir(SOR *mozgo, int dbf, int dbk,RANGLISTA jatekos) {
        printf("%s\n\n", mozgo->kerdes);

        printf("A: %s\n", mozgo->a);
        printf("B: %s\n", mozgo->b);
        printf("C: %s\n", mozgo->c);
        printf("D: %s\n\n", mozgo->d);


        if(dbf==0)
        {
            printf("Felezes(F)\n");
        }
        if(dbk==0)
        {
            printf("Kozonseg(K)\n");
        }

        printf("\nJelenlegi penzosszeg: %d Ft\n", jatekos.pont);

        printf("Valasz: ");
}

void kilepes(RANGLISTA *top, SOR *eleje)
{
    kiir(top);
    lista_felszabadit(eleje);
    exit(1);
}


