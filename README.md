# Nonstandard C++ Library


An educational project that reimplements selected parts of the C++ standard library.

## Requirements

- a C++20-compatible compiler;
- CMake 3.16 or newer;
- GoogleTest.

## Build

```bash
git clone https://github.com/plotnikovms/nonstandard-cpp-library.git
cd nonstandard-cpp-library
cmake -S . -B build
cmake --build build
```

The shared library is created in the `build` directory.

## Run tests

```bash
./build/nstd_tests
```

Tests are written with GoogleTest. They are also built and run automatically by GitHub Actions after every push.

## Project structure

```text
include/    Public headers
src/        Source files compiled into the nstd shared library
tests/      GoogleTest test files
.github/    GitHub Actions workflow
```

This project is written for educational purposes and is not intended to replace the standard library in production code.
