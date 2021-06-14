Linux:
========
Prerequisites: 
  - CLang 6.0
  - SWIG 4.x
  - JDK 11

```shell script
# build blst.lib
> cd <repo-dir>/build.native
> ../blst/build.sh

# build C-KZG static library
> cd <repo-dir>/c-kzg/src/
> make CFLAGS="-I../../blst/bindings -fPIC" lib
> mv libckzg.a ../../build.native/
    
# generate C++ and Java SWIG wrappers
> cd <repo-dir>
> swig -c++ -java -outdir src/generated/java/tech/pegasys/jckzg/swig -o src/generated/cpp/jc-kzg.cpp -Isrc/main/cpp -package tech.pegasys.jckzg.swig src/main/swig/jc-kzg.swg

# build JC-KZG shared library
> cd <repo-dir>/build.native
> export JDK_DIR=<JDK directory containing 'include' subdirectory>
> clang -O -fPIC -I../c-kzg/src -I../blst/bindings -I../src/main/cpp -I$JDK_DIR/include -I$JDK_DIR/include/linux -c ../src/generated/cpp/jc-kzg.cpp
# linking to libjc-kzg.so
> clang -Wl,--whole-archive -shared -o ../src/generated/resources/x86_64/libjc-kzg.so -L. -lblst -lckzg jc-kzg.o -Wl,--no-whole-archive
```
