#include <stdio.h>
#include <stdlib.h>

int neserbezzar(int pole[], int n, int klic)
{
    int i = 0;

    while(i < n && pole[i] != klic)
        i++;

    if(i < n)
        return i;
    return -1;
}

int nesersezar(int pole[], int n, int klic)
{
    int i = 0;
    pole[n] = klic;

    while(pole[i] != klic)
        i++;

    if(i < n)
        return i;
    return -1;
}

int serbezzar(int pole[], int n, int klic)
{
    int i = 0;

    while(i < n && pole[i] < klic)
        i++;

    if(pole[i] == klic)
        return i;
    return -1;
}

int sersezar(int pole[], int n, int klic)
{
    int i = 0;
    pole[n] = klic;

    while(pole[i] < klic)
        i++;

    if(i < n && pole[i] == klic)
        return i;

    return -1;
}

int binar(int pole[], int n, int klic)
{
    int l = 0;
    int p = n;

    while(l < p)
    {
        int stred = (l + p) / 2;

        if(pole[stred] == klic)
            return stred;
        if(klic < pole[stred])
            p = stred - 1;
        else
            l = stred + 1;
    }

    return -1;
}

int main()
{
    int pole[25] = {0, 1, 2, 5, 6, 8, 9, 12, 26, 27, 36, 45, 48, 59, 65};
    int n = 15;

    printf("%d", binar(pole, n, 65));

    return 0;
}
