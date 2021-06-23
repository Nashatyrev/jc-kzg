# JC-KZG
Java wrapper around C-KZG library: 
https://github.com/benjaminion/c-kzg/

# Repository 
The repository contains two submodules, so they need to be checked out
```shell script
> git clone <JC-KZZG repo>
> cd jc-kzg
> git submodule init
> git submodule update
```
# Building

### Building native part
- [Windows](doc/build-win.md)
- [Linux](doc/build-linux.md)
- [MacOS](doc/build-macos.md)

### Testing the build

```shell script
> ./gradlew build 
```

The test(s) should pass:
```
> Task :test

JcKZGTest > proofSingle() PASSED

```

### Building JAR 

```shell script
> ./gradlew jar
```

### Publishing artifact locally 
```shell script
> ./gradlew publishToMavenLocal
```

# Dependency 

```xml
<dependency>
  <groupId>tech.pegasys</groupId>
  <artifactId>jc-kzg</artifactId>
  <version>0.1.0-RELEASE</version>
</dependency>
```

# Supported platforms
- x86-64
  - Windows (tested on Win 10)
  - Linux (tested on Ubuntu 18.04)
  - MacOS (tested on 10.15.7 Catalina)
