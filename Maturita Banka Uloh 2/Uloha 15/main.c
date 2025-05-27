#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define MAX 100

typedef struct
{
    float prvek[MAX][MAX];
    int radku;
    int sloupcu;
} TMatice;

bool NactiMatici(TMatice* mat)
{
    if(scanf("%d%d", &mat->radku, &mat->sloupcu) != 2)
        return false;

    for(int r = 0; r < mat->radku; r++)
    {
        for(int s = 0; s < mat->sloupcu; s++)
        {
            if(scanf("%f", &mat->prvek[r][s]) != 1)
                return false;
        }
    }

    return true;
}

bool MuzeBytSoustavou(TMatice* mat)
{
    return mat->radku + 1 == mat->sloupcu;
}

void UpravMatici(TMatice* mat)
{
    for(int r = 0; r < mat->radku; r++)
    {
        float pom = mat->prvek[r][r];

        for(int s = 0; s < mat->sloupcu; s++)
        {
            mat->prvek[r][s] /= pom;
        }

        mat->prvek[r][r] = 0;
    }
}

bool JeDDM(TMatice* mat)
{
    for(int r = 0; r < mat->radku; r++)
    {
        float suma = 0;

        for(int s = 0; s < mat->sloupcu - 1; s++)
        {
            suma += fabs(mat->prvek[r][s]);
        }

        if(suma >= 1)
            return false;
    }

    return true;
}

void VypisMatici(TMatice* mat)
{
    for(int r = 0; r < mat->radku; r++)
    {
        for(int s = 0; s < mat->sloupcu; s++)
        {
            printf("%f, ", mat->prvek[r][s]);
        }

        printf("\n");
    }
    printf("\n");
}

void Jacobi(TMatice* mat, float x[], float eps)
{
    bool jepresny = false;

    float xpred[mat->radku];

    for(int i = 0; i < mat->radku; i++)
    {
        x[i] = 0;
    }

    while(!jepresny)
    {
        jepresny = true;

        for(int r = 0; r < mat->radku; r++)
        {
            float suma = 0;
            xpred[r] = x[r];

            for(int s = 0; s < mat->sloupcu - 1; s++)
            {
                suma += mat->prvek[r][s] * xpred[s];
            }

            x[r] = mat->prvek[r][mat->sloupcu - 1] - suma;
            jepresny = jepresny && (fabs(x[r] - xpred[r]) < eps);

        }
    }

}

void GaussSeidl(TMatice* mat, float x[], float eps)
{
    bool jePresny = false;

    while(!jePresny)
    {
        jePresny = true;

        for(int r = 0; r < mat->radku; r++)
        {
            float xpred = x[r];
            float suma = 0;

            for(int s = 0; s < mat->sloupcu - 1; s++)
            {
                suma += mat->prvek[r][s] * x[s];
            }

            x[r] = mat->prvek[r][mat->sloupcu - 1] - suma;
            jePresny = jePresny && (fabs(x[r] - xpred) <= eps);
        }
    }
}

int main()
{
    TMatice mat;

    NactiMatici(&mat);

    UpravMatici(&mat);

    VypisMatici(&mat);

    float x[mat.radku];

    GaussSeidl(&mat, x, 0.001);

    for(int i = 0; i < mat.radku; i++)
    {
        printf("%f\n", x[i]);
    }

    return 0;
}
