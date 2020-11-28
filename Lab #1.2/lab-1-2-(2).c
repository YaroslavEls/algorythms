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
        prod = prod * ( (i+1) * sin(i) );
        sum = sum + prod / ( i * (i+1) );
        operations += 8;
    }

    printf("Result: %.7f\n", sum);
    printf("Operations amount: %d\n", operations);
}