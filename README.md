# prime-number-generator
I first tried this in Zig but didnt understand anything so now its using C.

It generated primes.

## Building
I use zig cc to build

You need to install [zig](https://ziglang.org/).

and use this to build:

```
cd src
zig cc main.c -o main.exe 
```

dont add .exe if you're not on windows.

### Cross Compiling

To cross compile you need to add this argument:
`-target [platform]`

available platforms:
```
aarch64-windows-gnu
x86_64-windows-gnu
x86_64-windows-msvc
x86_64-linux-gnu
aarch64-linux-gnu
x86_64-macos
aarch64-macos
```

to run it just do this: `./[name of executable]`



## Some Useful Links
https://en.wikipedia.org/wiki/Sieve_of_Pritchard

https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

https://en.wikipedia.org/wiki/Sieve_of_Atkin ( converted from java to c)

https://en.wikipedia.org/wiki/Sieve_of_Sundaram ( python to c)


# Testing
Just run the code.

Change the `upto` variable in the code for different limit values, that way you can check how algorithms scale.

There is also a graph.py which will visualize it, but you need to put the data in there manually.
