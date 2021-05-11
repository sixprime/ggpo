/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#ifdef ENABLE_GGPO

#include "log.h"
#include "types.h"

static FILE *logfile = NULL;

void LogFlush()
{
#if 0
    if (logfile) {
       fflush(logfile);
    }
#endif
}

static char logbuf[4 * 1024 * 1024];

void Log(const char *fmt, ...)
{
#if 0
   va_list args;
   va_start(args, fmt);
   Logv(fmt, args);
   va_end(args);
#endif
}

void Logv(const char *fmt, va_list args)
{
#if 0
    if (!Platform::GetConfigBool("ggpo.log") || Platform::GetConfigBool("ggpo.log.ignore")) {
       return;
    }
    if (!logfile) {
       snprintf(logbuf, ARRAY_SIZE(logbuf), "log-%d.log", Platform::GetProcessID());
       logfile = fopen(logbuf, "w");
    }
    Logv(logfile, fmt, args);
#endif
}

void Logv(FILE *fp, const char *fmt, va_list args)
{
#if 0
   if (Platform::GetConfigBool("ggpo.log.timestamps")) {
      static int start = 0;
      int t = 0;
      if (!start) {
         start = Platform::GetCurrentTimeMS();
      } else {
         t = Platform::GetCurrentTimeMS() - start;
      }
      fprintf(fp, "%d.%03d : ", t / 1000, t % 1000);
   }

   vfprintf(fp, fmt, args);
   fflush(fp);
   
   vsnprintf(logbuf, ARRAY_SIZE(logbuf), fmt, args);
#endif
}

#endif // ENABLE_GGPO
