#!/usr/bin/env sh
set -e

if [ ! -f "$JDK_DIR/include/jni.h" ]; then
  echo "The env variable JDK_DIR is not set or invalid: $JDK_DIR"
  exit
fi

REPO_DIR="$(pwd -P )"

if [ ! -d "$REPO_DIR/blst/src" ]; then
  echo "Git 'blst' submodule missing: $REPO_DIR/blst/src"
  exit
fi

if [ ! -d "$REPO_DIR/c-kzg/src" ]; then
  echo "Git 'c-kzg' submodule missing: $REPO_DIR/c-kzg/src"
  exit
fi

# build blst.lib
cd $REPO_DIR/build.native
../blst/build.sh -Wno-missing-braces

# build C-KZG static library
cd $REPO_DIR/c-kzg/src/
make CFLAGS="-I../../blst/bindings -fPIC" lib
mv libckzg.a ../../build.native/

# generate C++ and Java SWIG wrappers
cd $REPO_DIR
swig -c++ -java -outdir src/generated/java/tech/pegasys/jckzg/swig -o src/generated/cpp/jc-kzg.cpp -Isrc/main/cpp -package tech.pegasys.jckzg.swig src/main/swig/jc-kzg.swg

# build JC-KZG shared library
cd $REPO_DIR/build.native
clang++ -O -fPIC -I../c-kzg/src -I../blst/bindings -I../src/main/cpp -I$JDK_DIR/include -I$JDK_DIR/include/linux -I$JDK_DIR/include/darwin -c ../src/generated/cpp/jc-kzg.cpp
# linking to libjc-kzg.so
clang++ -shared -o ../src/generated/resources/x86_64/libjc-kzg.dylib -L. -lblst -lckzg jc-kzg.o
