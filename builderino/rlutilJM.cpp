#include "rlutilJM.h"
#include "Entity.h"
#include <chrono>


int rlUtilJM::SCREEN_SIZE_WIDTH;
int rlUtilJM::SCREEN_SIZE_HEIGHT;
Tile** rlUtilJM::screenBuffer;
Tile** rlUtilJM::lastScreenBuffer;
sf::Music rlUtilJM::music;

void rlUtilJM::KeepScreenSize()
{

	HWND wnd = GetConsoleWindow();
	HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	PCONSOLE_SCREEN_BUFFER_INFO info;
	info = new CONSOLE_SCREEN_BUFFER_INFO;
	GetConsoleScreenBufferInfo(consoleOutput, info);

	if (info->dwSize.X != SCREEN_SIZE_WIDTH || info->dwSize.Y != SCREEN_SIZE_HEIGHT)
	{
		std::string mod = "MODE CON COLS=" + std::to_string(SCREEN_SIZE_WIDTH) + " LINES=" + std::to_string(SCREEN_SIZE_HEIGHT);
		std::system(mod.c_str());
	}
	hidecursor();
}

void rlUtilJM::WindowSize(int _x, int _y)
{
	cls();
	SCREEN_SIZE_HEIGHT = _y;
	SCREEN_SIZE_WIDTH = _x;

	std::string mod = "MODE CON COLS=" + std::to_string(SCREEN_SIZE_WIDTH) + " LINES=" + std::to_string(SCREEN_SIZE_HEIGHT);
	std::system(mod.c_str());
	saveDefaultColor();
	FontSize();
	CreateFakeScreenBuffer();
	{
		HWND wnd = GetConsoleWindow();
		HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coord;
		coord.X = _x / 10;
		coord.Y = _y / 20;
		SetConsoleScreenBufferSize(consoleOutput, coord);
		MoveWindow(wnd, 0, 0, _x - 1, _y - 1, FALSE);
	}
	KeepScreenSize();
	hidecursor();
}

void rlUtilJM::PlayMusicBackground(char * _musicPath, BOOL _loop, float _vol, BOOL _stopCurrentAudio)
{
	if (!music.openFromFile(_musicPath))
		return;
	if (_loop == TRUE)
		music.setLoop(true);
	if (_stopCurrentAudio == TRUE)
	{
		music.stop();
	}
	if (music.getStatus() != sf::Music::Playing)
	{
		music.setVolume(_vol);
		music.play();
	}
}

void rlUtilJM::PlaySoundEffect(char * _musicPath, float _vol)
{
	if (!music.openFromFile(_musicPath))
		return;
	music.setVolume(_vol);
	music.play();
}

