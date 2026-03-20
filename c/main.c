#include <stdio.h>
#include <stdbool.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

void basic_prime_gen(int **arr, int start, int upto);
bool basic_is_prime(int value);
bool cached_is_prime(int **cache, int value);
void cached_prime_gen(int **cache, int **arr, int start, int upto);
void eratosthenes_prime_gen(int **results, int n);

int main()
{
    printf("Hello World!\n");

    int start = 2;
    const int upto = 1000000;

    int *arr = NULL;
    int *cache = NULL;

    //   cached_prime_gen(&cache, &arr, start, upto);

    //   basic_prime_algo(&arr, start, upto);

    // for (int i=0; i <= arrlen(arr); i++) {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n");

    int *results = NULL;
    eratosthenes_prime_gen(&results, upto);
    for (int i=0; i <= arrlen(results) -1; i++) {
        printf("%d ", results[i]);
    }
    printf("\n");


    return 0;
}

void basic_prime_gen(int **arr, int start, int upto)
{
    bool val_prime = basic_is_prime(start);
    if (val_prime)
    {
        arrput(*arr, start);
    }

    if (start > upto)
    {
        return;
    }
    basic_prime_gen(arr, start + 1, upto);
}

bool basic_is_prime(int value)
{
    int i = 2;
    while (i < value)
    {
        // divisible by i
        if ((value % i) == 0)
        {
            return false;
        }
        i += 1;
    }
    return true;
}

void cached_prime_gen(int **cache, int **arr, int start, int upto)
{
    bool val_prime = cached_is_prime(cache, start);
    if (val_prime)
    {
        arrput(*arr, start);
    }
    if (start == upto)
    {
        return;
    }
    cached_prime_gen(cache, arr, start + 1, upto);
}

bool cached_is_prime(int **cache, int value)
{
    if (value < 2)
        return false;

    for (int i = 2; i < value; i++)
    {
        // ensure cache has info for i
        if (i - 2 >= arrlen(*cache))
        {
            // compute primality of i and store it
            bool is_prime = true;
            for (int j = 2; j < i; j++)
            {
                if (i % j == 0)
                {
                    is_prime = false;
                    break;
                }
            }
            arrput(*cache, is_prime);
        }

        // if i is prime, test divisibility
        if ((*cache)[i - 2])
        {
            if (value % i == 0)
            {
                return false;
            }
        }
    }
    return true;
}

void eratosthenes_prime_gen(int **results, int n)
{
    // A an array of Boolean values, indexed by integers 2 to n, initially all set to true.
    int *A = NULL;

    for (int i = 0; i <= n; i++)
    {
        arrput(A, true);
    }
    A[0] = false;
    A[1] = false;

    for (int i=2.0; i*i <= n; i++) {
        if (A[(int)i] == true) {
            for (double j = i*i; j <= n; j += i) {
                A[(int)j] = false;
            }
        }
    }

    for (int i=0; i<=n; i++) {
        int v = A[i];
        if (v == true) {
            arrput(*results, i);
        }
    }
}
