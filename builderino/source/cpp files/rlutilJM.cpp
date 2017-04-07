#include "h files\rlutilJM.h"


#pragma region GlobalVariables
	//Tamaño de la pantalla
	int SCREEN_SIZE_WIDTH;
	int SCREEN_SIZE_HEIGHT;

	//Fake screen buffer. Dejar como variable global.
	rlutilJM::tile** screenBuffer;
	rlutilJM::tile** lastScreenBuffer;
	sf::Music music;
#pragma endregion


void rlutilJM::WindowSize(int _x, int _y)
{
	cls();
	SCREEN_SIZE_HEIGHT = _y;
	SCREEN_SIZE_WIDTH =  _x;

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

void rlutilJM::KeepScreenSize()
{

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
	}
	hidecursor();
}
	
void rlutilJM::PlayMusic(char * _musicPath, BOOL _loop, float _vol)
{
	if (!music.openFromFile(_musicPath))
		return;
	if (_loop == TRUE)
		music.setLoop(true);
	music.setVolume(_vol);
	music.play();
}

void rlutilJM::FontSize()
{
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
}

void rlutilJM::FillBar(bar * _entity, int _fullParam, int _currParam)
{
	{
		int i, j;
		int percent, drawPercent;
		if (_fullParam != NULL)
			_entity->maxValue = _fullParam;
		_entity->currValue = _currParam;
		percent = (_entity->currValue* 100) / _entity->maxValue;
		drawPercent = (_entity->spriteSizeX*percent) / 100;
		_entity->percent = percent;
		for (i = 0; i < _entity->spriteSizeY; i++)
		{
			for (j = 0; j < _entity->spriteSizeX; j++)
			{
				if (i == 0 || i + 1 == _entity->spriteSizeY || j == 0 || j + 1 == _entity->spriteSizeX)
				{
					AddToBuffer(_entity->constraint, _entity->constraint, ' ', _entity->x + j, _entity->y + i, BAR);
				}
				else if (j <= drawPercent && (percent) >= 50)
				{
					AddToBuffer(_entity->color1, _entity->color1, ' ', _entity->x + j, _entity->y + i, BAR);
				}
				else if (j <= drawPercent && (percent) < 50 && (percent) > 25)
				{
					AddToBuffer(_entity->color2, _entity->color2, ' ', _entity->x + j, _entity->y + i, BAR);
				}
				else if (j <= drawPercent && (percent) <= 25)
				{
					AddToBuffer(_entity->color3, _entity->color3, ' ', _entity->x + j, _entity->y + i, BAR);
				}
				else
				{
					AddToBuffer(BLACK, BLACK, ' ', _entity->x + j, _entity->y + i, CLEAR);
				}
			}
		}
	}
}

void rlutilJM::SetStats(stats * _entity, int _x, int _y, int _life, int _attack, int _speed, int _characterType)
{
	{
		_entity->x = _x;
		_entity->y = _y;
		_entity->life = _life;
		_entity->attack = _attack;
		_entity->speed = _speed;
		if (_entity->life > 0)
			_entity->alive = 1;
		else
			_entity->alive = 0;
		_entity->type = _characterType;
	}
}

void rlutilJM::UpdateStats(stats * _entity, int _x, int _y, int _life, int _attack, int _speed)
{
	{
		_entity->x += _x;
		_entity->y += _y;
		_entity->life += _life;
		_entity->attack += _attack;
		_entity->speed += _speed;
		if (_entity->life > 0)
			_entity->alive = 1;
		else
			_entity->alive = 0;
	}
}

int ** rlutilJM::SpriteParams(stats * _entity, int _color1, int _color2, int _color3, int _color4, int _bg1, int _bg2, int _bg3, int _bg4, int ** _sprite, int _weapon)
{
	{
		_entity->color1 = _color1;
		_entity->color2 = _color2;
		_entity->color3 = _color3;
		_entity->color4 = _color4;
		_entity->bg1 = _bg1;
		_entity->bg2 = _bg2;
		_entity->bg3 = _bg3;
		_entity->bg4 = _bg4;
		int i, j;
		for (i = 0; i < _entity->spriteSizeY; i++)
		{
			for (j = 0; j < _entity->spriteSizeX; j++)
			{
				_entity->sprite[i][j] = _sprite[i][j];
			}
		}
		//*(_currSprite) = _sprite;
		//_entity->sprite = _sprite;
		_entity->weapon = _weapon;
		return _entity->sprite;
	}
}

