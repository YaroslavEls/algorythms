#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define n 12
#define PI 3.14159265359

const char ProgName[] = "Lab 6";

const int windowWidth = 1300;
const int windowHeight = 800;

const int side = 0.8 * windowHeight; //side of the square
const int r = 16; //radius of a vertex
const int shift = 5; //numeration offset

double** randm()
{
    double** resultingMatrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) resultingMatrix[i] = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double num = 2.0 * rand() / RAND_MAX;
            resultingMatrix[i][j] = num;
        }
    }

    return resultingMatrix;
}

int** mulmr(double coef, double **matrix)
{
    int** resultingMatrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) resultingMatrix[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double check = matrix[i][j] * coef;

            if (check < 1) resultingMatrix[i][j] = 0;
            else resultingMatrix[i][j] = 1;
        }
    }

    return resultingMatrix;
}

int** symmetrizeMatrix(int** matrix)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 0)
            {
                matrix[i][j] = matrix[j][i];
            }
        }
    }

    return matrix;
}

int** roundm(double** matrix)
{
    int** roundedMatrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) roundedMatrix[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            roundedMatrix[i][j] = round(matrix[i][j]);
        }
    }

    return roundedMatrix;
}

void printIntMatrix(int** matrix)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int** getWt(double** randm, int** A)
{
    double** resultOfMultiplication = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) resultOfMultiplication[i] = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            resultOfMultiplication[i][j] = randm[i][j] * 100 * A[i][j];
        }
    }

    int** Wt = roundm(resultOfMultiplication);

    for (int i = 0; i < n; i++) free(resultOfMultiplication[i]);
    free(resultOfMultiplication);

    //printIntMatrix(Wt);
    return Wt;
}

int** getB(int** Wt)
{
    int** B = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) B[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (Wt[i][j] == 0) B[i][j] = 0;
            else if (Wt[i][j] > 0) B[i][j] = 1;
        }
    }

    //printIntMatrix(B);
    return B;
}

int** getC(int** B)
{
    int** C = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) C[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (B[i][j] != B[j][i]) C[i][j] = 1;
            else C[i][j] = 0;
        }
    }

    //printIntMatrix(C);
    return C;
}

int** getD(int** B)
{
    int** D = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) D[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (B[i][j] == 1 && B[j][i] == 1) D[i][j] = 1;
            else D[i][j] = 0;
        }
    }

    //printIntMatrix(D);
    return D;
}

int** getTr()
{
    int** Tr = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) Tr[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j > i) Tr[i][j] = 1;
            else Tr[i][j] = 0;
        }
    }

    //printIntMatrix(Tr);
    return Tr;
}

int** refillWt(int** C, int** D, int** Tr, int** Wt)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Wt[i][j] = (C[i][j] + (D[i][j] * Tr[i][j])) * Wt[i][j];
        }
    }

    //printIntMatrix(Wt);
    return Wt;
}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w;

    w.lpszClassName = ProgName; //ім'я програми
    w.hInstance = hInstance; //ідентифікатор застосунку
    w.lpfnWndProc = WndProc; //вказівник на функцію вікна
    w.hCursor = LoadCursor(NULL, IDC_ARROW); //завантажений курсор
    w.hIcon = 0; //піктограми не буде
    w.lpszMenuName = 0; //меню не буде
    w.hbrBackground = NULL_BRUSH; //колір фона вікна
    w.style = CS_HREDRAW | CS_VREDRAW; //стиль: можна перемальовувати
    w.cbClsExtra = 0; //к-ть додаткових байтів для цього класу
    w.cbWndExtra = 0;

    if (!RegisterClass(&w)) return 0;

    hWnd = CreateWindow(
            ProgName, //Ім'я програми
            "Laboratory work 6. Tereshchenko Yaroslav", //заголовок
            WS_OVERLAPPEDWINDOW, //стиль вікна - комплексний
            240, //положення верхнього кута вікна на екрані по х
            10, // положення верхнього кута вікна на екрані по y
            windowWidth, //ширина вікна
            windowHeight, //висота вікна
            (HWND)NULL, // ідентифікатор породжуючого вікна
            (HMENU)NULL, //ідентифікатор меню (немає)
            (HINSTANCE)hInstance, //ідентифікатор екземпляра вікна
            (HINSTANCE)NULL
    ); // додаткові параметри відсутні

    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&lpMsg, hWnd, 0, 0)) // повідомлення з черги
    {
        TranslateMessage(&lpMsg); //перетворення повідомлення у рядок
        DispatchMessage(&lpMsg); //Передача повідомлення до функції вікна
    }

    return (lpMsg.wParam); // кінець основної функції
}

