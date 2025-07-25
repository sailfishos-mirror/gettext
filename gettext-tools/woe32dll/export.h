/* Exporting symbols from Windows shared libraries.
   Copyright (C) 2006, 2011-2025 Free Software Foundation, Inc.
   Written by Bruno Haible <bruno@clisp.org>, 2006.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* Two things are complicated when dealing with shared libraries on Windows:
     - Exporting symbols from shared libraries (→ 'dllexport'),
     - Referencing symbols in shared libraries from outside the library
       (→ 'dllimport').
   Without GNU libtool, the complications apply to both functions and variables.
   With GNU libtool, the complications apply to variables only; GNU libtool
   deals with the functions.

   There are four ways to build shared libraries on Windows:

   - Export only functions, no variables.
     This has the drawback of severely affecting the programming style in use.
     It does not let the programmer use full ANSI C.  It lets one platform
     dictate the code style on all platforms.  This is unacceptable.

   - Use the GNU ld --enable-auto-import option.  It is the default on Cygwin
     since July 2005. But it has three fatal drawbacks:
       - It produces executables and shared libraries with relocations in the
         .text segment, defeating the principles of virtual memory.
       - For some constructs such as
             extern int var;
             int * const b = &var;
         it creates an executable that will give an error at runtime, rather
         than either a compile-time or link-time error or a working executable.
         (This is with both gcc and g++.) Whereas this code, not relying on
         auto-import:
             extern __declspec (dllimport) int var;
             int * const b = &var;
         gives a compile-time error with gcc and works with g++.
       - It doesn't work in some cases (references to a member field of an
         exported struct variable, or to a particular element of an exported
         array variable), requiring code modifications.  Again one platform
         dictates code modifications on all platforms.

     This is unacceptable.  Therefore we disable this option, through the
     woe32-dll.m4 autoconf macro.

   - Define a macro that expands to  __declspec(dllexport)  when building
     the library and to  __declspec(dllimport)  when building code outside
     the library, and use it in all header files of the library.
     This is acceptable if
       1. the header files are unique to this library (not shared with
          other packages), and
       2. the library sources are contained in one directory, making it easy
          to define a -DBUILDING_LIBXYZ flag for the library (either in
          AM_CPPFLAGS or in libxyz_la_CPPFLAGS).
     Example:
         #if (defined _WIN32 || defined __CYGWIN__) && WOE32DLL
                                             // on Windows, with --enable-shared
         # if BUILDING_LIBXYZ                // building code for libxyz
         #  if defined DLL_EXPORT            // compiling object files for a DLL
         #   define LIBXYZ_SHLIB_EXPORTED __declspec(dllexport)
         #  else                             // compiling static object files
         #   define LIBXYZ_SHLIB_EXPORTED
         #  endif
         # else                              // building code outside libxyz
         #  define LIBXYZ_SHLIB_EXPORTED __declspec(dllimport)
         # endif
         #else                               // not Windows, or --disable-shared
         # define LIBXYZ_SHLIB_EXPORTED
         #endif

     We use this technique for
       - libiconv,
       - libintl,
       - libgettextlib and libgettextsrc.

   - Define a macro that expands to  __declspec(dllimport)  always, and use
     it in all header files of the library.  Use an explicit export list for
     the library.
     This is acceptable if
       1. the programming language is not C++ (because the name mangling of
          static struct/class fields and of variables in namespaces makes it
          hard to maintain an export list),
       2. there are no constructs such as
             extern __declspec (dllimport) int var;
             int * const b = &var;
          or equivalent (e.g. as in gnulib/lib/uninorm/nfc.c),
          because these constructs give a compilation error.
     The benefit of this approach is that the partitioning of the source files
     into libraries (which source file goes into which library) does not
     affect the source code; only the Makefiles reflect it.
     The performance loss due to the unnecessary indirection for references
     to variables from within the library defining the variable is acceptable.

   This file allows building an explicit export list.  You can either
     - specify the variables to be exported, and use the GNU ld option
       --export-all-symbols to export all function names, or
     - specify the variables and functions to be exported explicitly.

   Note: --export-all-symbols is the default when no other symbol is explicitly
   exported.  This means, the use of an explicit export on the variables has
   the effect of no longer exporting the functions! - until the option
   --export-all-symbols is used.

   See <https://haible.de/bruno/woe32dll.html> for more details.  */

#if defined __GNUC__ /* GCC compiler, GNU toolchain */

 /* IMP(x) is a symbol that contains the address of x.  */
# if defined _WIN64 || defined _LP64
#  define IMP(x) __imp_##x
# else
#  define IMP(x) _imp__##x
# endif

 /* Ensure that the variable x is exported from the library, and that a
    pseudo-variable IMP(x) is available.  */
# define VARIABLE(x) \
 /* Export x without redefining x.  This code was found by compiling a  \
    snippet:                                                            \
      extern __declspec(dllexport) int x; int x = 42;  */               \
 asm (".section .drectve\n");                                           \
 asm (".ascii \" -export:" #x ",data\"\n");                             \
 asm (".data\n");                                                       \
 /* Allocate a pseudo-variable IMP(x).  */                              \
 extern int x;                                                          \
 void * IMP(x) = &x;

#else /* non-GNU compiler, non-GNU toolchain */

# define VARIABLE(x) /* nothing */

#endif
