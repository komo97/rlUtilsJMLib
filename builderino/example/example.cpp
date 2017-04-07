// EngineVergudo.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "rlutil\rlutilJM.h"
using namespace rlutilJM;

stats player;
bar lifeBar;

int **playerSprite;
std::string lifeText;
bool jumpity = false, gravity = true;

void PlayerSpriteFill()
{
	int i, j;
	if (playerSprite == NULL) {
		playerSprite = new int*[140];
		for (i = 0; i < 10; i++)
		{
			playerSprite[i] = new int[10];
		}
	}
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			playerSprite[i][j] = EMPTY;
		}
	}
	playerSprite[1][4] = CHARACTER1;
	playerSprite[2][4] = CHARACTER2;
	playerSprite[3][3] = CHARACTER2;
	playerSprite[3][4] = CHARACTER2;
	playerSprite[3][5] = CHARACTER2;
	playerSprite[3][6] = CHARACTER2;
	playerSprite[3][7] = CHARACTER2;
	playerSprite[4][3] = CHARACTER3;
	playerSprite[4][4] = CHARACTER3;
	playerSprite[4][5] = CHARACTER2;
	playerSprite[5][3] = CHARACTER3;
	playerSprite[5][4] = CHARACTER3;
	playerSprite[5][5] = CHARACTER2;
	playerSprite[6][3] = CHARACTER3;
	playerSprite[6][4] = CHARACTER3;
	playerSprite[6][5] = CHARACTER4;
	playerSprite[7][3] = CHARACTER3;
	playerSprite[7][5] = CHARACTER4;
	playerSprite[8][3] = CHARACTER3;
	playerSprite[8][5] = CHARACTER4;

}

void PlayerSpriteFill2()
{
	int i, j;
	if (playerSprite == NULL) {
		playerSprite = new int*[32];
		for (i = 0; i < 32; i++)
		{
			playerSprite[i] = new int[32];
		}
	}
	for (i = 0; i < 32; i++)
	{
		for (j = 0; j < 32; j++)
		{
			playerSprite[i][j] = EMPTY;
		}
	}

	playerSprite[7][12] = CHARACTER1;
	playerSprite[7][13] = CHARACTER1;

	playerSprite[8][11] = CHARACTER1;
	playerSprite[8][12] = CHARACTER1;
	playerSprite[8][13] = CHARACTER1;
	playerSprite[8][14] = CHARACTER1;

	playerSprite[9][10] = CHARACTER1;
	playerSprite[9][11] = CHARACTER1;
	playerSprite[9][12] = CHARACTER1;
	playerSprite[9][13] = CHARACTER1;
	playerSprite[9][14] = CHARACTER1;
	playerSprite[9][15] = CHARACTER1;

	playerSprite[10][10] = CHARACTER1;
	playerSprite[10][11] = CHARACTER1;
	playerSprite[10][12] = CHARACTER1;
	playerSprite[10][13] = CHARACTER1;
	playerSprite[10][14] = CHARACTER1;
	playerSprite[10][15] = CHARACTER1;
	//1
	playerSprite[11][11] = CHARACTER1;
	playerSprite[11][12] = CHARACTER1;
	playerSprite[11][13] = CHARACTER1;
	playerSprite[11][14] = CHARACTER1;
	//2
	playerSprite[12][11] = CHARACTER1;
	playerSprite[12][12] = CHARACTER1;
	playerSprite[12][13] = CHARACTER1;
	playerSprite[12][14] = CHARACTER1;
	//3
	playerSprite[13][11] = CHARACTER1;
	playerSprite[13][12] = CHARACTER1;
	playerSprite[13][13] = CHARACTER1;
	playerSprite[13][14] = CHARACTER1;
	//4
	playerSprite[14][11] = CHARACTER1;
	playerSprite[14][12] = CHARACTER1;
	playerSprite[14][13] = CHARACTER1;
	playerSprite[14][14] = CHARACTER1;
	//5
	playerSprite[15][11] = CHARACTER1;
	playerSprite[15][12] = CHARACTER1;
	playerSprite[15][13] = CHARACTER1;
	playerSprite[15][14] = CHARACTER1;
	//6
	playerSprite[16][11] = CHARACTER1;
	playerSprite[16][12] = CHARACTER1;
	playerSprite[16][13] = CHARACTER1;
	playerSprite[16][14] = CHARACTER1;
	//7
	playerSprite[17][11] = CHARACTER1;
	playerSprite[17][12] = CHARACTER1;
	playerSprite[17][13] = CHARACTER1;
	playerSprite[17][14] = CHARACTER1;
	//8
	playerSprite[18][11] = CHARACTER1;
	playerSprite[18][12] = CHARACTER1;
	playerSprite[18][13] = CHARACTER1;
	playerSprite[18][14] = CHARACTER1;
	//9
	playerSprite[19][11] = CHARACTER1;
	playerSprite[19][12] = CHARACTER1;
	playerSprite[19][13] = CHARACTER1;
	playerSprite[19][14] = CHARACTER1;
	//10
	playerSprite[20][11] = CHARACTER1;
	playerSprite[20][12] = CHARACTER1;
	playerSprite[20][13] = CHARACTER1;
	playerSprite[20][14] = CHARACTER1;
	//11
	playerSprite[21][11] = CHARACTER1;
	playerSprite[21][12] = CHARACTER1;
	playerSprite[21][13] = CHARACTER1;
	playerSprite[21][14] = CHARACTER1;
	//12
	playerSprite[22][11] = CHARACTER1;
	playerSprite[22][12] = CHARACTER1;
	playerSprite[22][13] = CHARACTER1;
	playerSprite[22][14] = CHARACTER1;

	playerSprite[23][8] = CHARACTER1;
	playerSprite[23][9] = CHARACTER1;
	playerSprite[23][11] = CHARACTER1;
	playerSprite[23][12] = CHARACTER1;
	playerSprite[23][13] = CHARACTER1;
	playerSprite[23][14] = CHARACTER1;
	playerSprite[23][16] = CHARACTER1;
	playerSprite[23][17] = CHARACTER1;

	playerSprite[24][7] = CHARACTER1;
	playerSprite[24][8] = CHARACTER1;
	playerSprite[24][9] = CHARACTER1;
	playerSprite[24][10] = CHARACTER1;
	playerSprite[24][11] = CHARACTER1;
	playerSprite[24][12] = CHARACTER1;
	playerSprite[24][13] = CHARACTER1;
	playerSprite[24][14] = CHARACTER1;
	playerSprite[24][15] = CHARACTER1;
	playerSprite[24][16] = CHARACTER1;
	playerSprite[24][17] = CHARACTER1;
	playerSprite[24][18] = CHARACTER1;

	playerSprite[25][7] = CHARACTER1;
	playerSprite[25][8] = CHARACTER1;
	playerSprite[25][9] = CHARACTER1;
	playerSprite[25][10] = CHARACTER1;
	playerSprite[25][11] = CHARACTER1;
	playerSprite[25][12] = CHARACTER1;
	playerSprite[25][13] = CHARACTER1;
	playerSprite[25][14] = CHARACTER1;
	playerSprite[25][15] = CHARACTER1;
	playerSprite[25][16] = CHARACTER1;
	playerSprite[25][17] = CHARACTER1;
	playerSprite[25][18] = CHARACTER1;

	playerSprite[26][8] = CHARACTER1;
	playerSprite[26][9] = CHARACTER1;
	playerSprite[26][10] = CHARACTER1;
	playerSprite[26][15] = CHARACTER1;
	playerSprite[26][16] = CHARACTER1;
	playerSprite[26][17] = CHARACTER1;
}

