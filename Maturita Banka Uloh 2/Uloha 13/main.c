#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

typedef struct
{
    char jmeno[10];
    int id;
} TUzivatel;

typedef struct
{
    char email[20];
    int ciziId;
} TEmail;

typedef struct
{
    char nazev[20];
    int vyska;
    bool aktivni;
} TSopka;

int zjistiId(FILE* jmena, char jmeno[])
{
    TUzivatel uziv;

    while(fscanf(jmena, "%d, %9s", &uziv.id, uziv.jmeno) == 2)
    {
        if(strcmp(uziv.jmeno, jmeno) == 0)
            return uziv.id;
    }

    return -1;
}

void vypisEmaily(FILE* jmena, FILE* emaily, char jmeno[])
{
    int id = zjistiId(jmena, jmeno);

    if(id == -1)
        return;

    TEmail email;

    while(fscanf(emaily, "%d, %19s", &email.ciziId, email.email) == 2)
    {
        if(email.ciziId == id)
            printf("%d %s %s\n", id, jmeno, email.email);
    }
}

void nactiSopky(TSopka sopky[], FILE* vstup, int* n)
{
    int i = 0;
    char aktivni[5];

    while(fscanf(vstup, "%19s %d %4s", sopky[i].nazev, &sopky[i].vyska, aktivni) == 3)
    {
        if(strcmp(aktivni, "ano") == 0)
            sopky[i].aktivni = true;
        else
            sopky[i].aktivni = false;

        i++;
    }

    *n = i;
}

void vypis(TSopka sopky[], int n, int vyska, bool nadprumer, bool aktivni)
{
    for(int i = 0; i < n;i++)
    {
        if(sopky[i].aktivni == aktivni)
        {
            if(nadprumer && sopky[i].vyska > vyska)
            {
                printf("%s %d %s\n", sopky[i].nazev, sopky[i].vyska, sopky[i].aktivni ? "ano" : "ne");
            }
            else if (!nadprumer && sopky[i].vyska < vyska)
            {
                printf("%s %d %s\n", sopky[i].nazev, sopky[i].vyska, sopky[i].aktivni ? "ano" : "ne");
            }
        }
    }
}

int main()
{
    TSopka sopky[MAX];

    FILE* vstup = fopen("sopky.txt", "r");
    if(vstup == NULL)
        return -1;

    int n;

    nactiSopky(sopky, vstup, &n);

    vypis(sopky, n, 1500, false, true);

    fclose(vstup);
    return 0;
}
