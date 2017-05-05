#pragma once
#ifndef _BAR_H_
#define _BAR_H_
#include "rlUtilJM.h"
#include "Entity.h"

class Bar : Entity{
public:
	Bar(int _x, int _y);
	~Bar();
	//setters
	inline void setX(const int& _x) { x = _x; };
	inline void setY(const int& _y) { y = _y; };
	inline void setValue(const int& val) { currValue = val; };
	inline void setMax(const int& val) { maxValue = val; };
	void setColors(const int& col1, const int& col2, const int& col3);
	inline void setConstraint(const int& cons) { constraint = cons; };
	void InitSprite(const int& _width, const int& _height);
	 
	//getters
	inline int getX() { return x; };
	inline int getY() { return y; };
	inline int getValue() { return currValue; };
	inline int getMax() { return maxValue; };
	inline int getPercent() { return percent; };
	inline int getSizeHor() { return spriteSizeX; };
	inline int getSizeVer() { return spriteSizeY; };

	//modders
	inline void addValue(const int& x) { currValue += x; };

	void draw();

private:
	void DrawBody();
	int x, y;
	int currValue, maxValue;
	int color1, color2, color3, constraint;
	int spriteSizeX, spriteSizeY;
	int percent;
};

#endif