void Draw()
{
	ClearBuffer();

	FillBar(&lifeBar, NULL, player.life);
	DrawSprite(&player);
	lifeText = ("Life: " + std::to_string(player.life));
	TextWrapper(lifeText.c_str(), GREEN, BLACK, 10, 13);
	PrintBuffer();
	if (player.y < 30 && jumpity) {
		gravity = true;
		jumpity = false;
	}
	else if((!jumpity && player.y >= 70)){
		gravity = false;
	}
	if (gravity && !jumpity)
	{
		SpriteMoveY(&player, DIRDOWN);
	}
	if (jumpity) SpriteMoveY(&player, DIRUP);
	msleep(8);

}

int main()
{

	WindowSize(100, 100);
	PlayerSpriteFill();
	SetStats(&player, 10, 10, 100, 1, 1, CHARACTER);
	InitializeBar(&lifeBar, 10, 6, player.life, 25, 5, GREEN, YELLOW, RED, BLUE);
	player.sprite = InitializeSpriteArray(&player, 10, 10);
	/*player.sprite = InitializeSpriteArray(&player, 32, 32);*/
	player.sprite = SpriteParams(&player, LIGHTMAGENTA, BLUE, RED, GREEN, LIGHTMAGENTA, 0, 0, 0, (playerSprite), 0);
	CharSpriteParams(&player, '*', '*', '*', '*', '*');
	while (1)
	{
		KeepScreenSize();
		Draw();
		if (kbhit())
		{
			char hit = getch();
			if (hit == 'a')
			{
				SpriteMoveX(&player, DIRLEFT);
			}
			else if (hit == 'd')
			{
				SpriteMoveX(&player, DIRRIGHT);
			}
			else if (hit == ' ' || jumpity)
			{
				jumpity = true;
			}
			else if (hit == '6')
			{
				player.life--;
			}
			else if (hit == '-')
			{
				return 0;
			}
		}
		else
		{
			SpriteMoveX(&player, NOMOVE);
			SpriteMoveY(&player, NOMOVE);
		}
	}
	resetColor();
	return 0;
}