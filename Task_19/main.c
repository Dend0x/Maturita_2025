#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void SelectionSort(int pole[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for(int d = i + 1; d < n; d++)
        {
            if(pole[d] < pole[minIndex])
                minIndex = d;
        }

        int pom = pole[i];
        pole[i] = pole[minIndex];
        pole[minIndex] = pom;
    }
}

void InsertSort(int pole[], int n)
{
    for(int d = 1; d < n; d++)
    {
        int i = d;
        int vkladany = pole[d];

        while(i > 0 && pole[i - 1] > vkladany)
        {
            pole[i] = pole[i - 1];
            i--;
        }

        pole[i] = vkladany;
    }
}

void InsertSortZar(int pole[], int n)
{

    for(int d = n - 2; d >= 0; d--)
    {
        int i = d;
        pole[n] = pole[d];

        while(pole[i + 1] < pole[n])
        {
            pole[i] = pole[i + 1];
            i++;
        }

        pole[i] = pole[n];
    }
}

void BubbleSort(int pole[], int n)
{
    for(int d = 0; d < n - 1; d++)
    {
        for(int i = 1; i < n - d; i++)
        {
            if(pole[i] < pole[i - 1])
            {
                int pom = pole[i];
                pole[i] = pole[i - 1];
                pole[i - 1] = pom;
            }
        }
    }
}

void RippleSort(int pole[], int n)
{
    int posVymena = n - 1;

    while(posVymena > 0)
    {
        int novPosledni = 0;

        for(int i = 0; i < posVymena; i++)
        {
            if(pole[i] > pole[i + 1])
            {
                int pom = pole[i];
                pole[i] = pole[i + 1];
                pole[i + 1] = pom;
                novPosledni = i;
            }
        }

        posVymena = novPosledni;
    }
}

void vypisPole(int pole[], int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d, ", pole[i]);
    }
}

void rozdel(int pole[], int od, int po, int pivot, int* levy, int* pravy)
{
    *levy = od;
    *pravy = po;

    do
    {
        while(pole[*levy] < pivot && *levy < po) ++(*levy);
        while(pole[*pravy] > pivot && *pravy > od) --(*pravy);

        if(*levy < *pravy)
        {
            int pom = pole[*levy];
            pole[*levy] = pole[*pravy];
            pole[*pravy] = pom;
        }

        if(*levy <= *pravy)
        {
            ++(*levy);
            --(*pravy);
        }

    } while(*levy < *pravy);
}

void QuickSortRek(int pole[], int od, int po)
{
    if(od >= po)
        return;

    int pivot = pole[(od + po) / 2];
    int levy, pravy;

    rozdel(pole, od, po, pivot, &levy, &pravy);

    QuickSortRek(pole, od, pravy);
    QuickSortRek(pole, levy, po);
}

void QuickSort(int pole[], int n)
{
    QuickSortRek(pole, 0, n - 1);
}

void slevani(int pole[], int pompole[], int od, int po)
{
    int levy = od;
    int pom = od;
    int stred = (od + po) / 2;
    int pravy = stred + 1;

    while(levy <= stred && pravy <= po)
    {
        if(pole[levy] <= pole[pravy])
            pompole[pom++] = pole[levy++];
        else
            pompole[pom++] = pole[pravy++];
    }
    while(levy <= stred) pompole[pom++] = pole[levy++];
    while(pravy <= po) pompole[pom++] = pole[pravy++];
}

void MergeSortRek(int pole[], int pomPole[], int od, int po)
{
    if(od >= po)
        return;

    int stred = (od + po) / 2;
    MergeSortRek(pole, pomPole, od, stred);
    MergeSortRek(pole, pomPole, stred + 1, po);
    slevani(pole, pomPole, od, po);

    for(int i = od; i < po + 1; i++)
    {
        pole[i] = pomPole[i];
    }
}

void MergeSort(int pole[], int n)
{
    int pompole[n];

    MergeSortRek(pole, pompole, 0, n - 1);
}

int main()
{
    int pole[MAX] = {5, 3, 2, 9, 1, 6, 2, 0, 8};
    int n = 9;

    MergeSort(pole, n);

    vypisPole(pole, n);

    return 0;
}
