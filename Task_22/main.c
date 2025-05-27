#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _uzel TUzel;

struct _uzel
{
    TUzel* levy;
    TUzel* pravy;
    int klic;
};

typedef struct
{
    TUzel* koren;
} TStrom;

TStrom* StromInit()
{
    TStrom* strom = malloc(sizeof(TStrom));
    if(strom == NULL)
        return NULL;

    strom->koren = NULL;

    return strom;
}

void UzelFree(TUzel* uzel)
{
    if(uzel == NULL)
        return;

    UzelFree(uzel->levy);
    UzelFree(uzel->pravy);
    free(uzel);
}

void StromFree(TStrom* strom)
{
    UzelFree(strom->koren);
}

TUzel* UzelInit(int klic)
{
    TUzel* uzel = malloc(sizeof(TUzel));
    if(uzel == NULL)
        return NULL;

    uzel->levy = NULL;
    uzel->pravy = NULL;
    uzel->klic = klic;

    return uzel;
}

void UzelVloz(TUzel** uzel, int klic)
{
    TUzel* pom = *uzel;

    if(pom == NULL)
    {
        if((pom = UzelInit(klic)) == NULL)
            return;
        *uzel = pom;
        return;
    }

    if(klic < pom->klic)
        return UzelVloz(&pom->levy, klic);
    else
        return UzelVloz(&pom->pravy, klic);
}

void StromVloz(TStrom* strom, int klic)
{
    UzelVloz(&strom->koren, klic);
}

void UzelVzestupne(TUzel* uzel)
{
    if(uzel == NULL)
        return;

    UzelVzestupne(uzel->levy);
    printf("%d\n", uzel->klic);
    UzelVzestupne(uzel->pravy);
}

void StromVzestupne(TStrom* strom)
{
    UzelVzestupne(strom->koren);
}

void UzelSestupne(TUzel* uzel)
{
    if(uzel == NULL)
        return;

    UzelSestupne(uzel->pravy);
    printf("%d\n", uzel->klic);
    UzelSestupne(uzel->levy);
}

void StromSestupne(TStrom* strom)
{
    UzelSestupne(strom->koren);
}

void UzelMinimum(TUzel* uzel)
{
    if(uzel == NULL)
        return;

    if(uzel->levy == NULL)
    {
        printf("%d", uzel->klic);
        return;
    }

    UzelMinimum(uzel->levy);

}

void StromMinimum(TStrom* strom)
{
    UzelMinimum(strom->koren);
}

void UzelMaximum(TUzel* uzel)
{
    if(uzel == NULL)
        return;

    if(uzel->pravy == NULL)
    {
        printf("%d", uzel->klic);
        return;
    }

    UzelMaximum(uzel->pravy);
}

void StromMaximum(TStrom* strom)
{
    UzelMaximum(strom->koren);
}

int UzelVyhledej(TUzel* uzel, int klic)
{
    if(uzel == NULL)
        return -1;

    if(uzel->klic == klic)
        return klic;

    if(klic < uzel->klic)
        return UzelVyhledej(uzel->levy, klic);
    else
        return UzelVyhledej(uzel->pravy, klic);
}

int StromVyhledej(TStrom* strom, int klic)
{
    return UzelVyhledej(strom->koren, klic);
}

void UzelVypisVetsi(TUzel* uzel, int klic)
{
    if(uzel == NULL)
        return;

    if(klic < uzel->klic)
        printf("%d\n", uzel->klic);

    UzelVypisVetsi(uzel->levy, klic);
    UzelVypisVetsi(uzel->pravy, klic);
}

void StromVypisVetsi(TStrom* strom, int klic)
{
    UzelVypisVetsi(strom->koren, klic);
}

void UzelVypisMensi(TUzel* uzel, int klic)
{
    if(uzel == NULL)
        return;

    if(klic > uzel->klic)
        printf("%d\n", uzel->klic);

    UzelVypisMensi(uzel->levy, klic);
    UzelVypisMensi(uzel->pravy, klic);
}

void StromVypisMensi(TStrom* strom, int klic)
{
    UzelVypisMensi(strom->koren, klic);
}

void UzelZrusList(TUzel* uzel, int klic)
{
    if(uzel == NULL)
        return;

    if(uzel->levy != NULL && uzel->levy->klic == klic)
    {
        if(uzel->levy->levy == NULL && uzel->levy->pravy == NULL)
        {
            free(uzel->levy);
            uzel->levy = NULL;
            return;
        }
    }

    if(uzel->pravy != NULL && uzel->pravy->klic == klic)
    {
        if(uzel->pravy->levy == NULL && uzel->pravy->pravy == NULL)
        {
            free(uzel->pravy);
            uzel->pravy = NULL;
            return;
        }
    }

    if(klic < uzel->klic)
        UzelZrusList(uzel->levy, klic);
    else
        UzelZrusList(uzel->pravy, klic);
}

void StromZrusList(TStrom* strom, int klic)
{
    UzelZrusList(strom->koren, klic);
}

int UzelVaha(TUzel* uzel)
{
    if(uzel == NULL)
        return 0;

    return UzelVaha(uzel->levy) + UzelVaha(uzel->pravy) + 1;
}

int StromVaha(TStrom* strom)
{
    return UzelVaha(strom->koren);
}

int UzelVyska(TUzel* uzel)
{
    if(uzel == NULL)
        return 0;

    int levy = UzelVyska(uzel->levy) + 1;
    int pravy = UzelVyska(uzel->pravy) + 1;

    return fmax(levy, pravy);
}

int StromVyska(TStrom* strom)
{
    return UzelVyska(strom->koren);
}

int main()
{
    TStrom* strom = StromInit();
    if(strom == NULL)
        return -1;

    StromVloz(strom, 5);
    StromVloz(strom, 1);
    StromVloz(strom, 6);
    StromVloz(strom, 7);
    StromVloz(strom, 3);
    StromVloz(strom, 9);

    printf("%d\n", StromVyska(strom));

    StromFree(strom);
    return 0;
}
