/* --------------------------------------------------------------------------
 * WinUtils.h:	Jos� Enrique Gallardo Ruiz, Feb 1999
 *
 * Hugs for Windows is Copyright (c) Jos� Enrique Gallardo, Mark P Jones,
 * Alastair Reid, the Yale Haskell Group, and the Oregon Graduate Institute
 * of Science and Technology, 1994-1999, All rights reserved.  It is
 * distributed as free software under the license in the file "License",
 * which is included in the distribution.
 *
 * This file contains the Header file for some common functions
 * ------------------------------------------------------------------------*/

#define __WINUTILS_H

VOID 	CenterDialogInParent 	(HWND);
VOID	SetDialogFont		(HWND, HFONT);
BOOL 	CheckExt 		(LPCSTR, LPCSTR);
VOID 	DrawTransparentBitmap	(HDC, HBITMAP, UINT, UINT, COLORREF);
VOID 	DrawBitmap 		(HDC, HBITMAP, UINT, UINT);
VOID 	ExecDialog 		(HINSTANCE, WORD, WNDPROC);
VOID	FullPath		(LPSTR, LPCSTR);
VOID	MapBitmap 		(HBITMAP, COLORREF, COLORREF);
HBITMAP LoadMappedBitmap	(HINSTANCE, LPCSTR);
HBITMAP ResizeBitmap            (HBITMAP, UINT, UINT);
INT 	SetWorkingDir 		(LPCSTR);
VOID 	StrReplace		(CHAR*, CHAR*, CHAR*, CHAR*);
VOID    ShortFileName           (CHAR *, CHAR *);
