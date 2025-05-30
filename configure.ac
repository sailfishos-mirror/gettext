dnl Configuration for the toplevel directory of GNU gettext
dnl Copyright (C) 1995-2025 Free Software Foundation, Inc.
dnl
dnl This program is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program.  If not, see <https://www.gnu.org/licenses/>.

dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.64])
AC_INIT([gettext], [package], [bug-gettext@gnu.org])
AC_CONFIG_SRCDIR([gettext-tools/src/msgfmt.c])
AC_CONFIG_AUX_DIR([build-aux])
VERSION_NUMBER=`cd $srcdir \
                && build-aux/git-version-gen .tarball-version`
gl_INIT_PACKAGE_VERSION([$VERSION_NUMBER])
AM_INIT_AUTOMAKE([1.13 silent-rules parallel-tests tar-ustar])

dnl Override automake's tar command used for creating distributions:
dnl - Sort the files by basename, not by dirname, to achieve higher compression
dnl   ratios (because all compression programs have a limited-size "window").
dnl - Use format 'ustar' to avoid "file name is too long (max 99)" errors.
dnl - Use --owner=root --group=root to avoid unsuitable file ownership after
dnl   the tarball is unpacked by root.
am__tar='{ find "$$tardir" -type d | LC_ALL=C sort; find "$$tardir" ! -type d -printf "%f\\t%p\\n" | LC_ALL=C sort | LC_ALL=C cut -f2; } | ${AMTAR} chf - --no-recursion --files-from=- --format=ustar --owner=root --group=root'

dnl Checks for programs.

dnl Checks for libraries.

dnl Checks for header files.

dnl Checks for typedefs, structures, and compiler characteristics.

dnl Checks for library functions.

AC_CONFIG_SUBDIRS([gettext-runtime libtextstyle gettext-tools])

AM_EXTRA_RECURSIVE_TARGETS([maintainer-update-po])

dnl Ensure that "configure --help" lists all the command line options that
dnl are usable with the subdir configures. Really AC_CONFIG_SUBDIRS should
dnl do it by itself.
dnl System types:
AC_CANONICAL_HOST
dnl Optional Features: AC_ARG_ENABLE calls
dnl Optional Packages: AC_ARG_WITH calls
dnl Some influential environment variables: AC_ARG_VAR calls
esyscmd([{ cd gettext-runtime && autoconf --trace=AC_ARG_ENABLE:'$n([$1],[$2])' --trace=AC_ARG_WITH:'$n([$1],[$2])' --trace=AC_ARG_VAR:'$n($@)' && cd ..; cd libtextstyle && autoconf --trace=AC_ARG_ENABLE:'$n([$1],[$2])' --trace=AC_ARG_WITH:'$n([$1],[$2])' --trace=AC_ARG_VAR:'$n($@)' && cd ..; { cd gettext-tools && autoconf --trace=AC_ARG_ENABLE:'$n([$1],[$2])' --trace=AC_ARG_WITH:'$n([$1],[$2])' --trace=AC_ARG_VAR:'$n($@)' && cd ..; } | grep -v installed.libtextstyle | grep -v installed.csharp | grep -v 'installed C#'; } | sed -f build-aux/ac-help.sed ])

AC_CONFIG_FILES([Makefile],
                [FIX_MAKEFILE_DISTRIB])

AC_CONFIG_FILES([gnulib-local/Makefile])

gl_CONFIG_VERSION_STAMP

AC_OUTPUT
