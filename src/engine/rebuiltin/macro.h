// Copyright(c) 2019 - 2021, KaoruXun All rights reserved.

#pragma once

#include <string>

#include "Version.h"

namespace invade {
    static const int VERSION_MAJOR = INVADEENGINE_VERSION_MAJOR;
    static const int VERSION_MINOR = INVADEENGINE_VERSION_MINOR;
    static const int VERSION_REV = INVADEENGINE_VERSION_BUILD;
    static const char *VERSION = INVADEENGINE_VERSION_TEXT;
    static const char *VERSION_COMPATIBILITY[] = {VERSION, "1.0", "1.1", 0};
}

#define DEVELOPMENT_BUILD
#define ALPHA_BUILD

#define BUILD_WITH_STEAM 0
#define BUILD_WITH_DISCORD 0

#if defined(NDEBUG) && !defined(_DEBUG)
#define INENGINE_RELEASE
#else
#define INENGINE_DEBUG
#endif

#define INENGINE_LIB_NDEBUG

// assert handling 
#define IN_ASSERT_EXCEPTION

#define INENGINE_CONCAT_IMPL(x, y) x##y
#define INENGINE_CONCAT(x, y) INENGINE_CONCAT_IMPL(x, y)

#define INVOKE_ONCE(...) static char INENGINE_CONCAT(unused, __LINE__) = [&](){ __VA_ARGS__; return '\0'; }(); (void)INENGINE_CONCAT(unused, __LINE__)

#define BOOL_STRING(b) (bool(b) ? "true" : "false")

#define INENGINE_STRING_IMPL(x) #x
#define INENGINE_STRING(x) INENGINE_STRING_IMPL(x)

#define INENGINE_MAKE_INTERNAL_TAG(tag) ("!" tag)
#define INENGINE_INTERNAL_TAG_SYMBOL '!'

#define INENGINE_MAKE_MOVEONLY(class_name) class_name() = default; class_name(const class_name&) = delete; class_name& operator=(const class_name&) = delete;\
        class_name(class_name&&) = default; class_name& operator=(class_name&&) = default

#if defined(INENGINE_DEBUG)
#if defined(IN_ASSERT_EXCEPTION)
#include <exception>
namespace invade {
    class assert_exception : public std::exception {
        \
    public: const char* message; assert_exception(const char* msg) {}\
            const char* what() const noexcept { return message; }
    };
}
#define IN_ASSERT(expr) if(!(expr)) throw invade::assert_exception(#expr) 
#else
#define IN_ASSERT(expr) assert(expr)
#endif
#else
#define IN_ASSERT(expr)
#endif

#define GENERATE_METHOD_CHECK(NAME, ...) namespace invade { template<typename T> class has_method_##NAME {\
    template<typename U> constexpr static auto check(int) -> decltype(std::declval<U>().__VA_ARGS__, bool()) { return true; }\
    template<typename> constexpr static bool check(...) { return false; } public:\
    static constexpr bool value = check<T>(0); }; }

#define INENGINE_FORCE_REFLECTION(TYPE) namespace invade { \
    namespace detail {                                       \
        void INENGINE_DLL_EXPORT DynamicInitDummy##TYPE();   \
    }                                                        \
}                                                            \
namespace {                                                  \
    struct DynamicInit##TYPE {                               \
        DynamicInit##TYPE() {                                \
            ::invade::detail::DynamicInitDummy##TYPE();    \
        }                                                    \
    } dynamicInitInstance##TYPE;                             \
}

#define INENGINE_FORCE_REFLECTION_IMPLEMENTATION(TYPE) namespace invade { \
    namespace detail {                                                      \
        void INENGINE_DLL_EXPORT DynamicInitDummy##TYPE() { }               \
    }                                                                       \
}

// VS2013 doesn't support alignof
#if defined(_MSC_VER) && _MSC_VER <= 1800
#define INENGINE_ALIGNOF(x) __alignof(x)
#else
#define INENGINE_ALIGNOF(x) alignof(x)
#endif



// Platform stuff.
#if defined(WIN32) || defined(_WIN32)
#	define INENGINE_WINDOWS 1
#endif

// Endianness.
#if defined(__ppc__) || defined(__ppc) || defined(__powerpc__) || defined(__powerpc)
#	define INENGINE_BIG_ENDIAN 1
#else
#	define INENGINE_LITTLE_ENDIAN 1
#endif

// SSE instructions.
#if defined(__SSE__)
#	define INENGINE_SIMD_SSE
#elif defined(_MSC_VER)
#	if defined(_M_AMD64) || defined(_M_X64)
#		define INENGINE_SIMD_SSE
#	elif _M_IX86_FP
#		define INENGINE_SIMD_SSE
#	endif
#endif

// NEON instructions.
#if defined(__ARM_NEON)
#	define INENGINE_SIMD_NEON
#endif

// Warnings.
#ifndef _CRT_SECURE_NO_WARNINGS
#	define _CRT_SECURE_NO_WARNINGS
#endif

// Preferably, and ironically, this macro should go unused.
#ifndef INENGINE_UNUSED
#	define INENGINE_UNUSED(x) (void)sizeof(x)
#endif


// Warn on unused return values
#ifdef __GNUC__
#	define INENGINE_WARN_UNUSED __attribute__((warn_unused_result))
#elif _MSC_VER
#	define INENGINE_WARN_UNUSED _Check_return_
#else
#	define INENGINE_WARN_UNUSED
#endif

#ifndef INENGINE_BUILD
#	define INENGINE_BUILD
#	define INENGINE_BUILD_STANDALONE
#	define INENGINE_BUILD_EXE
//#	define INENGINE_BUILD_DLL
#endif

#define INENGINE_LEGENDARY_CONSOLE_IO_HACK

// Check we have a sane configuration
#if !defined(INENGINE_WINDOWS) && !defined(INENGINE_LINUX) && !defined(INENGINE_IOS) && !defined(INENGINE_MACOSX) && !defined(INENGINE_ANDROID)
#	error Could not detect target platform
#endif
#if !defined(INENGINE_LITTLE_ENDIAN) && !defined(INENGINE_BIG_ENDIAN)
#	error Could not detect endianness
#endif

#define PIXEL(surface, x, y) *((Uint32*)(\
(Uint8*)surface->pixels + ((y) * surface->pitch) + ((x) * sizeof(Uint32)))\
)

#ifndef UNUSED
#define UNUSED(x)    (x = x)    // for pesky compiler / lint warnings
#endif

