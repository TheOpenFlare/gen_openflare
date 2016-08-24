#include "stdafx.h"
#include <Windows.h>
#include "SDK\Winamp\wa_ipc.h"
#include <string>
#include "gen_openflare.h"

using namespace std;

int  init(void);
void config(void);
void quit(void);

static LRESULT WINAPI SubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void SendMsg(wstring msg);
wstring GetCurrentFile();
wstring GetStatus();

wchar_t *WIN_NAME = L"OpenFlare Client";

winampGeneralPurposePlugin plugin = {
	GPPHDR_VER,
	PLUGIN_NAME,
	init,
	config,
	quit,
	0,
	0,
};


WNDPROC oldWndProc;
BOOL fUnicode;
int init() {
	fUnicode = IsWindowUnicode(plugin.hwndParent);
	oldWndProc = (WNDPROC)((fUnicode) ? SetWindowLongPtrW(plugin.hwndParent, GWLP_WNDPROC, (LONG_PTR)SubclassProc) : SetWindowLongPtrA(plugin.hwndParent, GWLP_WNDPROC, (LONG_PTR)SubclassProc));
	return 0;
}

void config() {
}

void quit() { }

static LRESULT WINAPI SubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_WA_IPC:
		if (lParam == IPC_CB_MISC)
		{
			if (wParam == IPC_CB_MISC_TITLE)
			{
				SendMsg(GetCurrentFile() + L"<DATASEPARATOR>" + GetStatus());
			}

			if (wParam == IPC_CB_MISC_STATUS)
			{
				SendMsg(GetCurrentFile() + L"<DATASEPARATOR>" + GetStatus());
			}
		}
		break;
	case IPC_OF_GET:
		SendMsg(GetCurrentFile() + L"<DATASEPARATOR>" + GetStatus());
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return (fUnicode) ? CallWindowProcW(oldWndProc, hwnd, msg, wParam, lParam) : CallWindowProcA(oldWndProc, hwnd, msg, wParam, lParam);
}

wstring GetStatus() {
	wstring msg_st;
	int res;
	res = SendMessage(plugin.hwndParent, WM_WA_IPC, 0, IPC_ISPLAYING);

	switch (res) {

	case 1:
		msg_st = L"STATUS:playing";
		break;
	case 3:
		msg_st = L"STATUS:paused";
		break;
	case 0:
		msg_st = L"STATUS:not_playing";
		break;
	default:
		msg_st = L"STATUS:none";
	}

	return msg_st;
}
wstring GetCurrentFile() {
	wstring str = L"No Data";
	wchar_t *filename = (wchar_t *)SendMessage(plugin.hwndParent, WM_WA_IPC, 0, IPC_GET_PLAYING_FILENAME);

	int idx = SendMessage(plugin.hwndParent, WM_WA_IPC, 0, IPC_GETLISTPOS);
	wchar_t *filename2 = (wchar_t *)SendMessage(plugin.hwndParent, WM_WA_IPC, idx, IPC_GETPLAYLISTFILEW);

	if (filename != NULL) { str = filename; }
	else { str = filename2; }

	return str;
}

void SendMsg(wstring msg) {
	LRESULT copyDataResult;
	HWND target = FindWindow(NULL, WIN_NAME);
	wchar_t * str2 = (wchar_t *)msg.c_str();
	if (target)
	{
		COPYDATASTRUCT cds;
		cds.dwData = 1;
		cds.cbData = sizeof(TCHAR) * (wcslen(str2) + 1);
		cds.lpData = str2;
		copyDataResult = SendMessage(target, WM_COPYDATA, (WPARAM)target, (LPARAM)(LPVOID)&cds);
	}
}

extern "C" __declspec(dllexport) winampGeneralPurposePlugin * winampGetGeneralPurposePlugin() {
	return &plugin;
}