#ifndef __COMPILER_OP_H__
#define __COMPILER_OP_H__

#include <iostream>
#include <string>
#include <vector>

namespace compiler {

namespace pipe {

FILE *open(const char *cmd, const char *modes);
FILE *open(const std::string &cmd, const std::string &modes);
void  read_line(FILE *pipe, std::string &out);
void  print(FILE *pipe);
void  clear(FILE *pipe);
int   close(FILE *pipe);

} // namespace pipe

bool exist(const std::string &id);
bool exist(const std::string &id, std::string &version);

bool compile(const std::vector<std::string> &inputs, const std::vector<std::string> &flags,
             const std::string &compiler);

} // namespace compiler

#endif