HDC hdc; // контекст
PAINTSTRUCT ps; // екземпляр структури

double nx[n] = {};
double ny[n] = {};

double getAngle(int i, int j)
{
    COORD vector;
    vector.X = nx[i] - nx[j];
    vector.Y = ny[i] - ny[j];

    double lengthOfTheVector = sqrt(vector.X * vector.X + vector.Y * vector.Y);
    double cosOfTheAngle = vector.X / lengthOfTheVector;

    double angle = acos(cosOfTheAngle);
    if (ny[i] < ny[j]) angle *= -1;

    return angle;
}

void line(int i, int j)
{
    double angle = getAngle(i, j);

    MoveToEx(hdc, nx[i] - r * 0.9 * cos(angle), ny[i] - r * 0.9 * sin(angle), NULL);
    LineTo(hdc, nx[j] + r * 0.9 * cos(angle), ny[j] + r * 0.9 * sin(angle));
}

void loop(int vertex)
{
    int signX = 1;
    int signY = 1;
    if (nx[vertex] - windowWidth * 0.5 <= 0) signX = -1;
    if (ny[vertex] - windowHeight * 0.5 <= 0) signY = -1;

    Arc (hdc, nx[vertex], ny[vertex], nx[vertex] + signX * 40, ny[vertex] + signY * 40, nx[vertex], ny[vertex], nx[vertex], ny[vertex]);
}

void bentLine(int i, int j)
{
    double angle = getAngle(i, j);
    double shiftValue = 30;
    double middleX = (nx[i] + nx[j]) / 2 + shiftValue * sin(angle);
    double middleY = (ny[i] + ny[j]) / 2 + shiftValue * cos(angle);

    MoveToEx(hdc, nx[i] - r * 0.9 * cos(angle), ny[i] - r * 0.9 * sin(angle), NULL);
    LineTo(hdc, middleX, middleY);
    LineTo(hdc, nx[j] + r * 0.9 * cos(angle), ny[j] + r * 0.9 * sin(angle));
}

void drawGraph(int** matrix, int side, int centerX, int centerY)
{
    for (int i = 0; i < n; i++)
    {
        if (i < floor(n / 4))
            nx[i] = centerX - side / 2 + (side / 3) * (i + 0.5);
        else if (i < 2 * floor(n / 4))
            nx[i] = centerX + side / 2;
        else if (i < 3 * floor(n / 4))
            nx[i] = centerX + side / 2 - (side / 3) * (i - 2 * floor(n / 4) + 0.5);
        else if (i < 4 * floor(n / 4))
            nx[i] = centerX - side / 2;
    }
    for (int i = 0; i < n; i++)
    {
        if (i < floor(n / 4))
            ny[i] = centerY - side / 2;
        else if (i < 2 * floor(n / 4))
            ny[i] = centerY - side / 2 + (side / 3) * (i - floor(n / 4) + 0.5);
        else if (i < 3 * floor(n / 4))
            ny[i] = centerY + side / 2;
        else if (i < 4 * floor(n / 4))
            ny[i] = centerY + side / 2 - (side / 3) * (i - 3 * floor(n / 4) + 0.5);
    }

    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

    SelectObject(hdc, KPen);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 1 && j > i)
            {
                if (i == j) loop(i);
                else if (
                        abs(i - j) != 1
                        && ((j < floor(n / 4)
                             && i < floor(n / 4))
                            || (j < 2 * floor(n / 4)
                                && i < 2 * floor(n / 4)
                                && j >= floor(n / 4)
                                && i >= floor(n / 4))
                            || (j < 3 * floor(n / 4)
                                && i < 3 * floor(n / 4)
                                && j >= 2 * floor(n / 4)
                                && i >= 2 * floor(n / 4))
                            || (j >= 3 * floor(n / 4)
                                && i >= 3 * floor(n / 4)))
                        )
                {
                    bentLine(i, j);
                }
                else
                    line(i, j);
            }
        }
    }

    SelectObject(hdc, BPen);
    SetTextColor(hdc, RGB(0, 0, 0));
    for (int i = 0; i < n; i++)
    {
        Ellipse(hdc, nx[i] - r, ny[i] - r, nx[i] + r, ny[i] + r);
        char* numeration = malloc(2 * sizeof(char*));
        sprintf(numeration, "%d", i + 1);
        TextOut(hdc, nx[i] - shift, ny[i] - r / 2, numeration, 2);
        free(numeration);
    }
}

