#pragma once
#ifndef _BAR_H_
#define _BAR_H_
#include "rlUtilJM.h"

class Bar{
public:
	Bar(int _x, int _y);

	//setters
	inline void setX(int _x) { x = _x; };
	inline void setY(int _y) { y = _y; };
	inline void setValue(int val) { currValue = val; };
	inline void setMax(int val) { maxValue = val; };
	void setColors(int col1, int col2, int col3);
	inline void setConstraint(int cons) { constraint = cons; };
	void InitSprite(int _width, int _height);

	//getters
	inline int getX() { return x; };
	inline int getY() { return y; };
	inline int getValue() { return currValue; };
	inline int getMax() { return maxValue; };
	inline int getPercent() { return percent; };
	inline int getSizeHor() { return spriteSizeX; };
	inline int getSizeVer() { return spriteSizeY; };

	//modders
	inline void addValue(int x) { currValue += x; };

	void draw();

private:
	int x, y;
	int currValue, maxValue;
	int color1, color2, color3, constraint;
	int spriteSizeX, spriteSizeY;
	int percent;
};

#endif