#include "Pumpa.h"

void FormiranjePraznogSloga(Slog *slog){

    slog->statusSloga = 2;
    slog->pumpa.jedinicnaCena = 0;
    slog->pumpa.kolicinaDerivata = 0;
    slog->pumpa.sifraProdaje = 0;
    slog->pumpa.ukupnaCena = 0;
    strcpy(slog->pumpa.datumProdaje, "");
    strcpy(slog->pumpa.tipDerivata,"");
}

void FormiranjePraznogBloka(Blok *blok) {

    for (int i = 0; i < FAKTOR_BLOKIRANJA; i++) {
        FormiranjePraznogSloga(&blok->slog[i]);
    }
}

void FormiranjeDatoteke(char **naziv){

    FILE *f;
    Blok blok;

    printf("\nUnesite naziv nove datoteke: ");
    scanf("%s", naziv);

    f = fopen(naziv, "wb");
    FormiranjePraznogBloka(&blok);
    fwrite(&blok, sizeof(Blok), 1, f);

    printf("\nDatoteka uspesno formirana\n-----------------\n: ");
    fclose(f);
}

int FajlPostoji(char *naziv, FILE **f) {

    if ((*f = fopen(naziv, "rb+")) == NULL) {
        printf("\nNepostojeci fajl\n----------\n");
        return 0;
    }
    return 1;
}

void OdabirDatoteke(char **naziv){

    FILE *f;

    printf("\nOdaberite zeljenu datoteku: ");
    scanf("%s", naziv);

    if (!FajlPostoji(naziv, &f)) {
        return;
    }

    printf("\n----------------------\n");
    fclose(f);
}

void PrikazSvihSlogova(char *naziv){

    FILE *f;
    Blok blok;
    int i, brojac = 1;

    if (!FajlPostoji(naziv, &f)) {
        return;
    }

    while(fread(&blok, sizeof(Blok), 1, f)) {
        printf("\n------------BLOK%d-------------\n", brojac);
        for (i = 0; i < FAKTOR_BLOKIRANJA; i++) {
            printf("\nSlog---->%d\n", i);
            IspisiPumpu(&blok.slog[i].pumpa);
            printf("Status sloga: %d\n", blok.slog[i].statusSloga);
        }
        brojac++;
    }
    printf("\n------------------\n");
}

void PisanjeSlogaUDatoteku(char *naziv) {

    FILE *f;
    Blok blok, blok2;
    Pumpa pumpa;
    int i, flag = 0;

    if(!FajlPostoji(naziv, &f)) {
        return;
    }

    UpisiPumpu(&pumpa);

    while (flag == 0 && fread(&blok,sizeof(Blok), 1, f)) {
        for (i = 0; i < FAKTOR_BLOKIRANJA; i++) {
            if (blok.slog[i].statusSloga != 0) {
                flag = 1;
                break;
            }
        }
    }

    fseek(f, -sizeof(Blok), SEEK_CUR);
    if (i == FAKTOR_BLOKIRANJA - 1) {
        FormiranjePraznogBloka(&blok2);
        blok.slog[i].statusSloga = 0;
        blok.slog[i].pumpa = pumpa;
        fwrite(&blok, sizeof(Blok), 1, f);
        fwrite(&blok2, sizeof(Blok), 1, f);
        fclose(f);
    }
    else {
        blok.slog[i].statusSloga = 0;
        blok.slog[i].pumpa = pumpa;
        fwrite(&blok, sizeof(Blok), 1, f);
        fclose(f);
    }

    printf("\nSlog uspesno unet\n---------------------\n");
}

