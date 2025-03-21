/* Implementation of the textdomain(3) function.
   Copyright (C) 1995-2024 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation; either version 2.1 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdlib.h>
#include <string.h>

#include "gettextP.h"
#ifdef _LIBC
# include <libintl.h>
#else
# include "libgnuintl.h"
#endif

/* Handle multi-threaded applications.  */
#ifdef _LIBC
# include <libc-lock.h>
# define gl_rwlock_define __libc_rwlock_define
# define gl_rwlock_wrlock __libc_rwlock_wrlock
# define gl_rwlock_unlock __libc_rwlock_unlock
#else
# include "glthread/lock.h"
#endif

/* @@ end of prolog @@ */


/* Names for the libintl functions are a problem.  They must not clash
   with existing names and they should follow ANSI C.  But this source
   code is also used in GNU C Library where the names have a __
   prefix.  So we have to make a difference here.  */
#ifdef _LIBC
# define TEXTDOMAIN __textdomain
# ifndef strdup
#  define strdup(str) __strdup (str)
# endif
#else
# define TEXTDOMAIN libintl_textdomain
#endif

/* Set the current default message catalog to DOMAINNAME.
   If DOMAINNAME is null, return the current default.
   If DOMAINNAME is "", reset to the default of "messages".  */
char *
TEXTDOMAIN (const char *domainname)
{
  char *new_domain;
  char *old_domain;

  /* A NULL pointer requests the current setting.  */
  if (domainname == NULL)
    return (char *) _nl_current_default_domain;

  gl_rwlock_wrlock (_nl_state_lock);

  old_domain = (char *) _nl_current_default_domain;

  /* If domain name is the null string set to default domain "messages".  */
  if (domainname[0] == '\0'
      || strcmp (domainname, _nl_default_default_domain) == 0)
    {
      _nl_current_default_domain = _nl_default_default_domain;
      new_domain = (char *) _nl_current_default_domain;
    }
  else if (strcmp (domainname, old_domain) == 0)
    /* This can happen and people will use it to signal that some
       environment variable changed.  */
    new_domain = old_domain;
  else
    {
      /* If the following strdup fails '_nl_current_default_domain'
	 will be NULL.  This value will be returned and so signals we
	 are out of memory.  */
      new_domain = strdup (domainname);
      if (new_domain != NULL)
	_nl_current_default_domain = new_domain;
    }

  /* We use this possibility to signal a change of the loaded catalogs
     since this is most likely the case and there is no other easy we
     to do it.  Do it only when the call was successful.  */
  if (new_domain != NULL)
    {
      ++_nl_msg_cat_cntr;

      if (old_domain != new_domain && old_domain != _nl_default_default_domain)
	free (old_domain);
    }

  gl_rwlock_unlock (_nl_state_lock);

  return new_domain;
}

#ifdef _LIBC
/* Alias for function name in GNU C Library.  */
weak_alias (__textdomain, textdomain);
#endif
