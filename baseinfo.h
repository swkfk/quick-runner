#ifndef __BASEINFO_H__
#define __BASEINFO_H__

#include <string>

namespace baseinfo {
const std::string version    = "0.0.1";
const std::string bulit_date = __DATE__;
const std::string bulit_time = __TIME__;

#if defined(_MSC_VER)
const std::string complier = "MSVC";
#elif defined(__clang__)
const std::string complier = "clang++";
#elif defined(__GNUC__)
const std::string complier = "g++";
#elif defined(__BORLANDC__)
const std::string complier = "g++";
#else
const std::string complier = "unknown";
#endif

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
const std::string platform = "Windows";
#elif defined(__linux__)
const std::string platform = "Linux";
#elif defined(__APPLE__) || defined(TARGET_OS_MAC)
const std::string platform = "Mac";
#else
const std::string platform = "Unknown";
#endif

} // namespace baseinfo

#endif