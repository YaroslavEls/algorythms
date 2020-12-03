#include <stdio.h>

int main() {
    int matrix[3][4] = {
            {8, 9, 10, 11},
            {6, 12, 13, 14},
            {6, 6, 5, 4}
    };


        int left = 0, right = 3, med = (int)(left+right)/2;


        for(int i = 0; i < 3; i++) {
            if((matrix[i][0] >= 0) && (matrix[i][0] <= 5)) {
                printf("Coords: (%d; %d)", ++i, 1);
            }
        }



        if((matrix[2][med] >= 0) && (matrix[2][med] <= 5)) {
            printf("Coords: (%d; %d)", 3, ++med);
        }
        else {
            while (left != right) {
                if((matrix[2][med] >= 0) && (matrix[2][med] <= 5)) {
                    left = right;
                } else {
                    ++med;
                }
            }
            printf("Coords: (%d; %d)", 3, ++med);
        }

}
