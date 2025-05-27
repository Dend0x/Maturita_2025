#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

typedef enum
{
    SPRAVNE,
    SPATNE
} ESpravnost;

bool jeVAbecede(char sigma[], char znak)
{
    for(int i = 0; i < strlen(sigma); i++)
    {
        if(sigma[i] == znak)
            return true;
    }

    return false;
}

int jeVetouJazyka(char sigma[], char retezec[], bool jePlus)
{
    int i = 0;

    while(retezec[i] != '\0')
    {
        if(!jeVAbecede(sigma, retezec[i]))
            return i + 1;
        i++;
    }

    if(retezec[0] == '\0')
    {
        return (int)jePlus;
    }

    return 0;
}

void nactiAbecedu(char sigma[], char konec)
{
    char c;
    int i = 0;

    while((c = getc(stdin)) != konec)
    {
        sigma[i] = c;
        i++;
        fflush(stdin);
    }

    sigma[i] = '\0';
}



bool zavorkyJedny(char retezec[])
{
    int pocitadlo = 0;
    int i = 0;

    while(retezec[i] != '\0')
    {
        if(retezec[i] == '[')
            pocitadlo++;
        else if(retezec[i] == ']')
            pocitadlo--;

        if(pocitadlo < 0)
            return false;

        i++;
    }

    return pocitadlo == 0;
}

bool jeOteviraci(char znak)
{
    return znak == '(' || znak == '[' || znak == '{';
}

bool jeZaviraci(char znak)
{
    return znak == ')' || znak == ']' || znak == '}';
}

bool odpovidajiSi(char oteviraci, char zaviraci)
{
    switch(oteviraci)
    {
        case '(':
            return zaviraci == ')';
        case '[':
            return zaviraci == ']';
        case '{':
            return zaviraci == '}';
    }

    return false;
}

bool zavorkyVice(char retezec[])
{
    int i = 0;
    char zasobnik[MAX];
    int hlava = 0;

    while(retezec[i] != '\0')
    {
        if(jeOteviraci(retezec[i]))
        {
            zasobnik[hlava] = retezec[i];
            hlava++;
        }
        else if(jeZaviraci(retezec[i]))
        {
            if(!odpovidajiSi(zasobnik[hlava - 1], retezec[i]))
                return false;
            hlava--;
        }

        i++;
    }

    return true;
}

int main()
{

    return 0;
}
