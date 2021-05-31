# ofxCnpy
An openFrameworks addon to use @rogersce 's cnpy library (https://github.com/rogersce/cnpy)
Addon part is class-free implementation (using struct to implement NpyExport & NpzExport).

## you need to get the rogersce/cnpy library as a submodule
```
git submodule init && git submodule update
```

## warnings
- NPY exporting mode consumes a lot of memory space! You need to design your code properly so that you can prevent system crash.

### created by
Ryo Hajika (Empathic Computing Laboratory / imaginaryShort)
