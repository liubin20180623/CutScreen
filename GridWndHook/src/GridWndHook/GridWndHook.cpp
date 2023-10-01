#include "GridWndHook.h"
#pragma data_seg("MySeg")
HWND g_hWnd = NULL;
#pragma data_seg()
#pragma comment(linker, "/SECTION:MySeg,RWS")

HHOOK	g_hWndhook	  = NULL;
LRESULT CALLBACK WndhookProc(int nCode, WPARAM wParam, LPARAM lParam);

BOOL InstallHook(HWND hWnd){
	g_hWnd = hWnd;
	g_hWndhook = SetWindowsHookEx(WH_MOUSE, WndhookProc, g_hInstance, 0);
	return (g_hWndhook != NULL);
}

void UnInstallHook(){
	if (g_hWndhook)UnhookWindowsHookEx(g_hWndhook);
}

LRESULT CALLBACK WndhookProc(int nCode, WPARAM wParam, LPARAM lParam){
	static BOOL	   bCapture			= FALSE;
	static BOOL	   bMouseLBtnDown   = FALSE;
	static HWND    g_hPreWnd		= NULL;
	static HWND    g_hCurWnd		= NULL;
	static RECT    g_preRect;

	if (wParam == WM_NCLBUTTONDOWN || wParam == WM_LBUTTONDOWN){
		bMouseLBtnDown = TRUE;
	}

	if (wParam == WM_MOUSEMOVE && bMouseLBtnDown){
		MOUSEHOOKSTRUCTEX *mhookstruct = (MOUSEHOOKSTRUCTEX*)lParam;
		g_hCurWnd = mhookstruct->hwnd;
		POINT pt  = mhookstruct->pt;
	
		RECT rcWork;
		SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcWork, NULL);

		if (g_hCurWnd && IsWindow(g_hCurWnd) && ::PtInRect(&rcWork, pt)) {
			if (NULL == ::GetParent(g_hCurWnd)) {
				if (g_hPreWnd == NULL) {
					g_hPreWnd = g_hCurWnd;
					::GetWindowRect(g_hPreWnd, &g_preRect);
				}
				else {
					if (g_hPreWnd == g_hCurWnd) {
						int preWidth = g_preRect.right - g_preRect.left;
						int preHeigth = g_preRect.bottom - g_preRect.top;

						RECT rect;
						::GetWindowRect(g_hCurWnd, &rect);
						int curWidth = rect.right - rect.left;
						int curHeigth = rect.bottom - rect.top;

						if (preWidth == curWidth && preHeigth == curHeigth) {
							if (rect.left != g_preRect.left || rect.top != g_preRect.top) {
								SendMessage(g_hWnd, WM_WND_HOOK, USER_MOVE_WINDOWS, (LPARAM)g_hCurWnd);
								bCapture = TRUE;
								return CallNextHookEx(g_hWndhook, nCode, wParam, lParam);
							}
						}
					}
					g_hPreWnd = NULL;
				}
			}
		}
	}

	if (wParam == WM_LBUTTONUP){
		if (bCapture && bMouseLBtnDown) {
			MOUSEHOOKSTRUCT *mhookstruct = (MOUSEHOOKSTRUCT*)lParam;
			POINT pt = mhookstruct->pt;
			RECT rcWork;
			SystemParametersInfo(SPI_GETWORKAREA, NULL, &rcWork, NULL);
			if (::PtInRect(&rcWork, pt)) {
				PostMessage(g_hWnd, WM_WND_HOOK, USER_MOUSE_LBUTTON_UP, (LPARAM)g_hCurWnd);
				bCapture = FALSE;
				g_hPreWnd = NULL;
			}
		}
		bMouseLBtnDown = FALSE;
	}

	return CallNextHookEx(g_hWndhook, nCode, wParam, lParam);
}

