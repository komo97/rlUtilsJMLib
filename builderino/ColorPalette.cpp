#include "rlutil/ColorPalette.h"
#include "rlutilJM.h"

ColorPalette::ColorPalette()
{
	HANDLE WINAPI wnd = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX csbi;
	GetConsoleScreenBufferInfoEx(wnd, &csbi);
	for (int i = 16; --i;)
		colors[i] = csbi.ColorTable[i];
}

void ColorPalette::SetColorRGB(const int & position, const int & r, const int & g, const int & b)
{
	int x = position % 16;
	int _r = r % 256;
	int _g = g % 256;
	int _b = b % 256;
	colors[x] = RGB(_r, _g, _b);
}

void ColorPalette::SetColorBin(const int & position, const DWORD & color)
{
	int x = position % 16;
	colors[x] = color;
}

int ColorPalette::GetR(const int& position)
{
	int x = position % 16;
	return GetRValue(colors[x]);
}

int ColorPalette::GetG(const int& position)
{
	int x = position % 16;
	return GetGValue(colors[x]);
}

int ColorPalette::GetB(const int& position)
{
	int x = position % 16;
	return GetBValue(colors[x]);
}

int ColorPalette::UseColor(const int & color, const bool & isBg)
{
	switch (color)
	{
	case 0:
		return isBg ? BACKCOLOR1 : LETCOLOR1;
	case 1:
		return isBg ? BACKCOLOR2 : LETCOLOR2;
	case 2:
		return isBg ? BACKCOLOR3 : LETCOLOR3;
	case 3:
		return isBg ? BACKCOLOR4 : LETCOLOR4;
	case 4:
		return isBg ? BACKCOLOR5 : LETCOLOR5;
	case 5:
		return isBg ? BACKCOLOR6 : LETCOLOR6;
	case 6:
		return isBg ? BACKCOLOR7 : LETCOLOR7;
	case 7:
		return isBg ? BACKCOLOR8 : LETCOLOR8;
	case 8:
		return isBg ? BACKCOLOR9 : LETCOLOR9;
	case 9:
		return isBg ? BACKCOLOR10 : LETCOLOR10;
	case 10:
		return isBg ? BACKCOLOR11 : LETCOLOR11;
	case 11:
		return isBg ? BACKCOLOR12 : LETCOLOR12;
	case 12:
		return isBg ? BACKCOLOR13 : LETCOLOR13;
	case 13:
		return isBg ? BACKCOLOR14 : LETCOLOR14;
	case 14:
		return isBg ? BACKCOLOR15 : LETCOLOR15;
	case 15:
		return isBg ? BACKCOLOR16 : LETCOLOR16;
	}
}

void ColorPalette::SetActivePalette(CONSOLE_SCREEN_BUFFER_INFOEX & inf)
{
	for (int i = 16; i--;)
		inf.ColorTable[i] = colors[i];
}
