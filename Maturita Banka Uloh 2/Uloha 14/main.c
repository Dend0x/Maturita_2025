#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define MAX 100

typedef struct
{
    float prvek[MAX][MAX];
    int radku;
    int sloupcu;
} TMatice;

int pivotovani(TMatice* mat, int r)
{
    int pivot = r;
    for(int k = r + 1; k < mat->radku; k++)
    {
        if(fabs(mat->prvek[pivot][r]) < fabs(mat->prvek[k][r]))
            pivot = k;
    }
    return pivot;
}

void prohod(TMatice* mat, int pivot, int r)
{
    for(int s = 0; s < mat->sloupcu; s++)
    {
        float pom = mat->prvek[pivot][s];
        mat->prvek[pivot][s] = mat->prvek[r][s];
        mat->prvek[r][s] = pom;
    }
}

void radkoveUpravy(TMatice* mat, int r)
{
    for(int rr = r + 1; rr < mat->radku; rr++)
    {
        float koef = mat->prvek[rr][r] / mat->prvek[r][r];

        mat->prvek[rr][r] = 0.0;

        for(int s = r + 1; s < mat->sloupcu; s++)
        {
            mat->prvek[rr][s] = mat->prvek[r][s] * koef - mat->prvek[rr][s];
        }
    }
}

void GaussPrimy(TMatice* mat)
{
    for(int r = 0; r < mat->radku - 1; r++)
    {
        int pivot = pivotovani(mat, r);

        if(pivot != r)
            prohod(mat, r, pivot);

        radkoveUpravy(mat, r);
    }
}

void vypisMatici(TMatice* mat)
{
    for(int r = 0; r < mat->radku; r++)
    {
        for(int s = 0; s < mat->sloupcu; s++)
        {
            printf("%f, ", mat->prvek[r][s]);
        }

        printf("\n");
    }
}

int pocetReseni(TMatice* mat)
{
    for(int r = 0; r < mat->radku; r++)
    {
        if(mat->prvek[r][r] == 0)
        {
            if(mat->prvek[r][mat->sloupcu] == 0)
                return 2;
            else
                return 1;
        }
    }

    return 0;
}

bool jeHorniTrojuhelnikova(TMatice* mat)
{
    for(int r = 0; r < mat->radku; r++)
    {
        for(int s = 0; s < r; s++)
        {
            if(mat->prvek[r][s] != 0)
                return false;
        }
    }

    return true;
}

void GaussZpetny(TMatice* mat)
{
    for(int r = mat->radku - 1; r >= 0; r--)
    {
        float suma = 0;

        for(int s = r + 1; s < mat->sloupcu - 1; s++)
        {
            suma += mat->prvek[r][s] * mat->prvek[s][mat->sloupcu - 1];
        }

        mat->prvek[r][mat->sloupcu - 1] = (mat->prvek[r][mat->sloupcu - 1] - suma) / mat->prvek[r][r];
    }
}

void GaussCely(TMatice* mat)
{
    GaussPrimy(mat);

    int pocet = pocetReseni(mat);
    switch(pocet)
    {
    case 0:
        printf("jedno\n");
        break;
    case 1:
        printf("Zadne\n");
        break;
    case 2:
        printf("Nekonecne\n");
    }


    printf("Je HorTroj %s", jeHorniTrojuhelnikova(mat) ? "ano" : "ne");

    GaussZpetny(mat);

    vypisMatici(mat);
}

void radkoveUpravyNahoru(TMatice* mat, int r)
{
    for(int rr = r - 1; rr >= 0; rr--)
    {
        float koef = mat->prvek[rr][r] / mat->prvek[r][r];

        mat->prvek[rr][r] = 0.0;

        for(int s = r + 1; s < mat->sloupcu; s++)
        {
            mat->prvek[rr][s] = mat->prvek[rr][s] - mat->prvek[r][s] * koef;
        }
    }
}

void GaussJorPrimy(TMatice* mat)
{
    for(int r = 0; r < mat->radku; r++)
    {
        int pivot = pivotovani(mat, r);

        if(pivot != r)
            prohod(mat, r, pivot);

        radkoveUpravy(mat, r);
        radkoveUpravyNahoru(mat, r);
    }
}

bool jeDiagonalni(TMatice* mat)
{
    for(int r = 0; r < mat->radku; r++)
    {
        for(int s = 0; s < mat->sloupcu - 1; s++)
        {
            if(r != s)
            {
                if(mat->prvek[r][s] != 0)
                    return false;
            }
        }
    }

    return true;
}

void GaussJorZpetny(TMatice* mat)
{
    for(int r = 0; r < mat->radku; r++)
    {
        mat->prvek[r][mat->sloupcu - 1] /= mat->prvek[r][r];
    }
}

void GaussJorCely(TMatice* mat)
{
    GaussJorPrimy(mat);
    vypisMatici(mat);

    int pocet = pocetReseni(mat);
    switch(pocet)
    {
    case 0:
        printf("jedno\n");
        break;
    case 1:
        printf("Zadne\n");
        break;
    case 2:
        printf("Nekonecne\n");
    }

    printf("%s", jeDiagonalni(mat) ? "ano" : "ne");

    GaussJorZpetny(mat);

    vypisMatici(mat);
}

int main()
{
    TMatice mat = {.radku=3, .sloupcu=4, .prvek={{4, 5, 2, 4}, {6, 2, -9, 6}, {3, 8, 6, -2}}};

    GaussJorCely(&mat);

    return 0;
}
