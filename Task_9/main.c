#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

typedef enum
{
    S,
    A,
    B,
    K
} EStav;

bool jeVPoli(char pole[], char znak)
{
    for(int i = 0; i < strlen(pole); i++)
    {
        if(znak == pole[i])
            return true;
    }

    return false;
}

bool jeTypu2(char retezec[], char sigma[], char N[])
{
    char l;

    if(sscanf(retezec, "%c->", &l) != 1)
        return false;

    if(!jeVPoli(N, l))
    {
        return false;
    }

    if(strlen(retezec) < 4)
        return false;

    for(int i = 3; retezec[i] != '\0'; i++)
    {
        if(!jeVPoli(N, retezec[i]) && !jeVPoli(sigma, retezec[i]))
            return false;
    }

    return true;
}

bool jeTypu3(char retezec[], char sigma[], char N[])
{
    char l;

    if(sscanf(retezec, "%c->", &l) != 1)
        return false;

    if(!jeVPoli(N, l))
        return false;

    if(strlen(retezec) < 4)
        return false;

    if(jeVPoli(N, retezec[3]))
    {
        if(retezec[4] == '\0')
            return true;

        if(jeVPoli(sigma, retezec[4]))
        {
            if(retezec[5] == '\0')
                return true;
            return false;
        }

        return false;
    }

    if(jeVPoli(sigma, retezec[3]))
    {
        if(retezec[4] == '\0')
            return true;

        if(jeVPoli(N, retezec[4]))
        {
            if(retezec[5] == '\0')
                return true;
            return false;
        }

        return false;
    }

    return false;
}

void generujNVet(int n)
{
    for(int i = 0; i < n; i++)
    {
        char veta[MAX];
        EStav stav = S;
        int n = 0;

        int k = 0;
        while(stav != K)
        {
            switch(stav)
            {
                case S:
                    stav = A;
                    veta[n] = 'a';
                    break;
                case A:
                    stav = B;
                    veta[n] = 'b';
                    break;
                case B:
                    veta[n] = 'c';
                    if(k < i)
                    {

                        stav = A;
                        k++;
                        break;
                    }
                    stav = K;
                    break;
            }

            n++;
        }

        veta[n] = '\0';

        printf("%s\n", veta);
    }
}

int main()
{
    generujNVet(10);

    return 0;
}
