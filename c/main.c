#include <stdio.h>
#include <stdbool.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

void basic_prime_algo(int **arr, int start, int upto);
bool is_prime(int value);

int main() {
  printf("Hello World!\n");

  int start = 2;
  const int upto = 100;

  int *arr = NULL;
//   arrput(arr, upto);

  basic_prime_algo(&arr, start, upto);

    for (int i=0; i <= arrlen(arr); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

  return 0;
}

void basic_prime_algo(int **arr, int start, int upto) {
    bool val_prime = is_prime(start);
    if (val_prime) {
        arrput(*arr, start);
    }

    if (start == upto) {
        return;
    }
    basic_prime_algo(arr, start + 1, upto);
}

bool is_prime(int value) {
    int i = 2;
    while (i < value) {
        // divisible by i
        if ((value % i) == 0) {
            return false;
        }
        i += 1;
    }
    return true;
}
