#include "dllmain.h"
HINSTANCE g_hInstance = NULL;
BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved)
{
	g_hInstance = (HINSTANCE)hModule;
	return TRUE;
}