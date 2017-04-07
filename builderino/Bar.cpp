#include "Bar.h"

Bar::Bar(int _x, int _y)
{
	x = _x;
	y = _y;
}

Bar::~Bar()
{
}

void Bar::setColors(int col1, int col2, int col3)
{
	color1 = col1;
	color2 = col2;
	color3 = col3;
}

void Bar::InitSprite(int _width, int _height)
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
				rlUtilJM::AddToBuffer(constraint, constraint, ' ', x + j, y + i, BAR, nullptr);
			}
			else if (j <= drawPercent && (percent) >= 50)
			{
				rlUtilJM::AddToBuffer(color1, color1, ' ', x + j, y + i, BAR, nullptr);
			}
			else if (j <= drawPercent && (percent) < 50 && (percent) > 25)
			{
				rlUtilJM::AddToBuffer(color2, color2, ' ', x + j, y + i, BAR, nullptr);
			}
			else if (j <= drawPercent && (percent) <= 25)
			{
				rlUtilJM::AddToBuffer(color3, color3, ' ', x + j, y + i, BAR, nullptr);
			}
			else
			{
				rlUtilJM::AddToBuffer(BLACK, BLACK, ' ', x + j, y + i, CLEAR, nullptr);
			}
		}
	}
}
