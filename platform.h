#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(WIN64) || defined(_WIN64) || defined(_WIN64_)
#define _WINDOWS
#elif defined(__linux__)
#define _LINUX
#elif defined(__APPLE__) || defined(TARGET_OS_MAC)
#define _MACOS
#else
#error Unsupported platform!
#endif

#if defined(_LINUX) || defined(_MACOS)
#define _UNIX
#endif

#endif // __PLATFORM_H__