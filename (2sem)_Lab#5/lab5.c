#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define n 12
#define PI 3.14159265359

const char ProgName[] = "Lab 5";

const int window_width = 1300;
const int window_height = 800;

const int a = 0.8 * window_height; //side of the square
const int r = 16; //radius of a vertex
const int shift = 5; //numeration offset

double** randm()
{
    double** resulting_matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) resulting_matrix[i] = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double numbe = 2.0 * rand() / RAND_MAX;
            resulting_matrix[i][j] = numbe;
        }
    }

    return resulting_matrix;
}

int** mulmr(double coefficient, double **matrix)
{
    int** resulting_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) resulting_matrix[i] = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            double check = matrix[i][j] * coefficient;

            if (check < 1) resulting_matrix[i][j] = 0;
            else resulting_matrix[i][j] = 1;
        }
    }

    return resulting_matrix;
}

void print_int_matrix(int** matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
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
            "Laboratorty work 5. Tereshchenko Yaroslav", //заголовок
            WS_OVERLAPPEDWINDOW, //стиль вікна - комплексний
            240, //положення верхнього кута вікна на екрані по х
            10, // положення верхнього кута вікна на екрані по y
            window_width, //ширина вікна
            window_height, //висота вікна
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

double get_angle(int i, int j)
{
    COORD vector;
    vector.X = nx[i] - nx[j];
    vector.Y = ny[i] - ny[j];

    double vector_len = sqrt(vector.X * vector.X + vector.Y * vector.Y);
    double cos_angle = vector.X / vector_len;

    double angle = acos(cos_angle);
    if (ny[i] < ny[j]) angle *= -1;

    return angle;
}

void arrow(double fi, double px, double py)
{
    px += r * 0.9 * cos(fi);
    py += r * 0.9 * sin(fi);
    double lx = px + r * 0.9 * cos(fi + 0.3);
    double rx = px + r * 0.9 * cos(fi - 0.3);
    double ly = py + r * 0.9 * sin(fi + 0.3);
    double ry = py + r * 0.9 * sin(fi - 0.3);

    MoveToEx(hdc, lx, ly, NULL);
    LineTo(hdc, px, py);
    LineTo(hdc, rx, ry);
}

void line(int i, int j)
{
    double fi = get_angle(i, j);

    MoveToEx(hdc, nx[i] - r * 0.9 * cos(fi), ny[i] - r * 0.9 * sin(fi), NULL);
    LineTo(hdc, nx[j] + r * 0.9 * cos(fi), ny[j] + r * 0.9 * sin(fi));

    arrow(fi, nx[j], ny[j]);
}

void loop(int j)
{
    int x_sign = 1;
    int y_sign = 1;
    if (nx[j] - window_width * 0.5 <= 0) x_sign = -1;
    if (ny[j] - window_height * 0.5 <= 0) y_sign = -1;

    Arc (hdc, nx[j], ny[j], nx[j] + x_sign * 40, ny[j] + y_sign * 40, nx[j], ny[j], nx[j], ny[j]);

    if (x_sign == 1 && y_sign == -1) arrow(-0.15, nx[j], ny[j] + 3);
    if (x_sign == -1 && y_sign == -1) arrow(4.6, nx[j] + 3, ny[j]);
    if (x_sign == -1 && y_sign == 1) arrow(3, nx[j], ny[j] - 3);
    if (x_sign == 1 && y_sign == 1) arrow(1.5, nx[j] - 3, ny[j]);
}

void offset_line(int i, int j)
{
    double angle = get_angle(i, j);

    double shift_distance = 15;
    double dx1 = nx[i] - shift_distance * cos(angle - PI / 8);
    double dy1 = ny[i] - shift_distance * sin(angle - PI / 8);
    double dx2 = nx[j] + shift_distance * cos(angle + PI / 8);
    double dy2 = ny[j] + shift_distance * sin(angle + PI / 8);

    MoveToEx(hdc, dx1, dy1, NULL);
    LineTo(hdc, dx2, dy2);
    arrow(angle, dx2 - 15 * cos(angle), dy2 - 15 * sin(angle));
}

void bent_line(int i, int j)
{
    double fi = get_angle(i, j);

    double shift_distance = 30;

    double middle_x = (nx[i] + nx[j]) / 2 + shift_distance * sin(fi);
    double middle_y = (ny[i] + ny[j]) / 2 + shift_distance * cos(fi);

    MoveToEx(hdc, nx[i] - r * 0.9 * cos(fi), ny[i] - r * 0.9 * sin(fi), NULL);
    LineTo(hdc, middle_x, middle_y);
    LineTo(hdc, nx[j] + r * 0.9 * cos(fi), ny[j] + r * 0.9 * sin(fi));

    fi = PI + acos((nx[j] - middle_x) / (sqrt(pow(nx[j] - middle_x, 2) + pow(ny[j] - middle_y, 2))));
    if (ny[j] < middle_y) fi *= -1;

    arrow(fi, nx[j],ny[j] - r * 0.9 * sin(fi));
}

void draw_graph(int** matrix, int side, int x_center, int y_center)
{
    for (int i = 0; i < n; i++)
    {
        if (i < floor(n / 4))
            nx[i] = x_center - side / 2 + (side / 3) * (i + 0.5);
        else if (i < 2 * floor(n / 4))
            nx[i] = x_center + side / 2;
        else if (i < 3 * floor(n / 4))
            nx[i] = x_center + side / 2 - (side / 3) * (i - 2 * floor(n / 4) + 0.5);
        else if (i < 4 * floor(n / 4))
            nx[i] = x_center - side / 2;
    }
    for (int i = 0; i < n; i++)
    {
        if (i < floor(n / 4))
            ny[i] = y_center - side / 2;
        else if (i < 2 * floor(n / 4))
            ny[i] = y_center - side / 2 + (side / 3) * (i - floor(n / 4) + 0.5);
        else if (i < 3 * floor(n / 4))
            ny[i] = y_center + side / 2;
        else if (i < 4 * floor(n / 4))
            ny[i] = y_center + side / 2 - (side / 3) * (i - 3 * floor(n / 4) + 0.5);
    }

    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

    SelectObject(hdc, KPen);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == 1)
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
                    bent_line(i, j);
                }
                else if (matrix[j][i] == 1 && i > j) offset_line(i, j);
                else line(i, j);
            }
        }
    }

    SelectObject(hdc, BPen);
    SetTextColor(hdc, RGB(0, 0, 0));
    for (int i = 0; i < n; i++)
    {
        Ellipse(hdc, nx[i] - r, ny[i] - r, nx[i] + r, ny[i] + r);
        char* nn = malloc(2 * sizeof(char*));
        sprintf(nn, "%d", i + 1);
        TextOut(hdc, nx[i] - shift, ny[i] - r / 2, nn, 2);
        free(nn);
    }
}

