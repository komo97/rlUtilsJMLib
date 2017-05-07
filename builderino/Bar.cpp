#include "Bar.h"

Bar::Bar(int _x, int _y)
{
	x = _x;
	y = _y;
}

Bar::~Bar()
{
}

void Bar::setColors(const int& col1, const int& col2, const int& col3)
{
	color1 = col1;
	color2 = col2;
	color3 = col3;
}

void Bar::InitSprite(const int& _width, const int& _height)
{
	spriteSizeX = _width;
	spriteSizeY = _height;
}

void Bar::draw()
{
	rlUtilJM::AddToDrawThread(std::bind(&Bar::DrawBody, this));
}

void Bar::DrawBody()
{
	float aPercent = (currValue * 100) / maxValue;
	float drawPercent = (spriteSizeX*percent) / 100;
	percent = aPercent;
	for (int i = 0; i < spriteSizeY; i++)
	{
		for (int j = 0; j < spriteSizeX; j++)
		{
			if (i == 0 || i + 1 == spriteSizeY || j == 0 || j + 1 == spriteSizeX)
			{
				rlUtilJM::AddToBuffer(constraint, constraint, '\0', x + j, y + i, RLBAR, nullptr);
			}
			else if (j <= drawPercent && (percent) >= 50)
			{
				rlUtilJM::AddToBuffer(color1, color1, '\0', x + j, y + i, RLBAR, nullptr);
			}
			else if (j <= drawPercent && (percent) < 50 && (percent) > 25)
			{
				rlUtilJM::AddToBuffer(color2, color2, '\0', x + j, y + i, RLBAR, nullptr);
			}
			else if (j <= drawPercent && (percent) <= 25)
			{
				rlUtilJM::AddToBuffer(color3, color3, '\0', x + j, y + i, RLBAR, nullptr);
			}
			else
			{
				rlUtilJM::AddToBuffer(	ALPHACOLOR,	ALPHACOLOR, '\0', x + j, y + i, CLEAR, nullptr);
			}
		}
	}
}
