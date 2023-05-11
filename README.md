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
runner [--version] [--help] SOURCES [OPTIONS] [--] [ARGS]
```

### `--version`

[Unsupported nowadays.]

### `--help`

[Unsupported nowadays.]

### SOURCES

The source files to be run.

### OPITIONS

[Unsupported nowadays.]

### `--`

[Unsupported nowadays.]

A `--` means the end of the commands and the args left will be passed to the program.

### ARGS

[Unsupported nowadays.]

The args to be pass to the program. Before the ARGS, a `--` is needed.