void recolor_vertex(int vertex, int R, int G, int B)
{
    int x = nx[vertex];
    int y = ny[vertex];

    HPEN myPen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
    SelectObject(hdc, myPen);

    Ellipse(hdc, x - r, y - r, x + r, y + r);

    char* nn = malloc(2 * sizeof(char*));
    sprintf(nn, "%d", vertex + 1);
    SetTextColor(hdc, RGB(R, G, B));
    TextOut(hdc, x - shift, y - r / 2, nn, 2);
    free(nn);
}

void highlight_connection(int first_vertex, int second_vertex)
{
    HPEN GPen = CreatePen(PS_SOLID, 1, RGB(0, 200, 0));
    SelectObject(hdc, GPen);

    if (
        abs(first_vertex - second_vertex) != 1
        && ((second_vertex < floor(n / 4)
            && first_vertex < floor(n / 4))
            || (second_vertex < 2 * floor(n / 4)
                && first_vertex < 2 * floor(n / 4)
                && second_vertex >= floor(n / 4)
                && first_vertex >= floor(n / 4))
            || (second_vertex < 3 * floor(n / 4)
                && first_vertex < 3 * floor(n / 4)
                && second_vertex >= 2 * floor(n / 4)
                && first_vertex >= 2 * floor(n / 4))
            || (second_vertex >= 3 * floor(n / 4)
                && first_vertex >= 3 * floor(n / 4)))
    )
    {
        bent_line(first_vertex, second_vertex);
    }
    else line(first_vertex, second_vertex);
}


struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
};

void add_with_head_shift(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data = new_data;
    new_node->next = (*head_ref);
    new_node->prev = NULL;

    if ((*head_ref) != NULL) (*head_ref)->prev = new_node;
    (*head_ref) = new_node;
}

void add_without_headshift(struct Node** head_ref, int new_data)
{
    struct Node* last_node;
    if ((*head_ref)->prev) last_node = (*head_ref)->prev;
    else last_node = (*head_ref);
    while (last_node->prev) last_node = last_node->prev;

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data = new_data;
    new_node->next = last_node;
    new_node->prev = NULL;

    last_node->prev = new_node;
}

int detect_element_in_array(int* array, int arr_length, int desired)
{
    for (int i = 0; i < arr_length; i++)
    {
        if (array[i] == desired) return 1;
    }
    return 0;
}

int detect_element_in_list(struct Node* element, int desired)
{
    struct Node* node;
    if (element->next != NULL) node = element->next;
    else node = element;
    while (node->next) node = node->next;

    while (node != NULL)
    {
        if (node->data == desired)
        {
            //element deteceted in the queue
            return 1;
        }
        node = node->prev;
    }

    //element not detected in the queue
    free(node);
    return 0;
}


