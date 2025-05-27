#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

typedef struct
{
    float koef[MAX];
    int rad;
} TPoly;

float horner(TPoly* pol, float x)
{
    float suma = 0;

    for(int i = 0; i < pol->rad + 1; i++)
    {
        suma = suma * x + pol->koef[i];
    }

    return suma;
}

float bisekce(TPoly* pol, float a, float b, float eps)
{
    float fa = horner(pol, a);
    float c = (a + b) / 2;
    float fc;

    while(fabs(fc = horner(pol, c)) > eps)
    {
        if(fa * fc < 0)
        {
            b = c;
        }
        else
        {
            a = c;
            fa = fc;
        }

        c = (a + b) / 2;
    }

    return c;
}

float regulaFalsi(TPoly* pol, float a, float b, float eps)
{
    float fa = horner(pol, a);
    float fb = horner(pol, b);
    float fc;
    float c = (fa * b - fb * a) / (fa - fb);

    while(fabs(fc = horner(pol, c)) > eps)
    {
        if(fa * fc < 0)
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }

        c = (fa * b - fb * a) / (fa - fb);
    }

    return c;
}

float secny(TPoly* pol, float a, float b, float eps)
{
    float fa = horner(pol, a);
    float fb = horner(pol, b);
    float fc;
    float c = (fa * b - fb * a) / (fa - fb);

    while(fabs(fc = horner(pol, c)) > eps)
    {
        a = b;
        fa = fb;
        b = c;
        fb = fc;

        c = (fa * b - fb * a) / (fa - fb);
    }

    return c;
}

float Newton(TPoly* pol, TPoly* dpol, float x, float eps)
{
    while(fabs(horner(pol, x)) > eps)
        x = x - horner(pol, x) / horner(dpol, x);

    return x;
}

int main()
{
    TPoly pol = {.rad=3, .koef={5, 3, 6, 8}};
    TPoly dpol = {.rad=2, .koef={15, 6, 6}};

    printf("%f", Newton(&pol, &dpol, 2, 0.001));
    return 0;
}
