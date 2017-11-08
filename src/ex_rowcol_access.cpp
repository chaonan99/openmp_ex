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
    auto ary = new int*[n];
    for (int i = 0; i < n; ++i)
    {
        ary[i] = new int[n];
        for (int j = 0; j < n; ++j)
        {
            ary[i][j] = dist(mt);
        }
    }

    double sum = 0.0;
    t1 = omp_get_wtime();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            sum += ary[i][j];
        }
    }
    t2 = omp_get_wtime();
    printf("%d %f ", n, t2 - t1);
    sum = 0;
    t1 = omp_get_wtime();
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < n; ++i)
        {
            sum += ary[i][j];
        }
    }
    t2 = omp_get_wtime();
    printf("%f\n",t2 - t1);
}
