#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool nactiZnak(FILE* vstup, char* c)
{
    return fscanf(vstup, "%c", c) == 1;
}

bool vypisZnak(FILE* vystup, char c)
{
    return fprintf(vystup, "%c", c) > 0;
}

void slucDva(FILE* vstup, FILE* vstup2, FILE* vystup)
{
    char a, b;
    bool prvni = nactiZnak(vstup, &a);
    bool druhy = nactiZnak(vstup2, &b);

    while(prvni && druhy)
    {
        printf("a: %c, b: %c\n", a, b);
        if(a <= b)
        {
            vypisZnak(vystup, a);
            prvni = nactiZnak(vstup, &a);
        }
        else
        {
            vypisZnak(vystup, b);
            druhy = nactiZnak(vstup2, &b);
        }
    }

    while(prvni)
    {
        vypisZnak(vystup, a);
        prvni = nactiZnak(vstup, &a);
    }
    while(druhy)
    {
        vypisZnak(vystup, b);
        druhy = nactiZnak(vstup2, &b);
    }
}

void slucPoDvojicich(FILE* vstup, FILE* vstup2, FILE* vystup)
{
    char a, b;
    bool prvni = nactiZnak(vstup, &a);
    bool druhy = nactiZnak(vstup2, &b);

    while(prvni && druhy)
    {
        if(a <= b)
        {
            vypisZnak(vystup, a);
            vypisZnak(vystup, b);
        }
        else
        {
            vypisZnak(vystup, b);
            vypisZnak(vystup, a);
        }

        prvni = nactiZnak(vstup, &a);
        druhy = nactiZnak(vstup2, &b);
    }

    while(prvni)
    {
        vypisZnak(vystup, a);
        prvni = nactiZnak(vstup, &a);
    }

    while(druhy)
    {
        vypisZnak(vystup, b);
        druhy = nactiZnak(vstup2, &b);
    }
}

void PoNticich(FILE* vstup, FILE* vstup2, FILE* vystup, int n)
{
    char a, b;
    bool prvni = nactiZnak(vstup, &a);
    bool druhy = nactiZnak(vstup2, &b);

    while(prvni && druhy)
    {
        for(int i = 0; i < n && prvni; i++)
        {
            vypisZnak(vystup, a);
            prvni = nactiZnak(vstup, &a);
        }

        for(int i = 0; i < n && druhy; i++)
        {
            vypisZnak(vystup, b);
            druhy = nactiZnak(vstup2, &b);
        }
    }

    while(prvni)
    {
        vypisZnak(vystup, a);
        prvni = nactiZnak(vstup, &a);
    }

    while(druhy)
    {
        vypisZnak(vystup, b);
        druhy = nactiZnak(vstup2, &b);
    }
}

int main()
{
    char nazevVstupu[20];
    char nazevVstupu2[20];
    char nazevVystupu[20];

    printf("NazevVstupu: ");
    if(scanf("%s", nazevVstupu) != 1)
        return -1;

    printf("NazevVstupu2: ");
    if(scanf("%s", nazevVstupu2) != 1)
        return -1;

    printf("NazevVystupu: ");
    if(scanf("%s", nazevVystupu) != 1)
        return -1;

    FILE* vstup = fopen(nazevVstupu, "r");
    FILE* vstup2 = fopen(nazevVstupu2, "r");
    FILE* vystup = fopen(nazevVystupu, "w");
    if(vstup == NULL || vstup2 == NULL || vystup == NULL)
        return -1;

    PoNticich(vstup, vstup2, vystup, 4);

    fclose(vstup);
    fclose(vstup2);
    fclose(vystup);
    return 0;
}
