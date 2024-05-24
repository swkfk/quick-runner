# C/C++ Quick Runner [早期开发阶段 / In early development stage]

这是一个简单快速的 C/C++ 运行程序，不过，与其说是一个 “程序”，倒不如说是一段 “脚本”。

A simple and quick C/C++ runner. It is more a piece of script than a program.

这个运行程序 **并没有** 提供一个编译器，但是它可以自行检测可用的 `gcc/g++` 或者是 `clang/clang++` 来进行编译（尚未实现）。

The runner **does not** provide a compiler. But it can detect the `gcc/g++` or `clang/clang++` installed by you and use them autometically (Not available yet).

在编译运行程序的时候，我也提供了一些有用的选项，比如运行时间的限制等等。

I also provide some useful options to run the program, such as "time-limit".

## 安装 / Install

对于 Linux 系统，你可以使用：

For Linux, use

``` shell
git clone https://github.com/swkfk/quick-runner.git ~/quick-runner
cd ~/quick-runner
make
```

来克隆代码仓库，并且使用 make 进行构建，同时，你也可以使用

to clone the repo and build the program or use

``` shell
make install
```

来将其添加到全局目录。

to make the program can be called globally.

对于 Windows 系统，你也可以使用 `git clone` 来获取源代码，并使用下列指令进行编译。

For Windows, you can also use `git clone` to get the source file and build it with 

``` shell
mingw32-make PLATFORM=win
```

当然，其他工具链也没有问题。但是你必须手动将其添加到系统的环境变量（如果你想全局使用的话，`make install` 不支持 Windows 系统）。

or other tool-chains. But you may need to set the program to the `%PATH%` manually (`make install` is not supported on Windows).

很遗憾的是，在 Windows 中支持此程序的全部功能是挺困难的，因为我在原始程序中使用了很多 Unix 特有的函数 / 系统调用。但如果我有空的话，我会学习并使用 Windows 核心编程的相关内容来使其支持所有应有的功能。

It is a pity that, it is hard to supprot Windows fully now, because I use some Unix functions in this project. I will learn the Windows Programming if I were free to make it work on Windows as great as on Linux.

## 用法 / Usage

``` bash
runner [options] source-files [--] [args]
```

---

- 选项 / `options`:

  - `-V`,` --version`    展示程序版本信息，并退出。
  - `-?`, `--help`       展示帮助信息（英文），并退出。
  - `-c`, `--compiler`   选择编译器，如果不指定，将默认为 `auto`（对于 C++，检测顺序为 `g++`，`clang++`；对于 C，检测顺序为 `gcc`，`clang`）。
    - 需要一个参数：选项中的字符串，用来指定编译器；
    - 你只能基于下列五项参数： `gcc`, `g++`, `clang`, `clang++`, `auto`（默认）；
    - 如果指定的编译器没有找到，程序将会退出，并返回错误码；
    - 为了 **给选项设定参数**，你可以采用以下三种途径： `-c gcc`，`--compiler g++`，`--compiler=clang`. 后续需要参数的选项都遵循着相同的格式。
  - `-t`, `--time-limit`    限制程序运行的时间，如果设为 `0`（默认），则为无限制。
    - **该选项将在 Windows 系统中被忽略**；
    - 需要一个参数：0 ~ 1000 的一个整数，用来限制程序运行时间（单位：秒）；
    - 如果运行超时，你的程序将会被信号 `SIGALRM(14)` 终止；
    - 请格外注意，等待输入也会被计算时间，因此，你最好使用 `--input` 进行输入。
  - `-i`, `--input`    指定用来代替 `stdin` 的文件。
    - 需要一个参数：代表文件路径的字符串；
    - 对于 Linux 系统，当文件不存在时，程序将会退出并返回错误码。
  - `-k`, `--keep`     如果这个选项存在，编译后的程序在运行结束后将 **不** 会被删除。
  - `-d`, `--debug`    如果这个选项存在，将会在编译时给你的程序添加 `DEBUG` 宏（通过 `-DDEBUG` 编译选项）以方便调试。
  - `--no-color`       如果这个选项存在，程序将不会输出彩色文字。

---

  - `-V`,` --version`    Show the version information and exit.
  - `-?`, `--help`       Show the help message and exit.
  - `-c`, `--compiler`   Choose the compiler. If `auto` is given, the usable and suitable compiler will be chosen (The sequence is `g++`, `clang++` for C++ and `gcc`, `clang` for C).
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

---

- 源文件 / `source-files`:

  源文件列表，使用空格隔开。

  The lists of the source files.

- 运行参数 / `-- args`:

  `--` 之后的全部内容将被传递给子程序，不同参数间使用空格隔开

  Everything after the `--` will be passed to the program.

## 更新日志 / What's new

### [early] v1.0.3

支持 auto 自动检测，能够对 C、C++ 文件调用不同的编译器。

Can detect the compiler (auto mode) now!


### [early] v1.0.2

为 `README.md` 中的描述性信息增加了中文！

Add **Chinese** support for the descriptive information in the  `README.md`!


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

## 第三方 License / Third-Party License

- cmdline.h
  - By: Hideyuki Tanaka
  - License: BSD-3-Clause license
  - Detail: ThirdPartyLicense/cmdline/LICENSE
