//
// Created by chaonan99 on 11/4/17.
//

#include <cstdio>
#include <cstdlib>
#include <algorithm>
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

    auto a = new int*[n];
    for (int i = 0; i < n; ++i)
    {
        a[i] = new int[n];
        for (int j = 0; j < n; ++j)
        {
            a[i][j] = dist(mt);
        }
    }
    auto b = new int*[n];
    for (int i = 0; i < n; ++i)
    {
        b[i] = new int[n];
    }

    printf("%d ", n);

    // This is a pre-access step just to make sure each experiment
    // has the same cache state in the beginning. This may be optimized
    // in some level of compiler optimization.
    t1 = omp_get_wtime();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            b[j][i] = a[i][j];
    t2 = omp_get_wtime();

    t1 = omp_get_wtime();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            b[j][i] = a[i][j];
    t2 = omp_get_wtime();
    printf("%f ", t2 - t1);

    int bsize = 128;
    t1 = omp_get_wtime();
    for (int j1 = 0; j1 < n; j1+=bsize)
        for (int i = 0; i < n; ++i)
            for (int j2 = 0; j2 < std::min(n-j1, bsize); ++j2)
                b[j1+j2][i] = a[i][j1+j2];
    t2 = omp_get_wtime();
    printf("%f ", t2 - t1);

    // Another pre-access
    t1 = omp_get_wtime();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            b[j][i] = a[i][j];
    t2 = omp_get_wtime();

    bsize = 64;
    t1 = omp_get_wtime();
    for (int j1 = 0; j1 < n; j1+=bsize)
        for (int i = 0; i < n; ++i)
            for (int j2 = 0; j2 < std::min(n-j1, bsize); ++j2)
                b[j1+j2][i] = a[i][j1+j2];
    t2 = omp_get_wtime();
    printf("%f\n", t2 - t1);
}
