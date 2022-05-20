# stdsharp

[![Build](https://github.com/BlurringShadow/stdsharp/actions/workflows/build.yml/badge.svg?branch=master)](https://github.com/BlurringShadow/stdsharp/actions/workflows/build.yml)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/f08b08ddd5e146c69b39ac5001f06c6a)](https://www.codacy.com/gh/BlurringShadow/stdsharp/dashboard?utm_source=github.com&utm_medium=referral&utm_content=BlurringShadow/stdsharp&utm_campaign=Badge_Grade)
[![wakatime](https://wakatime.com/badge/user/2f4337be-cbd2-4165-a44e-e1c8d69c1644/project/2b2bd608-f0ae-4ee1-90e4-5917a79ef74c.svg)](https://wakatime.com/badge/user/2f4337be-cbd2-4165-a44e-e1c8d69c1644/project/2b2bd608-f0ae-4ee1-90e4-5917a79ef74c)

Contains commonly used c++ code that not impl or well impl in other libs. This project aim to supplement the c++ standard library with fundamental features. Headers are arranged in accordance with the standard library structure.

## Getting Started

### Prerequisites

- **CMake v3.15+**

- **C++ Compiler** - needs to support at least the **C++20** and **partial C++23** standard, i.e. _MSVC_, _GCC_, _Clang_

- **Vcpkg or Other Suitable Dependencies Manager** - this project use vcpkg manifest to maintain dependencies. check the
  [vcpkg.json](vcpkg.json) for required dependencies

### Installing

- Clone the project to your source dir and use cmake to install.
- Or add [my vcpkg registry](https://github.com/BlurringShadow/vcpkg-registry) to your vcpkg-configuration.json.

<br/>

### Building the project

Use cmake to build the project, check [github work flow](.github/workflows/build.yml) for details.

## License

This project is licensed under the [Unlicense](https://unlicense.org/) license - see the
[LICENSE](LICENSE) file for details
