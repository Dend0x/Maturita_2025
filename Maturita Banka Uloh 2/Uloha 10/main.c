#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prevestNaCislo(char znak)
{
    return znak - '0';
}

char prevestNaZnak(int cislo)
{
    return cislo + '0';
}

void soucin(char binar[], char binar2[], char vysledek[])
{
    int i;
    for(i = 0; binar[i] != '\0'; i++)
    {
        vysledek[i] = prevestNaZnak(prevestNaCislo(binar[i]) & prevestNaCislo(binar2[i]));
    }

    vysledek[i] = '\0';
}

void soucet(char binar[], char binar2[], char vysledek[])
{
    int i;
    for(i = 0; binar[i] != '\0'; i++)
    {
        vysledek[i] = prevestNaZnak(prevestNaCislo(binar[i]) | prevestNaCislo(binar2[i]));
    }

    vysledek[i] = '\0';
}

void xor(char binar[], char binar2[], char vysledek[])
{
    int i;
    for(i = 0; binar[i] != '\0'; i++)
    {
        vysledek[i] = prevestNaZnak(prevestNaCislo(binar[i]) ^ prevestNaCislo(binar2[i]));
    }

    vysledek[i] = '\0';
}

void bitovyPosun(char binar[], char vysledek[], int n)
{
    strcpy(vysledek, "0000000000000000");

    int i;

    for(i = 0; binar[i] != '\0'; i++)
    {
        int posun = i + n;

        if(posun <= 15 && posun >= 0)
            vysledek[posun] = binar[i];
    }

    vysledek[i] = '\0';
}

void bitovaRotace(char binar[], char vysledek[], int n)
{
    strcpy(vysledek, "0000000000000000");

    int i;

    for(i = 0; binar[i] != '\0'; i++)
    {
        int posun = i + n;

        if(posun < 0)
            posun += 16;

        vysledek[posun % 16] = binar[i];
    }

    vysledek[i] = '\0';
}

void aritmetickySoucet(char binar[], char binar2[], char vysledek[])
{
    int zbytek = 0;

    for(int i = 15; i >= 0; i--)
    {
        int hodnota = prevestNaCislo(binar[i]) + prevestNaCislo(binar2[i]) + zbytek;

        switch(hodnota)
        {
            case 0:
                vysledek[i] = '0';
                zbytek = 0;
                break;
            case 1:
                vysledek[i] = '1';
                zbytek = 0;
                break;
            case 2:
                vysledek[i] = '0';
                zbytek = 1;
                break;
            case 3:
                vysledek[i] = '1';
                zbytek = 1;
                break;
        }
    }

    vysledek[16] = '\0';
}

int main()
{
    char binar[17] = "0011100100001101";
    char binar2[17] = "0011010101110101";
    char vysledek[17];
    binar[16] = '\0';
    binar2[16] = '\0';

    aritmetickySoucet(binar, binar2, vysledek);

    for(int i = 0; vysledek[i] != '\0'; i++)
        printf("%c", vysledek[i]);

    return 0;
}
