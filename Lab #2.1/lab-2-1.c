#include <stdio.h>

int main() {
    int matrix[9][7] = {
            {12, 13, 14, 15, 16, 17, 18},
            {11, 19, 20, 21, 22, 24, 23},
            {10, 23, 24, 25, 26, 27, 28},
            {9, 29, 30, 31, 32, 33, 34},
            {8, 35, 36, 36, 37, 38, 39},
            {7, 40, 41, 42, 43, 44, 45},
            {5, 46, 47, 48, 49, 50, 51},
            {5, 51, 52, 53, 54, 55, 56},
            {4, 1, -1, -2, -3, -4, -5}
    };

    int left = 0, right = 6;
    int top = 0, bot = 8;
    int med = (left+right)/2;
    int med2 = (bot+top)/2;


    for (int x = 0; x < 9; x++) {
        for(int j=0; j < 7; j++) {
            printf("%d ", matrix[x][j]);
        }
        printf("\n");
    }


    if((matrix[med2][0] >= 0) && (matrix[med2][0] <= 5)) {
        printf("There ia an element in the last row with coordinates (%d; %d)\n", ++med2, 1);
    }
    else {
        while (top <= bot) {
            med2 = (top + bot)/2;
            if ((matrix[med2][0] >= 0) && (matrix[med2][0] <= 5)) {
                top = (bot + 1);
            }
            else if(matrix[med2][0] < 0) {
                bot = med2 - 1;
            } else if (matrix[med2][0] > 5) {
                top = med2 + 1;
            }

        }
        if ((matrix[med2][0] >= 0) && (matrix[med2][0] <= 5)) {
            printf("There is an element in the first column with coordinates (%d; %d)\n", ++med2, 1);
        } else {
            printf("There are no suitable elements in the first column\n");
        }
    }


    if((matrix[8][med] >= 0) && (matrix[8][med] <= 5)) {
        printf("There ia an element in the last row with coordinates (%d; %d)\n", 9, ++med);
    }
    else {
        while (left <= right) {
            med = (left+right)/2;
            if ((matrix[8][med] >= 0) && (matrix[8][med] <= 5)) {
                left = (right + 1);
            }
            else if(matrix[8][med] < 0) {
                right = med - 1;
            } else if (matrix[8][med] > 5) {
                left = med + 1;
            }
        }
        if ((matrix[8][med] >= 0) && (matrix[8][med] <= 5)) {
            printf("There ia an element in last row with coordinates (%d; %d)\n", 9, ++med);
        } else {
            printf("There are no suitable elements in the last row\n");
        }
    }

}
