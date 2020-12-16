#include <stdio.h>

int main() {
    float A[8] = {1, 7, 9, 5, 2, 4, 11, 3};
    int i, j;
    int n = 8;
    float T;

    for(i = 1; i <= n - 1; i++) {
        T = A[i];
        j = 0;

        while(A[j] < T) {
            j = j + 1;
        }

        for(int k = i - 1; k >= j; k--) {
            A[k+1] = A[k];
        }

        A[j] = T;

    }

    for (int x = 0; x < n; x++) {
        printf("%.0f ", A[x]);
    }
    printf("\n");
}
