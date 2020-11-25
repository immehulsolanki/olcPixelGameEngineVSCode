#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// define map in 1d array
// load sprite and draw
// move with mouse

class BreakOut : public olc::PixelGameEngine
{
public:
	BreakOut()
	{
		sAppName = "Pixel Experiments";
	}

private:
	float fBatPos = 20.0f;
	float fBatWidth = 40.0f;
	olc::vf2d vBall = { 200.0f, 200.0f };
	olc::vf2d vBallVel = { 200.0f, -100.0f };
	float fBatSpeed = 250.0f;
	float fBallRadius = 5.0f;
	olc::vi2d vBlockSize = { 16,16 };
	std::unique_ptr<int[]> blocks;

	std::unique_ptr<olc::Sprite> sprTile;

	//test
	olc::vd2d tilePosition = {5, 5};

public:
	bool OnUserCreate() override
	{	
		// 10x10 is our cutom map for putting obstacle and things as sprited (assmued square).
		// so always take dimention of sprite as 10x10 dim or no. defined here.
		blocks = std::make_unique<int[]>(10 * 10);
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				// when this virtual 2d we write in index
				if (x == 0 || y == 0 || x == 9 || y == 9) // this will draw in whole line.
				// we write in index single value
				// i = x + width * y
					blocks[y * 10 + x] = 10;
				else
					blocks[y * 10 + x] = 0;
				
				if(x == 5 && y == 5){
					blocks[y * 10 + x] = 1;
				}
				//if (x > 2 && x <= 20 && y > 3 && y <= 5)
					//blocks[y * 24 + x] = 1;
				//if (x > 2 && x <= 20 && y > 5 && y <= 7)
					//blocks[y * 24 + x] = 2;
				//if (x > 2 && x <= 20 && y > 7 && y <= 9)
					//blocks[y * 24 + x] = 3;
				// std::cout << blocks [y * 10 + x]; // debug
			}
			// std::cout << std::endl; //debug
		 }
		
		// Load the sprite
		
		sprTile = std::make_unique<olc::Sprite>("D:/ADesktop/vsCppWorkSpace/cpppge/pge_pixel_experiments/gfx/tut_tiles.png");
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Draw Screen
		Clear(olc::DARK_BLUE);
		SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x <10; x++)
			{
				switch (blocks[y * 10 + x])
				{
				case 0: // Do nothing
					break;
				case 10: // Draw Boundary, second (0,0) is index of tile.png to get diff. color tile.
					DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(0, 0) * vBlockSize, vBlockSize);
					break;
				// case 1: // Draw Red Block
				 	// DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(1, 0) * vBlockSize, vBlockSize);
				 	// break;
				// case 2: // Draw Green Block
				// 	DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(2, 0) * vBlockSize, vBlockSize);
				// 	break;
				// case 3: // Draw Yellow Block
				// 	DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(3, 0) * vBlockSize, vBlockSize);
				// 	break;
				}	
			//std::cout << olc::vi2d(x, y) * vBlockSize;
			}
			//std::cout << std::endl;			
		}	
		if ( GetMouse(0).bHeld ){
			tilePosition = {GetMouseX() / 16, GetMouseY() / 16}; 
			// our greed is 160x160 and sprite are 16x16
			// mouse will return actuali pixel so we need to devide by sprite dim 16x16
			// to move with mouse
		}
		DrawPartialSprite(olc::vi2d(tilePosition) * vBlockSize, sprTile.get(), olc::vi2d(1, 0) * vBlockSize, vBlockSize);
		SetPixelMode(olc::Pixel::NORMAL); // Draw all pixels
		return true;
	}
};

int main()
{
	BreakOut demo;
	//std::cout << system("dir") << std::endl;
	if ( demo.Construct(160, 160, 4, 4) );
		demo.Start();
	return 0;
}