void TrazenjeSlogaPoKljucu(char *naziv) {

    FILE *f;
    Blok blok;
    int flag = 0, i;
    int sifra;

    if(!FajlPostoji(naziv, &f)) {
        return;
    }

    printf("\nUnesite sifru sloga: ");
    scanf("%d", &sifra);

    while(flag == 0 && fread(&blok, sizeof(Blok), 1, f)) {
        for (i = 0; i < FAKTOR_BLOKIRANJA; i++) {
            if (blok.slog[i].pumpa.sifraProdaje == sifra){
            flag = 1;
            break;
            }
        }
    }

    if (flag == 0) {
        printf("\nUneli ste nepostojecu sifru\n------------\n");
    }
    else {
        IspisiPumpu(&blok.slog[i].pumpa);
    }
    printf("\n---------------------\n");
    fclose(f);
}

void LogickoBrisanjeSloga(char *naziv) {

    FILE *f;
    Blok blok;
    int flag = 0, i;
    int sifra;

    if(!FajlPostoji(naziv, &f)) {
        return;
    }

    printf("\nUnesite sifru sloga: ");
    scanf("%d", &sifra);

    while(flag == 0 && fread(&blok, sizeof(Blok), 1, f)) {
        for (i = 0; i < FAKTOR_BLOKIRANJA; i++) {
            if (blok.slog[i].pumpa.sifraProdaje == sifra){
            blok.slog[i].statusSloga = 1;
            flag = 1;
            break;
            }
        }
    }

    if (flag == 0) {
        printf("\nUneli ste nepostojecu sifru\n-----------\n");
    }
    else {
        fseek(f, -sizeof(Blok), SEEK_CUR);
        fwrite(&blok, sizeof(Blok), 1, f);
        printf("Slog uspesno logicki izbrisan\n-------------------");
        IspisiPumpu(&blok.slog[i].pumpa);
        printf("Status sloga: %d\n", blok.slog[i].statusSloga);
        printf("-------------------\n");
    }
    fclose(f);
}

void FizickoBrisanjeSloga(char *naziv) {

    FILE *f;
    Blok blok, blok2;
    Slog slog, temp;
    int sifra, flag = 0, i;

    if(!FajlPostoji(naziv, &f)) {
        return;
    }

    printf("\nUnesite sifru sloga: ");
    scanf("%d", &sifra);

    while(flag == 0 && fread(&blok, sizeof(Blok), 1, f)) {
        for (i = 0; i < FAKTOR_BLOKIRANJA; i++) {
            if (blok.slog[i].pumpa.sifraProdaje == sifra){
            flag = 1;
            break;
            }
        }
    }

    if (flag == 0) {
        printf("\nNepostojeca sifra\n------------------\n");
        fclose(f);
        return;
    }

        do {

            for (; i < FAKTOR_BLOKIRANJA - 1; i++){
                memcpy(&temp, &blok.slog[i], sizeof(Slog));
                memcpy(&blok.slog[i], &blok.slog[i + 1], sizeof(Slog));
                memcpy(&blok.slog[i+1], &temp, sizeof(Slog));
            }
            if (fread(&blok2, sizeof(Blok), 1, f)) {
                memcpy(&temp, &blok2.slog[0], sizeof(Slog));
                memcpy(&blok2.slog[0], &blok.slog[FAKTOR_BLOKIRANJA - 1], sizeof(Slog));
                memcpy(&blok.slog[FAKTOR_BLOKIRANJA - 1], &temp, sizeof(Slog));
                fseek(f, -2*sizeof(Blok), SEEK_CUR);

                fwrite(&blok, sizeof(Blok), 1, f);
                fflush(f);
                fwrite(&blok2, sizeof(Blok), 1, f);
                fflush(f);
                memcpy(&blok, &blok2, sizeof(Blok));
                i = 0;
            }
            else {
                fseek(f, -sizeof(Blok), SEEK_CUR);
                FormiranjePraznogSloga(&blok.slog[FAKTOR_BLOKIRANJA - 1]);
                fwrite(&blok, sizeof(Blok), 1, f);
                printf("\nBrisanje uspesno izvrseno\n-------------------\n");
                fclose(f);
                PrikazSvihSlogova(naziv);
                printf("--------------------\n");
                return;
            }
        }while (1);
}

