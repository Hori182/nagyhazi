#ifndef JATEK_H_INCLUDED
#define JATEK_H_INCLUDED
#include "seged.h"
#include "ranglista.h"

typedef struct SOR SOR;
typedef struct RANGLISTA RANGLISTA;

void jatek(RANGLISTA jatekos, SOR *eleje, RANGLISTA *top);
void jatek_kiir(SOR *mozgo, int dbf, int dbk,RANGLISTA jatekos);
void kilepes(RANGLISTA *top, SOR *eleje);

#endif // JATEK_H_INCLUDED
