#include <stdio.h>

double firstMatrix[7][7] = {
        {1, -4, -20, -9, 29, 6, 16},
        {7, 23, 7, 5, -8, 3, -11},
        {9, -9, -6, -6, -11, 28, -6},
        {5, -18, 12.4, -16, 3, -19, 3},
        {2, -10, 12.1, 11, 14, -15, 15},
        {4, 11, 11, 4, 27, -14, 16},
        {11, 25, -17, -6, 23, -16, -17}
};

int col;
int i, j;
double T;
int rows = 7;
int columns = 7;
double sort;
double sortReverse;
double print;


double printMatrix(char* sortType) {
    printf("%s", sortType);
    printf("\n");
    for (int x = 0; x < rows; x++) {
        for(int y = 0; y < columns; y++) {
            printf("%.0f ", firstMatrix[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}


double matrixSorting(double matrix[7][7], int type) // arg type: 1 for default or 0 for reverse sorting
{
    for(col = 0; col < columns; col++) {

        for (i = 1; i <= rows - 1; i++) {
            T = matrix[i][col];
            j = 0;

            if (type == 1 ) {
                while (matrix[j][col] < T) {
                    j = j + 1;
                }
            } else {
                while (matrix[j][col] > T) {
                    j = j + 1;
                }
            }

            for (int k = i - 1; k >= j; k--) {
                matrix[k + 1][col] = matrix[k][col];
            }

            matrix[j][col] = T;
        }
    }
}


int main() {
    print = printMatrix("Original matrix:");

    sort = matrixSorting(firstMatrix, 1);
    print = printMatrix("Sorted matrix:");

    sort = matrixSorting(firstMatrix, 1);
    print = printMatrix("Again sorted matrix:");

    sortReverse = matrixSorting(firstMatrix, 0);
    print = printMatrix("Reverse matrix:");

    sort = matrixSorting(firstMatrix, 1);
    print = printMatrix("Sorted reverse matrix:");
}
