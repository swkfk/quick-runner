#ifndef __PROGRAM_OP_H__
#define __PROGRAM_OP_H__

#include <string>
#include <vector>

namespace program {

int run(const std::vector<std::string> &args, int time_limit, const std::string &input);

} // namespace program

#endif