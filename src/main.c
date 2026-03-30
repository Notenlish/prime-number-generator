#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h> // used for system calls
#include <sys/stat.h>

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h> // for nanosleep
#else
#include <unistd.h> // for usleep
#endif


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
void atkin_prime_gen(int **results, int limit);
void sundaram_prime_gen(int **results, int n);
void display_graph();

void sleep_ms(int milliseconds) { // cross-platform sleep function
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    if (milliseconds >= 1000)
        sleep(milliseconds / 1000);
    usleep((milliseconds % 1000) * 1000);
#endif
}


int main()
{
    printf("Starting tests! Running from n=10k to n=1 million.\n");
    sleep_ms(500);
    printf("*PLEASE* make sure python is installed and accessible via PATH(ie it works when you type py on windows and python3 on mac/linux). Otherwise there could be errors.\n");
    sleep_ms(4000);

    FILE *fptr;
    fptr = fopen("results.csv", "w");
    fprintf(fptr, "upto,basic,better,cached,eratosthenes,pritchard,atkin,sundaram\n");

    clock_t start_time;
    clock_t end_time;

    int uptoArr[] = {
        10 * 1000,
        50 * 1000,
        100 * 1000,
        250 * 1000,
        500 * 1000,
        1 * 1000 * 1000
    };

    for (int u = 0; u < (sizeof(uptoArr) / sizeof(uptoArr[0])); u++)
    {
        double times[7] = {0, 0, 0, 0, 0, 0, 0};
        double time_taken = 0;

        int start = 2;
        const int upto = uptoArr[u];
        int *arr = NULL;
        int *cache = NULL;

        printf("Starting test for n=%d\n", upto);

        //  ---------------------------------  //

        start_time = clock();
        basic_prime_gen(&arr, start, upto);
        end_time = clock();
        time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("basic: %f seconds\n", time_taken);
        times[0] = time_taken;

        //

        arr = NULL;
        start_time = clock();
        better_prime_gen(&arr, start, upto);
        end_time = clock();
        time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("better: %f seconds\n", time_taken);
        times[1] = time_taken;

        //

        arr = NULL;
        start_time = clock(); // Get the current time
        cached_prime_gen(&cache, &arr, start, upto);
        end_time = clock(); // Get the current time
        time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("cached: %f seconds\n", time_taken);
        times[2] = time_taken;

        //

        int *results = NULL;
        start_time = clock();
        eratosthenes_prime_gen(&results, upto);
        end_time = clock();
        time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("eratosthenes: %f seconds\n", time_taken);
        times[3] = time_taken;

        //

        results = NULL;
        start_time = clock();
        pritchard_prime_gen(&results, upto);
        end_time = clock();
        time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("pritchard: %f seconds\n", time_taken);
        times[4] = time_taken;

        //

        results = NULL;
        start_time = clock();
        atkin_prime_gen(&results, upto);
        end_time = clock();
        time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("atkin: %f seconds\n", time_taken);
        times[5] = time_taken;

        //

        results = NULL;
        start_time = clock();
        sundaram_prime_gen(&results, upto);
        end_time = clock();
        time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("sundaram: %f seconds\n", time_taken);
        times[6] = time_taken;

        printf("Test run for n=%d over.\n", upto);
        printf("Writing results to csv.\n");

        fprintf(fptr, "%d,", upto);  // %d = format int
        int totalResultsLength = sizeof(times) / sizeof(times[0]);
        for (int f = 0; f < totalResultsLength; f++)
        {
            fprintf(fptr, "%.6f", times[f]);
            if (f < totalResultsLength -1) {
                fprintf(fptr, ",");
            }
        }
        fprintf(fptr, "\n");
        printf("--------\n");
    }
    
    fclose(fptr);

    sleep_ms(500);
    printf("Tests are done! Now it will call python3 (py in windows) to display graphs. I hope you've already created an venv and installed matplotlib and numpy!! \n");
    sleep_ms(2500);

    display_graph();

    return 0;
}

void display_graph() {
    #ifdef _WIN32
        system("rmdir /s /q venv");  // delete venv
        system("py -m venv venv");
        system("venv\\Scripts\\python -m pip install -r requirements.txt");
        system("venv\\Scripts\\python graph.py");
    #elif __APPLE__ || __linux__
        system("rm -rf venv");  // delete broken venv
        system("python3 -m venv venv");
        system("source venv/bin/activate");
        system("venv/bin/python3 -m pip install -r requirements.txt");
        system("venv/bin/python3 graph.py");
    #else
        printf("Unsupported OS\n");
    #endif
    sleep_ms(500);
    printf("Done! It should already have created a graph.png image in the current working directory.\n");
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
    if (value < 2)
    {
        return false;
    }

    for (int i = 2; i * i <= value; i++)
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
    for (int i = start; i <= upto; i++)
    {
        if (cached_is_prime(cache, i))
        {
            arrput(*arr, i);
        }
    }
}

bool cached_is_prime(int **cache, int value)
{
    if (value < 2)
    {
        return false;
    }

    for (int i = 2; i * i <= value; i++)
    {
        // ensure cache has info for i
        if (i - 2 >= arrlen(*cache))
        {
            // compute primality of i and store it
            bool is_prime = true;
            for (int j = 2; j * j <= i; j++)
            {
                if (i % j == 0)
                {
                    is_prime = false;
                    break;
                }
            }
            arrput(*cache, is_prime);
        }

        // if i is prime, test if it can be divided
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

    // use bool arr instead of int. W[x] == true means its a candidate
    bool *W = NULL;
    arrsetlen(W, n + 1);
    for (int i = 0; i < (n + 1); i++)
    {
        W[i] = false;
    }
    W[1] = true;

    int length = 2;
    int p = 3;      // p = pk+1 (p is always the next prime we are about to process)
    int *Pr = NULL; // Pr = the primes up to pk(primes we have found already)
    arrput(Pr, 2);

    while (p * p <= n)
    {
        // step 2: extend W up to min(p * length, n)
        long long new_length_64bit = (long long)p * (long long)length;
        int new_length = (new_length_64bit > n) ? n : (int)new_length_64bit;

        for (int i = 1; i <= length; i++)
        {
            if (W[i]) // is candidate
            {
                for (int k = i; k <= new_length; k += length)
                {
                    W[k] = true;
                }
            }
        }

        length = new_length;

        // get rid of multiples of p
        for (int w = p; w * p <= length; w++)
        {
            if (W[w])
            {
                W[p * w] = false;
            }
        }

        arrput(Pr, p);

        // find next p(next element thats bigger than 1 in the W arr)
        int found = 0;
        for (int i = p + 1; i <= length; i++)
        {
            if (W[i])
            {
                p = i;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            break;
        }
    }

    if (length < n)
    {
        for (int i = 1; i <= length; i++)
        {
            if (W[i])
            {
                for (int k = i; k <= n; k += length)
                {
                    W[k] = true;
                }
            }
        }
        length = n;
    }

    int *final = NULL;

    for (int i = 2; i <= n; i++)
    {
        if (W[i])
        {
            arrput(final, i);
        }
    }

    // add missing primes from Pr
    for (int i = 0; i < arrlen(Pr); i++)
    {
        int v = Pr[i];
        bool exists = false;

        for (int j = 0; j < arrlen(final); j++)
        {
            if (final[j] == v)
            {
                exists = true;
                break;
            }
        }
        if (!exists)
        {
            arrput(final, v);
        }
    }

    *results = final;
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
        // fix overflow by using long long(forced 64bit)
        while ((long long)i + j + (long long)2 * i * j <= k)
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