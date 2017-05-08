#pragma once
#ifndef _TILE_H_
#define _TILE_H_
class Entity;
class Tile {
public:
	inline int getColor() { return colorVal; };
	inline int getBackground() { return backVal; };
	inline char getLetter() { return letVal; };
	inline int getOcupant() { return ocupant; };
	inline Entity* getEntity() { return entity; };
	inline void setColor(const int& _color) { colorVal = _color; };
	inline void setBackground(const int& _back) { backVal = _back; };
	inline void setChar(const char& _letter) { letVal = _letter; };
	inline void setOcupant(const int& _ocupant) { ocupant = _ocupant; };
	inline void setEntity(Entity* const& _entity) { entity = _entity; };
	inline void setStatic(bool _static) { isStatic = _static; };
	inline void setDrawn(bool _drawn) { isDrawn = _drawn; };
	inline bool getIsStatic() { return isStatic; };
	inline bool getIsDrawn() { return isDrawn; };

private:
	int colorVal;
	int backVal;
	char letVal;
	int ocupant;
	Entity* entity = NULL;
	bool isStatic;
	bool isDrawn;
};
#endif