void rlUtilJM::FontSize()
{
	HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX currFont;
	currFont.cbSize = sizeof currFont;
	currFont.nFont = 0;
	currFont.dwFontSize.X = 8;
	currFont.dwFontSize.Y = 8;
	currFont.FontFamily = FF_DONTCARE;
	currFont.FontWeight = FW_NORMAL;
	wcscpy_s(currFont.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(consoleOutput, FALSE, &currFont);
}

void rlUtilJM::AddToBuffer(int _colorVal, int _backVal, char _letVal, int posx, int posy, int ocup, Entity* entity)
{
	screenBuffer[posy][posx].setBackground(_backVal);
	screenBuffer[posy][posx].setColor(_colorVal);
	screenBuffer[posy][posx].setChar(_letVal);
	screenBuffer[posy][posx].setOcupant(ocup);
	screenBuffer[posy][posx].setEntity(entity);
}

void rlUtilJM::ClearBuffer()
{
	rlutil::resetColor();
	int i, j;
	for (i = 0; i < SCREEN_SIZE_HEIGHT; i++)
	{
		for (j = 0; j < SCREEN_SIZE_WIDTH; j++)
		{
			screenBuffer[i][j].setBackground(0);
			screenBuffer[i][j].setColor(0);
			screenBuffer[i][j].setChar('\0');
			screenBuffer[i][j].setOcupant(EMPTY);
		}
	}
}

void rlUtilJM::PrintBuffer()
{
	for (int i = 0; i < SCREEN_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_SIZE_WIDTH; j++)
		{
			if (screenBuffer[i][j].getOcupant() != lastScreenBuffer[i][j].getOcupant() &&
				screenBuffer[i][j].getOcupant() != EMPTY &&
				screenBuffer[i][j].getOcupant() != BAR)
			{
				setEventCollisionStatus(true, lastScreenBuffer[i][j].getEntity(), screenBuffer[i][j].getEntity());
				setEventCollisionStatus(true, screenBuffer[i][j].getEntity(), lastScreenBuffer[i][j].getEntity());
			}
			if (screenBuffer[i][j].getBackground() != lastScreenBuffer[i][j].getBackground() ||
				screenBuffer[i][j].getColor() != lastScreenBuffer[i][j].getColor() ||
				screenBuffer[i][j].getLetter() != lastScreenBuffer[i][j].getLetter())
			{
				locate(j, i);
				setColor(screenBuffer[i][j].getColor());
				setBackgroundColor(screenBuffer[i][j].getBackground());
				printf("%c", screenBuffer[i][j].getLetter());
			}
		}
	}
	for (int i = 0; i < SCREEN_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_SIZE_WIDTH; j++)
		{
			lastScreenBuffer[i][j].setBackground(screenBuffer[i][j].getBackground());
			lastScreenBuffer[i][j].setColor(screenBuffer[i][j].getColor());
			lastScreenBuffer[i][j].setChar(screenBuffer[i][j].getLetter());
			lastScreenBuffer[i][j].setOcupant(screenBuffer[i][j].getOcupant());
		}
	}
}

void rlUtilJM::CreateFakeScreenBuffer()
{
	screenBuffer = new Tile*[SCREEN_SIZE_HEIGHT];
	lastScreenBuffer = new Tile*[SCREEN_SIZE_HEIGHT];
	for (int i = 0; i < SCREEN_SIZE_HEIGHT; i++)
	{
		screenBuffer[i] = new Tile[SCREEN_SIZE_WIDTH];
		lastScreenBuffer[i] = new Tile[SCREEN_SIZE_WIDTH];
	}
	for (int i = 0; i < SCREEN_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < SCREEN_SIZE_WIDTH; j++)
		{
			lastScreenBuffer[i][j].setBackground(screenBuffer[i][j].getBackground());
			lastScreenBuffer[i][j].setColor(screenBuffer[i][j].getColor());
			lastScreenBuffer[i][j].setChar(screenBuffer[i][j].getLetter());
		}
	}
}

void rlUtilJM::TextWrapper(const char * text, int color, int background, int posx, int posy)
{
	std::string a(text);
	for (int i = 0; i < a.size(); i++)
	{
		AddToBuffer(color, background, a[i], posx + i, posy, TEXT, nullptr);
	}
}

void rlUtilJM::AddPixel(int y, int x, int content, int **& _sprite)
{
	_sprite[y][x] = content;
}

int ** rlUtilJM::InitSpriteArray(int y, int x)
{
	int** arr;
	arr = new int*[y];
	for (int i = 0; i <x; i++)
	{
		arr[i] = new int[x];
	}
	return arr;
}

void rlUtilJM::AddToDrawThread(std::function<void()> funct)
{
	//drawThread += std::thread(funct);
	delegator.push(funct);

}

void rlUtilJM::setEventCollisionStatus(bool _status, Entity * collisioned, Entity * other)
{
	collisioned->SetCollisionState(_status, other); 
}

void rlUtilJM::executeDraw()
{
	drawThread.detach();
	while (1)
	{
		if (delegator.empty())
			std::this_thread::sleep_for(std::chrono::milliseconds(11));
		delegator.front()();
		delegator.pop();
	}
}

void rlUtilJM::startDrawThread(std::function<void()> funct)
{
	drawThread = std::thread(funct);
}
