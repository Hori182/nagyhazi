#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#endif

typedef struct SOR
{
    char kerdes[200];
    char a[20];
    char b[20];
    char c[20];
    char d[20];
    char jo;
    int nehezseg;
    char kategoria[20];
    struct SOR *kov;
} SOR;

//struktura a jelenlegi jatekos nevehez/idejehez/pontszamahoz
typedef struct RANGLISTA
{
    int helyezes;
    char nev[20];
    int pont;
    double ido;
} RANGLISTA;

void jatek(RANGLISTA jatekos, SOR *eleje, RANGLISTA *top);
void ranglista(RANGLISTA *top);
void felezes(char *kivesz, SOR *mozgo);
void kozonseg(int *szazalek, char jo);
void tope(RANGLISTA *top, char *nev, int pont, double ido);
void ranglista_rendez(RANGLISTA *top, int db);
void lista_felszabadit(SOR *eleje);
void kiir(RANGLISTA *top);

void kilepes(RANGLISTA *top, SOR *eleje)
{
    kiir(top);
    lista_felszabadit(eleje);
    exit(1);
}

//menu:
//ez a fuggveny irja ki a menupontokat, itt lehet kivalasztani, hogy a felhasznalo mit szeretne csinálni(jatek/dicsosegtabla megtekintese/kilepes)
//a valasztastol fuggoen meghivja a megfelelo fuggvenyt
void menu(RANGLISTA jatekos, SOR *eleje, RANGLISTA *top)
{
    system("cls");
    printf("1. Uj jatek\n");
    printf("2. Dicsosegtabla\n");
    printf("3. Kilepes\n");

    int mvalaszt;

    printf("Mit szeretnél? ");

    scanf("%d", &mvalaszt);

    switch (mvalaszt)
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
    }
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

//ez a fuggveny a jatekert felel, kiirja a kerdest es bekeri a felasznalotol a valaszt
//ez addig fut, mig a felhasznalo helyes valaszokat ad
void jatek(RANGLISTA jatekos, SOR *eleje, RANGLISTA *top)
{
    system("cls");

    printf("Add meg a neved: ");

    jatekos.pont=0;
    int hozzaad=12500;
    int db=0;

    scanf("%s", jatekos.nev);

    clock_t start = clock();
    bool game=true;

    char kivesz[2];
    int dbf=0,dbk=0;

    while(game)
    {
        system("cls");
        int hanyadik=rand()%listahossz(eleje);

        SOR *mozgo;
        int i;
        for (mozgo = eleje, i=0; mozgo != NULL && i<hanyadik; mozgo = mozgo->kov, i++)
        {
            ;
        }

        char valasz;
        int szazalek[4];

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
/*bool volte() {

}*/

//felezos segitseg:
void felezes(char *kivesz, SOR *mozgo)
{
    int i;
    bool van;
    int j;
    char a;
    for(i=0;i<2;i++)
    {
        do {
            a=rand()%4+65;
            van = false;
            for (j = 0; j < i; j++) {
                if (kivesz[j] == a) {
                    van = true;
                }
            }
        } while (van || a==mozgo->jo);
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
        if(i!=jo-66 && db==0)
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

//ranglista.txt be kell olvasni

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
        printf("%d: %s, %d Ft, %f mp\n", i+1, top[i].nev, top[i].pont, top[i].ido);
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

void ranglista_rendez(RANGLISTA *top, int db) {
    int i, j;

    for (i = db-1; i > 0; --i)
        for (j = 0; j < i; ++j)
            if (top[j+1].pont > top[j].pont) {
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
//kilepes fuggvenye


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

    while (1)
    {
        menu(jatekos, eleje, top);
    }

    return 0;
}
