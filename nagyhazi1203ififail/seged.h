#ifndef SEGED_H_INCLUDED
#define SEGED_H_INCLUDED

typedef struct SOR SOR;

int listahossz(SOR *eleje);
void felezes(char *kivesz, SOR *mozgo);
void kozonseg(int *szazalek, char jo);
SOR *beolvas();
void lista_felszabadit(SOR *eleje);


#endif // SEGED_H_INCLUDED
