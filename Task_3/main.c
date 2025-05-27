#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define N 20

bool jeCislice(char znak)
{
    return znak >= '0' && znak <= '9';
}

int pocetCislic(char retezec[])
{
    int pocet = 0;

    for(int i = 0; retezec[i] != '\0'; i++)
    {
        if(jeCislice(retezec[i]))
            pocet++;
    }

    return pocet;
}

void indexyPrvniAPosledni(char retezec[], int* prvni, int* posledni)
{
    *prvni = -1;
    *posledni = -1;

    for(int i = 0; retezec[i] != '\0'; i++)
    {
        if(jeCislice(retezec[i]))
        {
            *posledni = i;
            if(*prvni == -1)
                *prvni = i;
        }
    }
}

void nahradZnakemHash(char retezec[])
{
    for(int i = 0; retezec[i] != '\0'; i++)
    {
        if(jeCislice(retezec[i]))
            retezec[i] = '#';
    }
}

int pocetSlovVRetezci(char retezec[])
{
    bool veSlove = false;
    int pocetSlov = 0;

    for(int i = 0; retezec[i] != '\0'; i++)
    {
        if(isspace(retezec[i]))
        {
            veSlove = false;
        }
        else
        {
            if(!veSlove)
            {
                veSlove = true;
                pocetSlov++;
            }
        }
    }

    return pocetSlov;
}

bool jeMale(char znak)
{
    return znak >= 'a' && znak <= 'z';
}

bool jeVelke(char znak)
{
    return znak >= 'A' && znak <= 'Z';
}

void malaZaVelkaANaopak(char retezec[])
{
    int rozdil = 'A' - 'a';
    for(int i = 0; retezec[i] != '\0'; i++)
    {
        if(jeMale(retezec[i]))
        {
            retezec[i] += rozdil;
        }
        else if(jeVelke(retezec[i]))
        {
            retezec[i] -= rozdil;
        }
    }
}

void reverzeStringu(char retezec[])
{
    int delka = strlen(retezec);
    for(int i = 0; i < delka / 2; i++)
    {
        char pom = retezec[i];
        retezec[i] = retezec[delka - i - 1];
        retezec[delka - i - 1] = pom;
    }
}

void stringRekurze(char retezec[], int l, int p)
{
    if(l >= p)
        return;

    char pom = retezec[l];
    retezec[l] = retezec[p];
    retezec[p] = pom;

    stringRekurze(retezec, l + 1, p - 1);
}

void reverzeStringRek(char retezec[])
{
    stringRekurze(retezec, 0, strlen(retezec) - 1);
}

int main()
{
    char retezec[N];

    if(scanf("%[^\n]19s", retezec) != 1)
        return -1;

    reverzeStringRek(retezec);

    printf("%s", retezec);

    return 0;
}
