# C/C++ Quick Runner [In early development stage]

**Released: 2023/08/07**

A simple and quick C/C++ runner. It is more a piece of script than a program.

The runner **does not** provide a compiler. But it can detect the `gcc/g++` or `clang/clang++` installed by you and use them autometically.

I also provide some useful options to run the program, such as "time-limit".

## Install

For Linux, use

``` shell
git clone https://github.com/swkfk/quick-runner.git ~/quick-runner
cd ~/quick-runner
make
```

to clone the repo and build the program or use

``` shell
make install
```

to make the program can be called globally.

For Windows, you can also use `git clone` to get the source file and build it with 

``` shell
mingw32-make PLATFORM=win
```

or other tool-chains. But you may need to set the program to the `%PATH%` manually (`make install` is not supported on Windows).

It is a pity that, it is hard to supprot Windows fully now, because I use some Unix functions in this project. I will learn the Windows Programming if I were free to make it work on Windows as great as on Linux.

## Usage

``` bash
runner [options] source-files [--] [args]
```

- options:

  - `-V`,` --version`    Show the version information and exit.
  - `-?`, `--help`       Show the help message and exit.
  - `-c`, `--compiler`   Choose the compiler. If `auto` is given, the usable and suitable compiler will be chosen (This version will use `gcc` by default).
    - Need a string parameter to specify the compiler.
    - The choices are: `gcc`, `g++`, `clang`, `clang++`, `auto`(dufault).
    - If the compiler is not found, the program will exit with an error.
    - To **add a parameter**, you can use `-c gcc` or `--compiler g++` or `--compiler=clang`. The following options that need parameters have the same behavior.
  - `-t`, `--time-limit`    Limit the run time of your program. If `0` is given, there will be no limits.
    - This argument will be ignored on Windows.
    - Need an int parameter to specify the time limit.
    - Your program will be killed with the `SIGALRM(14)` if TLE.
    - Pay attention that, the input time will be calulated in the total time. So it's better to use this option with the `--input`.
  - `-i`, `--input`         To specify the file to replace the stdin of your program.
    - Need a string parameter to specify the input file. If the file does not exist, the program will exit with an error.
  - `-k`, `--keep`          If this option exists, the binary file generated will be kept after running it instead of deleting it.
  - `-d`, `--debug`         Enable the macro `DEBUG` for your program.
  - `--no-color`            Dismiss the colorful output.
- source-files:

  The lists of the source files.

- -- args:

  Everything after the `--` will be passed to the program.

## What's new

### [early] v1.0.1

Some bugs are fixed:

- The binary will not be removed on Windows.
- The "Time Limit Exceeded" string has no color.
- Extra blanks in strings.
- Some typos in strings and `README.md`.

### [early] v1.0.0

Add a simple support for Windows! Although the "--time-limit" argument will be ignored and `Ctrl-C` will kill this program along with your program.

The compiler detect function has not been supported yet, but the version starts with a `1`. This is because that, it can run on Windows now and its basic functions are finished.

### [early] v0.0.6

Now the output will be colorful! But you can also change to the "no-color" mode by the `--no-color` option.

### [early] v0.0.5

Add the `--debug` or `-d` option to enable the DEBUG mode for your program via the macro `DEBUG`.

### [early] v0.0.4

Add the `--input` or `-i` option to specify the file whose content will be send to your program's stdin. In this version, the program will not check the existence of the input file.

Add the `--keep` or `-k` option. If this option exists, the binary generated will not be removed after running it.

The program now use `pipe` to send data to your program if `--input` is specified.

### [early] v0.0.3

The program now use `fork` to run the program and can get the return value of the program. Press `Ctrl+C` to make an interruption to kill your program with `SIGKILL(9)`.

Add the `--time-limit` or `-t` option to limit the run time of your program.

### [early] v0.0.2

The program can now compile the sources and run it! The binary will be removed after running.

Add the `--compiler` or `-c` option to specify the compiler. Now the program has the ability to check whether the compiler specified by the user is available.

### [early] v0.0.1

The `--help` and `--version` are available now. The program starts to use `cmdline` the project to handle the arguments.

## Third-Party License

- cmdline.h
  - By: Hideyuki Tanaka
  - License: BSD-3-Clause license
  - Detail: ThirdPartyLicense/cmdline/LICENSE
