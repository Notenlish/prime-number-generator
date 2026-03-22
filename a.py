from math import isqrt
 
def sieve_of_sundaram(n):
    if n < 3:
        if n < 2:
            return 0
        else:
            return 1    
    k = (n - 3) // 2 + 1

    integers_list = [True for i in range(k)]

    ops = 0

    for i in range((isqrt(n) - 3) // 2 + 1):
        if integers_list[i]: # adding this condition turns it into a SoE!
            p = 2 * i + 3
            s = (p * p - 3) // 2 # compute cull start

            for j in range(s, k, p):
                integers_list[j] = False
                ops += 1

    print("Total operations:  ", ops, ";", sep='')

    arr = []

    count = 1
    for i in range(k):
        if integers_list[i]:
            count += 1
            arr.append(i)

    print("Found ", count, " primes to ", n, ".", sep='')
    print(arr)

def sieve_of_sundaram_alt(n):
    k = (n - 2) // 2
    integers_list = [True] * (k + 1)
    for i in range(1, k + 1):
        j = i
        while i + j + 2 * i * j <= k:
            integers_list[i + j + 2 * i * j] = False
            j += 1
    if n > 2:
        print(2, end=" ")
    for i in range(1, k + 1):
        if integers_list[i]:
            print(2 * i + 1, end=" ")

def sieve_of_sundaram_alt2(n):
    if n < 2:
        return []

    k = (n - 2) // 2
    marked = [False] * (k + 1)

    for i in range(1, k + 1):
        j = i
        while i + j + 2*i*j <= k:
            marked[i + j + 2*i*j] = True
            j += 1

    primes = [2] if n >= 2 else []

    for i in range(1, k + 1):
        if not marked[i]:
            primes.append(2*i + 1)

    return primes


if __name__ == '__main__':
     sieve_of_sundaram_alt(2000)
     print("\n")
     sieve_of_sundaram(2000)
     print("\n")
     p = sieve_of_sundaram_alt2(2000)
     print(p)