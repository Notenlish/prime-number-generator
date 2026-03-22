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


## Some Useful Links
https://en.wikipedia.org/wiki/Sieve_of_Pritchard

https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

https://en.wikipedia.org/wiki/Sieve_of_Atkin ( converted from java to c)

https://en.wikipedia.org/wiki/Sieve_of_Sundaram ( python to c)


# Testing
Just run the code.

Change the `upto` variable in the code for different limit values, that way you can check how algorithms scale.

There is also a graph.py which will visualize it, but you need to put the data in there manually.
