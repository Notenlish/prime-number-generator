# prime-number-generator
I first tried this in Zig but didnt understand anything so now its using C.

It generated primes.

## Building
I use zig cc to build

You need to install [zig](https://ziglang.org/).

make sure zig is added to the PATH(ie the zig command works when you type it in a terminal). 

run the `build.py` script to build the code.

for windows:
`py build.py`
for linux:
`python3 build.py`

### Cross Compiling

The build script takes care of this.


## Graph

To graph the data you need to run the graph.py script. The required dependencies are matplotlib and numpy.

Use this to install the dependencies. 

`pip install matplotlib numpy`

if you dont want to pollute your global environment or you are on Mac/Linux do this:

```
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
```

## Optimization

The "better" algorithm is optimized by changing the function for checking whether something is a prime. Instead of checking for every value from 2 to v, I instead check every value from 2 to square root of v. For n = 250k the better algorithm is roughly 90x faster.

I also tried caching but that was actually slower than the "better" algorithm.

Also the original "basic" and "cached" algorithms were using recursion which just led to the program terminating randomly after n was like 80k which was a problem. Appearently C does not like recursion very much. I had to convert the recursion into a normal function.

Pritchard's Sieve was really slow because I tried to translate the pseudocode to C but the way I setup the next/prev functions and some other stuff like me using arrdel led it to being really slow. Now its faster thankfully.

I didnt record how fast certain algorithms were before changing them but Pritchards sieve was like 6s for like 160k items or smth, and now its 0.22 seconds so a lot faster ig.

Peak mem usage is 51mb with 6% cpu(the code is single threaded) for me.


## Some Useful Links
https://en.wikipedia.org/wiki/Sieve_of_Pritchard

https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

https://en.wikipedia.org/wiki/Sieve_of_Atkin ( converted from java to c)

https://en.wikipedia.org/wiki/Sieve_of_Sundaram ( python to c)


# Testing
Just run the code.

Change the `upto` variable in the code for different limit values, that way you can check how algorithms scale.

There is also a graph.py which will visualize it, but you need to put the data in there manually.


## License

MIT
the stb_ds.h code is in public domain data structures - Sean Barrett 2019