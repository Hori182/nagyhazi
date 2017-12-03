#ifndef RANGLISTA_H_INCLUDED
#define RANGLISTA_H_INCLUDED

typedef struct RANGLISTA RANGLISTA;

void ranglista_beolvas(RANGLISTA *top);
void ranglista(RANGLISTA *top);
void tope(RANGLISTA *top, char *nev, int pont, double ido);
void ranglista_rendez(RANGLISTA *top, int db);
void kiir(RANGLISTA *top);

#endif // RANGLISTA_H_INCLUDED
