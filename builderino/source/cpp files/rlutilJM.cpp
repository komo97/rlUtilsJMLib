#include "rlutilJM.h"
#include "Entity.h"
#include <chrono>
#include <mutex>


int rlUtilJM::SCREEN_SIZE_WIDTH;
int rlUtilJM::SCREEN_SIZE_HEIGHT;
Tile** rlUtilJM::screenBuffer = NULL;
Tile** rlUtilJM::lastScreenBuffer = NULL;
sf::Music rlUtilJM::music;
sf::SoundBuffer rlUtilJM::soundBuffer;
sf::Sound rlUtilJM::sound;
CONSOLE_FONT_INFOEX rlUtilJM::savedFont;
std::queue<std::function<void()>> rlUtilJM::delegator;
std::thread rlUtilJM::drawThread;
std::mutex rlUtilJM::m;
PCONSOLE_SCREEN_BUFFER_INFO info = new CONSOLE_SCREEN_BUFFER_INFO;
bool rlUtilJM::buffIsEmpty = false;
std::vector<Entity*> rlUtilJM::entityManager;
HANDLE WINAPI rlUtilJM::mainBuffer;
HANDLE WINAPI rlUtilJM::backBuffer;
HANDLE WINAPI rlUtilJM::savedBuffer;
bool rlUtilJM::mainBuffActive = true;
CHAR_INFO *rlUtilJM::printBufferCont;
CONSOLE_SCREEN_BUFFER_INFOEX rlUtilJM::savedBuffInfoEx;
CONSOLE_SCREEN_BUFFER_INFO rlUtilJM::savedBuffInfo;
ColorPalette rlUtilJM::basicPalette;
ColorPalette rlUtilJM::currentPallete;
bool rlUtilJM::ShouldCls = false;

void rlUtilJM::KeepScreenSize()
{

	HWND wnd = GetConsoleWindow();
	HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	m.lock();
		GetConsoleScreenBufferInfo(consoleOutput, info);
		if (info->dwSize.X != SCREEN_SIZE_WIDTH || info->dwSize.Y != SCREEN_SIZE_HEIGHT)
		{
			SetConsoleActiveScreenBuffer(backBuffer);
			COORD coord{ (SHORT)SCREEN_SIZE_WIDTH,
				(SHORT)SCREEN_SIZE_HEIGHT };
			std::string mod = "MODE CON: COLS=" + std::to_string(SCREEN_SIZE_WIDTH) + " LINES=" + std::to_string(SCREEN_SIZE_HEIGHT);
			SetConsoleScreenBufferSize(backBuffer, coord);
			std::system(mod.c_str());
			SetConsoleActiveScreenBuffer(mainBuffer);
			SetConsoleScreenBufferSize(mainBuffer, coord);
			std::system(mod.c_str());
			SMALL_RECT wndw{ 0, 0,(SHORT)SCREEN_SIZE_WIDTH,
				(SHORT)SCREEN_SIZE_HEIGHT };
			SetConsoleWindowInfo(mainBuffer, TRUE, &wndw);
			wndw = { 0, 0,(SHORT)SCREEN_SIZE_WIDTH,
				(SHORT)SCREEN_SIZE_HEIGHT };
			SetConsoleWindowInfo(backBuffer, TRUE, &wndw);
		}
	m.unlock();

}

void rlUtilJM::WindowSize(const int& _x, const int& _y)
{
	cls();
	HWND hwnd = GetConsoleWindow();
	savedBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(savedBuffer, &savedBuffInfo);
	GetConsoleScreenBufferInfoEx(savedBuffer, &savedBuffInfoEx);
	SCREEN_SIZE_HEIGHT = _y;
	SCREEN_SIZE_WIDTH = _x;
	std::string mod = "MODE CON COLS=" + std::to_string(SCREEN_SIZE_WIDTH) + " LINES=" + std::to_string(SCREEN_SIZE_HEIGHT);
	std::system(mod.c_str());
	saveDefaultColor();
	FontSize();
	CreateFakeScreenBuffer();
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(backBuffer, &structCursorInfo); // Get current cursor size
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(mainBuffer, &structCursorInfo);
	KeepScreenSize();
}

void rlUtilJM::PlayMusicBackground(const char * _musicPath, const BOOL& _loop, const float& _vol, const BOOL& _stopCurrentAudio)
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

