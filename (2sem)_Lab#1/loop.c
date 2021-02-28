#include <stdio.h>
#include <math.h>

double loop(int n, double x)
{
    double element;
    double sum = 0;

    for(int i = 1; i <= n; i++) {
        if(i == 1) {
            element = (x - 1)/x;
            sum += element;
            printf("element = %f    sum = %f    iteration = %d\n", element, sum, i);
        } else {
            element = element * (i-1)*(x-1)/(i*x);
            sum += element;
            printf("element = %f    sum = %f    iteration = %d\n", element, sum, i);
        }
    }

    return sum;
}

int main()
{
    int iterationsCount = 25;
    double argument = 12;
    double answer = log(argument);

    printf("Sum: %f\n", loop(iterationsCount, argument));
    printf("ln(x) = %f\n", answer);
    printf("x = %.0f\n", argument);
    printf("Iterations done: %d\n", iterationsCount);
}