int** breadth_first_search(HWND hWnd, int **matrix)
{
    printf("\nBFS:");

    int output[n] = {};
    struct Node* my_queue = NULL;
    int visited[n] = {};

    int** traversal_tree_matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) traversal_tree_matrix[i] = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            traversal_tree_matrix[i][j] = 0;
        }
    }

    output[0] = 0;
    add_with_head_shift(&my_queue, 0); // ads 0 vertex to the queue
    visited[0] = 0;

    int noe = 1; //number of output elements
    while (my_queue != NULL)
    {
        if (MessageBox(hWnd, "OK.", "OK", MB_OK))
        {
            printf("\n\nexamining vertex %d\n\n", my_queue->data + 1);

            recolor_vertex(my_queue->data, 0, 200, 0);
            if (my_queue->next != NULL) recolor_vertex(my_queue->next->data, 100, 100, 100);
        }
        for (int j = 0; j < n; j++)
        {
            if (
                    matrix[my_queue->data][j] == 1
                    && !detect_element_in_list(my_queue, j)
                    )
            {
                add_without_headshift(&my_queue, j);

                highlight_connection(my_queue->data, j);

                output[noe] = j;
                traversal_tree_matrix[my_queue->data][j] = 1;
                noe++;

                printf("connection with element %d found\n", j + 1);
            }
        }
        my_queue = my_queue->prev;
    }

    printf("\nBFS output: ");
    for (int i = 0; i < n; i++)
    {
        printf(" %d ", output[i] + 1);
    }

    printf("\n\nTraversal tree matrix (BFS):\n");
    print_int_matrix(traversal_tree_matrix, n);

    return traversal_tree_matrix;
}

int** depth_first_search(HWND hWnd, int **matrix)
{
    printf("\n\n\nDFS:");

    int** search_tree = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) search_tree[i] = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            search_tree[i][j] = 0;
        }
    }

    int output[n] = {};
    struct Node* my_stack = NULL;

    output[0] = 0;
    add_with_head_shift(&my_stack, 0); // ads 0 vertex to the queue

    int noe = 1; //number of output elements
    while (my_stack != NULL)
    {
        if (MessageBox(hWnd, "OK.", "OK", MB_OK))
        {
            printf("\nexamining vertex %d\n", my_stack->data + 1);

            if (my_stack->prev == NULL)
            {
                recolor_vertex(my_stack->data, 0, 200, 0);
                if (my_stack->next != NULL) recolor_vertex(my_stack->next->data, 100, 100, 100);
            }
            else
            {
                recolor_vertex(my_stack->data, 0, 200, 0);
                recolor_vertex(my_stack->prev->data, 100, 100, 100);
            }
        }
        for (int j = 0; j < n; j++)
        {
            if (
                    matrix[my_stack->data][j] == 1
                    && !detect_element_in_array(output, n, j)
                    )
            {
                highlight_connection(my_stack->data, j);
                search_tree[my_stack->data][j] = 1;

                add_with_head_shift(&my_stack, j);

                output[noe] = j;
                noe++;

                printf("connection with element %d found\n", j + 1);

                break;
            }
            else if(j == n - 1) my_stack = my_stack->next;
        }
    }

    printf("\nDFS output: ");
    for (int i = 0; i < n; i++)
    {
        printf(" %d ", output[i] + 1);
    }

    printf("\n\nTraversal tree matrix (DFS):\n");
    print_int_matrix(search_tree, n);

    return search_tree;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
    switch(messg)
    {
        case WM_PAINT:
            srand(0423);

            double** T;
            int** A;

            T = randm();
            A = mulmr(( 1.0 - 2 * 0.01 - 3 * 0.005 - 0.15), T);

            printf("Adjacency matrix:\n");
            print_int_matrix(A, n);

            hdc = BeginPaint(hWnd, &ps);
            draw_graph(A, a, window_width / 3, window_height / 2);

            //depth_first_search(hWnd, A);
            draw_graph(
                    breadth_first_search(hWnd, A),
                    a * 0.45,
                    window_width * 0.77,
                    window_height * 0.25
            );
            TextOut(
                    hdc,
                    window_width * 0.77 - a  * 0.22,
                    window_height * 0.22 - a * 0.22,
                    "BFS:",
                    4
            );

            //reset graph outlook
            if (MessageBox(hWnd, "Reset.", "OK", MB_OK))
                draw_graph(A, a, window_width / 3, window_height / 2);

            //depth_first_search(hWnd, A);
            draw_graph(
                    depth_first_search(hWnd, A),
                    a * 0.45,
                    window_width * 0.77,
                    window_height * 0.7
            );
            TextOut(
                    hdc,
                    window_width * 0.77 - a * 0.22,
                    window_height * 0.7 - a * 0.22,
                    "DFS:",
                    4
            );

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