void rlUtilJM::PlaySoundEffect(const char * _musicPath, const float& _vol)
{
	if (!soundBuffer.loadFromFile(_musicPath))
		return;
	sound.setBuffer(soundBuffer);
	sound.setVolume(_vol);
	sound.play();
}

void rlUtilJM::ChangeBackgroundVolume(const float& _vol)
{
	if (_vol == music.getVolume())
		return;
	music.setVolume(_vol);
}

float rlUtilJM::GetBackgroundVolume()
{
	return music.getVolume();
}

void rlUtilJM::PauseBackgroundMusic()
{
	if (music.getStatus() == music.Stopped)
		return;
	music.pause();
}

void rlUtilJM::UnPauseBackgroundMusic()
{
	if (music.getStatus() == music.Playing)
		return;
	music.play();
}

bool rlUtilJM::BackgroundMusicIsPlaying()
{
	return music.getStatus() == music.Playing;
}

bool rlUtilJM::BackgroundMusicIsPaused()
{
	return music.getStatus() == music.Paused;
}

void rlUtilJM::FontSize()
{
	HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX currFont;
	GetCurrentConsoleFontEx(consoleOutput, FALSE, &savedFont);
	currFont.cbSize = sizeof currFont;
	currFont.nFont = 0;
	currFont.dwFontSize.X = 8;
	currFont.dwFontSize.Y = 8;
	currFont.FontFamily = FF_DONTCARE;
	currFont.FontWeight = FW_NORMAL;
	wcscpy_s(currFont.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(consoleOutput, FALSE, &currFont);
}

void rlUtilJM::AddToBuffer(const int& _colorVal, const int& _backVal, const char& _letVal,
	const int& posx, const int& posy, const int& ocup, Entity* const& entity)
{
	if (_colorVal == ALPHACOLOR && _backVal == ALPHACOLOR)
		return;
	buffIsEmpty = false;
	if(_backVal != ALPHACOLOR)
		screenBuffer[posy][posx].setBackground(_backVal);
	if(_colorVal != ALPHACOLOR)
		screenBuffer[posy][posx].setColor(_colorVal);
	screenBuffer[posy][posx].setChar(_letVal);
	screenBuffer[posy][posx].setOcupant(ocup);
	screenBuffer[posy][posx].setEntity(entity);
}

void rlUtilJM::ClearBuffer()
{
	rlutil::resetColor();
	int i, j;
	for (i = 0; i < SCREEN_SIZE_HEIGHT; ++i)
	{
		for (j = 0; j < SCREEN_SIZE_WIDTH; ++j)
		{
			if (screenBuffer[i][j].getIsStatic() && screenBuffer[i][j].getIsDrawn())
				continue;
			screenBuffer[i][j].setBackground(0);
			screenBuffer[i][j].setColor(0);
			screenBuffer[i][j].setChar('\0');
			screenBuffer[i][j].setOcupant(EMPTY);
			screenBuffer[i][j].setEntity(nullptr);
			screenBuffer[i][j].setDrawn(false);
		}
	}
	buffIsEmpty = true;
}

void rlUtilJM::RestoreFont()
{
	rlutil::resetColor();
	HANDLE consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetCurrentConsoleFontEx(consoleOutput, FALSE, &savedFont);
}

void rlUtilJM::Cleanup()
{
	for (int i = SCREEN_SIZE_HEIGHT; i--;)
	{
		delete[] screenBuffer[i];
		delete[] lastScreenBuffer[i];
	}
	delete screenBuffer;
	delete lastScreenBuffer;
	delete[] printBufferCont;
	SetConsoleActiveScreenBuffer(savedBuffer);
	SetConsoleScreenBufferInfoEx(savedBuffer, &savedBuffInfoEx);
	CleanEntities();
}

void rlUtilJM::PrintBuffer()
{
	if (buffIsEmpty)
		return;
	mainBuffActive ^= true;
	hidecursor();
	HANDLE WINAPI buff = mainBuffActive ? mainBuffer : backBuffer;
	COORD dir{ (SHORT)0, (SHORT)0 };
	CONSOLE_SCREEN_BUFFER_INFO csbi;
		SMALL_RECT s{ (SHORT)0, (SHORT)0,
		(SHORT)SCREEN_SIZE_WIDTH - 1, (SHORT)SCREEN_SIZE_HEIGHT - 1 };
	COORD sizeArr{ (SHORT)SCREEN_SIZE_WIDTH, (SHORT)SCREEN_SIZE_HEIGHT};
	bool screenChanged = false;
	GetConsoleScreenBufferInfo(buff, &csbi);
	for (int i = 0; i < SCREEN_SIZE_HEIGHT; ++i)
	{
		for (int j = 0; j < SCREEN_SIZE_WIDTH; ++j)
		{
			if (screenBuffer[i][j].getOcupant() != lastScreenBuffer[i][j].getOcupant() &&
				screenBuffer[i][j].getOcupant() != EMPTY &&
				screenBuffer[i][j].getOcupant() != RLBAR && 
				lastScreenBuffer[i][j].getEntity() != nullptr &&
				screenBuffer[i][j].getEntity() != nullptr)
			{
				setEventCollisionStatus(true, lastScreenBuffer[i][j].getEntity(), screenBuffer[i][j].getEntity());
				setEventCollisionStatus(true, screenBuffer[i][j].getEntity(), lastScreenBuffer[i][j].getEntity());
			}
				if (!screenChanged && !screenBuffer[i][j].getIsDrawn())
				{
					screenChanged = true;
				}
				printBufferCont[SCREEN_SIZE_WIDTH * i + j].Char.AsciiChar =
					screenBuffer[i][j].getLetter();
				printBufferCont[SCREEN_SIZE_WIDTH * i + j].Attributes =
					screenBuffer[i][j].getColor() |
					screenBuffer[i][j].getBackground();
				screenBuffer[i][j].setDrawn(true);
			lastScreenBuffer[i][j].setOcupant(screenBuffer[i][j].getOcupant());
			lastScreenBuffer[i][j].setEntity(screenBuffer[i][j].getEntity());
		}
	}
	if (!screenChanged) return;
	WriteConsoleOutput(buff, printBufferCont, sizeArr, dir, &s);
	std::this_thread::sleep_for(std::chrono::milliseconds(11));
	SetConsoleActiveScreenBuffer(buff);
	if(ShouldCls)
		ClearBuffer();
}

void rlUtilJM::CreateFakeScreenBuffer()
{	
	screenBuffer = new Tile*[SCREEN_SIZE_HEIGHT];
	lastScreenBuffer = new Tile*[SCREEN_SIZE_HEIGHT];
	for (int i = 0; i < SCREEN_SIZE_HEIGHT; ++i)
	{
		screenBuffer[i] = new Tile[SCREEN_SIZE_WIDTH];
		lastScreenBuffer[i] = new Tile[SCREEN_SIZE_WIDTH];
		for (int j = 0; j < SCREEN_SIZE_WIDTH; ++j)
		{
			screenBuffer[i][j].setEntity(nullptr);
			screenBuffer[i][j].setDrawn(false);
			lastScreenBuffer[i][j].setEntity(nullptr);
		}
	}
	CloseHandle(mainBuffer);
	CloseHandle(backBuffer);
	mainBuffer = CreateConsoleScreenBuffer(GENERIC_READ |           // read/write access 
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,        // shared 
		NULL,                    // default security attributes 
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
		NULL);
	backBuffer = CreateConsoleScreenBuffer(GENERIC_READ |           // read/write access 
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,        // shared 
		NULL,                    // default security attributes 
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
		NULL);
	SetConsoleActiveScreenBuffer(backBuffer);
	HWND wnd = GetConsoleWindow();
	COORD coord{ (SHORT)SCREEN_SIZE_WIDTH,
			(SHORT)SCREEN_SIZE_HEIGHT };
	SMALL_RECT wndw{ 0, 0,(SHORT)SCREEN_SIZE_WIDTH,
		(SHORT)SCREEN_SIZE_HEIGHT };
	MoveWindow(wnd, -8, 0, SCREEN_SIZE_WIDTH - 1, SCREEN_SIZE_HEIGHT - 1, FALSE);
	std::string mod = "MODE CON: COLS=" + std::to_string(SCREEN_SIZE_WIDTH) + " LINES=" + std::to_string(SCREEN_SIZE_HEIGHT);
	CONSOLE_SCREEN_BUFFER_INFO inf;
	GetConsoleScreenBufferInfo(mainBuffer, &inf);
	SetConsoleScreenBufferSize(backBuffer, coord);
	std::system(mod.c_str());
	SetConsoleActiveScreenBuffer(mainBuffer);
	SetConsoleScreenBufferSize(mainBuffer, coord);
	std::system(mod.c_str());
	SetConsoleWindowInfo(mainBuffer, TRUE, &wndw);
	wndw = { 0, 0,(SHORT)SCREEN_SIZE_WIDTH,
		(SHORT)SCREEN_SIZE_HEIGHT };
	SetConsoleWindowInfo(backBuffer, TRUE, &wndw);
	printBufferCont = new CHAR_INFO[SCREEN_SIZE_HEIGHT * SCREEN_SIZE_WIDTH];
	for (int i = SCREEN_SIZE_WIDTH * SCREEN_SIZE_HEIGHT;
		i--;)
	{
		printBufferCont[i].Char.AsciiChar =  '\0';
	}
}

void rlUtilJM::CleanEntities()
{
	for(auto entity : entityManager)
	{
		delete entity;
	}
}

void rlUtilJM::TextWrapper(const char * text, const int& color,
	const int& background, const int& posx, const int& posy)
{
	std::string a(text);
	for (int i = 0; i < a.size(); ++i)
	{
		AddToBuffer(color, background, a[i], posx + i, posy, RLTEXT, nullptr);
		SetStaticTile(false, posx + i, posy);
	}
}

void rlUtilJM::AddPixel(const int& y, const int& x, const int& content, int **& _sprite)
{
	_sprite[y][x] = content;
}

int ** rlUtilJM::InitSpriteArray(const int& y, const int& x)
{
	int** arr;
	arr = new int*[y];
	for (int i = 0; i < y; ++i)
	{
		arr[i] = new int[x];
	}
	return arr;
}

void rlUtilJM::AddToDrawThread(const std::function<void()>& funct)
{
	m.lock();
		delegator.push(funct);
	m.unlock();

}

void rlUtilJM::AddEntityToManager(Entity * const & entity)
{
	entityManager.push_back(entity);
}

void rlUtilJM::ChangeColorPalette(const ColorPalette & pal)
{
	currentPallete = pal;
	CONSOLE_SCREEN_BUFFER_INFOEX inf;
	inf.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(mainBuffer, &inf);
	currentPallete.SetActivePalette(inf);
	inf.srWindow = { (SHORT)0, (SHORT)0, (SHORT)SCREEN_SIZE_WIDTH, (SHORT)SCREEN_SIZE_HEIGHT };
	SetConsoleScreenBufferInfoEx(mainBuffer, &inf);
	GetConsoleScreenBufferInfoEx(backBuffer, &inf);
	currentPallete.SetActivePalette(inf);
	inf.srWindow = { (SHORT)0, (SHORT)0, (SHORT)SCREEN_SIZE_WIDTH, (SHORT)SCREEN_SIZE_HEIGHT };
	SetConsoleScreenBufferInfoEx(backBuffer, &inf);
}

ColorPalette rlUtilJM::GetColorPalette()
{
	return currentPallete;
}

void rlUtilJM::ChangeWindowTitle(const char * title)
{
	SetConsoleTitle(title);
}

void rlUtilJM::SetStaticTile(const bool & _static, const int& x, const int& y)
{
	screenBuffer[y][x].setStatic(_static);
}

void rlUtilJM::SetDrawnTile(const bool & _drawn, const int& x, const int& y)
{
	screenBuffer[y][x].setDrawn(_drawn);
}

void rlUtilJM::ForceClearScreen() {
	rlutil::resetColor();
	int i, j;
	for (i = 0; i < SCREEN_SIZE_HEIGHT; ++i)
	{
		for (j = 0; j < SCREEN_SIZE_WIDTH; ++j)
		{

			screenBuffer[i][j].setBackground(0);
			screenBuffer[i][j].setColor(0);
			screenBuffer[i][j].setChar('\0');
			screenBuffer[i][j].setOcupant(EMPTY);
			screenBuffer[i][j].setEntity(nullptr);
			screenBuffer[i][j].setDrawn(false);
		}
	}
	buffIsEmpty = true;
}

void rlUtilJM::ShouldClearScreen(const bool& cls)
{
	ShouldCls = cls;
}

void rlUtilJM::setEventCollisionStatus(const bool& _status, Entity * collisioned, Entity * const& other)
{
	collisioned->SetCollisionState(_status, other); 
}

void rlUtilJM::executeDraw()
{

	while (1)
	{
		if (delegator.size() <= 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(11));
			continue;
		}
		m.try_lock();
			std::function<void()> f = delegator.front();
			delegator.pop();
		m.unlock();
		f();
	}
}

void rlUtilJM::startDrawThread(const std::function<void()>& funct)
{
	drawThread = std::thread(funct);
	drawThread.detach();
}
