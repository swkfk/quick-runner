#include "baseinfo.h"
#include "cmdline.h"
#include "compiler_op.h"
#include "program_op.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    std::cout << "[[In early development stage!]]" << std::endl;

    // register the argument parser
    cmdline::parser parser;
    parser.add("help", '?', "Show this help message and exit.");
    parser.add("version", 'V', "Show the version information and exit.");
    parser.add<std::string>(
        "compiler", 'c', "Choose the compiler. If given \"auto\", the usable and suitable compiler will be chosen.",
        false, "auto", cmdline::oneof<std::string>("gcc", "clang", "g++", "clang++", "auto", "233"));

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

    // read the compiler flags
    // TODO
    std::vector<std::string> c_flags;

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
    int ret_run = program::run(args);
    // TODO: remove or keep, check the status
    remove("./a.out");
    if (ret_run) {
        // TODO: error
        std::cerr << "Runtime Error! The return value is " << ret_run << std::endl;
        return 1;
    }

    return 0;
}
