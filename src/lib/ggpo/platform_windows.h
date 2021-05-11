/* -----------------------------------------------------------------------
 * GGPO.net (http://ggpo.net)  -  Copyright 2009 GroundStorm Studios, LLC.
 *
 * Use of this software is governed by the MIT license that can be found
 * in the LICENSE file.
 */

#ifdef ENABLE_GGPO

#ifdef _WINDOWS

#ifndef _GGPO_WINDOWS_H_
#define _GGPO_WINDOWS_H_

#ifdef UNREAL_HOST
// UE4: allow Windows platform types to avoid naming collisions
#	include "Windows/AllowWindowsPlatformTypes.h"
#	include "Windows/prewindowsapi.h"
#endif

#include <winsock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <timeapi.h>
#include "types.h"

class Platform {
public:  // types
   typedef DWORD ProcessID;

public:  // functions
   static ProcessID GetProcessID() { return GetCurrentProcessId(); }
   static void AssertFailed(char *msg) { MessageBoxA(NULL, msg, "GGPO Assertion Failed", MB_OK | MB_ICONEXCLAMATION); }

   static int GetConfigInt(const char* name);
   static bool GetConfigBool(const char* name);

   static uint32_t GetCurrentTimeMS();
   static void SleepMS(int ms);
   static void CreateDir(const char* pathname);
};

#ifdef UNREAL_HOST
// UE4: disallow windows platform types
#	include "Windows/PostWindowsApi.h"
#	include "Windows/HideWindowsPlatformTypes.h"
#endif

#endif // !_GGPO_WINDOWS_H_
#endif // _WINDOWS

#endif // ENABLE_GGPO
