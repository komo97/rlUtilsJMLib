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
	Entity* getEntity() { return entity; };
	inline void setColor(const int& _color) { colorVal = _color; };
	inline void setBackground(const int& _back) { backVal = _back; };
	inline void setChar(const char& _letter) { letVal = _letter; };
	inline void setOcupant(const int& _ocupant) { ocupant = _ocupant; };
	void setEntity(Entity* const& _entity) { entity = _entity; };

private:
	int colorVal;
	int backVal;
	char letVal;
	int ocupant;
	Entity* entity = NULL;
};
#endif