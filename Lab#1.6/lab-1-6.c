#include <windows.h>
#include <stdio.h>
#include <unistd.h>

void printChar(int x, int y, char c) {
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%c", c);
    usleep(10000);
}

void main() {
    int p, j, i;
    int n = 24;

    for (p = n/2-1; p >= 0; p-- ) {

        for (j = n-p-1; j >= (p-56); j--) {
            printChar(j+56, n-p-1, '+');
        }

        for (i = n-p-1; i >= p + 1; i--) {
            printChar(p, i-1, '+');
        }

        for (j = p; j <= (n-p-1)+56; j++) {
            printChar(j, p, '+');
        }

        for (i = p; i <= n-p-1; i++) {
            printChar(j, i, '+');
        }

    }

}
