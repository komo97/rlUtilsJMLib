#pragma once
/**
* File: rlUtilJM
* About: Description
* Library for creating 2D Games for the Windows CMD.
* For exclusive use with Windows. Not compatible for versions lower than Windows vista.
*
* Uses SFML for audio and networking properties.
* You should probably use the following guide to set up the project
* https://www.sfml-dev.org/tutorials/2.3/start-vc.php
*
* This library utilizes rlutil from Tapio Vierros
*
* About: License
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
#ifndef _RLUTILJM_H_
#define _RLUTILJM_H_

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <Windows.h>
#include <Wincon.h>
#include <mmsystem.h>
#include <iostream>
#include "rlutil\ColorPalette.h"
#include "rlutil\rlutil.h"
#include "SFML\System.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"
#include "SFML\Window.hpp"
#include "Tile.h"
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#define _CRT_SECURE_NO_WARNINGS


using namespace rlutil;

	//This are color bytes. Use them for sprites along with the function
	//SetPixel.
#define CLEAR			0
#define BACKGROUND1		2
#define BACKGROUND2		(2<<1)
#define BACKGROUND3		(2<<2)
#define BACKGROUND4		(2<<3)
#define BAR1			3
#define BAR2			(3<<1)
#define BAR3			(3<<2)
#define BARCONSTRAINTS	(3<<3)
#define CHARACTER1		(4<<1)
#define CHARACTER2		(4<<2)
#define CHARACTER3		(4<<3)
#define CHARACTER4		(4<<4)
#define WEAPON			(4<<5)
#define EMPTY			5

	//This are defines for directions. You might want to use them for orienting yourself with
	//the screen.
#define DIRRIGHT		1
#define DIRLEFT			-1
#define DIRUP			1
#define DIRDOWN			-1
#define NOMOVE			0

	//This are the type of the entity. You can use them if you want on the functions that require them.
#define RLCHARACTER		0x0001
#define RLBACKGROUND	0x0002
#define RLBAR			0x0003
#define RLTEXT			0x0004 
#define RLWALL			0x0005
#define RLENEMY			0x0006

	//This values are for using a custom color pallete.
#define LETCOLOR1		0x0000			//0000
#define LETCOLOR2		0x0001			//0001
#define LETCOLOR3		0x0002			//0010
#define LETCOLOR4		0x0003			//0011	
#define LETCOLOR5		0x0004			//0100
#define LETCOLOR6		0x0005			//0101
#define LETCOLOR7		0x0006			//0110
#define LETCOLOR8		0x0007			//0111
#define LETCOLOR9		0x0008			//1000
#define LETCOLOR10		0x0009			//1001
#define LETCOLOR11		0x000A			//1010
#define LETCOLOR12		0x000B			//1011
#define LETCOLOR13		0x000C			//1100
#define LETCOLOR14		0x000D			//1101
#define LETCOLOR15		0x000E			//1110
#define LETCOLOR16		0x000F			//1111

#define BACKCOLOR1		0x0000
#define BACKCOLOR2		0x0010
#define BACKCOLOR3		0x0020
#define BACKCOLOR4		0x0030
#define BACKCOLOR5		0x0040
#define BACKCOLOR6		0x0050
#define BACKCOLOR7		0x0060
#define BACKCOLOR8		0x0070
#define BACKCOLOR9		0x0080
#define BACKCOLOR10		0x0090
#define BACKCOLOR11		0x00A0
#define BACKCOLOR12		0x00B0
#define BACKCOLOR13		0x00C0
#define BACKCOLOR14		0x00D0
#define BACKCOLOR15		0x00E0
#define BACKCOLOR16		0x00F0
	
	//Use this ones if you aren't using a new pallete.
#define LBASEBLACK			LETCOLOR1
#define LBASEBLUE			LETCOLOR2
#define LBASEGREEN			LETCOLOR3
#define LBASECYAN			LETCOLOR4
#define LBASERED			LETCOLOR5
#define LBASEMAGENTA		LETCOLOR6
#define LBASEBROWN			LETCOLOR7
#define LBASEGREY			LETCOLOR8
#define LBASEDARKGREY		LETCOLOR9
#define LBASELIGHTBLUE		LETCOLOR10
#define LBASELIGHTGREEN		LETCOLOR11
#define LBASELIGHTCYAN		LETCOLOR12
#define LBASELIGHTRED		LETCOLOR13
#define LBASELIGHTMAGENTA	LETCOLOR14
#define	LBASEYELLOW			LETCOLOR15
#define LBASEWHITE			LETCOLOR16

#define BBASEBLACK			BACKCOLOR1
#define BBASEBLUE			BACKCOLOR2
#define BBASEGREEN			BACKCOLOR3
#define BBASECYAN			BACKCOLOR4
#define BBASERED			BACKCOLOR5
#define BBASEMAGENTA		BACKCOLOR6
#define BBASEBROWN			BACKCOLOR7
#define BBASEGREY			BACKCOLOR8
#define BBASEDARKGREY		BACKCOLOR9
#define BBASELIGHTBLUE		BACKCOLOR10
#define BBASELIGHTGREEN		BACKCOLOR11
#define BBASELIGHTCYAN		BACKCOLOR12
#define BBASELIGHTRED		BACKCOLOR13
#define BBASELIGHTMAGENTA	BACKCOLOR14
#define	BBASEYELLOW			BACKCOLOR15
#define BBASEWHITE			BACKCOLOR16

#define ALPHACOLOR			100


class Entity;

//The static is left here for the purpose of telling the user 
//that NO instance of this class should ever be created.
static class rlUtilJM
{
public:


	///<summary>Initiates an event for music to reproduce. Only works with .ogg and .flac files. This is a song that will play only if nothing else is playing.
	///It may stop any other song from playing by using stopCurrentAudio.
	///<remark>Uses SFML</remark>.</summary>
	///<param name="_musicPath">The complete path to the music file. From "C:\\".</param>
	///<param name="_loop">Will the music loop? TRUE or FALSE only.</param>
	///<param name="_vol">The music volume.</param>
	///<param name="_stopCurrentAudio">If the current music should be stopped to start a new one.</param>
	static void PlayMusicBackground(const char* _musicPath, const BOOL& _loop, const float& _vol, const BOOL& _stopCurrentAudio);

	///<summary>Initiates an event for music to reproduce. Only works with .ogg and .flac files.
	///<remark>Uses SFML</remark>.</summary>
	///<param name="_musicPath">The complete path to the music file. From "C:\\".</param>
	///<param name="_vol">The music volume.</param>
	static void PlaySoundEffect(const char* _musicPath, const float& _vol);

	///<summary>
	///Changes the volume of the background music.
	///</summary>
	static void ChangeBackgroundVolume(const float& _vol);

	///<summary>
	///Returns the background's music volume.
	///</summary>
	static float GetBackgroundVolume();

	///<summary>
	///Pauses the background music.
	///</summary>
	static void PauseBackgroundMusic();

	///<summary>
	///Unpauses the background music.
	///</summary>
	static void UnPauseBackgroundMusic();

	///<summary>
	///Returns if there is a track playing on the background.
	///</summary>
	static bool BackgroundMusicIsPlaying();

	///<summary>
	///Returns if the background track is currently paused.
	///</summary>
	static bool BackgroundMusicIsPaused();

	///<summary>
	///To print the sprites to the screen the engine creates a fake screen macrobuffer which later is printed onto the console.
	///Please do not use anywhere as each draw method works around this.
	///Insead use Enitity->draw() or bar->draw().
	///</summary>
	///<param name="_colorVal">The letter's color.</param>
	///<param name="_backVal">The background's color.</param>
	///<param name="_letVal">The letter to show.</param>
	///<param name="posx">The buffer's position in X.</param>
	///<param name="posy">The buffer's position in Y.</param>
	///<param name="ocup">The tile's ocupant.</param>
	static void AddToBuffer(const int& _colorVal, const int& _backVal,
		const char& _letVal, const int& posx, const int& posy, const int& ocup, Entity* const& entity);

	///<summary>
	///Writes text to the fake screen buffer. Using <code>cout</code> will not give any results, use this instead.
	///Doesn't allow line skips.
	///</summary>
	///<param name="text">The text to show.</param>
	///<param name="color">The letter's color.</param>
	///<param name="background">The background's color.</param>
	///<param name="posx">The starting position of the letters in X.</param>
	///<param name="posy">The starting position of the letters in Y.</param>
	static void TextWrapper(const char* text, const int& color,
		const int& background, const int& posx, const int& posy);

	///<summary>
	///Alternative to filling each element in a sprite array.
	///</summary>
	///<param name="y">The sprite's space in Y.</param><param name="x">The sprite's space in X.</param>
	///<param name="content">The pixel's content.</param><param name="_sprite">The array to work with by ref.</param>
	static void AddPixel(const int& y, const int& x, const int& content, int**& _sprite);

	///<summary>
	///Returns an initialized bi dimensional Int array. Simple method for saving some lines.
	///</summary>
	static int** InitSpriteArray(const int& y, const int& x);

	///<summary>
	///Returns the screen width.
	///</summary>
	inline static int getScreenWidth() { return SCREEN_SIZE_WIDTH; };
	
	///<summary>
	///Returns the screen height.
	///</summary>
	inline static int getScreenHeight() { return SCREEN_SIZE_HEIGHT; };

	///<summary>
	///Avoid calls to this method as it is automatically called on every draw method.
	///Adds a function to the draw thread queue.
	///</summary>
	static void AddToDrawThread(const std::function<void()>& func);

	///<summary>
	///Adds an enitity to the memory manager for disposal.
	///</summary>
	static void AddEntityToManager(Entity * const& entity);

	///<summary>
	///Changes the color palette.
	///</summary>
	static void ChangeColorPalette(const ColorPalette& pal);
	
	///<summary>
	///Returns the current color pallete.
	///</summary>
	static ColorPalette GetColorPalette();

	///<summary>
	///Changes the name on the title bar on the window. 
	///</summary>
	static void ChangeWindowTitle(const char* title);

	///<summary>
	///Sets if the screen should refresh with each frame.
	///</summary>
	static void ShouldClearScreen(const bool& cls = true);

	///<summary>
	///Sets a pixel to be static. That means that it wont be refreshed with each frame
	///unless it is completely changed, either by overlapping or changing the sprite.
	///</summary>
	static void SetStaticTile(const bool& _static, const int& x, const int& y);

	///<summary>
	///Deletes the current entities in the entity manager.
	///</summary>
	static void CleanEntities();

	///<summary>
	///Sets a the drawn state of a pixel. 
	///The drawn state refers to the question, has the pixel been drawn before
	///and its not been refreshed?</summary>
	///<param name="_drawn"> The state of the pixel.</param>
	///<param name="x"> The x position of the pixel.</param>
	///<param name="y"> The y position of the pixel.</param>
	static void SetDrawnTile(const bool& _drawn, const int& x, const int& y);

	///<summary>
	///Forces the screen to clear itself up. 
	///Used for custom refresh rates.
	///</summary>
	static void ForceClearScreen();

private:
	///<summary>
	///The screen width in console pixels.
	///</summary>
	static int SCREEN_SIZE_WIDTH;
	///<summary>
	///The screen height in console pixels.
	///</summary>
	static int SCREEN_SIZE_HEIGHT;
	///<summary>
	///This variable controls most of the data that enters the real console buffer.
	///Most draw operations fo first here and then they are inserted in the console.
	///</summary>
	static Tile** screenBuffer;
	///<summary>
	///This is used for collision overlapping comprobations.
	///It saves the contents of the last frame.
	///</summary>
	static Tile** lastScreenBuffer;
	///<summary>
	///Audio buffer for the background music. While the engine only provides one
	///it is perfectly safe for anybody to use more than one.
	///</summary>
	static sf::Music music;
	///<summary>
	///Audio buffer for the sound effects. While the engine only provides one
	///it is perfectly safe for anybody to use more than one.
	///</summary>
	static sf::SoundBuffer soundBuffer;
	///<summary>
	///Audio player for the sound effects. While the engine only provides one
	///it is perfectly safe for anybody to use more than one.
	///</summary>
	static sf::Sound sound;
	///<summary>
	///The thread that manages all draw operations.
	///</summary>
	static std::thread drawThread;
	///<summary>
	///This queue holds all functions that run on the draw thread.
	///</summary>
	static std::queue<std::function<void()>> delegator;
	///<summary>
	///This variable saves the original font of the console for restoring it once the program closes.
	///</summary>
	static CONSOLE_FONT_INFOEX savedFont;
	///<summary>
	///Mutex for solving race issues with the draw thread
	///</summary>
	static std::mutex m;
	///<summary>
	///Saves the state of the buffer, if it's just been cleaned then it's empty.
	///</summary>
	static bool buffIsEmpty;
	///<summary>
	///This vector saves a reference to every entity that is created. Then deletes them at the program end.
	///</summary>
	static std::vector<Entity*> entityManager;
	///<summary>
	///This the first of the two buffers that the engine use for rendering.
	///</summary>
	static HANDLE WINAPI mainBuffer;
	///<summary>
	///This is the second of the two buffers that the engine use for rendering.
	///</summary>
	static HANDLE WINAPI backBuffer;
	///<summary>
	///This is the original buffer of the console, that is restored upon closing the program.
	///</summary>
	static HANDLE WINAPI savedBuffer;
	///<summary>
	///Saves the state of the swap buffer, if the active buffer is the first one this is true, if not then
	///the second one is the active buffer.
	///</summary>
	static bool mainBuffActive;
	///<summary>
	///The contents of the buffer. This is filled using the Tiles members.
	///</summary>
	static CHAR_INFO *printBufferCont;
	///<summary>
	///This member saves the information about the console for restoring it at the end.
	///</summary>
	static CONSOLE_SCREEN_BUFFER_INFOEX savedBuffInfoEx;
	///<summary>
	///This member saves the information about the console for restoring it at the end.
	///</summary>
	static CONSOLE_SCREEN_BUFFER_INFO savedBuffInfo;
	///<summary>
	///This palete is saved for restoring at the end.
	///</summary>
	static ColorPalette basicPalette;
	///<summary>
	///This palete is the one that is assigned and used at every moment of the runtime.
	///</summary>
	static ColorPalette currentPallete;
	///<summary>
	///Should the screen be cleared at the end of the frame?
	///</summary>
	static bool ShouldCls;

	///<summary>
	///Sets the collision status for every Entity in screen.
	///</summary>
	static void setEventCollisionStatus(const bool& _status,Entity* collisioned,Entity* const& other);
	
	///<summary>
	///Makes the CMD have square pixels. It's already called in WindowSize;
	///</summary>
	static void FontSize();
	
	///<summary>
	///Creates the aforementioned fake screen buffer. Do not call anywhere.
	///It is already called in <code>WindowSize()</code> 
	///</summary>
	static void CreateFakeScreenBuffer();


protected:

	///<summary>
	///Executes the draw step. Runs in another thread.
	///</summary>
	static void executeDraw();

	///<summary>
	///Starts the draw thread.
	///</summary>
	static void startDrawThread(const std::function<void()>& funct);

	///<summary>
	///Keeps the screen size at all times during runtime. 
	///Call one time each frame at it's start.
	///</summary>
	static void KeepScreenSize();

	///<summary>
	///Changes the screen size along with the font size. You should only use this at a startup function and once.
	///</summary>
	///<param name="_x">Window's width.</param>
	///<param name="_y">Window's height.</param>
	static void WindowSize(const int& _x, const int& _y);

	///<summary>
	///Print method. Always call only once at the end of each frame.
	///</summary>
	static void PrintBuffer();

	///<summary>
	///Clears the fake screen buffer. Call each frame on the start before anything else.
	///</summary>
	static void ClearBuffer();

	///<summary>
	///Called at program's exit. Restores the CMD functionality to 
	///its defaults.
	///</summary>
	static void RestoreFont();

	///<summary>
	///Cleans every pointer at the end of the program.
	///</summary>
	static void Cleanup();

};



#endif // !_RLUTILSJM_H_
