## Makefile for libtextstyle/install-tests.
## Copyright (C) 2025 Free Software Foundation, Inc.
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

installcheck-local:
	$(CC) -I$(includedir) -L$(libdir) \
	      $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
	      $(AM_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) $(LDFLAGS) \
	      -o test-version $(srcdir)/test-version.c -ltextstyle
	@AUGMENT_SHLIBPATH@ ./test-version
	rm -rf test-version test-version$(EXEEXT)
	$(CC) -I$(includedir) -L$(libdir) \
	      $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
	      -DTOP_SRCDIR=\"$(top_srcdir)/\" \
	      $(AM_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) $(LDFLAGS) \
	      -o test-api $(srcdir)/test-api.c -ltextstyle
	@AUGMENT_SHLIBPATH@ ./test-api
	rm -rf test-api test-api$(EXEEXT)

EXTRA_DIST = test-version.c test-api.c
CLEANFILES = test-version test-version$(EXEEXT) test-api test-api$(EXEEXT)
