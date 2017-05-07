#pragma once
#include <Windows.h>
class ColorPalette {
public:
	ColorPalette();
	void SetColorRGB(const int& position, const int& r, const int& g, const int& b);
	void SetColorBin(const int& position, const DWORD& color);
	int GetR(const int& position);
	int GetG(const int& position);
	int GetB(const int& position);
	int UseColor(const int& color, const bool& isBg);
	void SetActivePalette(CONSOLE_SCREEN_BUFFER_INFOEX& inf);
private:
	COLORREF colors[16];
	
};