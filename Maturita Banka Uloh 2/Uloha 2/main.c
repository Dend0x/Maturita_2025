#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
#include <ctype.h>

typedef struct
{
    float koef[MAX];
    int rad;
} TPoly;

typedef int (*TAkce) (void);

typedef struct
{
    bool chyba;
    char zprava[MAX];
    TAkce akce;
} TPolozka;

float vycisli(TPoly* pol, float x)
{
    float suma = 0;

    for(int i = 0; i < pol->rad + 1; i++)
    {
        suma = suma * x + pol->koef[i];
    }

    return suma;
}

bool nactiPolynom(TPoly* pol, FILE* vstup)
{
    if(fscanf(vstup, "%d", &pol->rad) != 1)
        return false;

    for(int i = 0; i < pol->rad + 1; i++)
    {
        if(fscanf(vstup, "%f", &pol->koef[i]) != 1)
            return false;
    }

    return true;
}

void vypisPoslednichN(float pole[], int n, int i)
{
    for(int j = i; j < i + n; j++)
    {
        printf("%.1f\n", pole[j % n]);
    }
}

void vypisSoucetPoslednichN(float pole[], int n)
{
    float suma = 0;

    for(int i = 0; i < n; i++)
    {
        suma += pole[i];
    }

    printf("%.1f\n", suma);
}

void vypisPoslednichNObracene(float pole[], int n, int i)
{
    for(int j = i + n - 1; j >= i; j--)
    {
        printf("%.1f\n", pole[j % n]);
    }
}

void nactiNHodnot(FILE* vstup, int n)
{
    float pole[n];

    int i = 0;

    while(fscanf(vstup, "%f", &pole[i % n]) == 1)
    {
        i++;
    }

    vypisPoslednichNObracene(pole, n, i);
}

void poctyHistogram(int histogram[], char konec)
{
    char znak;
    while(scanf("%c", &znak) == 1 && znak != konec)
    {
        histogram[znak]++;
    }
}

void vypisHistogram(int histogram[])
{
    for(int i = 0; i < 256; i++)
    {
        if(histogram[i] != 0 && !isspace(i))
            printf("\'%c\' = %d\n", i, histogram[i]);
    }
}

int akceChyba()
{
    printf("Chyba\n");
    return 0;
}

int akceA()
{
    printf("A\n");
    return 0;
}

int akceB()
{
    printf("B\n");
    return 0;
}

int akceX()
{
    printf("Neznama Volba\n");
    return 0;
}

int akceKonec()
{
    printf("Konec");
    return 1;
}

void vypisNabidku(TPolozka polozky[])
{
    for(int i = 0; i < MAX; i++)
    {
        if(!polozky[i].chyba)
            printf("%c - %s\n", i, polozky[i].zprava);
    }
}

int main()
{
    TPolozka polozky[MAX];

    for(int i = 0; i < MAX; i++)
    {
        polozky[i] = (TPolozka){true, "chyba", akceChyba};
    }

    polozky['A'] = (TPolozka){false, "Volba A", akceA};
    polozky['B'] = (TPolozka){false, "Volba B", akceB};
    polozky['X'] = (TPolozka){false, "Neznama volba", akceX};
    polozky['K'] = (TPolozka){false, "Konec", akceKonec};

    while(1)
    {
        char volba;

        vypisNabidku(polozky);

        if(scanf("%c", &volba) != 1)
            continue;

        fflush(stdin);

        if(polozky[volba].akce() == 1)
            return 0;
    }

    return 1;
}
