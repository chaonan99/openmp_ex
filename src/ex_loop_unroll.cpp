//
// Created by chaonan99 on 11/4/17.
//

#include <cstdio>
#include <cstdlib>
#include <string>
#include <random>
#include <omp.h>

int main(int argc, char *argv[])
{
    int n = 1000;
    double t1, t2;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 100);

    if (argc > 1)
    {
        n = std::stoi(argv[1]);
    }

    n = n*60;

    auto a = new int[n];
    auto b = new int[n];
    auto c = new int[n];

    for (int i = 0; i < n; ++i)
    {
        a[i] = 0;
        b[i] = dist(mt);
        c[i] = 0;
    }

    t1 = omp_get_wtime();
    for (int i = 1; i < n; i++)
    {
        a[i] = b[i] + 1;
        c[i] = a[i-1] + a[i] + b[i-1];
    }
    t2 = omp_get_wtime();
    printf("%d %f ", n, t2 - t1);

    for (int i = 0; i < n; i++)
    {
        a[i] = 0;
        c[i] = 0;
    }
    t1 = omp_get_wtime();
    for (int i = 1; i < n; i+=2)
    {
        a[i] = b[i] + 1;
        c[i] = a[i-1] + a[i] + b[i-1];
        a[i+1] = b[i+1] + 1;
        c[i+1] = a[i] + a[i+1] + b[i];
    }
    t2 = omp_get_wtime();
    printf("%f ", t2 - t1);

    for (int i = 0; i < n; i++)
    {
        a[i] = 0;
        c[i] = 0;
    }
    t1 = omp_get_wtime();
    for (int i = 1; i < n; i+=3)
    {
        a[i] = b[i] + 1;
        c[i] = a[i-1] + a[i] + b[i-1];
        a[i+1] = b[i+1] + 1;
        c[i+1] = a[i] + a[i+1] + b[i];
        a[i+2] = b[i+2] + 1;
        c[i+2] = a[i+1] + a[i+2] + b[i+1];
    }
    t2 = omp_get_wtime();
    printf("%f\n", t2 - t1);
}
