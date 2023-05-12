#include "program_op.h"

namespace program {
int run(const std::vector<std::string> &args) {
    // TODO: modify the exec name
    std::string cmd = "./a.out";
    for (auto &s : args) {
        cmd += " \"" + s + "\"";
    }

    return system(cmd.c_str());
}

}; // namespace program