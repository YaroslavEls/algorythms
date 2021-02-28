#include <stdio.h>
#include <math.h>

double recursion1(int n, double x, int i, double previous, double sum)
{
    double current;

    if (i == 1) {
        current = (x-1)/x;
    } else {
        current = previous * (i-1) * (x-1) / (i*x);
    }

    previous = current;
    sum += current;

    printf("element = %f    sum = %f    iteration = %d\n", current, sum, i);

    if (i < n) {
        sum = recursion1(n, x, i + 1, previous, sum);
    }
    return sum;
}

int main()
{
    int iterationsCount = 10;
    double argument = 5;
    double answer = log(argument);

    printf("Sum: %f\n", recursion1(iterationsCount, argument, 1, 0, 0));
    printf("ln(x) = %f\n", answer);
    printf("x = %.0f\n", argument);
    printf("Iterations done: %d\n", iterationsCount);
}