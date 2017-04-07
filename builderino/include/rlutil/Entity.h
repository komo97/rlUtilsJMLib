#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "rlUtilJM.h"

class Entity {
public:
	///<param name="_type">The entity's type. Use CHARACTER, BACKGROUND or WALL</param>
	Entity(int _type, int _x, int _y);

	//Getters
	inline int getX() { return x; };
	inline int getY() { return y; };
	inline int getAttack() { return attack; };
	inline int getSpeed() { return speed; };
	inline bool isAlive() { return alive; };
	inline int** getSprite() { return sprite; };
	inline int getSpriteSizeHor() { return spriteSizeX; };
	inline int getSpriteSizeVer() { return spriteSizeY; };
	inline int getType() { return type; };
	inline int getLife() { return life; };

	//Setters
	inline void setX(int _x) { x = _x; };
	inline void setY(int _y) { y = _y; };
	///<summary>
	///Don't fill if it's a background.
	///</summary>
	inline void setAttack(int _attack) { attack = _attack; };
	inline void setLife(int _life) { life = _life; };
	///<summary>
	///Don't fill if it's a background.
	///</summary>
	inline void setSpeed(int _speed) { speed = _speed; };
	void setSprite(int** _sprite);
	void setColors(int col1, int col2, int col3, int col4);
	///<summary>
	///Don't fill if it's a background.
	///</summary>
	inline void setWeaponColor(int _weapon) { weapon = _weapon; };
	void setLetters(char let1, char let2, char let3, char let4);
	///<summary>
	///Don't fill if it's a background.
	///</summary>
	inline void setWeaponLetter(char _let) { charWeapon = _let; };
	void setBackgrounds(int _bg1, int _bg2, int _bg3, int _bg4);
	void InitSprite(int sizeX, int sizeY);

	//Modders
	inline void addX(int _x) { x += _x; };
	inline void addY(int _y) { y += _y; };
	inline void addLife(int _life) { life += _life; };
	inline void addAttack(int _attack) { attack += _attack; };
	inline void changeAlive() { alive ^= true; };
	inline void addSpeed(int _speed) { speed += _speed; };

	void draw();
	void freeSprite();

private:
	int x, y;
	int life;
	int attack;
	int speed;
	int** sprite;
	bool alive;
	int color1;
	int color2;
	int color3;
	int color4;
	int weapon;
	char letter1;
	char letter2;
	char letter3;
	char letter4;
	char charWeapon;
	int bg1;
	int bg2; 
	int bg3;
	int bg4;
	int spriteSizeX;
	int spriteSizeY;
	int type;
};
#endif // !_ENTITY_H_
