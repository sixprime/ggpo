/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#ifdef __GNUC__

#include "platform_unix.h"

int Platform::GetConfigInt(const char *name)
{
  if (const char *env_p = std::getenv(name))
  {
    return atoi(env_p);
  }
  return 0;
}

bool Platform::GetConfigBool(const char *name)
{
  if (const char *env_p = std::getenv(name))
  {
    return atoi(env_p) != 0 || strncmp(env_p, "true", 4) == 0;
  }
  return false;
}

uint32_t Platform::GetCurrentTimeMS()
{
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (ts.tv_sec * 1000) + (ts.tv_nsec / (1000 * 1000));
}

void Platform::SleepMS(int milliseconds)
{
#if _POSIX_C_SOURCE >= 199309L
  struct timespec ts;
  ts.tv_sec = milliseconds / 1000;
  ts.tv_nsec = (milliseconds % 1000) * 1000000;
  nanosleep(&ts, NULL);
#else
  usleep(milliseconds * 1000);
#endif
}

void Platform::CreateDir(const char *pathname)
{
  mkdir(pathname, -1);
}

static void __attribute__((constructor)) DllMain()
{
  srand(Platform::GetCurrentTimeMS() + Platform::GetProcessID());
}

#endif // __GNUC__
