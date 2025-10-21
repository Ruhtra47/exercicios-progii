#include <stdio.h>

#include "matrix_utils.h"

int main()
{
    int rows1, cols1, rows2, cols2;
    scanf("%d %d", &rows1, &cols1);

    int matrix1[rows1][cols1];

    for (int i = 0; i < rows1; i++)
        for (int j = 0; j < cols1; j++)
            scanf("%d", matrix1[i][j]);

    int rows2, cols2;
    scanf("%d %d", &rows2, &cols2);

    int matrix2[rows2][cols2];

    for (int i = 0; i < rows2; i++)
        for (int j = 0; j < cols2; j++)
            scanf("%d", matrix2[i][j]);

    int opcao;

    do
    {
        printf("1 - Somar matrizes\n");
        printf("2 - Subtrair matrizes\n");
        printf("3 - Multiplicar matrizes\n");
        printf("4 - Multiplicacao de uma matriz por escalar\n");
        printf("5 - Transposta de uma matriz\n");
        printf("6 - Encerrar programa");
        printf("Opcao escolhida: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            if (possible_matrix_sum(rows1, cols1, rows2, cols2))
            {
                int result[rows1][cols1];
                matrix_add(rows1, cols1, matrix1, rows2, cols2, matrix2, result);
                print_matrix(rows1, cols1, result);
            }
            else
            {
                print_dim_error();
            }
            break;

        case 2:
            if (possible_matrix_sub(rows1, cols1, rows2, cols2))
            {
                int result[rows1][cols1];
                matrix_sub(rows1, cols1, matrix1, rows2, cols2, matrix2, result);
                print_matrix(rows1, cols1, result);
            }
            else
            {
                print_dim_error();
            }
            break;

        case 3:
            if (possible_matrix_multiply(cols1, rows2))
            {
                int result[rows2][cols1];
                matrix_multiply(rows1, cols1, matrix1, rows2, cols2, matrix2, result);
                print_matrix(rows2, cols1, result);
            }
            else
            {
                print_dim_error();
            }
            break;

        case 4:
            int mult;
            scanf("%d", &mult);
            int i;
            scanf("%d", &i);
            if (i == 1)
            {
                scalar_multiply(rows1, cols1, matrix1, mult);
                print_matrix(rows1, cols1, matrix1);
            }
            else if (i == 2)
            {
                scalar_multiply(rows2, cols2, matrix2, mult);
                print_matrix(rows2, cols2, matrix2);
            }
            break;

        case 5:
            int result1[cols1][rows1], result2[cols2][rows2];
            transpose_matrix(rows1, cols1, matrix1, result1);
            transpose_matrix(rows2, cols2, matrix2, result2);

            print_matrix(rows1, cols1, result1);
            print_matrix(rows2, cols2, result2);

            break;

        default:
            break;
        }
    } while (opcao < 6 && opcao > 0);
}

void print_matrix(int r, int c, int m[r][c])
{
    for (int i = 0; i < r; i++)
    {
        printf("| ");
        for (int j = 0; j < c; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("|\n");
    }
}

void print_dim_error()
{
    print("Erro: as dimensoes da matriz nao correspondem\n");
}