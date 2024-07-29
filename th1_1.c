#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void init_h();

void init_h2();

void init_h3();

int estimator(int stream[], int n);

int f2(int arr[], int n);

void generate(int n);

int stream[100000];

int harray[100][10000];

int U = 100;

int f[100];

int main()
{
    srand(time(NULL));
    int u[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // int z = 0;
    // for (int i = 0; i < sizeof(stream)/sizeof(int); i++) {
    //     z += h(stream[i]);
    // }
    init_h();
   // int n = sizeof(stream) / sizeof(stream[0]);
    int n;
    n = 1000;
    generate(n);
    printf("estimate: %d\n", estimator(stream, n));
    printf("f2: %d\n", f2(stream, n));
}

void init_h()
{
    for (int i = 0; i < 10000; i++)
    {
        for (int j = 0; j < U; j++)
        {
            harray[j][i] = rand() % 2 == 0 ? -1 : 1;
        }
    }
}

int estimator(int stream[], int n)
{
    int z = 0;
    int z2 = 0;
    for (int i = 0; i < 10000; i++)
    {
        z = 0;
        for (int j = 0; j < n; j++)
        {
            z += harray[stream[j]][i];
        }
        z2 += z * z;
    }
    return z2 / 10000;
}

int f2(int arr[], int n)
{
    for (int i = 0; i < U; i++)
    {
        f[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        f[arr[i]]++;
    }
    int f2 = 0;
    for (int i = 0; i < U; i++)
    {
        f2 += (f[i] * f[i]);
    }
    return f2;
}

void generate(int n)
{
    if (n > 10000)
    {
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        stream[i] = rand() % U;
    }
}