void rlutilJM::CharSpriteParams(stats * _entity, char _letter1, char _letter2, char _letter3, char _letter4, char _charWeapon)
{
	{
		_entity->letter1 = _letter1;
		_entity->letter2 = _letter2;
		_entity->letter3 = _letter3;
		_entity->letter4 = _letter4;
		_entity->charWeapon = _charWeapon;
	}
}

void rlutilJM::DrawSprite(stats * _entity)
{
	if(_entity->type == CHARACTER)
	{
		int i, j;
		for (i = 0; i < _entity->spriteSizeY; i++)
		{
			for (j = 0; j < _entity->spriteSizeX; j++)
			{
				if ((_entity->sprite[i][j]) & CHARACTER1)
				{
					AddToBuffer(_entity->color1, _entity->bg1, _entity->letter1, _entity->x + j, _entity->y + i, _entity->type);
				}
				else if ((_entity->sprite[i][j]) & CHARACTER2)
				{
					AddToBuffer(_entity->color2, _entity->bg2, _entity->letter2, _entity->x + j, _entity->y + i, _entity->type);
				}
				else if ((_entity->sprite[i][j]) & CHARACTER3)
				{
					AddToBuffer(_entity->color3, _entity->bg3, _entity->letter3, _entity->x + j, _entity->y + i, _entity->type);
				}
				else if ((_entity->sprite[i][j]) & CHARACTER4)
				{
					AddToBuffer(_entity->color4, _entity->bg4, _entity->letter4, _entity->x + j, _entity->y + i, _entity->type);
				}
				else if ((_entity->sprite[i][j]) & WEAPON)
				{
					AddToBuffer(_entity->weapon, BLACK, _entity->charWeapon, _entity->x + j, _entity->y + i, _entity->type);
				}
				else if ((_entity->sprite[i][j]) & CLEAR)
				{
					AddToBuffer(BLACK, BLACK, ' ', _entity->x + j, _entity->y + i, CLEAR);
				}
				else
				{

				}
			}
		}
	}
	else if (_entity->type == BACKGROUND)
	{
		int i, j;
		for (i = 0; i < _entity->spriteSizeY; i++)
		{
			for (j = 0; j < _entity->spriteSizeX; j++)
			{
				if ((_entity->sprite[i][j]) & BACKGROUND1)
				{
					AddToBuffer(_entity->color1, _entity->bg1, _entity->letter1, _entity->x + j, _entity->y + i, _entity->type);
				}
				else if ((_entity->sprite[i][j]) & BACKGROUND2)
				{
					AddToBuffer(_entity->color2, _entity->bg2, _entity->letter2, _entity->x + j, _entity->y + i, _entity->type);
				}
				else if ((_entity->sprite[i][j]) & BACKGROUND3)
				{
					AddToBuffer(_entity->color3, _entity->bg3, _entity->letter3, _entity->x + j, _entity->y + i, _entity->type);
				}
				else if ((_entity->sprite[i][j]) & BACKGROUND4)
				{
					AddToBuffer(_entity->color4, _entity->bg4, _entity->letter4, _entity->x + j, _entity->y + i, _entity->type);
				}
				else if ((_entity->sprite[i][j]) & CLEAR)
				{
					AddToBuffer(BLACK, BLACK, ' ', _entity->x + j, _entity->y + i, CLEAR);
				}
				else
				{

				}
			}
		}
	}
}

int ** rlutilJM::InitializeSpriteArray(stats * _entity, int _spriteSizeX, int _spriteSizeY)
{
	{
		_entity->spriteSizeX = _spriteSizeX;
		_entity->spriteSizeY = _spriteSizeY;
		_entity->sprite = new int*[_entity->spriteSizeY];
		int i;
		for (i = 0; i < _entity->spriteSizeX; i++)
		{
 			_entity->sprite[i] = new int[_entity->spriteSizeX];
		}
		return _entity->sprite;
	}
}

void rlutilJM::InitializeBar(bar * _entity, int _x, int _y, int _maxValue, int _spriteSizeX, int _spriteSizeY, int _color1, int _color2, int _color3, int _constraint)
{
	_entity->x = _x;
	_entity->y = _y;
	_entity->maxValue = _maxValue;
	_entity->currValue = _maxValue;
	_entity->spriteSizeX = _spriteSizeX;
	_entity->spriteSizeY = _spriteSizeY;
	_entity->color1 = _color1;
	_entity->color2 = _color2;
	_entity->color3 = _color3;
	_entity->constraint = _constraint;
}

