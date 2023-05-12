# C/C++ Quick Runner [In early development stage]

**Released: 2023/05/12**

A simple and quick C/C++ runner. It is more a piece of script than a program.

The runner **does not** provide a compiler. But it can detect the `gcc/g++` or `clang/clang++` installed by you and use them autometically (**In later version**).

## Functions

- [x] Complie and run the specified source file.
- [ ] Provide a simple way to redirect the `stdin`.
- [ ] Detect the latest source file and run it.
- [ ] Detect the existed compiler.

## Install

For Linux, use

``` bash
git clone https://github.com/swkfk/quick-runner.git ~/quick-runner
cd ~/quick-runner
make
```

to clone the repo and build the program or use

``` bash
make install
```

to make the program can be called globally.

For Windows, you can also use `git clone` to get the source file and build it with `make` or other compiler. But you may need to set the program to the `%PATH%` manually.

## Usage

``` bash
runner [options] source-files [--] [args]
```

- options:

  - `-V`,` --version`    Show the version information and exit.
  - `-?`, `--help`       Show the help message and exit.
  - `-c`, `--compiler`   Choose the compiler. If given "auto", the usable and suitable compiler will be chosen (This version will use `gcc` by default).
    - Need a string parameter to specify the compiler.
    - The choices are: `gcc`, `g++`, `clang`, `clang++`, `auto`(dufault).
    - If the compiler is not found, the program will exit with an error.
    - To **add a parameter**, you can use `-c gcc` or `--compiler g++` or `--compiler=clang`. The following options that need parameters have the same behavior.

- source-files:

  The lists of the source files

- -- args:

  Everything after the `--` will be passed to the program.

## What's new

### [early] v0.0.2

The program can now compile the sources and run it! The binary will be removed after running.

Add the `--conpiler` option to specify the compiler. Now the program has the ability to check whether the compiler specified by the user is available.

### [early] v0.0.1

The `--help` and `--version` are available now. The program starts to use `cmdline` the project to handle the arguments.

## Third-Party License

- cmdline.h
  - By: Hideyuki Tanaka
  - License: BSD-3-Clause license
  - Detail: ./Third-Party-License/cmdline/LICENSE
