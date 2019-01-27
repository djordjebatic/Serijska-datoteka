#ifndef PUMPA_H_INCLUDED
#define PUMPA_H_INCLUDED
#define FAKTOR_BLOKIRANJA 3

#include <string.h>
#include <stdio.h>

typedef struct pumpa {

    int sifraProdaje;
    int kolicinaDerivata;
    char tipDerivata[15];
    char datumProdaje[15];
    int jedinicnaCena;
    int ukupnaCena;

}Pumpa;

typedef struct slog {

    Pumpa pumpa;
    int statusSloga;//0-1-2

}Slog;

typedef struct blok {

    Slog slog[FAKTOR_BLOKIRANJA];

}Blok;

int FajlPostoji(char *naziv, FILE **f);
void FormiranjePraznogSloga(Slog *slog);
void FormiranjePraznogBloka(Blok *blok);
void OdabirDatoteke(char **naziv);
void FormiranjeDatoteke(char **naziv);
void PisanjeSlogaUDatoteku(char *naziv);
void PrikazSvihSlogova(char *naziv);
void TrazenjeSlogaPoKljucu(char *naziv);
void LogickoBrisanjeSloga(char *naziv);
void FizickoBrisanjeSloga(char *naziv);
void PretragaPoTipuDerivata(char *naziv);
void UkupanProfitPoDerivatu(char *naziv);
void SekvencijalnaDatoteka(char *naziv);
void Reorganizacija(char *naziv);

void IspisiPumpu(Pumpa *pumpa);
void UpisiPumpu(Pumpa *pumpa);


#endif // PUMPA_H_INCLUDED
