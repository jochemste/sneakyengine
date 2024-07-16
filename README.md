# SneakyEngine

Work in progress!

## Build

Currently, the pipeline builds for both Linux and Windows systems, although the main
target platform is Linux and development happens on Debian based systems, using CMake
and GCC. This means that Windows builds are only compiled by the pipeline at the moment
and might have more hidden issues/warnings/etc (feel free to improve it!). Currently tests
also fail on Windows.

- Create a build directory

```
mkdir build && cd build
```

- Run CMake to configure the build

```
cmake ..
```

- Compile

```
cmake --build ./
```

- Test

```
ctest --test-dir test --output-on-failure
```

