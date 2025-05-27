#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#define N 20

void nahradHash(FILE* vstup, FILE* vystup, char retezec[])
{
    char c;
    while((c = fgetc(vstup)) != EOF)
    {
        if(c == '#')
            fputs(retezec, vystup);
        else
            fputc(c, vystup);
    }
}

bool nactiRadek(FILE* vstup, FILE* vystup)
{
    char c;

    while((c = fgetc(vstup)) != EOF)
    {
        fputc(c, vystup);

        if(c == '\n')
        {
            return true;
        }
    }

    return false;
}

void doDvou(FILE* vstup, FILE* vstup2, FILE* vystup)
{
    bool prvni = true;
    bool druhy = true;

    while(prvni && druhy)
    {
        prvni = nactiRadek(vstup, vystup);
        druhy = nactiRadek(vstup2, vystup);
    }

    while(prvni)
        prvni = nactiRadek(vstup, vystup);
    while(druhy)
        druhy = nactiRadek(vstup2, vystup);
}

void pocetSlov(FILE* vstup, FILE* vystup)
{
    bool veSlove = false;
    int pocetSlov = 0;
    char c;

    while((c = fgetc(vstup)) != EOF)
    {
        if(isspace(c))
        {
            if(c == '\n')
            {
                fprintf(vystup, "%d\n", pocetSlov);
                pocetSlov = 0;
                veSlove = false;
            }
            else
                veSlove = false;
        }
        else
        {
            if(!veSlove)
            {
                veSlove = true;
                pocetSlov++;
            }
        }
    }

    if(pocetSlov > 0)
        fprintf(vystup, "%d\n", pocetSlov);
}

int najdiNulu(FILE* vstup)
{
    int cislo;
    while(fscanf(vstup, "%d", &cislo) == 1)
    {
        if(cislo == 0)
            return ftell(vstup);
    }

    return -1;
}

int najdiCislo(FILE* vstup, int klic)
{
    int indexNula = najdiNulu(vstup);

    rewind(vstup);

    int cislo;

    while(fscanf(vstup, "%d", &cislo) == 1 && cislo <= klic)
    {
        if(cislo == klic)
            return cislo;
    }


    fseek(vstup, indexNula, SEEK_SET);

    while(fscanf(vstup, "%d", &cislo) == 1)
    {
        if(cislo == klic)
            return cislo;
    }

    return -1;
}

int main()
{
    char nazevVstup[N];

    printf("Vstup: ");
    if(scanf("%19s", nazevVstup) != 1)
        return -1;

    FILE* vstup = fopen(nazevVstup, "r");
    if(vstup == NULL)
        return -2;

    printf("%d", najdiCislo(vstup, 10));

    fclose(vstup);
    return 0;
}
