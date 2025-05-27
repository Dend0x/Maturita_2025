#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

typedef struct
{
    char nazev[20];
    int vyska;
    bool jeAktivni;
} TSopka;

bool nactiSopky(TSopka sopky[], FILE* vstup, int* n)
{
    *n = 0;
    char jeAktivni[4];

    while(fscanf(vstup, "%19s %d %3s", sopky[*n].nazev, &sopky[*n].vyska, jeAktivni) == 3)
    {
        if(strcmp(jeAktivni, "ano") == 0)
            sopky[*n].jeAktivni = true;
        else if(strcmp(jeAktivni, "ne") == 0)
            sopky[*n].jeAktivni = false;
        else
            return false;

        (*n)++;
    }

    return true;
}

void vypisSopky(TSopka sopky[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%s %d %s\n", sopky[i].nazev, sopky[i].vyska, sopky[i].jeAktivni ? "ano" : "ne");
    }
}

float vypisPrumer(TSopka sopky[], int n, bool aktivni)
{
    int suma = 0;

    for(int i = 0; i < n; i++)
    {
        suma += sopky[i].vyska;
    }

    return suma / (float) n;
}

void vypisVetsi(TSopka sopky[], int n, float vyska)
{
    for(int i = 0; i < n; i++)
    {
        if(sopky[i].vyska > vyska)
            printf("%s %s\n", sopky[i].nazev, sopky[i].jeAktivni ? "ano" : "ne");
    }
}

void vypisDoSouboru(TSopka sopky[], int n, FILE* vystup, bool aktivni)
{
    for(int i = 0; i < n; i++)
    {
        if(sopky[i].jeAktivni == aktivni)
        {
            fprintf(vystup, "%s %d %s\n", sopky[i].nazev, sopky[i].vyska, sopky[i].jeAktivni ? "ano" : "ne");
        }
    }
}

int main()
{
    char nazev[20];
    int n;

    printf("Zadej nazev souboru: ");

    if(scanf("%19s", nazev) != 1)
        return -1;

    TSopka sopky[MAX];

    FILE* vstup = fopen(nazev, "r");
    if(vstup == NULL)
        return -2;

    FILE* vystupAkt = fopen("aktivni.txt", "w");
    if(vystupAkt == NULL)
        return -2;

    FILE* vystupNeakt = fopen("neaktivni.txt", "w");
    if(vystupNeakt == NULL)
        return -2;

    if(!nactiSopky(sopky, vstup, &n))
    {
        fclose(vstup);
        fclose(vystupAkt);
        fclose(vystupNeakt);
        return -3;
    }

    vypisDoSouboru(sopky, n, vystupAkt, true);
    vypisDoSouboru(sopky, n, vystupNeakt, false);

    fclose(vstup);
    fclose(vystupAkt);
    fclose(vystupNeakt);
    return 0;
}
