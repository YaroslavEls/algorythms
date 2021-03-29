#include<windows.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>

double** randmm(int rows, int cols)
{
    double** matrix = (double**)malloc(rows * sizeof(double*));

    for (int i = 0; i < rows; i++)
        matrix[i] = (double*)malloc(cols * sizeof(double));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] =  2.0 / RAND_MAX * rand();
        }
    }

    return matrix;
}

double** mulmr(double num, double **mat, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat[i][j] = mat[i][j] * num;

            if(mat[i][j] > 1.0)
            {
                mat[i][j] = 1;
            } else mat[i][j] = 0;
        }
    }

    return mat;
}

//


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[]="Laboratory work #3";
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS w;
    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = NULL_BRUSH;
    w.style = CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if(!RegisterClass(&w))
    {
        return 0;
    }

    hWnd = CreateWindow(ProgName,
                      "Laboratory #3. Yaroslav Tereschenko",
                      WS_OVERLAPPEDWINDOW,
                      150, 150,
                      650, 650,
                      (HWND)NULL, (HMENU)NULL,
                      (HINSTANCE)hInstance, (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while(GetMessage(&lpMsg, hWnd, 0, 0))
    {
    TranslateMessage(&lpMsg);
    DispatchMessage(&lpMsg);
    }

    return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    void arrow(float fi, int px,int py)
    {
        fi = 3.1416*(180.0 - fi)/180.0;
        int lx,ly,rx,ry;
        lx = px+15*cos(fi+0.3);
        rx = px+15*cos(fi-0.3);
        ly = py+15*sin(fi+0.3);
        ry = py+15*sin(fi-0.3);
        MoveToEx(hdc, lx, ly, NULL);
        LineTo(hdc, px, py);
        LineTo(hdc, rx, ry);
        // return 0;
    }

    switch(messg)
    {
        case WM_PAINT :
        hdc=BeginPaint(hWnd, &ps);

        char *nn[12] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
        int nx[12] = {};
        int ny[12] = {};
        int num = 100;
        for(int i = 0; i < 12; i++)
        {
            if(i == 0)
            {
                nx[i] = num;
                ny[i] = num;
            } else if(i < 4)
            {
                nx[i] = nx[i - 1] + num;
                ny[i] = ny[i - 1];
            } else if(i < 7)
            {
                nx[i] = nx[i - 1];
                ny[i] = ny[i - 1] + num;
            } else if(i < 10)
            {
                nx[i] = nx[i - 1] - num;
                ny[i] = ny[i - 1];
            } else
            {
            nx[i] = nx[i - 1];
            ny[i] = ny[i - 1] - num;
            }
        }
        int dx = 16, dy = 16, dtx = 7;
        int i;

        HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

        srand(0423);
        double** T = randmm(12, 12);
        double coef = 1.0 - 2*0.02 - 3*0.005 - 0.25;
        double** A = mulmr(coef, T, 12, 12);


        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                printf("%.0f ", A[i][j]);
            }
            printf("\n");
        }

        SelectObject(hdc, KPen);

        ///////////////////////// Сейчас начнеться жепа \\\\\\\\\\\\\\\\\\\\\\\\\

        for(int i = 0; i < 12; i++)
        {
            for(int j = 0; j < 12; j++)
            {
                if(A[i][j] == 1)
                {
                    MoveToEx(hdc, nx[i], ny[i], NULL);

                    if((ny[i] == ny[j]) && (nx[j] != nx[i] + num) && (nx[j] != nx[i] - num))
                    {

                        if(i < 4)
                        {
                            if(nx[i] < nx[j])
                            {
                                Arc(hdc, nx[i], ny[i]-50, nx[j], ny[j]+50, nx[j], ny[j], nx[i], ny[i]);
                            }
                            else if(nx[i] > nx[j])
                            {
                                Arc(hdc, nx[j], ny[j]-40, nx[i], ny[i]+40, nx[i], ny[i], nx[j], ny[j]);
                            }
                        }
                        else if(i > 5 && i < 10)
                        {
                            if(nx[i] < nx[j])
                            {
                                Arc(hdc, nx[j], ny[j]-50, nx[i], ny[i]+50, nx[i], ny[i], nx[j], ny[j]);
                            }
                            else if(nx[i] > nx[j])
                            {
                                Arc(hdc, nx[i], ny[i]-40, nx[j], ny[j]+40, nx[j], ny[j], nx[i], ny[i]);
                            }
                        }

                    }
                    else if((nx[i] == nx[j]) && (ny[j] != ny[i] + num) && (ny[j] != ny[i] - num))
                    {

                        if(i > 2 && i < 7)
                        {
                            if(ny[i] < ny[j])
                            {
                                Arc(hdc, nx[i]-40, ny[i], nx[j]+40, ny[j], nx[j], ny[j], nx[i], ny[i]);
                            }
                            else if(ny[i] > ny[j])
                            {
                                Arc(hdc, nx[j]-50, ny[j], nx[i]+50, ny[i], nx[i], ny[i], nx[j], ny[j]);
                            }
                        }
                        else if(i > 8)
                        {
                            if(ny[i] < ny[j])
                            {
                                Arc(hdc, nx[j]-40, ny[j], nx[i]+40, ny[i], nx[i], ny[i], nx[j], ny[j]);
                            }
                            else if(ny[i] > ny[j])
                            {
                                Arc(hdc, nx[i]-40, ny[i], nx[j]+40, ny[j], nx[j], ny[j], nx[i], ny[i]);
                            }
                        }

                    } else
                    {
                        LineTo(hdc, nx[j], ny[j]);
                    }
                }
            }
        }

        ///////////////////////// Жепа закончилась (нет) \\\\\\\\\\\\\\\\\\\\\\\\\

        SelectObject(hdc, BPen);
        for(i = 0; i < 12; i++)
        {
            Ellipse(hdc, nx[i]-dx, ny[i]-dy, nx[i]+dx, ny[i]+dy);
            if(i < 9)
            {
                TextOut(hdc, nx[i]-dtx, ny[i]-dy/2, nn[i], 1);
            } else TextOut(hdc, nx[i]-dtx, ny[i]-dy/2, nn[i], 2);
        }

        EndPaint(hWnd, &ps);
        break;

        case WM_DESTROY:
        PostQuitMessage(0);
        break;

        default:
        return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
