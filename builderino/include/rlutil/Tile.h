#pragma once
#ifndef _TILE_H_
#define _TILE_H_

class Tile {
public:
	inline int getColor() { return colorVal; };
	inline int getBackground() { return backVal; };
	inline char getLetter() { return letVal; };
	inline int getOcupant() { return ocupant; };
	inline void setColor(int _color) { colorVal = _color; };
	inline void setBackground(int _back) { backVal = _back; };
	inline void setChar(char _letter) { letVal = _letter; };
	inline void setOcupant(int _ocupant) { ocupant = _ocupant; };

private:
	int colorVal;
	int backVal;
	char letVal;
	int ocupant;
};
#endif