void drawWeights(int** weightMatrix, int** adjacencyMatrix)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adjacencyMatrix[i][j] == 1 && j > i)
            {
                char* weight = malloc(3 * sizeof(char*));
                sprintf(weight, "%d", weightMatrix[i][j]);

                if (
                        abs(i - j) != 1
                        && ((j < floor(n / 4)
                             && i < floor(n / 4))
                            || (j < 2 * floor(n / 4)
                                && i < 2 * floor(n / 4)
                                && j >= floor(n / 4)
                                && i >= floor(n / 4))
                            || (j < 3 * floor(n / 4)
                                && i < 3 * floor(n / 4)
                                && j >= 2 * floor(n / 4)
                                && i >= 2 * floor(n / 4))
                            || (j >= 3 * floor(n / 4)
                                && i >= 3 * floor(n / 4)))
                        )
                {
                    TextOut(
                            hdc,
                            (nx[i] + nx[j]) * 0.5 + 30 * sin(getAngle(i, j)) - shift,
                            (ny[i] + ny[j]) * 0.5 + 30 * cos(getAngle(i, j)) - shift * 0.2,
                            weight,
                            3
                    );
                }
                else if (abs(i - j) == 6)
                {
                    TextOut(
                            hdc,
                            (nx[i] + nx[j]) * 0.5 - shift * sin(getAngle(i, j)) * 10,
                            (ny[i] + ny[j]) * 0.5 - shift * cos(getAngle(i, j)) * 9.2,
                            weight,
                            3
                    );
                }
                else
                {
                    TextOut(
                            hdc,
                            (nx[i] + nx[j]) * 0.5 - shift,
                            (ny[i] + ny[j]) * 0.5 - shift * 0.2,
                            weight,
                            3
                    );
                }

                free(weight);
            }
        }
    }
}

void recolorVertex(int vertex, int R, int G, int B)
{
    int x = nx[vertex];
    int y = ny[vertex];

    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
    SelectObject(hdc, BPen);

    Ellipse(hdc, x - r, y - r, x + r, y + r);

    char* numeration = malloc(2 * sizeof(char*));
    sprintf(numeration, "%d", vertex + 1);
    SetTextColor(hdc, RGB(R, G, B));
    TextOut(hdc, x - shift, y - r / 2, numeration, 2);
    free(numeration);
}

void recolorConnection(int firstVertex, int secondVertex)
{
    HPEN GPen = CreatePen(PS_SOLID, 1, RGB(0, 200, 0));
    SelectObject(hdc, GPen);

    if (
            abs(firstVertex - secondVertex) != 1
            && ((secondVertex < floor(n / 4)
                 && firstVertex < floor(n / 4))
                || (secondVertex < 2 * floor(n / 4)
                    && firstVertex < 2 * floor(n / 4)
                    && secondVertex >= floor(n / 4)
                    && firstVertex >= floor(n / 4))
                || (secondVertex < 3 * floor(n / 4)
                    && firstVertex < 3 * floor(n / 4)
                    && secondVertex >= 2 * floor(n / 4)
                    && firstVertex >= 2 * floor(n / 4))
                || (secondVertex >= 3 * floor(n / 4)
                    && firstVertex >= 3 * floor(n / 4)))
            )
    {
        bentLine(firstVertex, secondVertex);
    }
    else line(firstVertex, secondVertex);
}


