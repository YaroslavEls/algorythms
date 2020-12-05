#include <stdio.h>

int main() {
    int matrix[8][7] = {
            {12, 13, 14, 15, 16, 17, 18},
            {11, 19, 20, 21, 22, 24, 23},
            {10, 23, 24, 25, 26, 27, 28},
            {9, 29, 30, 31, 32, 33, 34},
            {8, 35, 36, 36, 37, 38, 39},
            {7, 40, 41, 42, 43, 44, 45},
            {5, 46, 47, 48, 49, 50, 51},
            {4, 1, -1, -1, -3, -4, -5}
    };

    int left = 0, right = 6;
    int med = (left+right)/2;


    for (int x = 0; x < 8; x++) {
        for(int j=0; j < 7; j++) {
            printf("%d ", matrix[x][j]);
        }
        printf("\n");
    }


    for(int i = 0; i < 8; i++) {
        if ((matrix[i][0] >= 0) && (matrix[i][0] <= 5)) {
            printf("There is an element in the first column with coordinates (%d; %d)\n", ++i, 1);
        } else if (((matrix[i][0] < 0) || (matrix[i][0] > 5)) && i == 7) {
            printf("There are no suitable elements in the first column\n");
        }
    }


    if((matrix[7][med] >= 0) && (matrix[7][med] <= 5)) {
        printf("There ia an element in the last row with coordinates (%d; %d)\n", 8, ++med);
    }
    else {
        while (left != right) {
            if ((matrix[7][med] >= 0) && (matrix[7][med] <= 5)) {
                left = right;
            }
            else if(matrix[7][med] < 0) {
                --med;
            } else if (matrix[7][med] > 5) {
                ++med;
            }

            if ((med < 0) || (med > 8)) {left = right;}

        }
        if ((matrix[7][med] >= 0) && (matrix[7][med] <= 5)) {
            printf("There ia an element in last row with coordinates (%d; %d)\n", 8, ++med);
        } else {
            printf("There are no suitable elements in the last row\n");
        }
    }

}
