#pragma once

#include "../ResDll/resource.h"

static HBITMAP LoadBMP(int resourceID)
{
	HMODULE hModule = LoadLibrary(L"ResDll.dll");

	HBITMAP hBitmap = NULL;

	if (hModule != NULL)
	{
		hBitmap = LoadBitmap(hModule, MAKEINTRESOURCE(resourceID));
	}

	FreeResource(hModule);

	return hBitmap;
}

static HICON LoadICO(int resourceID)
{
	HMODULE hModule = LoadLibrary(L"ResDll.dll");

	HICON hIcon = NULL;

	if (hModule != NULL)
	{
		hIcon = LoadIcon(hModule, MAKEINTRESOURCE(resourceID));
	}

	FreeResource(hModule);
	return hIcon;
}
