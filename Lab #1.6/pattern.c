#include <windows.h>
#include <stdio.h>

COORD GetCursorPosition() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    GetConsoleScreenBufferInfo(h, &bufferInfo);
    return bufferInfo.dwCursorPosition;
}

void PrintCharAtCursorPosition(int XPos, int YPos, char c[]) {
    COORD coord;
    coord.X = XPos; coord.Y = YPos;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("%s", c);

}

void main() {
    for (int j=0; j<25; j++) {
        for (int i=0; i<80; i++) {
            PrintCharAtCursorPosition(0+i, 0+j, "+");
        }
    }
}


// PrintCharAtCursorPosition(20, 20, "f");
// PrintCharAtCursorPosition(25, 20, "k");