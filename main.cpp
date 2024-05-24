#include "baseinfo.h"
#include "cmdline.h"
#include "compiler.h"
#include "program.h"
#include "strings.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {

    // register the argument parser
    cmdline::parser parser;

    // arg: --help / -?  !![exit]
    parser.add("help", '?', "Show this help message and exit.");

    // arg: --version / -V  !![exit]
    parser.add("version", 'V', "Show the version information and exit.");

    // arg: --compiler / -c  parameter: string, @option{gcc | clang | g++ | clang++ | {auto}}
    parser.add<std::string>(
        "compiler", 'c',
        "Choose the compiler. If `auto`(default) is given, the usable and suitable compiler will be chosen.", false,
        "auto", cmdline::oneof<std::string>("gcc", "clang", "g++", "clang++", "auto"));

    // arg: --time-limit / --t  parameter: int, @range(0, 1000)
    parser.add("time-limit", 't',
               "Limit the run time of the program. If `0`(default) is given, there will be no limits.", false, 0,
               cmdline::range_reader<int>(0, 1000));

    // arg: --input / -i  parameter: string, @[-f $1] == true
    parser.add<std::string>("input", 'i', "To specify the file to replace the stdin of the program.", false, "");

    // arg: --keep / -k
    parser.add("keep", 'k', "Keep the binary file after running it instead of deleting it. (Not by default)");

    // arg: --debug / -d
    parser.add("debug", 'd', "Enable the macro `DEBUG` for your program. (Not by default)");

    // arg: --no-color
    parser.add("no-color", 0, "This program's output will be without colors. (Colorful by default)");

    parser.footer("source-files [--] [args]");
    parser.set_program_name("runner");

    // find the argument `--`
    int idx_of_double_stash = argc;
    for (int i = 1; i < argc; ++i) {
        if (strcmp("--", argv[i]) == 0) {
            idx_of_double_stash = i;
            break;
        }
    }

    // do parser
    parser.parse_check(idx_of_double_stash, argv);

    // color be the first
    if (parser.exist("no-color")) {
        string_wrapper::set_no_color_mode();
    }

    // `--help` => exit
    if (parser.exist("help")) {
        std::cout << parser.usage();
        return 0;
    }

    // `--version` => exit
    if (parser.exist("version")) {
        std::cout << "C/C++ Quick Runner (visit https://swkfk.top/jump/manual-runner for more information)"
                  << std::endl;
        std::cout << "Version: " << baseinfo::version << std::endl;
        std::cout << "Built at " << baseinfo::bulit_time << " " << baseinfo::bulit_date;
        std::cout << " By " << baseinfo::compiler << std::endl;
        std::cout << "Platform: " << baseinfo::platform << std::endl;
        return 0;
    }

    // read the source files
    std::vector<std::string> sources;
    for (auto &filename : parser.rest()) {
        sources.push_back(filename);
    }

    // read the program args
    std::vector<std::string> args;
    for (int i = idx_of_double_stash + 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }

    // get the options
    int option_time_limit = parser.get<int>("time-limit");
    bool option_keep = parser.exist("keep");
    std::string option_input = parser.exist("input") ? parser.get<std::string>("input") : "";
    bool debug_enable = parser.exist("debug");

    // read the compiler flags
    std::vector<std::string> c_flags;
    if (debug_enable) {
        c_flags.push_back("-DDEBUG");
    }
    // TODO

    // check and detect the compiler
    std::string c_compiler = parser.get<std::string>("compiler");
    if (c_compiler != "auto") {
        if (!compile::exist(c_compiler)) {
            std::cerr << string_wrapper::error(string_compile::not_available, c_compiler) << std::endl;
            return 1;
        }
    } else {
        bool cpp = false;
        for (auto sourse : sources) {
            auto dot_pos = sourse.rfind(".");
            if (dot_pos == std::string::npos) {
                continue;
            }
            auto extension = sourse.substr(dot_pos + 1);
            if (extension == "cpp") {
                cpp = true;
                break;
            }
        }
        if (cpp) {
            if (compile::exist("g++")) {
                c_compiler = "g++";
            } else if (compile::exist("clang++")) {
                c_compiler = "clang++";
            } else {
                std::cerr << string_wrapper::error(string_compile::not_available, "g++ or clang++") << std::endl;
                return 1;
            }
        } else {
            if (compile::exist("gcc")) {
                c_compiler = "gcc";
            } else if (compile::exist("clang")) {
                c_compiler = "clang";
            } else {
                std::cerr << string_wrapper::error(string_compile::not_available, "gcc or clang") << std::endl;
                return 1;
            }
        }
    }

    // compile
    bool ret_compile = compile::compile(sources, c_flags, c_compiler);
    if (!ret_compile) {
        std::cerr << string_wrapper::error(string_user::error_compile) << std::endl;
        return 1;
    }

    // run the program and remove the file
    int exit_code = program::run(args, option_time_limit, option_input);

    if (!option_keep) {
#ifdef _UNIX
        remove("./a.out");
#else
        remove("a.exe");
#endif
    }

    if (exit_code) {
#ifdef _UNIX
        int ret_value = (exit_code >> 8) & 0xFF;
        int ret_sig = exit_code & 0x7F;
#else
        int ret_value = exit_code;
#endif
        std::cerr << string_wrapper::error(string_user::error_runtime) << std::endl;
        if (ret_value) {
            std::cerr << string_wrapper::error(string_user::info_return_val, ret_value) << std::endl;
        }
#ifdef _UNIX
        if (ret_sig) {
            std::cerr << string_wrapper::error(string_user::info_return_sig, ret_sig) << std::endl;
        }
#endif
        return 1;
    }

    std::cout << string_wrapper::info(string_user::info_exit_0) << std::endl;

    return 0;
}
