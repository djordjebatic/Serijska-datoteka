#include "Pumpa.h"

void ispisMeni() {

    printf("0: Odabir datoteke\n");
    printf("1: Formiranje nove datoteke\n");
    printf("2: Pisanje sloga u datoteku\n");
    printf("3: Prikaz svih slogova\n");
   printf("4: Trazenje sloga po kljucu\n");
    printf("5: Logicko brisanje sloga\n");
    printf("6: Fizicko brisanje sloga\n");
    printf("7: Trazenje sloga po tipu derivata\n");
   printf("8: Profiti po derivatu\n");
    printf("9: Sekvencijalna datoteka\n");
    printf("10: Reorganizacija\n");
    printf("11: Izlaz\n");
}

int main()
{
    int naredba;
    char naziv[15];

    while(naredba!=11) {
        ispisMeni();
        printf("\nIzbor: ");
        scanf("%d", &naredba);

        switch(naredba){
            case 0: OdabirDatoteke(&naziv);
            break;
            case 1: FormiranjeDatoteke(&naziv);
            break;
            case 2: PisanjeSlogaUDatoteku(naziv);
            break;
            case 3: PrikazSvihSlogova(naziv);
            break;
            case 4: TrazenjeSlogaPoKljucu(naziv);
            break;
            case 5: LogickoBrisanjeSloga(naziv);
            break;
            case 6: FizickoBrisanjeSloga(naziv);
            break;
            case 7: PretragaPoTipuDerivata(naziv);
            break;
            case 8: UkupanProfitPoDerivatu(naziv);
            break;
            case 9: SekvencijalnaDatoteka(naziv);
            break;
            case 10: Reorganizacija(naziv);
            break;
            case 11: break;

            default: printf("Neposotjeca naredba");break;
        }
    }
}
