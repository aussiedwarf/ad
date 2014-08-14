#ifndef AD_PLATFORM_H
#define AD_PLATFORM_H

/*
Copyright (c) 2014 Eden Harris

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

/*

		
x86
	x64
	x86_64
arm
	arm_64
windows
	win
	win rt
	win phone
linux
	linux
	android
apple
	osx
	ios
bsd

gcc
	gcc
	mingw32
	mingw64
llvm/clang
intel
msvc


X86		//defined if x32 or x64 compatible
X86_32
X86_64
ARM
ARM_32
ARM_64
POWERPC
POWERPC_32
POWERPC_64

ANDROID
LINUX
WINDOWS
OSX
IOS

GCC
CLANG
MSVC
INTEl

http://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html

http://nadeausoftware.com/articles/2012/10/c_c_tip_how_detect_compiler_name_and_version_using_compiler_predefined_macros

Clang also defines the __GNUC__ macros
#if defined __clang__  The Clang frontend to LLVM (Clang)
#define COMPILER "Clang"
#elif defined __llvm__  The GCC frontend to LLVM (LLVM-GCC)
#define COMPILER "LLVM-GCC"
#elif defined __GNUC__  The GNU GCC compiler
#define COMPILER "GCC"
#else
#define COMPILER "Unknown"
#endif
	
__ANDROID__

*/

//Compiler
#if defined(__clang__)  //must detect before gnuc as clang also defines it
  #define AD_CLANG 1
#elif defined(__ICC) || defined(__INTEL_COMPILER) //must detect before gnuc as intel also defines it
  #define AD_INTEL_COMPILER 1
#elif defined(__GNUC__)
  #define AD_GNUC 1
#elif defined(_MSC_VER)
  #define AD_MSVC 1
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386) || defined(_M_IX86)
  #define AD_X86 1
#endif

#if defined(__x86_64__) || defined(_M_X64)
  #define AD_X86_64 1
#elif defined(__i386) || defined(_M_IX86)
  #define AD_X86_32 1
#elif defined(__arm__) || defined(_M_ARM)
  #define AD_ARM 1
  #if defined(__aarch64__)
    #define AD_ARM_64 1
  #else
    #define AD_ARM_32 1
  #endif
#endif

#if defined(_WIN32)
  #define AD_WINDOWS 1
#elif defined(__linux__)
  #define AD_LINUX 1
#elif defined(__APPLE__)
	#define AD_OSX 1
#endif

#if defined(AD_LINUX) && defined(AD_ARM)
  #define AD_RASPI 1
#endif

#endif	//AD_PLATFORM_H

