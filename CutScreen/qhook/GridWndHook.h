#pragma once
#include <windows.h>

#ifdef MOUSEHOOK_EXPORTS
#define MOUSEHOOK_API extern "C" __declspec(dllexport)
#else
#define MOUSEHOOK_API extern "C" __declspec(dllimport)
#endif

#define  WM_WND_HOOK					0xD123
#define	 USER_MOVE_WINDOWS				1
#define  USER_MOUSE_LBUTTON_UP			2

MOUSEHOOK_API BOOL InstallHook(HWND hWnd);
MOUSEHOOK_API void UnInstallHook();
