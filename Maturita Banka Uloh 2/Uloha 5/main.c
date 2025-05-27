#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 30

int NaHodnotu(char znak)
{
    if(znak >= '0' &&znak <= '9')
        return znak - '0';
    if(znak >= 'A' && znak <= 'Z')
        return znak - 'A' + 10;

    return -1;
}

int DoDesitkove(char retezec[], int soustava)
{
    int suma = 0;

    for(int i = 0; retezec[i] != '\0'; i++)
    {
        int hodnota;

        if((hodnota = NaHodnotu(retezec[i])) == -1)
            return -1;

        suma = suma * soustava + hodnota;
    }

    return suma;
}

char NaZnak(int hodnota, int soustava)
{
    if(hodnota >= 0 && hodnota <= 9)
        return hodnota + '0';
    if(hodnota >= 10 && hodnota < soustava)
        return hodnota + 'A' - 10;

    return -1;
}

int doJineSoustavy(int cislo, int soustava, char vysledek[])
{
    if(soustava < 2 || soustava > 32)
        return -1;

    int i = 0;

    while(cislo > 0)
    {
        char znak = NaZnak(cislo % soustava, soustava);

        if(znak == -1)
            return -1;

        vysledek[i] = znak;
        cislo /= soustava;
        i++;
    }
    vysledek[i] = '\0';

    int delka = strlen(vysledek);

    for(int i = 0; i < delka / 2; i++)
    {
        char pom = vysledek[i];
        vysledek[i] = vysledek[delka - i - 1];
        vysledek[delka - i - 1] = pom;
    }

    printf("%s\n", vysledek);

    return 0;
}

int NacitejSestnackove(FILE* vstup)
{
    char retezec[30];
    while(fscanf(vstup, "%29s", retezec) == 1)
    {
        int hodnota;
        if((hodnota = DoDesitkove(retezec, 16)) == -1)
            return -1;
        //printf("%d\n", hodnota);

        char vysledek[N];

        if(doJineSoustavy(hodnota, 16, vysledek) == -1)
            return -1;
    }

    return 0;
}

float prevedDoNormalniho()
{
    int a, b;
    if(scanf("%dE%d", &a, &b) != 2)
        return 0.0/0.0;

    float zaklad = a;
    float posun;

    if(b == 0)
        return zaklad;
    if(b > 0)
        posun = 10;
    else
        posun = 0.1;

    for(int i = 0; i < fabs(b); i++)
    {
        zaklad *= posun;
    }

    return zaklad;

}

int main()
{
    FILE* vstup = fopen("a.txt", "r");
    if(vstup == NULL)
        return -1;

    float a = prevedDoNormalniho();

    printf("%f", a);

    fclose(vstup);
    return 0;
}
