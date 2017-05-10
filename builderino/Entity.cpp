#include "Entity.h"

Entity::Entity(const int& _type, const int& _x, const int& _y)
{
	type = _type;
	pos = rlVector2(_x, _y);
	sprite = NULL;
	otherColEntity = NULL;
	rlUtilJM::AddEntityToManager(this);
}

Entity::Entity()
{
	sprite = NULL;
	otherColEntity = NULL;
	rlUtilJM::AddEntityToManager(this);
}

Entity::~Entity()
{
	freeSprite();
}

void Entity::setSprite( int ** const& _sprite)
{
	for (int i = 0; i < spriteSizeY; ++i)
	{
		for (int j = 0; j < spriteSizeX; ++j)
		{
			if (sprite[i][j] != NULL && sprite[i][j] != _sprite[i][j] && 
				!(pos.getX() + j > rlUtilJM::getScreenWidth() - 1 ||
				pos.getX() + j < 0 || pos.getY() + i < 0 ||
				pos.getY() + i > rlUtilJM::getScreenHeight() - 1))
				rlUtilJM::SetDrawnTile(false, pos.getX() + j, pos.getY() + i);
			sprite[i][j] = _sprite[i][j];
		}
	}
}

void Entity::setColors(const int& col1, const int& col2, const int& col3, const int& col4)
{
	color1 = col1;
	color2 = col2;
	color3 = col3;
	color4 = col4;
}

void Entity::setLetters(const char& let1, const char& let2, const char& let3, const char& let4)
{
	letter1 = let1;
	letter2 = let2;
	letter3 = let3;
	letter4 = let4;
}

void Entity::setBackgrounds(const int& _bg1, const int& _bg2, const int& _bg3, const int& _bg4)
{
	bg1 = _bg1;
	bg2 = _bg2;
	bg3 = _bg3;
	bg4 = _bg4;
}

void Entity::InitSprite(const int& sizeX, const int& sizeY)
{
	spriteSizeX = sizeX;
	spriteSizeY = sizeY;
	sprite = new int*[spriteSizeY];
	for (int i = 0; i <spriteSizeY; ++i)
	{
		sprite[i] = new int[spriteSizeX];
		for (int j = spriteSizeX; j--;)
			sprite[i][j] = NULL;
	}
}

void Entity::addX(const float & _x)
{
	pos.moveX(_x); 
}

void Entity::addY(const float & _y)
{
	pos.moveY(_y);
}

void Entity::draw()
{
	if (sprite == NULL)
		return;
	DrawBody();
}

void Entity::freeSprite()
{
	for (int i = 0; i < spriteSizeY; ++i)
	{
		delete[](sprite[i]);
	}
	delete(sprite);
}

void Entity::DrawBody()
{
	if (type == RLCHARACTER || type == RLENEMY)
	{
		int i, j;
		for (i = 0; i < spriteSizeY; ++i)
		{
			for (j = 0; j < spriteSizeX; ++j)
			{
				int x = (pos.getX() + j) % rlUtilJM::getScreenWidth();
				int y = (pos.getY() + i) % rlUtilJM::getScreenHeight();
				x = x < 0 ? (rlUtilJM::getScreenWidth() + x) : x;
				y = y < 0 ? (rlUtilJM::getScreenHeight() + y) : y;
				if ((sprite[i][j]) & CHARACTER1)
				{
					rlUtilJM::AddToBuffer(color1, bg1, letter1, x, y, type, this);
					rlUtilJM::SetStaticTile(isStatic, x, y);
				}
				else if ((sprite[i][j]) & CHARACTER2)
				{
					rlUtilJM::AddToBuffer(color2, bg2, letter2, x, y, type, this);
					rlUtilJM::SetStaticTile(isStatic, x, y);
				}
				else if ((sprite[i][j]) & CHARACTER3)
				{
					rlUtilJM::AddToBuffer(color3, bg3, letter3, x, y, type, this);
					rlUtilJM::SetStaticTile(isStatic, x, y);
				}
				else if ((sprite[i][j]) & CHARACTER4)
				{
					rlUtilJM::AddToBuffer(color4, bg4, letter4, x, y, type, this);
					rlUtilJM::SetStaticTile(isStatic, x, y);
				}
				else if ((sprite[i][j]) & WEAPON)
				{
					rlUtilJM::AddToBuffer(weapon, ALPHACOLOR, charWeapon, x, y, type, this);
					rlUtilJM::SetStaticTile(isStatic, x, y);
				}
				else if ((sprite[i][j]) & CLEAR)
				{
					rlUtilJM::AddToBuffer(ALPHACOLOR, ALPHACOLOR, '\9', x, y, CLEAR, nullptr);
				}
				else
				{

				}
			}
		}
	}
	else if (type == RLBACKGROUND)
	{
		int i, j;
		for (i = 0; i < spriteSizeY; ++i)
		{
			for (j = 0; j < spriteSizeX; ++j)
			{
				if (pos.getX() + j > rlUtilJM::getScreenWidth() - 1 ||
					pos.getX() + j < 0 || pos.getY() + i < 0 ||
					pos.getY() + i > rlUtilJM::getScreenHeight() - 1)
					continue;
				if ((sprite[i][j]) & BACKGROUND1)
				{
					rlUtilJM::AddToBuffer(color1, bg1, letter1, pos.getX() + j, pos.getY() + i, type, this);
					rlUtilJM::SetStaticTile(isStatic, pos.getX() + j, pos.getY() + i);
				}
				else if ((sprite[i][j]) & BACKGROUND2)
				{
					rlUtilJM::AddToBuffer(color2, bg2, letter2, pos.getX() + j, pos.getY() + i, type, this);
					rlUtilJM::SetStaticTile(isStatic, pos.getX() + j, pos.getY() + i);
				}
				else if ((sprite[i][j]) & BACKGROUND3)
				{
					rlUtilJM::AddToBuffer(color3, bg3, letter3, pos.getX() + j, pos.getY() + i, type, this);
					rlUtilJM::SetStaticTile(isStatic, pos.getX() + j, pos.getY() + i);
				}
				else if ((sprite[i][j]) & BACKGROUND4)
				{
					rlUtilJM::AddToBuffer(color4, bg4, letter4, pos.getX() + j, pos.getY() + i, type, this);
					rlUtilJM::SetStaticTile(isStatic, pos.getX() + j, pos.getY() + i);
				}
				else if ((sprite[i][j]) & CLEAR)
				{
					rlUtilJM::AddToBuffer(ALPHACOLOR, ALPHACOLOR, '\0', pos.getX() + j, pos.getY() + i, CLEAR, nullptr);
				}
				else
				{

				}
			}
		}
	}
}
