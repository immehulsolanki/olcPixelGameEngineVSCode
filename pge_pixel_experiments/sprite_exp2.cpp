#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

// define map in 1d array
// load sprite and draw
// move with mouse
// pan the whole freme with red tile inside.

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

	int gpixel_sx = 0;
	int gpixel_sy = 0;
	
	int fOffsetX = 0;
	int fOffsetY = 0;

	int fStartPanX = 0; // for mouse offset, mainoffset + mouse offset
	int fStartPanY = 0;

	olc::vd2d tilePosition = {5, 5};	
	int diffx = 0;
	int diffy = 0;

	// equation to substract our world space with respect to screen space
	// offset x,y is how far our scree from main display
	// sx = wx - ox; sy = wy - oy; we get screen space calculated
	// world to screen or our drawing to actual screen
	void WorldToScreen(int fWorldX, int fWorldY, int &nScreenX, int &nScreenY ){
		nScreenX = fWorldX - fOffsetX;
		nScreenY = fWorldY - fOffsetY;
		// directly write in to reference varialble no return.
	}

	// wx = sx + ox; wy = sy + oy;
	// actual screen to our drawing or screen to world.
	void ScreenToWorld(int nScreenX, int nScreenY, int &fWorldX, int &fWorldY){
		fWorldX =  nScreenX + fOffsetX;
		fWorldY =  nScreenY + fOffsetY;
	}

public:
	bool OnUserCreate() override
	{	
		// default place for world space.
		fOffsetX = -1; // in sprite drawing we mul with 16. later - - = +;
		fOffsetY = -1;

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
		// Draw Screen boundry ==================================
		Clear(olc::DARK_BLUE);
		SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x <10; x++)
			{
				// new coords for x,y drawing offset this our world space or our drawings.
				int sx = x, sy = y;
				int ex = 0, ey = y;

				int pixel_sx, pixel_sy, pixel_ex, pixel_ey;

				//pixel_sy, pixel_sy is not initialized yet, but it will return from function.
				WorldToScreen(sx, sy, pixel_sx, pixel_sy);

				// update global pixel var for to use outside space only save first pixel of greed
				// to use as referece for next.
				if(x == 0 && y == 0){
					gpixel_sx = pixel_sx; //get first x,y
					gpixel_sy = pixel_sy;
				}

				switch (blocks[y * 10 + x])
				{
				case 0: // Do nothing
					break;
				case 10: // Draw Boundary, second (0,0) is index of tile.png to get diff. color tile.
					//DrawPartialSprite(olc::vi2d(x, y) * vBlockSize, sprTile.get(), olc::vi2d(0, 0) * vBlockSize, vBlockSize);
					DrawPartialSprite(olc::vi2d(pixel_sx, pixel_sy) * vBlockSize, sprTile.get(), olc::vi2d(0, 0) * vBlockSize, vBlockSize);
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
		// =======================================================

		// if ( GetMouse(0).bHeld ){
		// 	tilePosition = {GetMouseX() / 16, GetMouseY() / 16}; 
		// 	// our greed is 160x160 and sprite are 16x16
		// 	// mouse will return actuali pixel so we need to devide by sprite dim 16x16
		// 	// to move with mouse
		// }
		
		// mouse for pan
		int fMouseX = GetMouseX() / 16;
		int fMouseY = GetMouseY() / 16;

		//std::cout<< fMouseX << "_" << fMouseY << std::endl;

		if ( fMouseX < gpixel_sx || fMouseY < gpixel_sy || fMouseX > gpixel_sx + 10 || fMouseY > gpixel_sy + 10 ){
			
			if( GetMouse(0).bPressed ){
				fStartPanX = fMouseX ;
				fStartPanY = fMouseY ;				
			}

			if( GetMouse(0).bHeld ){
				fOffsetX -= (fMouseX - fStartPanX); // now change our default offset -1 to new mouse pos.
				fOffsetY -= (fMouseY - fStartPanY);

				//update mouse offset for next epoch
				fStartPanX = 0 - fOffsetX - 1;
				fStartPanY = 0 - fOffsetY - 1;

				//std::cout<< fStartPanX << "_" << fStartPanY << std::endl;
				tilePosition.x = diffx + gpixel_sx;
				tilePosition.y = diffy + gpixel_sy;

				//DrawPartialSprite(olc::vi2d(tilePosition.x, tilePosition.y) * vBlockSize, sprTile.get(), olc::vi2d(1, 0) * vBlockSize, vBlockSize);

				}
		
		}
		
		else{
		//for red tile
		
		if( GetMouse(0).bHeld ){
			tilePosition = {GetMouseX() / 16, GetMouseY() / 16}; 		
		}

		//DrawPartialSprite(olc::vi2d(tilePosition.x, tilePosition.y) * vBlockSize, sprTile.get(), olc::vi2d(1, 0) * vBlockSize, vBlockSize);
		diffx = tilePosition.x - gpixel_sx;
		diffy = tilePosition.y - gpixel_sy;


		}

		DrawPartialSprite(olc::vi2d(tilePosition.x, tilePosition.y) * vBlockSize, sprTile.get(), olc::vi2d(1, 0) * vBlockSize, vBlockSize);

		SetPixelMode(olc::Pixel::NORMAL); // Draw all pixels
		return true;
	}
};

int main()
{
	BreakOut demo;
	//std::cout << system("dir") << std::endl;
	if ( demo.Construct(600, 600, 1, 1) );
		demo.Start();
	return 0;
}