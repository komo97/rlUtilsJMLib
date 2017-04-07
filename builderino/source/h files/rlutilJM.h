/** 
* File: rlutilJM
* About: Description
* Library for creating 2D Games for the Windows CMD.
* For exclusive use with Windows. Not compatible for versions lower than Windows vista.
*
* Uses SFML for audio and networking properties.
* You should probably use the following guide to set up the proyect
* https://www.sfml-dev.org/tutorials/2.3/start-vc.php
*
* This library utilizes rlutil from Tapio Vierros
*
* About: Licence
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from
* the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:

* 1. The origin of this software must not be misrepresented; you must not claim
* that you wrote the original software. If you use this software in a product,
* an acknowledgment in the product documentation would be appreciated but is
* not required.
*
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*
* José María Pérez Parrillat 2016
*/


#pragma once
#ifndef _RLUTILJM_H_
#define _RLUTILJM_H_
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <Windows.h>
#include <Wincon.h>
#include <mmsystem.h>
#include <iostream>
#include "h files\rlutil.h"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"
#define _CRT_SECURE_NO_WARNINGS

#pragma region Structs
using namespace rlutil;

namespace rlutilJM{

//Base structure for every entity of the engine.
//Contains it's position(The left topmost pixel of the sprite array).
//It's life, attack, speed, 4 color channels, 4 background color channels,
//it's weapon color, and a sprite array pointer. 
//Not every single component of this struct will be always required. 
//It's not obligatory to fill each and every component for that same reason.
//Do not fill directly. Use the functions given for that exact purpose.
//Doing this will avoid several basic issues.
typedef struct stats {
	int x, y;
	int life;
	int attack;
	int speed;
	int** sprite;
	int alive;
	int color1, color2, color3, color4;
	int weapon;
	char letter1, letter2, letter3, letter4, charWeapon;
	int bg1, bg2, bg3, bg4;
	int spriteSizeX, spriteSizeY;
	int type;
}stats;

//Each space from the CMD is a buffer in itself and has 3 basic properties.
//A letter, a letter color and a background color.
//Do not use this struct outside it's given functions.
typedef struct tile
{
	int colorVal;
	int backVal;
	char letVal;
	int ocupant;
}tile;

//This is an extra structure specific for status bars. 
//You shouldn't use it outside its given functions.
typedef struct bar
{
	int x, y;
	int currValue, maxValue;
	int color1, color2, color3, constraint;
	int spriteSizeX, spriteSizeY;
	int percent;
}bar;
#pragma endregion

#pragma region Defines
//This are colors bytes. You will probably won't use them at all directly.
#define CLEAR 0
#define FLOOR1 1
#define FLOOR2 (1<<1)
#define FLOOR3 (1<<2)
#define FLOOR4 (1<<3)
#define BACKGROUND1 2
#define BACKGROUND2 (2<<1)
#define BACKGROUND3 (2<<2)
#define BACKGROUND4 (2<<3)
#define BAR1 3
#define BAR2 (3<<1)
#define BAR3 (3<<2)
#define BARCONSTRAINTS (3<<3)
#define CHARACTER1 (4<<1)
#define CHARACTER2 (4<<2)
#define CHARACTER3 (4<<3)
#define CHARACTER4 (4<<4)
#define WEAPON (4<<5)
#define EMPTY 5

//This are defines for directions. You might want to use them on specific cases.
#define DIRRIGHT 1
#define DIRLEFT -1
#define DIRUP 1
#define DIRDOWN -1
#define NOMOVE 0

//This are the type of the entity. You can use them if you want on the functions that require them.
#define CHARACTER 0x0001
#define BACKGROUND 0x0002
#define BAR 0x0003
#define TEXT 0x0004 
 
#pragma endregion


///<summary>
///Keeps the screen size at all times during runtime. 
///Call one time each frame at it's start.
///</summary>
void KeepScreenSize();

///<summary>
///Changes the screen size along with the font size. You should only use this at a startup function and once.
///</summary>
///<param name="_x">Window's width.</param>
///<param name="_y">Window's height.</param>
void WindowSize(int _x, int _y);

///<summary>Initiates an event for music to reproduce. Only works with .ogg and .flac files.
///<remark>Uses SFML</remark></summary>
///<param name="_musicPath">The complete path to the music file. From "C:\\"</param>
///<param name="_loop">Will the music loop? TRUE or FALSE only</param>
///<param name="_vol">The music volume</param>
void PlayMusic(char* _musicPath, BOOL _loop, float _vol);

///<summary>
///Makes the CMD have square pixels. It's already called in WindowSize;
///</summary>
void FontSize();

///<summary>
///This will make and fill a status bar. Should be called in an update method.
///</summary>
///<param name="_entity">The structure that contains a base bar struct.</param>
///<param name="_fullParam">The value that represents 100% of the bar. Use NULL for updating without changing its current size.</param>
///<param name="_currParam">The current percentage of the bar.</param>
void FillBar(bar * _entity, int _fullParam, int _currParam);

///<summary>
///This function inits the logical values for a <remark>stats struct</remark>,
///to init its visual values use <code>SpriteParams()</code>.
///</summary>
///<param name="_entity">The struct entity to init.</param><param name="_x">It's position in X.</param>
///<param name="_y">It's position in Y.</param><param name="_life">Life of the character. Leave in 1 if it's not an alive character.</param>
///<param name="_attack">Attack, if it's not used utilize 0 as the value.</param>
///<param name="_speed">Speed,if it's not used utilize 0 as the value.</param>
///<param name="_characterType">The type of the entity. Please use CHARACTER, BACKGROUND or BAR only.</param>
void SetStats(stats* _entity, int _x, int _y, int _life, int _attack, int _speed, int _characterType);

///<summary>
///Updates the stats of an entity. Using 0 will avoid modifying anything.
///</summary>
///<param name="_entity">The struct entity to work with.</param>
///<param name="_x">The X modifier.</param><param name="_y">The Y modifier.</param>
///<param name="_life">Life modifier.</param><param name="_attack">Attack modifier.</param>
///<param name="_speed">Speed modifier.</param>
void UpdateStats(stats* _entity, int _x, int _y, int _life, int _attack, int _speed);

///<summary>
///Inits an entity's visual parameters. Using 0 will set the channel to nonuse.
///To modify the entity's logical values use <code>SetStats()</code>.
///Returns the sprite array. Use it to fill the sprite. See the example for correct usage.
///</summary>
///<param name="_entity">The struct to work with.</param><param name="_color1">The sprite's channel 1 color.</param>
///<param name="_color2">The sprite's channel 2 color.</param><param name="_color3">The sprite's channel 3 color.</param>
///<param name="_color4">The sprite's channel 4 color.</param><param name="_bg1">The sprite's background channel 1 color.</param>
///<param name="_bg2">The sprite's background channel 2 color.</param><param name="_bg3">The sprite's background channel 3 color.</param>
///<param name="_bg4">The sprite's background channel 4 color.</param><param name="_sprite">The sprite's array.</param>
///<param name="_weapon">The sprite's weapon color.</param>
int** SpriteParams(stats* _entity, int _color1, int _color2, int _color3, int _color4, int _bg1, int _bg2, int _bg3, int _bg4, int** _sprite, int _weapon);

///<summary>
///Assigns the char parameters to an entity. Use " " if you wish to leave the empty space.
///</summary>
///<param name="_entity">The struct to work with.</param><param name="_letter1">The sprite's letter 1.</param>
///<param name="_letter2">The sprite's letter 2.</param><param name="_letter3">The sprite's letter 3.</param>
///<param name="_letter4">The sprite's letter 4.</param><param name="_weapon">The sprite's weapon letter.</param>
void CharSpriteParams(stats* _entity, char _letter1, char _letter2, char _letter3, char _letter4, char _charWeapon);

///<summary>
///Draws a sprite.
///</summary>
///<param name="_entity">The struct that contains the sprite.</param>
void DrawSprite(stats* _entity);

///<summary>
///Inits a sprite array. It's a wrapper for a a normal array init.
///See the example for correct usage.
///</summary>
///<param name="_entity">The entity that contains the sprite array.</param><param name="_spriteSizeX">The array size in X.</param>
///<param name="_spriteSizeY">The array size in Y.</param>
int** InitializeSpriteArray(stats* _entity, int _spriteSizeX, int _spriteSizeY);

///<summary>
///Call once to set up the status bar.
///</summary>
///<param name="_entity">The entity to work with.</param><param name="_x">It's position in X.</param>
///<param name="_y">It's position in Y.</param><param name="_maxValue">The value that represents 100%.</param>
///<param name="_spriteSizeX">The bar's horizontal size.</param><param name="_spriteSizeY">The bar's vertical size.</param>
///<param name="_color1">The color of the bar when it's above 50%.</param><param name="_color2">The bar's color when its above 20% and below 50%.</param>
///<param name="_color3">The color of the bar when it's below 20%.</param><param name="_constraint">The color of the bar's constraints.</param>
void InitializeBar(bar* _entity, int _x, int _y, int _maxValue, int _spriteSizeX, int _spriteSizeY, int _color1, int _color2, int _color3, int _constraint);

///<summary>
///Delete method for the sprite array.
///</summary>
///<param name="_entity">The entity that contains the sprite.</param>
void FreeSpriteArray(stats* _entity);

///<summary>
///Simple method for moving a sprite.
///</summary>
///<param name="_entity">The entity that contains the sprite.</param>
///<param name="_movDirX"> The sprite's direction, use DIRRIGHT, DIRLEFT or NOMOVE.</param>
void SpriteMoveX(stats* _entity, int _movDirX);

///<summary>
///Simple method for moving a sprite.
///</summary>
///<param name="_entity">The entity that contains the sprite.</param>
///<param name="_movDirX">The sprite's direction, use DIRUP, DIRDOWN or NOMOVE.</param>
void SpriteMoveY(stats* _entity, int _movDirY);

///<summary>
///To print the sprites to the screen the engine creates a fake screen macrobuffer which later is printed onto the console.
///Please do not use anywhere.
///</summary>
///<param name="_colorVal">The letter's color.</param>
///<param name="_backVal">The background's color.</param>
///<param name="_letVal">The letter to show.</param>
///<param name="posx">The buffer's position in X.</param>
///<param name="posy">The buffer's position in Y.</param>
///<param name="ocup">The tile's ocupant.</param>
void AddToBuffer(int _colorVal, int _backVal, char _letVal, int posx, int posy, int ocup);

///<summary>
///Clears the fake screen buffer. Call each frame on the start before anything else.
///</summary>
void ClearBuffer();

///<summary>
///Imprime el fakse screen buffer. Solo llamar una vez al final de todas las operaciones
///</summary>
void PrintBuffer();

///<summary>
///Creates the aforementioned fake screen buffer. Do not call anywhere.
///It is already called in <code>WindowSize()</code> 
///</summary>
void CreateFakeScreenBuffer();

///<summary>
///Writes text to the fake screen buffer. Using <code>cout</code> will not give any results, use this instead.
///Doesn't allow line skips.
///</summary>
///<param name="text">The text to show.</param>
///<param name="color">The letter's color.</param>
///<param name="background">The background's color.</param>
///<param name="posx">The starting position of the letters in X.</param>
///<param name="posy">The starting position of the letters in Y.</param>
void TextWrapper(const char* text, int color, int background, int posx, int posy);

///<summary>
///Fills and inits a sprite array.
///</summary>
///<param name ="_entity">The entity to work with.</param>
///<param name ="_sprite">The array to init.</param>
int** FillEmptySprite(stats* _entity, int** _sprite);

///<summary>
///Alternative to filling each element in a sprite array.
///</summary>
///<param name="y">The sprite's space in Y.</param><param name="x">The sprite's space in X.</param>
///<param name="content">The pixel's content.</param><param name="_sprite">The array to work with by ref.</param>
void AddPixel(int y, int x, int content, int*** _sprite);
};
#endif 