int detectElementInArray(int* array, int desired)
{
    for (int i = 0; i < n; i++)
    {
        //element detected in the array
        if (array[i] == desired)
            return 1;
    }
    //element not detected in the array
    return 0;
}

int findSmallestInArray(int* array, int* exceptions)
{
    int minValue = 201;
    int index = -1;
    for (int i = 0; i < n; i++)
    {
        if (
            array[i] > 0
            && array[i] < minValue
            && !detectElementInArray(exceptions, i)
        )
        {
            minValue = array[i];
            index = i;
        }
    }
    return index;
}

int* findSmallestAvailable(int** W, int* found)
{
    int* indexesArrayOfSmallestAvailable = (int*)malloc(2 * sizeof(int));
    int smallestAvailableValue = 201;

    for (int i = 0; found[i] >= 0; i++)
    {
            int columnOfSmallestAvailable = findSmallestInArray(W[found[i]], found);

            if (
                W[found[i]][columnOfSmallestAvailable] < smallestAvailableValue
                && columnOfSmallestAvailable >= 0
            )
            {
                indexesArrayOfSmallestAvailable[0] = found[i];
                indexesArrayOfSmallestAvailable[1] = columnOfSmallestAvailable;
            }
    }

    return indexesArrayOfSmallestAvailable;
}

int** findMinimumSpanningTree(int** W)
{
    int found[n] = {};
    int foundLength = 0;

    int** minimumSpanningTree = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) minimumSpanningTree[i] = (int*)malloc(n * sizeof(int));

    //start exploration from
    found[foundLength] = 0;
    foundLength++;
    recolorVertex(0, 0, 200, 0);
    Sleep(300);

    for (int i = 1; i < n; i++)
        found[i] = -1;

    for (int i = 0; foundLength != n; i++)
    {
        int* indexes = findSmallestAvailable(W, found);

        found[foundLength] = indexes[1];
        foundLength++;

        minimumSpanningTree[indexes[0]][indexes[1]] = 1;
        minimumSpanningTree[indexes[1]][indexes[0]] = 1;

        printf("Smallest available element found at position %d %d  it`s weight is %d\n",
               indexes[0] + 1,
               indexes[1] + 1,
               W[indexes[0]][indexes[1]]);

        recolorVertex(indexes[1], 0, 200, 0);
        recolorConnection(indexes[0], indexes[1]);
        Sleep(300);
    }


    return minimumSpanningTree;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    switch(messg)
    {
        case WM_PAINT:
            srand(0423);

            double** T = randm();
            int** A = mulmr(( 1.0 - 2 * 0.01 - 3 * 0.005 - 0.05), T);
            int** Wt = getWt(T, A);
            int** B = getB(Wt);
            int** C = getC(B);
            int** D = getD(B);
            int** Tr = getTr();
            Wt = refillWt(C, D, Tr, Wt);

            int** W = symmetrizeMatrix(Wt);

            printf("Generated adjacency matrix:\n");
            printIntMatrix(A);

            printf("Symmetrized adjacency matrix:\n");
            A = symmetrizeMatrix(A);
            printIntMatrix(A);

            printf("Weight matrix:\n");
            printIntMatrix(W);

            hdc = BeginPaint(hWnd, &ps);
            drawGraph(A, side, windowWidth / 3, windowHeight / 2);
            drawWeights(W, A);

            int** MST = findMinimumSpanningTree(W);
            drawGraph(MST, side * 0.6, windowWidth * 0.8, windowHeight / 2);
            drawWeights(W, MST);

            printf("\nMinimum spanning tree is:\n");
            printIntMatrix(MST);

            for (int i = 0; i < n; i++) free(T[i]);
            free(T);
            for (int i = 0; i < n; i++) free(A[i]);
            free(A);

            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return (DefWindowProc(hWnd, messg, wParam, lParam));
    }
}
