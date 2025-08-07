## to make cmake cache
```bash
cmake -S . -B bin -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++
```

## Build Phase
```bash
cmake --build bin
```
### if librariesaren't downloaded
```bash
cmake --build bin --target updateDependency
```

## to run:
```
cd bin
```

```
app.exe
```