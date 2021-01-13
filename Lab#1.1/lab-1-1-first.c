#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x;
    int y;
    printf("Enter a number: \n");scanf("%d", &x);
    if (x > 12) {
        y = -14*x-20;
        printf("y = %d\n", y);
    }
    else if (x > 3) {
        printf("no such value found");
    }
    else if (x > -21){
        y = -14*x-20;
        printf("y = %d\n", y);
    }
    else if (x > -41) {
        printf("no such value found");
    }
    else {
        y = 13*x*2/11-6;
        printf("y = %d\n", y);
    }
    return 0;
}
