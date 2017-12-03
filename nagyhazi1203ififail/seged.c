#include "seged.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

int listahossz(SOR *eleje)
{
    int hossz = 0;
    SOR *p = eleje;
    while (p != NULL)
    {
        hossz++;
        p = p->kov;
    }
    return hossz;
}
SOR *beolvas()
{
    FILE* fptr;

    fptr = fopen("loim.csv", "r");

    char line[400];
    int nehez;
    char ker[200];
    char a[30];
    char b[30];
    char c[30];
    char d[30];
    char j;
    char k[20];

    SOR *eleje=NULL;
    while(fgets(line, 300,fptr))
    {
        sscanf(line,"%d;%[^;];%[^;];%[^;];%[^;];%[^;];%c;%s\n", &nehez, ker, a, b, c, d, &j, k);

        SOR *t=(SOR*) malloc(sizeof(SOR));

        strcpy(t->kerdes,ker);
        strcpy(t->a,a);
        strcpy(t->b,b);
        strcpy(t->c,c);
        strcpy(t->d,d);
        t->jo=j;
        t->nehezseg=nehez;
        strcpy(t->kategoria,k);
        t->kov=NULL;

        if(eleje==NULL)
        {
            eleje=t;
        }
        else
        {
            t->kov=eleje;
            eleje=t;
        }
    }

    return eleje;
}


//felezos segitseg:
void felezes(char *kivesz, SOR *mozgo)
{
    int i;
    bool van;
    int j;
    char a;
    for(i=0; i<2; i++)
    {
        do
        {
            a=rand()%4+65;
            van = false;
            for (j = 0; j < i; j++)
            {
                if (kivesz[j] == a)
                {
                    van = true;
                }
            }
        }
        while (van || a==mozgo->jo);
        kivesz[i]=a;
    }

}
//kozonseg segitsege: a tomb elso tagjanal azert van ketszerezve a random szam,
//hogy valoszinubb legyen, hogy a kozonseg jo valaszt ad a kerdesre,
//de lehetoseg legyen arra is hogy rossz valaszt adnak
void kozonseg(int *szazalek, char jo)
{

    int szaz=100;

    szazalek[0]=(rand()%50+1)*2;
    szaz-=szazalek[0];
    szazalek[1]=rand()%szaz;
    szaz-=szazalek[1];
    szazalek[2]=rand()%szaz;
    szaz-=szazalek[2];
    szazalek[3]=szaz;

    int i;
    int db=0;
    for(i=0; i<4; i++)
    {
        if(i!=jo-65 && db==0)
        {
            int temp=szazalek[i];
            szazalek[i]=szazalek[i+1];
            szazalek[i+1]=temp;
        }
        if(i==jo-66)
        {
            db++;
        }
    }
}
void lista_felszabadit(SOR *eleje)
{
    SOR *p = eleje;
    while (p != NULL)
    {
        SOR *tmp = p->kov;
        free(p);
        p = tmp;
    }
}
