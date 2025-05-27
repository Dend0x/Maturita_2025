/*
    Task 1 - Load a MxN matrix into an 2D array from stdin/File
    Task 2 - Print 2D array on stdout/File
    Task 3 - Print the number of even numbers in a column to the very last row of that column
    Task 4 - Return the sum of the numbers on the edges and all except from the edges
    Task 5 - Print a 2x2 Matrix with sums of quarters of the loaded Matrix
    Task 6 - Is the Matrix vertically or horizontally symmetrical?
    Task 7 - Create a transposed Matrix
    Task 8 - Rotate the Matrix by n (n is number of times rotated by 90 degrees)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100

typedef struct
{
    int cell[MAX][MAX];
    int rows;
    int columns;
} TMatrix;

// Task 1

bool loadMatrix(FILE* in, TMatrix* mat)
{
    if(fscanf(in, "%d %d", &mat->rows, &mat->columns) != 2)
    {
        return false;
    }

    for(int r = 0; r < mat->rows; r++)
    {
        for(int c = 0; c < mat->columns; c++)
        {
            if(fscanf(in, "%d", &mat->cell[r][c]) != 1)
                return false;
        }
    }

    return true;
}

// Task 2

void printMatrix(FILE* out, TMatrix* mat)
{
    for(int r = 0; r < mat->rows; r++)
    {
        for(int c = 0; c < mat->columns; c++)
        {
            fprintf(out, "%d ", mat->cell[r][c]);
        }
        fprintf(out, "\n");
    }
}

// Task 3

void numberOfEven(TMatrix* mat)
{
    for(int c = 0; c < mat->columns; c++)
    {
        int evenCount = 0;

        for(int r = 0; r < mat->rows; r++)
        {
            if(mat->cell[r][c] % 2 == 0)
                evenCount++;
        }

        mat->cell[mat->rows - 1][c] = evenCount;
    }
}

// Task 4

int sumEdges(TMatrix* mat)
{
    int sum = 0;

    for(int c = 0; c < mat->columns; c++)
    {
        sum += mat->cell[0][c];
        sum += mat->cell[mat->rows - 1][c];
    }

    for(int r = 1; r < mat->rows - 1; r++)
    {
        sum += mat->cell[r][0];
        sum += mat->cell[r][mat->columns - 1];
    }

    return sum;
}

int sumAll(TMatrix* mat)
{
    int sum = 0;

    for(int r = 0; r < mat->rows; r++)
    {
        for(int c = 0; c < mat->columns; c++)
        {
            sum += mat->cell[r][c];
        }
    }

    return sum;
}

int sumOutOfEdges(TMatrix* mat)
{
    return sumAll(mat) - sumEdges(mat);
}

// Task 5

void sumOfQuarters(TMatrix* mat)
{
    TMatrix resMat = {.rows=2, .columns=2, .cell={{0, 0}, {0, 0}}};

    for(int r = 0; r < mat->rows / 2; r++)
    {
        for(int c = 0; c < mat->columns / 2; c++)
        {
            resMat.cell[0][0] += mat->cell[r][c];
        }

        for(int c = mat->columns / 2; c < mat->columns; c++)
        {
            resMat.cell[0][1] += mat->cell[r][c];
        }
    }

    for(int r = mat->rows / 2; r < mat->rows; r++)
    {
        for(int c = 0; c < mat->columns / 2; c++)
        {
            resMat.cell[1][0] += mat->cell[r][c];
        }

        for(int c = mat->columns / 2; c < mat->columns; c++)
        {
            resMat.cell[1][1] += mat->cell[r][c];
        }
    }

    printMatrix(stdout, &resMat);
}

// Task 6

bool isVertical(TMatrix* mat)
{
    for(int r = 0; r < mat->rows; r++)
    {
        for(int c = 0; c < mat->columns / 2; c++)
        {
            if(mat->cell[r][c] != mat->cell[r][mat->columns - c - 1])
                return false;
        }
    }

    return true;
}

bool isHorizontal(TMatrix* mat)
{
    for(int r = 0; r < mat->rows / 2; r++)
    {
        for(int c = 0; c < mat->columns; c++)
        {
            if(mat->cell[r][c] != mat->cell[mat->rows - r - 1][c])
                return false;
        }
    }

    return true;
}

// Task 7

void createTrans(TMatrix* mat, TMatrix* trans)
{
    trans->rows = mat->columns;
    trans->columns = mat->rows;

    for(int r = 0; r < mat->rows; r++)
    {
        for(int c = 0; c < mat->columns; c++)
        {
            trans->cell[c][r] = mat->cell[r][c];
        }
    }
}

// Task 8

void turnByNTurns(TMatrix* mat, TMatrix* turn, int n)
{
    n %= 4;

    if(n == 0)
    {
        turn->rows = mat->rows;
        turn->columns = mat->columns;

        for(int r = 0; r < mat->rows; r++)
        {
            for(int c = 0; c < mat->columns; c++)
            {
                turn->cell[r][c] = mat->cell[r][c];
            }

        }

        return;
    }

    if(n == 1)
    {
        turn->rows = mat->columns;
        turn->columns = mat->rows;

        for(int r = 0; r < mat->rows; r++)
        {
            for(int c = 0; c < mat->columns; c++)
            {
                turn->cell[c][mat->rows - r - 1] = mat->cell[r][c];
            }

        }

        return;
    }

    if(n == 2)
    {
        turn->rows = mat->rows;
        turn->columns = mat->columns;

        for(int r = 0; r < mat->rows; r++)
        {
            for(int c = 0; c < mat->columns; c++)
            {
                turn->cell[mat->rows - r - 1][mat->columns - c - 1] = mat->cell[r][c];
            }

        }

        return;
    }

    turn->rows = mat->columns;
    turn->columns = mat->rows;

    for(int r = 0; r < mat->rows; r++)
    {
        for(int c = 0; c < mat->columns; c++)
        {
            turn->cell[mat->columns - c - 1][r] = mat->cell[r][c];
        }

    }

    return;
}

// Main

int main()
{
    TMatrix mat;
    TMatrix turn;

    FILE* in = fopen("a.txt", "r");
    if(in == NULL)
        return -1;

    if(!loadMatrix(in, &mat))
    {
        fclose(in);
        return -2;
    }

    turnByNTurns(&mat, &turn, 3);

    printMatrix(stdout, &turn);

    fclose(in);
    return 0;
}
