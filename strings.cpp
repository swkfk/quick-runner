#include "strings.h"

namespace string_user {

const char *error_compile = "Compile error!";
const char *error_runtime = "Runtime error!";
const char *info_return_val = "| Return value:";
const char *info_return_sig = "| Return signal:";
const char *info_exit_0 = "The program exits successfully!";

#ifdef _WINDOWS
const char *warn_unsupport_tle = "The `tle` function is not supported on Windows now. The request will be ignored!";
#endif

} // namespace string_user

namespace string_compile {

const char *auto_detect = "Auto detected compiler:";
const char *not_available = "Error! Compiler not available:";

} // namespace string_compile

namespace string_wrapper {

bool _no_color_mode = false;

void set_no_color_mode() {
    _no_color_mode = true;
}

const char *GREEN = "\033[32m";
const char *RED = "\033[31m";
const char *CYAN = "\033[36m";
const char *BLUE = "\033[34m";
const char *YELLOW = "\033[33m";
const char *HIGH_RED = "\033[1;31m";
const char *RESET = "\033[0m";

// If I use `#define` here, the namespace will lose its effect.
const char *C_QUOTE = GREEN;
const char *C_INFO = BLUE;
const char *C_WARN = YELLOW;
const char *C_ERROR = RED;
const char *C_CRITICLE = HIGH_RED;

std::string base(const char *base_color, const char *s) {
    std::ostringstream oss;
    if (!_no_color_mode) {
        oss << base_color << s << RESET;
    } else {
        oss << s;
    }
    return oss.str();
}

template <typename T> std::string base(const char *base_color, const char *prefix, T quote) {
    std::ostringstream oss;
    if (!_no_color_mode) {
        oss << base_color << prefix << " " << C_QUOTE << quote << base_color << " " << RESET;
    } else {
        oss << prefix << " " << quote << " ";
    }
    return oss.str();
}

template <typename T> std::string base(const char *base_color, const char *prefix, T quote, const char *postfix) {
    std::ostringstream oss;
    if (!_no_color_mode) {
        oss << base_color << prefix << " " << C_QUOTE << quote << base_color << " " << postfix << RESET;
    } else {
        oss << prefix << " " << quote << " " << postfix;
    }
    return oss.str();
}

std::string info(const char *s) {
    return base(C_INFO, s);
}

template <typename T> std::string info(const char *s, const T quote) {
    return base(C_INFO, s, quote);
}

template <typename T> std::string info(const char *pre, const T quote, const char *post) {
    return base(C_INFO, pre, quote, post);
}

std::string warn(const char *s) {
    return base(C_WARN, s);
}

std::string error(const char *s) {
    return base(C_ERROR, s);
}

template <typename T> std::string error(const char *s, const T quote) {
    return base(C_ERROR, s, quote);
}

template std::string info(const char *, const char *);
template std::string info(const char *, const int, const char *);
template std::string error(const char *, const char *);
template std::string error(const char *, const int);
template std::string error(const char *, const std::string);

} // namespace string_wrapper