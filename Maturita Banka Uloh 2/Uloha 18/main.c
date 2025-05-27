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

float KonstRegrese(float y[], int n)
{
    float sumy = 0;

    for(int i = 0; i < n; i++)
    {
        sumy += y[i];
    }

    printf("%f", sumy);

    return sumy / n;
}

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

    GaussZpetny(mat);
}

void LinearRegrese(float x[], float y[], int n, float* a, float* b)
{
    float sumx = 0;
    float sumy = 0;
    float sumxy = 0;
    float sumx2 = 0;

    for(int i = 0; i < n; i++)
    {
        sumx += x[i];
        sumy += y[i];
        sumxy += x[i] * y[i];
        sumx2 += x[i] * x[i];
    }

    TMatice mat = {.radku=2, .sloupcu=3, .prvek={{sumx2, sumx, sumxy}, {sumx, n, sumy}}};

    GaussCely(&mat);

    *a = mat.prvek[0][2];
    *b = mat.prvek[1][2];
}

float naDruhou(float x)
{
    return x * x;
}

float SoucetCtvercu(float x[], float y[], float a, float b, int n)
{
    float soucet = 0;

    for(int i = 0; i < n; i++)
    {
        soucet += naDruhou((a*x[i] + b) - y[i]);
    }

    return soucet;
}

void NactiMatici(TMatice* mat)
{
    if(scanf("%d%d", &mat->radku, &mat->sloupcu) != 2)
        return;

    for(int r = 0; r < mat->radku; r++)
    {
        for(int s = 0; s < mat->sloupcu; s++)
        {
            if(scanf("%f", &mat->prvek[r][s]) != 1)
                return;
        }
    }
}

bool jeVerti(TMatice* mat)
{
    for(int r = 0; r < mat->radku; r++)
    {
        for(int s = 0; s < mat->sloupcu / 2; s++)
        {
            if(mat->prvek[r][s] != mat->prvek[r][mat->sloupcu - s - 1])
                return false;
        }
    }

    return true;
}

bool jeHori(TMatice* mat)
{
    for(int r = 0; r < mat->radku / 2; r++)
    {
        for(int s = 0; s < mat->sloupcu; s++)
        {
            if(mat->prvek[r][s] != mat->prvek[mat->radku - r - 1][s])
                return false;
        }
    }

    return true;
}

bool jeHlavni(TMatice* mat)
{
    for(int r = 0; r < mat->radku; r++)
    {
        for(int s = 0; s < r; s++)
        {
            if(mat->prvek[r][s] != mat->prvek[s][r])
                return false;
        }
    }

    return true;
}

bool jeVedlejsi(TMatice* mat)
{
    for(int r = mat->radku - 1; r >= 0; r--)
    {
        for(int s = mat->sloupcu - 1; s < r; s--)
        {
            printf("%f : %f\n", mat->prvek[r][s], mat->prvek[s][r]);
            if(mat->prvek[r][s] != mat->prvek[s][r])
                return false;
        }
    }

    return true;
}

int main()
{
    TMatice mat;
    NactiMatici(&mat);

    printf("%s", jeVedlejsi(&mat) ? "ano" : "ne");

    return 0;
}
