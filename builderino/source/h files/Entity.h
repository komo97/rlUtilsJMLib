#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "rlUtilJM.h"
#include "rlVector2.h"

class Entity {
public:
	///<param name="_type">The entity's type. Use CHARACTER, BACKGROUND or WALL</param>
	Entity(const int& _type, const int& _x, const int& _y);
	///<summary>Empty entity</summary>
	Entity();
	~Entity();
	//Getters
	inline int getX() { return pos.getX(); };
	inline float getXf() { return pos.getXf(); };
	inline int getY() { return pos.getY(); };
	inline float getYf(){ return pos.getYf(); };
	inline int getAttack() { return attack; };
	inline int getSpeed() { return speed; };
	inline bool isAlive() { return alive; };
	inline int** getSprite() { return sprite; };
	inline int getSpriteSizeHor() { return spriteSizeX; };
	inline int getSpriteSizeVer() { return spriteSizeY; };
	inline int getType() { return type; };
	inline int getLife() { return life; };
	inline bool isOnCollision() { return isCollisioning; };
	inline Entity* collisionOther() { return otherColEntity; };
	inline bool getIsStatic() { return isStatic; };

	//Setters
	inline void setX(const float& _x) { pos.setX(_x); };
	inline void setY(const float& _y) { pos.setY( _y); };
	///<summary>
	///Don't fill if it's a background.
	///</summary>
	inline void setAttack(const int& _attack) { attack = _attack; };
	inline void setLife(const int& _life) { life = _life; };
	///<summary>
	///Don't fill if it's a background.
	///</summary>
	inline void setSpeed(const int& _speed) { speed = _speed; };
	void setSprite(int** const& _sprite);
	void setColors(const int& col1, const int& col2, const int& col3, const int& col4);
	///<summary>
	///Don't fill if it's a background.
	///</summary>
	inline void setWeaponColor(const int& _weapon) { weapon = _weapon; };
	void setLetters(const char& let1, const char& let2, const char& let3, const char& let4);
	///<summary>
	///Don't fill if it's a background.
	///</summary>
	inline void setWeaponLetter(const char& _let) { charWeapon = _let; };
	void setBackgrounds(const int& _bg1, const int& _bg2, const int& _bg3, const int& _bg4);
	void InitSprite(const int& sizeX, const int& sizeY);
	inline void setIsStatic(const bool& _static) { isStatic = _static; };

	//Modifiers
	void addX(const float& _x);
	void addY(const float& _y);
	inline void addLife(const int& _life) { life += _life; };
	inline void addAttack(const int& _attack) { attack += _attack; };
	inline void changeAlive() { alive ^= true; };
	inline void addSpeed(const int& _speed) { speed += _speed; };

	void draw();
	void freeSprite();

	///<summary>
	///DO NOT CALL THIS METHOD.
	///It is used internally to manage layer collisions.
	///</summary>
	inline void SetCollisionState(const bool& onCol, Entity* const& other) { isCollisioning = onCol; otherColEntity = other; };

private:

	void DrawBody();
	rlVector2 pos;
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
	bool isCollisioning;
	bool isStatic;
	Entity* otherColEntity;
};
#endif // !_ENTITY_H_