void rlutilJM::FreeSpriteArray(stats * _entity)
{
	{
		int i;
		for (i = 0; i < _entity->spriteSizeY; i++)
		{
			delete(_entity->sprite[i]);
		}
		delete(_entity->sprite);
	}
}

//void CheckCollisions(stats * _entity, stats _entities[])
//{
//}

void rlutilJM::SpriteMoveX(stats * _entity, int _movDirX)
{
	{
		_entity->x += (_entity->speed*_movDirX);
	}
}

void rlutilJM::SpriteMoveY(stats * _entity, int _movDirY)
{
	{
		_entity->y -= (_entity->speed*_movDirY);
	}
}

void rlutilJM::AddToBuffer(int _colorVal, int _backVal, char _letVal, int posx, int posy, int ocup)
{
	screenBuffer[posy][posx].backVal = _backVal;
	screenBuffer[posy][posx].colorVal = _colorVal;
	screenBuffer[posy][posx].letVal = _letVal;
	screenBuffer[posy][posx].ocupant = ocup;
}

void rlutilJM::ClearBuffer()
{
	rlutil::resetColor();
	int i, j;
	for (i = 0; i < SCREEN_SIZE_HEIGHT; i++)
	{
		for (j = 0; j < SCREEN_SIZE_WIDTH; j++)
		{
			screenBuffer[i][j].backVal = 0;
			screenBuffer[i][j].colorVal = 0;
			screenBuffer[i][j].letVal = ' ';
		}
	}
}

void rlutilJM::PrintBuffer()
{
	int i, j;
	for (i = 0; i < SCREEN_SIZE_HEIGHT; i++)
	{
		for (j = 0; j < SCREEN_SIZE_WIDTH; j++)
		{
			if (screenBuffer[i][j].backVal != lastScreenBuffer[i][j].backVal ||
				screenBuffer[i][j].colorVal != lastScreenBuffer[i][j].colorVal ||
				screenBuffer[i][j].letVal != lastScreenBuffer[i][j].letVal)
			{
				locate(j, i);
				setColor(screenBuffer[i][j].colorVal);
				setBackgroundColor(screenBuffer[i][j].backVal);
				printf("%c", screenBuffer[i][j].letVal);
			}
		}
	}
	for (i = 0; i < SCREEN_SIZE_HEIGHT; i++)
	{
		for (j = 0; j < SCREEN_SIZE_WIDTH; j++)
		{
			lastScreenBuffer[i][j].backVal = screenBuffer[i][j].backVal;
			lastScreenBuffer[i][j].colorVal = screenBuffer[i][j].colorVal;
			lastScreenBuffer[i][j].letVal = screenBuffer[i][j].letVal;
		}
	}
}

void rlutilJM::CreateFakeScreenBuffer()
{
	int i, j;
	screenBuffer = new tile*[SCREEN_SIZE_HEIGHT];
	lastScreenBuffer = new tile*[SCREEN_SIZE_HEIGHT];
	for (i = 0; i < SCREEN_SIZE_HEIGHT; i++)
	{
		screenBuffer[i] = new tile[SCREEN_SIZE_WIDTH];
		lastScreenBuffer[i] = new tile[SCREEN_SIZE_WIDTH];
	}
	for (i = 0; i < SCREEN_SIZE_HEIGHT; i++)
	{
		for (j = 0; j < SCREEN_SIZE_WIDTH; j++)
		{
			lastScreenBuffer[i][j].backVal = screenBuffer[i][j].backVal;
			lastScreenBuffer[i][j].colorVal = screenBuffer[i][j].colorVal;
			lastScreenBuffer[i][j].letVal = screenBuffer[i][j].letVal;
		}
	}
}

void rlutilJM::TextWrapper(const char * text, int color, int background, int posx, int posy)
{
	std::string a(text);
	for (int i = 0; i < a.size(); i++)
	{
		AddToBuffer(color, background, a[i], posx + i, posy, TEXT);
	}
}

int ** rlutilJM::FillEmptySprite(stats * _entity, int ** _sprite)
{
	int i, j;
	if (_sprite == NULL) {
		_sprite = new int*[_entity->spriteSizeY];
		for (i = 0; i < _entity->spriteSizeY; i++)
		{
			_sprite[i] = new int[_entity->spriteSizeX];
		}
	}
	for (i = 0; i < _entity->spriteSizeY; i++)
	{
		for (j = 0; j < _entity->spriteSizeX; j++)
		{
			_sprite[i][j] = EMPTY;
		}
	}
	return _sprite;
}

void rlutilJM::AddPixel(int y, int x, int content, int *** _sprite)
{
	*_sprite[y][x] = content;
}

