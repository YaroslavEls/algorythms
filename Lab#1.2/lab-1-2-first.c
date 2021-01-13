#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n;
    int operations = 0;
    double sum = 0;
    double prod = 1;

    printf("Enter a number: \n");
    scanf("%d", &n );

    for (int i = 1; i<=n; i++){
        prod = 1;
        for(int j = 1; j<=i ; j++){
            prod = prod * ( (j+1) * sin(j) );
            operations += 4;
        }
        sum = sum + prod / ( i * (i+1) );
        operations += 4;
    }

    printf("Result: %.7f\n", sum);
    printf("Operations amount: %d\n", operations);
}