#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

void basic_prime_gen(int **arr, int start, int upto);
bool basic_is_prime(int value);
void better_prime_gen(int **arr, int start, int upto);
bool better_is_prime(int value);
bool cached_is_prime(int **cache, int value);
void cached_prime_gen(int **cache, int **arr, int start, int upto);
void eratosthenes_prime_gen(int **results, int n);
void pritchard_prime_gen(int **results, int n);
void pritchard_delete(int length, int p, int **W);
void pritchard_extend(int *length, int **W, int n);
bool contains_in_arr(int *arr, int value);
int *array_union(int *a, int *b);
int next(int *W, int current);
int prev(int *W, int current);
void atkin_prime_gen(int **results, int limit);
void sundaram_prime_gen(int **results, int n);

int main()
{
    printf("Starting tests!\n");

    clock_t start_time;
    clock_t end_time;

    int start = 2;
    const int upto = 80 * 1000;

    int *arr = NULL;
    int *cache = NULL;

    start_time = clock();
    basic_prime_gen(&arr, start, upto);
    end_time = clock();
    printf("basic: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    //

    arr = NULL;
    start_time = clock();
    better_prime_gen(&arr, start, upto);
    end_time = clock();
    printf("better: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    //

    arr = NULL;
    start_time = clock(); // Get the current time
    cached_prime_gen(&cache, &arr, start, upto);
    end_time = clock(); // Get the current time
    printf("cached: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    //

    int *results = NULL;
    start_time = clock();
    eratosthenes_prime_gen(&results, upto);
    end_time = clock();
    printf("eratosthenes: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    //

    results = NULL;
    start_time = clock();
    pritchard_prime_gen(&results, upto);
    end_time = clock();
    printf("pritchard: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    //

    results = NULL;
    start_time = clock();
    atkin_prime_gen(&results, upto);
    end_time = clock();
    printf("atkin: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    //

    results = NULL;
    start_time = clock();
    sundaram_prime_gen(&results, upto);
    end_time = clock();
    printf("sundaram: %f seconds\n", (double)(end_time - start_time) / CLOCKS_PER_SEC);

    return 0;
}

void basic_prime_gen(int **arr, int start, int upto)
{
    for (int i = start; i <= upto; i++)
    {
        if (basic_is_prime(i))
        {
            arrput(*arr, i);
        }
    }
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

void better_prime_gen(int **arr, int start, int upto)
{
    for (int i = start; i <= upto; i++)
    {
        if (better_is_prime(i))
        {
            arrput(*arr, i);
        }
    }
}

bool better_is_prime(int value)
{
    if (value < 2) {return false;}

    for (int i = 2; i*i <= value; i++)
    {
        if (value % i == 0)
        {
            return false;
        }
    }
    return true;
}

void cached_prime_gen(int **cache, int **arr, int start, int upto)
{
    for (int i = start; i <= upto; i++) {
        if(cached_is_prime(cache, i)) {
            arrput(*arr,i);
        }
    }
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

// sieve of eratosthenes
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

    for (int i = 2.0; i * i <= n; i++)
    {
        if (A[(int)i] == true)
        {
            for (double j = i * i; j <= n; j += i)
            {
                A[(int)j] = false;
            }
        }
    }

    for (int i = 0; i <= n; i++)
    {
        int v = A[i];
        if (v == true)
        {
            arrput(*results, i);
        }
    }
}

void pritchard_prime_gen(int **results, int n)
{
    if (n < 2)
        return;

    // W contains current candidates that haven't been eliminated yet.
    // length = minimum of Pk,N

    int k = 1;

    int *W = NULL;
    arrput(W, 1);

    int length = 2;
    int p = 3;      // p = pk+1 (p is always the next prime we are about to process)
    int *Pr = NULL; // Pr = the primes up to pk(primes we have found already)
    arrput(Pr, 2);

    while (p * p <= n)
    {
        if (length < n)
        {
            // extend W, length to minimum of p*length, N;
            pritchard_extend(&length, &W, n);
        }
        // delete multiples of p from W;
        pritchard_delete(length, p, &W);
        arrput(Pr, p); // insert p into Pr
        k = k + 1;
        p = next(W, 1); // next(W, 1)
    }
    if (length < n)
    {
        // extend W, length to N;
        pritchard_extend(&length, &W, n);
    }

    int len_W = arrlen(W);
    int len_Pr = arrlen(Pr);
    int *arr_to_use = NULL;
    int *other_array = NULL;
    if (len_W > len_Pr)
    {
        arr_to_use = W;
        other_array = Pr;
    }
    else
    {
        arr_to_use = Pr;
        other_array = W;
    }

    // return union of Pr and W - {1}
    int *final = array_union(Pr, W);

    // remove the 1
    for (int i = 0; i < arrlen(final); i++)
    {
        if (final[i] == 1)
        {
            arrdel(final, i);
            break;
        }
    }

    *results = final;
}

void pritchard_extend(int *length, int **W, int n)
{
    // {in: W = Wk and length = Pk and n > length}
    // {out: W = Wk → n and length = n}

    int w = 1;
    int x = *length + 1;

    while (x <= n)
    {
        arrput((*W), x); // Insert x into W
        w = next(*W, w); // next(W,w);
        x = *length + w;
    }
    *length = n;
}

void pritchard_delete(int length, int p, int **W)
{
    int w;
    w = p;
    while (p * w <= length)
    {
        w = next(*W, w); // next(W,w);
    }
    while (w > 1)
    {
        w = prev(*W, w); // prev(W, w);
        // remove p*w from W;
        for (int i = 0; i < arrlen(*W); i++)
        {
            if ((*W)[i] == p * w)
            {
                arrdel(*W, i);
                break;
            }
        }
    }
}

bool contains_in_arr(int *arr, int value)
{
    for (int i = 0; i < arrlen(arr); i++)
    {
        if (arr[i] == value)
        {
            return true;
        }
    }
    return false;
}

int *array_union(int *a, int *b)
{
    int *result = NULL;

    // add elements from a
    for (int i = 0; i < arrlen(a); i++)
    {
        arrput(result, a[i]);
    }

    // add elements from b if they dont exist
    for (int i = 0; i < arrlen(b); i++)
    {
        if (!contains_in_arr(result, b[i]))
        {
            arrput(result, b[i]);
        }
    }
    return result;
}

int next(int *W, int current)
{
    for (int i = 0; i < arrlen(W); i++)
    {
        if (W[i] == current && i + 1 < arrlen(W))
        {
            return W[i + 1];
        }
    }
    return -1;
}

int prev(int *W, int value)
{
    for (int i = 0; i < arrlen(W); i++)
    {
        if (W[i] == value && i - 1 >= 0)
        {
            return W[i - 1];
        }
    }
    return -1;
}

void atkin_prime_gen(int **results, int limit)
{
    if (limit < 2)
    {
        return;
    }

    bool *arr = NULL;
    arrsetlen(arr, limit + 1);
    for (int i = 0; i < arrlen(arr); i++)
    {
        arr[i] = false;
    }

    if (limit > 2)
    {
        arr[2] = true;
    }
    if (limit > 3)
    {
        arr[3] = true;
    }

    // check for 3 conditions
    for (int x = 1; x * x <= limit; x++)
    {
        for (int y = 1; y * y <= limit; y++)
        {
            // condition 1
            int n = (4 * x * y) + (y * y);
            if (n <= limit && (n % 12 == 1 || n % 12 == 5))
            {
                arr[n] = !arr[n];
            }

            // condition 2
            n = (3 * x * x) + (y * y);
            if (n <= limit && n % 12 == 7)
            {
                arr[n] = !arr[n];
            }

            // condition 3
            n = (3 * x * x) - (y * y);
            if (x > y && n <= limit && n % 12 == 11)
            {
                arr[n] = !arr[n];
            }
        }
    }

    // mark all multiples of squares as non-prime
    for (int i = 5; i * i <= limit; i++)
    {
        if (arr[i] == false)
        {
            continue;
        }
        for (int j = i * i; j <= limit; j += i * i)
        {
            arr[j] = false;
        }
    }

    // store all prime numbers
    int *primes = NULL;
    for (int i = 2; i <= limit; i++)
    {
        if (arr[i] == true)
        {
            arrput(primes, i);
        }
    }
    *results = primes;
}

void sundaram_prime_gen(int **results, int n)
{
    if (n < 2)
    {
        return;
    }
    int k = (n - 2) / 2;

    bool *marked = NULL;
    arrsetlen(marked, k + 1);
    for (int i = 0; i < arrlen(marked); i++)
    {
        marked[i] = false;
    }

    for (int i = 1; i < k + 1; i++)
    {
        int j = i;
        while (i + j + 2 * i * j <= k)
        {
            marked[i + j + 2 * i * j] = true;
            j += 1;
        }
    }

    int *primes = NULL;
    if (n >= 2)
    {
        arrput(primes, 2);
    }

    for (int i = 1; i < k + 1; i++)
    {
        if (!marked[i])
        {
            arrput(primes, 2 * i + 1);
        }
    }

    *results = primes;
}