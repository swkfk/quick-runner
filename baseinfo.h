#ifndef __BASEINFO_H__
#define __BASEINFO_H__

#include "platform.h"

#include <string>

namespace baseinfo {
const std::string version = "1.0.3";
const std::string bulit_date = __DATE__;
const std::string bulit_time = __TIME__;

#if defined(_MSC_VER)
const std::string compiler = "MSVC";
#elif defined(__clang__)
const std::string compiler = "LLVM clang++";
#elif defined(__GNUC__)
const std::string compiler = "GNU g++";
#else
const std::string compiler = "Unknown";
#endif

#ifdef _WINDOWS
const std::string platform = "Windows";
#elif defined(_LINUX)
const std::string platform = "Linux";
#elif defined(_MACOS)
const std::string platform = "Mac";
#else
const std::string platform = "Unknown";
#endif

} // namespace baseinfo

#endif