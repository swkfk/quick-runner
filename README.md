# C/C++ Quick Runner [In early development]

**Released: 2023/05/11**

A simple and quick C/C++ runner. It is more a piece of script than a program.

The runner **does not** provide a complier. But it can detect the `gcc/g++` or `clang/clang++` installed by you and use them autometically (**In later version**).

## Functions

- [ ] Complie and run the specified source file.
- [ ] Provide a simple way to redirect the `stdin`.
- [ ] Detect the latest source file and run it.
- [ ] Detect the existed complier.

## Install

Use

``` bash
make
```

to build the program or use

``` bash
make install
```

to make the program can be called globally(For linux only).

For Windows, you may need to set the program to the `%PATH%` manually.

## Usage

``` bash
./runner [options] source-files [--] [args]
```

- options:

  `-V`,` --version`    Show the version information and exit.

  `-?`, `--help`       Show the help message and exit.

- source-files:

  The lists of the source files

- -- args:

  Everything after the `--` will be passed to the program.

## Third-Party License

- cmdline.h
  - By: Hideyuki Tanaka
  - License: BSD-3-Clause license
  - Detail: ./Third-Party-License/cmdline/LICENSE
