
#include <windows.h>
#include <richedit.h>

#include "prelude.h"
#include "storage.h"
#include "connect.h"
#include "machdep.h"

LPSTR readRegStrDup(LPSTR Key, LPSTR Default)
{
    return readRegString(HKEY_CURRENT_USER, hugsRegRoot, Key, Default);
}

void readRegStr(LPSTR Key, LPSTR Default, LPSTR Buffer)
{
    String res = readRegStrDup(Key, Default);
    strcpy(Buffer, res);
    free(res);
}

void RegistryReadMru(char** Buffer)
{
    int i;
    char Buf[5] = "Mru1";

    for (i = 0; ; i++) {
	char* Res;
	Buf[3] = i + '0';
	Res = readRegStrDup(Buf, "");

	Buffer[i] = Res;
	if (Res[0] == '\0') {
	    Buffer[i] = NULL;
	    free(Res);
	    break;
	}
    }
}

void RegistryWriteMru(char** Buffer)
{
    int i;
    char Buf[5] = "Mru1";

    for (i = 0; Buffer[i] != NULL; i++) {
	Buf[3] = i + '0';
	writeRegString(Buf, Buffer[i]);
    }
}

void RegistryReadFont(CHARFORMAT* cf)
{
    cf->cbSize = sizeof(CHARFORMAT);
    cf->dwMask = CFM_BOLD | CFM_FACE | CFM_ITALIC | CFM_SIZE;
    cf->dwEffects = 0;

    readRegStr("FontName", "Courier New", cf->szFaceName);
    cf->yHeight = readRegInt("FontSize", 16);
    if (readRegInt("FontWeight", 0)) cf->dwEffects |= CFE_BOLD;
    if (readRegInt("FontItalic", 0)) cf->dwEffects |= CFE_ITALIC;
}

void RegistryWriteFont(CHARFORMAT* cf)
{
    writeRegString("FontName", cf->szFaceName);
    writeRegInt("FontSize", cf->yHeight);
    writeRegInt("FontWeight", (cf->dwEffects & CFE_BOLD ? 1 : 0));
    writeRegInt("FontItalic", (cf->dwEffects & CFE_ITALIC ? 1 : 0));
}

void RegistryReadWindowPos(HWND hWnd)
{
    int x, y, cx, cy;
    int Maximized = readRegInt("WindowMaximized", 1);

    if (Maximized) {
	ShowWindow(hWnd, SW_MAXIMIZE);
	return;
    }

    x = readRegInt("WindowLeft", -1);
    y = readRegInt("WindowTop", -1);
    cx = readRegInt("WindowWidth", -1);
    cy = readRegInt("WindowHeight", -1);

    if (x == -1) return;

    SetWindowPos(hWnd, NULL, x, y, cx, cy, SWP_NOZORDER);
}

void RegistryWriteWindowPos(HWND hWnd)
{
    WINDOWPLACEMENT wpl;
    int Maximized;

    GetWindowPlacement(hWnd, &wpl);
    Maximized = (wpl.showCmd == SW_MAXIMIZE ? 1 : 0);
    writeRegInt("WindowMaximized", Maximized);

    if (Maximized)
	return;

    writeRegInt("WindowLeft", wpl.rcNormalPosition.left);
    writeRegInt("WindowTop", wpl.rcNormalPosition.top);
    writeRegInt("WindowWidth", wpl.rcNormalPosition.right - wpl.rcNormalPosition.left);
    writeRegInt("WindowHeight", wpl.rcNormalPosition.bottom - wpl.rcNormalPosition.top);
}
