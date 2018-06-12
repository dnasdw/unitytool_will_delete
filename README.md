# unitytool

An all-in-one tool for extracting/creating unity assets.

## Platforms

- Windows
- Linux
- macOS

## Building

### Dependencies

- cmake

### Compiling

- make 64-bit version
~~~
mkdir build
cd build
cmake -DUSE_DEP=OFF ..
make
~~~

- make 32-bit version
~~~
mkdir build
cd build
cmake -DBUILD64=OFF -DUSE_DEP=OFF ..
make
~~~

### Installing

~~~
make install
~~~

## Usage

~~~
unitytool [option...] [option]...
~~~
