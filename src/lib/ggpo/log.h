/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#ifdef ENABLE_GGPO

#ifndef _LOG_H
#define _LOG_H

#include <cstdarg>
#include <cstdio>

extern void Log(const char *fmt, ...);
extern void Logv(const char *fmt, va_list list);
extern void Logv(FILE *fp, const char *fmt, va_list args);
extern void LogFlush();
extern void LogFlushOnLog(bool flush);

#endif

#endif // ENABLE_GGPO
