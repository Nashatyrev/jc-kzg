# JC-KZG
Java wrapper around C-KZG library: 
https://github.com/benjaminion/c-kzg/

# Repository 
The repository contains two submodules, so they need to be checked out
```shell script
> git clone <JC-KZZG repo>
> git submodule init
> git submodule update
```
# Building

### Building native part
[Windows](doc/build-win.md)

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
  - Windows
