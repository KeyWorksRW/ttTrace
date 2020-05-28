// This header file is used to create a pre-compiled header for use in the entire project

#pragma once

#ifndef _WIN32_WINNT_VISTA
    #define _WIN32_WINNT_NT4   0x0400
    #define _WIN32_WINNT_WINXP 0x0501
    #define _WIN32_WINNT_VISTA 0x0600
    #define _WIN32_WINNT_WIN7  0x0601
    #define _WIN32_WINNT_WIN8  0x0602
    #define _WIN32_WINNT_WIN10 0x0A00
#endif

#define WINVER       _WIN32_WINNT_VISTA  // minimum OS required
#define _WIN32_WINNT _WIN32_WINNT_VISTA

#define STRICT
#define WIN32_LEAN_AND_MEAN

#define _WTL_NEW_PAGE_NOTIFY_HANDLERS
#define _ATL_NO_DEBUG_CRT

#define _WINSOCKAPI_  // so atlbase.h won't pull in WinSock2.h

#include <windows.h>

// Ensure the following libraries get passed to the linker

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "gdi32.lib")

#include <stdint.h>

#include <ttTR.h>        // Function for translating strings
#include <ttdebug.h>     // ttASSERT macros
#include <ttlibspace.h>  // Master header file for ttLib

// atlbase.h must be included first so shut off formatting
// clang-format off
#include <atlbase.h>
#include <atlapp.h>
// clang-format on

#include <atlwin.h>
#include <atlctrls.h>
#include <atlframe.h>

extern CAppModule _Module;

#include "strtable.h"

struct TRACE_FLAGS
{
    bool ShowGeneral { true };
    bool ShowWarning { true };
    bool ShowError { true };

    bool ShowEvent { true };
    bool ShowProperty { true };
    bool ShowScript { true };
};

extern TRACE_FLAGS uprof;

constexpr const auto txtVersion = "ttTrace 2.2.0";
constexpr const auto txtCopyRight = "Copyright (c) 2000-2020 [Ralph Walden]";
constexpr const auto txtAppName = "ttTrace";
