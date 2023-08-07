#ifndef __STRINGS_H__
#define __STRINGS_H__

#include "platform.h"

#include <sstream>
#include <string>

namespace string_user {

extern const char *error_compile;
extern const char *error_runtime;
extern const char *info_return_val;
extern const char *info_return_sig;
extern const char *info_exit_0;

#ifdef _WINDOWS
extern const char *warn_unsupport_tle;
#endif

} // namespace string_user

namespace string_compile {

extern const char *auto_detect;
extern const char *not_available;

} // namespace string_compile

namespace string_wrapper {

void set_no_color_mode();

std::string info(const char *s);
template <typename T> std::string info(const char *s, const T quote);
template <typename T> std::string info(const char *pre, const T quote, const char *post);

std::string warn(const char *s);

std::string error(const char *s);
template <typename T> std::string error(const char *s, const T quote);

} // namespace string_wrapper
#endif