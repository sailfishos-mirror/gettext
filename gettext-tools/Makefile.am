## Makefile for the gettext-tools directory of GNU gettext
## Copyright (C) 1995-2024 Free Software Foundation, Inc.
##
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <https://www.gnu.org/licenses/>.

## Process this file with automake to produce Makefile.in.

AUTOMAKE_OPTIONS = 1.5 gnu
ACLOCAL_AMFLAGS = -I m4 -I ../gettext-runtime/m4 -I ../m4 -I gnulib-m4 -I libgrep/gnulib-m4 -I libgettextpo/gnulib-m4 -I tests/gnulib-m4

SUBDIRS = gnulib-lib libgrep src libgettextpo po its projects styles emacs misc man m4 tests system-tests gnulib-tests examples doc

EXTRA_DIST = misc/DISCLAIM
MOSTLYCLEANFILES = core *.stackdump


# Files installed for use by gettextize.

gettextsrcdir = $(datadir)/gettext
gettextsrc_SCRIPTS = ../build-aux/config.rpath


# Files installed for the examples.

examplesbuildauxdir = $(docdir)/examples/build-aux
examplesbuildaux_DATA = \
  ../build-aux/javacomp.sh.in ../build-aux/javaexec.sh.in \
  ../build-aux/csharpcomp.sh.in ../build-aux/csharpexec.sh.in


# Files copied from other directories.

all-local: $(srcdir)/ABOUT-NLS
$(srcdir)/ABOUT-NLS: $(srcdir)/../gettext-runtime/ABOUT-NLS
	cp $(srcdir)/../gettext-runtime/ABOUT-NLS $(srcdir)/ABOUT-NLS


# Allow users to use "gnulib-tool --update".
EXTRA_DIST += gnulib-m4/gnulib-cache.m4


# Windows support.

EXTRA_DIST += INSTALL.windows


# Cygwin support.

EXTRA_DIST += woe32dll/export.h


# Support for "make dist" without prior "make".

# Prerequisites of both distdir1 and distdir2.
.PHONY: programs-for-distdir
programs-for-distdir:
	cd gnulib-lib && $(MAKE) $(AM_MAKEFLAGS)
	cd libgrep && $(MAKE) $(AM_MAKEFLAGS)
	cd src \
	&& $(MAKE) $(AM_MAKEFLAGS) built-sources \
	&& $(MAKE) $(AM_MAKEFLAGS) \
	   msgcmp$(EXEEXT) \
	   msgfmt$(EXEEXT) \
	   msgmerge$(EXEEXT) \
	   msgunfmt$(EXEEXT) \
	   xgettext$(EXEEXT) \
	   msgattrib$(EXEEXT) \
	   msgcat$(EXEEXT) \
	   msgcomm$(EXEEXT) \
	   msgconv$(EXEEXT) \
	   msgen$(EXEEXT) \
	   msgexec$(EXEEXT) \
	   msgfilter$(EXEEXT) \
	   msggrep$(EXEEXT) \
	   msginit$(EXEEXT) \
	   msguniq$(EXEEXT) \
	   recode-sr-latin$(EXEEXT)

# Ensure that the manual pages are up-to-date when "make dist" runs.
# Hidden from automake, but really activated. Works around an automake bug.
#distdir: distdir1
.PHONY: distdir1
distdir1: \
  man/msgcmp.1 \
  man/msgfmt.1 \
  man/msgmerge.1 \
  man/msgunfmt.1 \
  man/xgettext.1 \
  man/msgattrib.1 \
  man/msgcat.1 \
  man/msgcomm.1 \
  man/msgconv.1 \
  man/msgen.1 \
  man/msgexec.1 \
  man/msgfilter.1 \
  man/msggrep.1 \
  man/msginit.1 \
  man/msguniq.1 \
  man/recode-sr-latin.1
man/msgcmp.1 \
  man/msgfmt.1 \
  man/msgmerge.1 \
  man/msgunfmt.1 \
  man/xgettext.1 \
  man/msgattrib.1 \
  man/msgcat.1 \
  man/msgcomm.1 \
  man/msgconv.1 \
  man/msgen.1 \
  man/msgexec.1 \
  man/msgfilter.1 \
  man/msggrep.1 \
  man/msginit.1 \
  man/msguniq.1 \
  man/recode-sr-latin.1 \
  : gen-man1
.PHONY: gen-man1
gen-man1: programs-for-distdir \
          src/msgcmp.c man/msgcmp.x \
          src/msgfmt.c man/msgfmt.x \
          src/msgmerge.c man/msgmerge.x \
          src/msgunfmt.c man/msgunfmt.x \
          src/xgettext.c man/xgettext.x \
          src/msgattrib.c man/msgattrib.x \
          src/msgcat.c man/msgcat.x \
          src/msgcomm.c man/msgcomm.x \
          src/msgconv.c man/msgconv.x \
          src/msgen.c man/msgen.x \
          src/msgexec.c man/msgexec.x \
          src/msgfilter.c man/msgfilter.x \
          src/msggrep.c man/msggrep.x \
          src/msginit.c man/msginit.x \
          src/msguniq.c man/msguniq.x \
          src/recode-sr-latin.c man/recode-sr-latin.x
	cd man \
	&& $(MAKE) $(AM_MAKEFLAGS) \
	   msgcmp.1 \
	   msgfmt.1 \
	   msgmerge.1 \
	   msgunfmt.1 \
	   xgettext.1 \
	   msgattrib.1 \
	   msgcat.1 \
	   msgcomm.1 \
	   msgconv.1 \
	   msgen.1 \
	   msgexec.1 \
	   msgfilter.1 \
	   msggrep.1 \
	   msginit.1 \
	   msguniq.1 \
	   recode-sr-latin.1

# Ensure that the examples are up-to-date when "make dist" runs.
# Hidden from automake, but really activated. Works around an automake bug.
#distdir: distdir2
.PHONY: distdir2
distdir2: programs-for-distdir
	cd misc && $(MAKE) $(AM_MAKEFLAGS)
	cd examples && $(MAKE) $(AM_MAKEFLAGS)


maintainer-update-po: $(top_builddir)/config.status
	$(SHELL) ./config.status --recheck
	$(SHELL) ./config.status po/Makefile.in po-directories
	cd po && $(MAKE) update-po
	cd examples && $(MAKE) maintainer-update-po
