#include <stdio.h>
#include <math.h>

double sum = 0;

double recursion(int n, double x, int i)
{
    double element;

    if (i == 1) {
        element = (x-1)/x;
    } else {
        element = recursion(n, x, i - 1) * (i -1) * (x-1) / (i*x);
    }

    sum += element;

    printf("element = %f    sum = %f    iteration = %d\n", element, sum, i);

    if(i == n) {
        return sum;
    }
    return element;
}

int main()
{
    int iterationsCount = 10;
    double argument = 5;
    double answer = log(argument);

    printf("Sum: %f\n", recursion(iterationsCount, argument, iterationsCount));
    printf("ln(x) = %f\n", answer);
    printf("x = %.0f\n", argument);
    printf("Iterations done: %d\n", iterationsCount);
}