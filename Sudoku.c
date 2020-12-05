#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char fileout[100];
int max_solutions;
int actual_solution;
FILE *fp2;

void print_solution(int nGrid[9][9])
{
    int r, c;

    fprintf(fp2,"----- solution %d -----\n", actual_solution+1);
    for (r = 0; r < 9; r++)
    {
        for (c = 0; c < 9; c++)
        {
            fprintf(fp2,"%d ", nGrid[r][c]);
        }
        fprintf(fp2,"\n");
        if (r % 3 == 2) fprintf(fp2,"\n");
    }

}

int check(int row, int col, int n, int nGrid[9][9])
{
    int r, c, br, bc;

    if (nGrid[row][col] == n) return 1;
    if (nGrid[row][col] != 0) return 0;
    for (c = 0; c < 9; c++)
        if (nGrid[row][c] == n) return 0;
    for (r = 0; r < 9; r++)
        if (nGrid[r][col] == n) return 0;
    br = row / 3;
    bc = col / 3;
    for (r = br * 3; r < (br + 1) * 3; r++)
        for (c = bc * 3; c < (bc + 1) * 3; c++)
            if (nGrid[r][c] == n) return 0;

    return 1;
}

void solve(int row, int col, int nGrid[9][9])
{
    int n, t;

    if (row == 9)
    {

        if(actual_solution == max_solutions)
        {
            printf("Solucio al fitxer de sortida %s", fileout);
            exit(0);
        }
        else
        {
            print_solution(nGrid);
        }
        actual_solution++;
    }
    else{
        for (n = 1; n <= 9; n++)
            if (check(row, col, n,nGrid))
            {
                t = nGrid[row][col];
                nGrid[row][col] = n;
                if (col == 8)
                    solve(row + 1, 0,nGrid);
                else
                    solve(row, col + 1,nGrid);

                nGrid[row][col] = t;
            }
}
}
int main(int argc, char **argv)
{
    int i=0, j=0;
    FILE *fp;
    int nGrid[9][9];
    char caracter;
    actual_solution = 0;
    strcpy(fileout, argv[2]);
    max_solutions = atoi(argv[3]);
    fp = fopen(argv[1],"r");
    fp2= fopen(fileout, "w");
    if (fp == NULL || fp2 == NULL)
    {

        printf("\nInput file, outputfile n_solutions. To check solution use - not 0\n\n");
    }
    else
    {



        while (feof(fp) == 0)
        {
            caracter = fgetc(fp);

            if((caracter>='1' && caracter<='9')|| caracter == '-')
            {
                if(caracter == '-')
                {
                    caracter = 48;
                }
                nGrid[j][i] = caracter - 48;
                i++;
                if(i==9)
                {
                    i=0;
                    j++;
                }
            }
        }
        solve(0,0,nGrid);
    }
    fclose(fp);
    fclose(fp2);

    if(actual_solution > 0){
    printf("Solution has been saved in %s\n", fileout);
    }
    else{
    printf("No solution has been found\n");
    }
    return 0;
}
