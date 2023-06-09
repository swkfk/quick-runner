#include "baseinfo.h"
#include "cmdline.h"
#include "compiler_op.h"
#include "program_op.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {

    // register the argument parser
    cmdline::parser parser;
    parser.add("help", '?', "Show this help message and exit.");
    parser.add("version", 'V', "Show the version information and exit.");
    parser.add<std::string>(
        "compiler", 'c', "Choose the compiler. If \"auto\" is given, the usable and suitable compiler will be chosen.",
        false, "auto", cmdline::oneof<std::string>("gcc", "clang", "g++", "clang++", "auto", "233"));
    parser.add("time-limit", 't', "Limit the run time of the program. If `0` is given, there will be no limits.", false,
               0, cmdline::range_reader<int>(0, 1000));
    parser.add<std::string>("input", 'i', "To specify the file to replace the stdin of the program.", false, "");
    parser.add("keep", 'k', "Keep the binary file after running it instead of deleting it.");
    parser.add("debug", 'd', "Enable the macro `DEBUG` for your program.");

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

    // `--help` => exit
    if (parser.exist("help")) {
        std::cout << parser.usage();
        return 0;
    }

    // `--version` => exit
    if (parser.exist("version")) {
        std::cout << "C/C++ Quick Runner " << std::endl;
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
        if (!compiler::exist(c_compiler)) {
            // TODO: error
            std::cerr << "Compiler " << c_compiler << " not exists!" << std::endl;
            return 1;
        }
    } else {
        // TODO: C or CPP
        c_compiler = "gcc";
    }

    // compile
    bool ret_compile = compiler::compile(sources, c_flags, c_compiler);
    if (!ret_compile) {
        // TODO: error
        std::cerr << "Compile Error!" << std::endl;
        return 1;
    }

    // run the program and remove the file
    int exit_code = program::run(args, option_time_limit, option_input);

    if (!option_keep) {
        remove("./a.out");
    }

    if (exit_code) {
        // TODO: error
        int ret_value = (exit_code >> 8) & 0xFF;
        int ret_sig = exit_code & 0x7F;
        std::cerr << "Runtime Error!" << std::endl;
        if (ret_value) {
            std::cerr << "/ Return value: " << ret_value << std::endl;
        }
        if (ret_sig) {
            std::cerr << "/ Return signal: " << ret_sig << std::endl;
        }
        return 1;
    }
    std::cout << "The program exits successfully!" << std::endl;

    return 0;
}
