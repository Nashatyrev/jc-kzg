#!/usr/bin/env sh

if [ ! -d "$JDK_DIR/include/jni.h" ]; then
  echo "The env variable JDK_DIR is not set or invalid: $JDK_DIR"
  exit -1
fi

REPO_DIR=$(dirname "$0")/../../..

# build blst.lib
cd $REPO_DIR/build.native
../blst/build.sh

# build C-KZG static library
cd $REPO_DIR/c-kzg/src/
make CFLAGS="-I../../blst/bindings -fPIC" lib
mv libckzg.a ../../build.native/

# generate C++ and Java SWIG wrappers
cd $REPO_DIR
swig -c++ -java -outdir src/generated/java/tech/pegasys/jckzg/swig -o src/generated/cpp/jc-kzg.cpp -Isrc/main/cpp -package tech.pegasys.jckzg.swig src/main/swig/jc-kzg.swg

# build JC-KZG shared library
cd $REPO_DIR/build.native
clang -O -fPIC -I../c-kzg/src -I../blst/bindings -I../src/main/cpp -I$JDK_DIR/include -I$JDK_DIR/include/linux -c ../src/generated/cpp/jc-kzg.cpp
# linking to libjc-kzg.so
clang -Wl,--whole-archive -shared -o ../src/generated/resources/x86_64/libjc-kzg.so -L. -lblst -lckzg jc-kzg.o -Wl,--no-whole-archive
