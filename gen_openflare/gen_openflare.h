#ifndef gen_openflare_h
//---------------------------------------------------------------------------
#define gen_openflare_h
#include <windows.h>
#include "SDK/Aimp/apiPlugin.h"
#include "SDK/Aimp/apiPlaylists.h"
#include "SDK/Aimp/apiMessages.h"
#include "SDK/Aimp/apiMUI.h"
#include "IUnknownInterfaceImpl.h"
#include <queue>

using namespace std;

#define GPPHDR_VER 0x10
 
#define PLUGIN_NAME "OpenFlare"
#define PLUGIN_NAMEW L"OpenFlare"

#define SHORTNAME        PLUGIN_NAME
#define LONGNAME         "OpenFlare v1"
#define LONGNAMEW        L"OpenFlare v1"

#define WINDOWCAPTION   SHORTNAME
#define DLLDESC         LONGNAME
#define MODULEDESC      LONGNAME
#define AUTHOR_NAME     L"POQDavid"
#define COPYRIGHT       L"Copyright (c) POQDavid. All rights reserved."

#define CLASSNAME       L"OpenFlare1"

#define IPC_OF_GET 23948

typedef struct {
	int version;
	char *description;
	int(*init)();
	void(*config)();
	void(*quit)();
	HWND hwndParent;
	HINSTANCE hDllInstance;
} winampGeneralPurposePlugin;

#endif //gen_openflare_h
