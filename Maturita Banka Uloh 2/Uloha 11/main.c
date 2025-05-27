#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _prvek TPrvek;

struct _prvek
{
    char znak;
    TPrvek* dalsi;
};

typedef struct
{
    TPrvek* vrchol;
} TZasobnik;

typedef struct _fprvek TFPrvek;

struct _fprvek
{
    char znak;
    TFPrvek* dalsi;
};

typedef struct
{
    TFPrvek* prvni;
    TFPrvek* posledni;
} TFronta;

TZasobnik* zasInit()
{
    TZasobnik* zas = malloc(sizeof(TZasobnik));
    if(zas == NULL)
        return NULL;

    zas->vrchol = NULL;

    return zas;
}

TPrvek* novyPrvek(char c)
{
    TPrvek* prvek = malloc(sizeof(TPrvek));
    if(prvek == NULL)
        return NULL;

    prvek->dalsi = NULL;
    prvek->znak = c;

    return prvek;
}

void zasPush(TZasobnik* zas, char c)
{
    TPrvek* prvek = novyPrvek(c);
    if(prvek == NULL)
        return;

    if(zas->vrchol == NULL)
    {
        zas->vrchol = prvek;
        return;
    }

    prvek->dalsi = zas->vrchol;
    zas->vrchol = prvek;
    return;
}

void zasPop(TZasobnik* zas, char* c)
{
    if(zas->vrchol == NULL)
        return;

    TPrvek* pom = zas->vrchol;
    zas->vrchol = pom->dalsi;
    *c = pom->znak;
    free(pom);
}

void zasVypis(TZasobnik* zas)
{
    TPrvek* pom = zas->vrchol;
    while(pom != NULL)
    {
        printf("%c, ", pom->znak);
        pom = pom->dalsi;
    }
}

bool jeOteviraci(char znak)
{
    return znak == '(' || znak == '[' || znak == '{';
}

bool jeZaviraci(char znak)
{
    return znak == ')' || znak == ']' || znak == '}';
}

bool jsouOdpovidajici(char oteviraci, char zaviraci)
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

bool jsouSpravneZavorky(TZasobnik* zas, char retezec[])
{
    char c;
    for(int i = 0; retezec[i] != '\0'; i++)
    {
        if(jeOteviraci(retezec[i]))
            zasPush(zas, retezec[i]);
        else if (jeZaviraci(retezec[i]))
        {
            zasPop(zas, &c);
            if(!jsouOdpovidajici(c, retezec[i]))
                return false;
        }
    }

    if(zas->vrchol == NULL)
        return true;
    return false;
}

void zasFree(TZasobnik* zas)
{
    char c;
    while(zas->vrchol != NULL)
    {
        zasPop(zas, &c);
    }

    free(zas);
}

TFronta* froInit()
{
    TFronta* fronta = malloc(sizeof(TFronta));
    if(fronta == NULL)
        return NULL;

    fronta->prvni = NULL;
    fronta->posledni = NULL;

    return fronta;
}

TFPrvek* novyPrvekFro(char znak)
{
    TFPrvek* prvek = malloc(sizeof(TFPrvek));
    if(prvek == NULL)
        return NULL;

    prvek->dalsi = NULL;
    prvek->znak = znak;

    return prvek;
}

void Enqueue(TFronta* fronta, char c)
{
    TFPrvek* prvek = novyPrvekFro(c);
    if(prvek == NULL)
        return;

    if(fronta->prvni == NULL)
    {
        fronta->prvni = prvek;
        fronta->posledni = prvek;
        return;
    }

    fronta->posledni->dalsi = prvek;
    fronta->posledni = prvek;
}

void Dequeue(TFronta* fronta, char* c)
{
    if(fronta->prvni == NULL)
        return;

    TFPrvek* pom = fronta->prvni;

    if(fronta->prvni == fronta->posledni)
    {
        *c = pom->znak;
        fronta->prvni = NULL;
        fronta->posledni = NULL;
        free(pom);
        return;
    }

    fronta->prvni = fronta->prvni->dalsi;
    *c = pom->znak;
    free(pom);
}

void froFree(TFronta* fronta)
{
    char c;

    while(fronta->prvni != NULL)
        Dequeue(fronta, &c);

    free(fronta);
}

void froVypis(TFronta* fronta)
{
    TFPrvek* pom = fronta->prvni;

    while(pom != NULL)
    {
        printf("%c", pom->znak);
        pom = pom->dalsi;
    }

}

void vypisNPoslednich(TFronta* fronta, int n)
{
    char c;
    int i = 0;

    while((c = getc(stdin)) && c != '0')
    {
        fflush(stdin);

        if(i > (n - 1))
        {
            char znak;
            Dequeue(fronta, &znak);
        }

        Enqueue(fronta, c);

        i++;
    }

    froVypis(fronta);
}

int main()
{
    TFronta* fronta = froInit();
    if(fronta == NULL)
        return -1;

    vypisNPoslednich(fronta, 5);

    froFree(fronta);
    return 0;
}
