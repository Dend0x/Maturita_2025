#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool jeSpravne(char znak)
{
    return znak >= '0' && znak <= '1';
}

void oprav(char retezec[], char vysledek[])
{
    int j = 0;
    for(int i = 0; retezec[i] != '\0'; i++)
    {
        if(jeSpravne(retezec[i]))
        {
            vysledek[j] = retezec[i];
            j++;
        }
    }

    vysledek[j] = '\0';
}

int naCislo(char znak)
{
    if(znak >= '0' && znak <= '9')
        return znak - '0';
    if(znak >= 'A' && znak <= 'Z')
        return znak - 'A' + 10;

    return -1;
}

int vycisli(char retezec[], int soustava)
{
    int suma = 0;

    for(int i = 0; retezec[i] != '\0'; i++)
    {
        suma = suma * soustava + naCislo(retezec[i]);
    }

    return suma;
}

int jakySystem(char retezec[])
{
    int hodnota = vycisli(retezec, 16);
    int pocitadlo = 0;

    while(hodnota > 0)
    {
        hodnota >>= 1;
        pocitadlo++;
    }

    if(pocitadlo <= 8)
        return 8;
    if(pocitadlo <= 16)
        return 16;
    if(pocitadlo <= 32)
        return 32;
    if(pocitadlo <= 64)
        return 64;

    return 0;
}

int main()
{
    char retezec[12] = "FF562F";
    retezec[6] = '\0';

    printf("%d", jakySystem(retezec));

    return 0;
}