void PretragaPoTipuDerivata(char *naziv) {

    FILE *f;
    Blok blok;
    int i, flag = 0;
    char *derivat;

    if(!FajlPostoji(naziv, &f)) {
        return;
    }

    printf("\nUnesite tip derivata: ");
    scanf("%s", &derivat);

    while(fread(&blok, sizeof(Blok), 1, f)) {
        for (i = 0; i < FAKTOR_BLOKIRANJA; i++) {
            if (!strcmp(blok.slog[i].pumpa.tipDerivata, &derivat)){
                IspisiPumpu(&blok.slog[i].pumpa);
                flag = 1;
            }
        }
    }

    if (flag == 0) {
        printf("\nUneli ste nepostojeci derivat\n-----------\n");
    }
    else {
        printf("\n-----------\n");
    }
    fclose(f);
}

void UkupanProfitPoDerivatu(char *naziv) {

    FILE *f;
    Blok blok;
    char tipovi[50][15] = {""};
    int sume[50] = {0};
    int i, brojac = 0;

    if(!FajlPostoji(naziv, &f)){
        return;
    }

    while (fread(&blok,sizeof(Blok), 1, f)) {
        for (i = 0; i < FAKTOR_BLOKIRANJA; i ++) {
            if (blok.slog[i].pumpa.jedinicnaCena == 0){
                break;
            }

            for (int a = 0; a < brojac + 1; a++) {
                if (strcmp(blok.slog[i].pumpa.tipDerivata, tipovi[a])) {
                    if (!strcmp(tipovi[a], "")) {
                        strcpy(tipovi[brojac], blok.slog[i].pumpa.tipDerivata);
                        sume[brojac] = blok.slog[i].pumpa.ukupnaCena;
                        brojac++;
                        break;
                    }
                }
                else {
                    sume[a] += blok.slog[i].pumpa.ukupnaCena;
                    break;
                }
            }
        }
    }

    for (int a = 0; a < brojac; a++){
        printf("\nUkupan profit za tip derivata %s je %d\n", tipovi[a],sume[a]);
    }
    printf("\n-----------------------\n");
    fclose(f);
}

//Ne radi najbolje - debagovati.
void SekvencijalnaDatoteka(char *naziv) {

    FILE *f;
    Blok blok, blok2;
    int i, a;
    Slog slog, temp;
    int stop = 0;

    if(!FajlPostoji(naziv, &f)){
        return;
    }

    while (fread(&blok, sizeof(Blok), 1, f)) {
        for (i = 1; i < FAKTOR_BLOKIRANJA - 1; i++) {
            do {
                stop = 0;
                for (; i < FAKTOR_BLOKIRANJA; i++) {
                    if (blok.slog[i-1].pumpa.ukupnaCena < blok.slog[i].pumpa.ukupnaCena){
                        memcpy(&temp, &blok.slog[i - 1], sizeof(Slog));
                        memcpy(&blok.slog[i - 1], &blok.slog[i], sizeof(Slog));
                        memcpy(&blok.slog[i], &temp, sizeof(Slog));
                    }
                }
                if (fread(&blok2,sizeof(Blok),1,f)) {
                    if (blok2.slog[0].pumpa.jedinicnaCena > blok.slog[FAKTOR_BLOKIRANJA - 1].pumpa.jedinicnaCena) {
                        memcpy(&temp, &blok2.slog[0], sizeof(Slog));
                        memcpy(&blok2.slog[0], &blok.slog[FAKTOR_BLOKIRANJA - 1], sizeof(Slog));
                        memcpy(&blok.slog[FAKTOR_BLOKIRANJA - 1], &temp, sizeof(Slog));
                        for ( a = 1; a < FAKTOR_BLOKIRANJA; a++) {
                            if (blok2.slog[a-1].pumpa.ukupnaCena < blok2.slog[a].pumpa.ukupnaCena){
                                memcpy(&temp, &blok2.slog[a - 1], sizeof(Slog));
                                memcpy(&blok2.slog[a - 1], &blok2.slog[a], sizeof(Slog));
                                memcpy(&blok2.slog[a], &temp, sizeof(Slog));
                        }
                        }
                    }
                        fseek(f, -2*sizeof(Blok), SEEK_CUR);

                        fwrite(&blok,sizeof(Blok), 1, f);
                        fflush(f);
                        fwrite(&blok2, sizeof(Blok), 1, f);
                        fflush(f);

                        i = 0;
                }
                else {
                    fseek(f, -sizeof(Blok), SEEK_CUR);
                    fwrite(&blok, sizeof(Blok),1,f);
                    fwrite(&blok2, sizeof(Blok), 1, f);
                    fclose(f);
                    printf("\Sekvencijalizacija uspesnan--------------------\n");
                    stop = 1;
                }
            }while(stop!=1);
    }
    }
}

