#include "baseinfo.h"
#include "cmdline.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    cmdline::parser parser;
    parser.add("version", 'V', "Show the version information and exit.");
    parser.add("help", '?', "Show this help message and exit.");

    parser.footer("source-files [--] [args]");

    int idx_of_double_stash = argc;
    for (int i = 1; i < argc; ++i) {
        if (strcmp("--", argv[i]) == 0) {
            idx_of_double_stash = i;
            break;
        }
    }

    parser.parse_check(idx_of_double_stash, argv);

    if (parser.exist("help")) {
        std::cout << parser.usage();
        return 0;
    }

    if (parser.exist("version")) {
        std::cout << "C/C++ Quick Runner " << std::endl;
        std::cout << "Version: " << baseinfo::version << std::endl;
        std::cout << "Built at " << baseinfo::bulit_time << " " << baseinfo::bulit_date << std::endl;
        std::cout << "Platform: " << baseinfo::platform << std::endl;
        return 0;
    }

    return 0;
}
