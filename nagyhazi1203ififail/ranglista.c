#include "ranglista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct RANGLISTA
{
    int helyezes;
    char nev[20];
    int pont;
    double ido;
};

//ranglista.txt beolvassa
void ranglista_beolvas(RANGLISTA *top)
{
    FILE* fptr;

    fptr = fopen("ranglista.txt", "r");

    char line[100];
    int h;
    char nev[20];
    int p;
    int i=0;
    double t;

    while(fgets(line, 100,fptr))
    {
        sscanf(line,"%d;%[^;];%d;%lf\n",&h,nev,&p, &t);

        top[i].helyezes=h;
        strcpy(top[i].nev,nev);
        top[i].pont=p;
        top[i].ido=t;
        i++;
    }

}

void ranglista(RANGLISTA *top)
{
    system("cls");

    printf("Dicsosegtabla: \n");
    int i;
    for(i=0; i<3; i++)
    {
        printf("%d: %s, %d Ft, %.2f mp\n", i+1, top[i].nev, top[i].pont, top[i].ido);
    }
    printf("Nyomjon meg egy billentyut a folytatashoz\n");
    getch();
}

//megnezi, hogy a jelenlegi jatekos ranglistas helyezest ert e el, felulirja a tombben
void tope(RANGLISTA *top, char *nev, int pont, double ido)
{
    int i=0;
    while(i<3 && top[i].pont>pont)
    {
        i++;
    }
    if(i<3)
    {
        strcpy(top[2].nev, nev);
        top[2].pont=pont;
        top[2].helyezes=i+1;
        top[2].ido=ido;
    }
    ranglista_rendez(top,3);
}

void ranglista_rendez(RANGLISTA *top, int db)
{
    int i, j;
    for (i = db-1; i > 0; --i)
        for (j = 0; j < i; ++j)
            if (top[j+1].pont > top[j].pont)
            {
                RANGLISTA temp = top[j];
                top[j] = top[j+1];
                top[j+1] = temp;
            }
}

//a ranglistaba ir ki, ha a jatekos elert annyi pontot, hogy felkeruljon ra
void kiir(RANGLISTA *top)
{
    FILE *fptr;

    fptr = fopen("ranglista.txt", "w");

    int i;

    for(i=0; i<3; i++)
    {
        fprintf(fptr, "%d;%s;%d;%f\n", top[i].helyezes, top[i].nev, top[i].pont, top[i].ido);
    }

    fclose(fptr);

}
