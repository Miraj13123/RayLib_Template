## to make cmake cach (without downloading lib)
cmake -S . -B bin -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++

## to download dependency
cmake -S . -B bin -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++ -DDEPENDENCY_UPDATE=ON

## to build
cmake --build bin

## to run:
```
cd bin
```

```
app.exe
```