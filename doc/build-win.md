Windows:
========
Prerequisites: 
  - MSVC 2019 (Community edition) + "C++ Clang tools for Windows" component
  - SWIG 4.x
  - JDK 11

Run `x64 Native Tools Command Prompt for VS 2019` (`cmd.exe` with correctly set MSVC `%PATH%`)

```cmd
:: build blst.lib
> cd <repo-dir>
> cd build.native
> ..\blst\build.bat

:: generate C++ and Java SWIG wrappers
> cd ..
> swig.exe -c++ -java -outdir src\generated\java\tech\pegasys\jckzg\swig -o src\generated\cpp\jc-kzg.cpp -Isrc\main\cpp -package tech.pegasys.jckzg.swig src\main\swig\jc-kzg.swg

:: build DLL
> set JDK_DIR=<JDK directory containing 'include' subdirectory>
> devenv msvc\jc-kzg.sln /Build Release
> copy build.native\Release\jc-kzg.dll src\generated\resources\x86_64
```