void Reorganizacija(char *naziv) {

    FILE *f;
    Blok blok, blok2;
    Slog temp, slog;
    int i, stop = 0;

    if(!FajlPostoji(naziv, &f)){
        return;
    }

    while (fread(&blok,sizeof(Blok),1 ,f)){
        for (i = 0; i < FAKTOR_BLOKIRANJA; i++) {
            if (blok.slog[i].statusSloga == 1) {
                do {
                    for (; i < FAKTOR_BLOKIRANJA - 1; i++){
                        memcpy(&temp, &blok.slog[i], sizeof(Slog));
                        memcpy(&blok.slog[i], &blok.slog[i+1], sizeof(Slog));
                        memcpy(&blok.slog[i+1], &temp, sizeof(Slog));
                    }
                    if (fread(&blok2, sizeof(Blok), 1, f)) {
                        memcpy(&temp, &blok2.slog[0], sizeof(Slog));
                        memcpy(&blok2.slog[0], &blok.slog[FAKTOR_BLOKIRANJA - 1], sizeof(Slog));
                        memcpy(&blok.slog[FAKTOR_BLOKIRANJA - 1], &temp, sizeof(Slog));
                        fseek(f, -2*sizeof(Blok), SEEK_CUR);

                        fwrite(&blok, sizeof(Blok), 1, f);
                        fflush(f);
                        fwrite(&blok2, sizeof(Blok), 1 ,f);
                        fflush(f);
                        memcpy(&blok, &blok2, sizeof(Blok));
                        i = 0;
                    }
                    else {
                        fseek(f, -sizeof(Blok), SEEK_CUR);
                        fwrite(&blok, sizeof(Blok),1 , f);
                        fclose(f);
                        stop = 1;
                    }
                }while(stop!=1);
            }
        }
    }

}

void UpisiPumpu(Pumpa *pumpa) {

    printf("\nSifra prodaje: ");
    scanf("%d", &pumpa->sifraProdaje);
    printf("\nKolicina derivata: ");
    scanf("%d", &pumpa->kolicinaDerivata);
    printf("\nTip derivata: ");
    scanf("%s", &pumpa->tipDerivata);
    printf("\nDatum prodaje: ");
    scanf("%s", &pumpa->datumProdaje);
    printf("\nJedinicna cena: ");
    scanf("%d", &pumpa->jedinicnaCena);
    pumpa->ukupnaCena = pumpa->jedinicnaCena * pumpa->kolicinaDerivata;

    printf("\nUpis uspesno obavljen\n------------\n");
}

void IspisiPumpu(Pumpa *pumpa) {

    printf("\nSifra prodaje: %d", pumpa->sifraProdaje);
    printf("\nKolicina derivata: %d", pumpa->kolicinaDerivata);
    printf("\nTip derivata: %s", pumpa->tipDerivata);
    printf("\nDatum prodaje: %s", pumpa->datumProdaje);
    printf("\nJedinicna cena: %d", pumpa->jedinicnaCena);
    printf("\nUkupna cena: %d\n", pumpa->ukupnaCena);
}

