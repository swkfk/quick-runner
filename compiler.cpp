#include "compiler.h"

namespace compile::pipe {

FILE *open(const char *cmd, const char *modes = "r") {
    FILE *pipe = popen(cmd, modes);
    if (!pipe) {
        std::cerr << "Cannot open pipe: " << cmd << "@ func: " << __FUNCTION__ << std::endl;
        return nullptr;
    }
    return pipe;
}

FILE *open(const std::string &cmd, const std::string &modes = "r") {
    return open(cmd.c_str(), modes.c_str());
}

void read_line(FILE *pipe, std::string &out) {
    char tmp[1024], *p = tmp;
    fgets(tmp, 1024, pipe);
    while (*p != '\0') {
        ++p;
    }
    --p;
    while (*p == '\n' || *p == '\r' || *p == '\t' || *p == ' ') {
        *(p--) = '\0';
    }
    out = out.assign(tmp);
}

void print(FILE *pipe) {
    int chr;
    while (chr = fgetc(pipe), chr != EOF) {
        putchar(chr);
    }
}

void clear(FILE *pipe) {
    while (fgetc(pipe) != EOF)
        ;
}

int close(FILE *pipe) {
    int ret = pclose(pipe);
    if (ret == -1) {
        std::cerr << "Cannot close pipe @ func: " << __FUNCTION__ << std::endl;
        return -1;
    }
    return ret;
}

} // namespace compile::pipe

namespace compile {

bool exist(const std::string &id) {
    FILE *pipe = pipe::open(id + " --version 2>&1");
    if (!pipe) {
        return false;
    }
    pipe::clear(pipe);
    int ret = pipe::close(pipe);
    return WIFEXITED(ret) && !WEXITSTATUS(ret);
}

bool exist(const std::string &id, std::string &version) {
    FILE *pipe = pipe::open(id + " --version 2>&1");
    if (!pipe) {
        return false;
    }
    pipe::read_line(pipe, version);
    int ret = pipe::close(pipe);
    return WIFEXITED(ret) && !WEXITSTATUS(ret);
}

bool compile(const std::vector<std::string> &inputs, const std::vector<std::string> &flags,
             const std::string &compile) {

    std::string cmd = compile;
    for (auto &s : inputs) {
        cmd += " " + s;
    }
    for (auto &s : flags) {
        cmd += " " + s;
    }

    FILE *pipe = compile::pipe::open(cmd + " 2>&1", "w");
    if (!pipe) {
        return false;
    }

    int ret = pipe::close(pipe);
    return WIFEXITED(ret) && !WEXITSTATUS(ret);
}

} // namespace compile
