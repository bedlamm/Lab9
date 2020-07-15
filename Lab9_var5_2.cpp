#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct struct_type
{
    int deg;
    int k;
}struct_type;
void read_matr(int* pa[], int m, int n)
{
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            scanf_s("%d", &pa[i][j]);
}
int search(int d, struct_type* mas, int n)
{
    int i = 0;
    while (i < n && mas[i].deg != d)
        i++;

    if (i == n)
        i = EOF;
    return i;
}
struct_type* create_struct(int* pa[], int i, int n, int* l)
{
    struct_type* mas = (struct_type*)calloc(n, sizeof(struct_type));
    int m = 0;
    for (int j = 0; j < n; j++)
    {
        int s = search(pa[i][j], mas, m);
        if (s == EOF)
        {
            mas[m].k = 1;
            mas[m].deg = pa[i][j];
            m++;
        }
        else
            mas[s].k++;
    }
    *l = m;
    mas = (struct_type*)realloc(mas, (*l) * sizeof(struct_type));
    return mas;
}
int search_el(int d, int* b, int n)
{
    int i = 0;

    while (i < n && b[i] != d)
        i++;

    if (i == n)
        i = EOF;
    return i;
}
void write_el(int* b, int* k, struct_type* ptr, int l)
{
    int i;
    int m = *k;
    for (i = 0; i < l; i++)
    {
        if (ptr[i].k == 1)
        {
            int s = search_el(ptr[i].deg, b, l);
            if (s == EOF)
            {
                b[m] = ptr[i].deg;
                m++;
            }
        }
    }
    *k = m;
}
void print_mass(int* a, size_t m)
{
    int i;
    for (i = 0; i < m; i++)
    {
        printf("%d ", a[i]);
    }
}


void main()
{
    int n, m;
    int l;
    int k = 0;
    struct_type* ptr;
    setlocale(LC_ALL, "RUS");
    printf("Введите количество строк:");
    scanf_s("%d", &m);
    int** a = (int**)calloc(m, sizeof(int*));
    printf("Введите количество столбцов:");
    scanf_s("%d", &n);
    for (int i = 0; i < m; i++)
        a[i] = (int*)calloc(n, sizeof(int));
    printf("Введите элементы матрицы a размеры %d,%d\n", m, n);
    read_matr(a, m, n);
    int* b = (int*)calloc(m, n * sizeof(int));

    for (int i = 0; i < m; i++)
    {
        ptr = create_struct(a, i, n, &l);
        write_el(b, &k, ptr, l);
    }
    b = (int*)realloc(b, k * sizeof(int));
    printf("Результат программы:\n");
    print_mass(b, k);
    free(b);
    for (int i = 0; i < m; i++)
        free(a[i]);
    free(a);
}