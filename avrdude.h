/*
 * avrdude - A Downloader/Uploader for AVR device programmers
 * Copyright (C) 2007 Joerg Wunsch
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* $Id$ */

#ifndef avrdude_h
#define avrdude_h

extern char * progname;		/* name of program, for messages */
extern char progbuf[];		/* spaces same length as progname */

extern int ovsigck;		/* override signature check (-F) */
extern int verbose;		/* verbosity level (-v, -vv, ...) */
extern int quell_progress;	/* quiteness level (-q, -qq) */

int avrdude_message(const int msglvl, const char *format, ...);

#define MSG_INFO    (0) /* no -v option, can be supressed with -qq */
#define MSG_NOTICE  (1) /* displayed with -v */
#define MSG_NOTICE2 (2) /* displayed with -vv, used rarely */
#define MSG_DEBUG   (3) /* displayed with -vvv */
#define MSG_TRACE   (4) /* displayed with -vvvv, show trace commuication */
#define MSG_TRACE2  (5) /* displayed with -vvvvv */

#if defined(WIN32NATIVE)

#include "ac_cfg.h"
#include <windows.h>

#ifdef _MSC_VER
#include "msvc/msvc_compat.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(HAVE_USLEEP)
int usleep(unsigned int us);
#endif

#if !defined(HAVE_GETTIMEOFDAY)
struct timezone;
int gettimeofday(struct timeval *tv, struct timezone *tz);
#endif /* HAVE_GETTIMEOFDAY */

#ifdef __cplusplus
}
#endif
#endif /* defined(WIN32NATIVE) */

#endif
