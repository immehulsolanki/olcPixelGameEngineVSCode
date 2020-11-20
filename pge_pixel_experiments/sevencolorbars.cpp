#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class BreakOut : public olc::PixelGameEngine
{
public:
	BreakOut()
	{
		sAppName = "Pixel_Experiments";
	}

public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Erase previous frame
		Clear(olc::DARK_BLUE);

		// Draw Boundary
		DrawLine(0, 0, 0, 7, olc::WHITE);
		DrawLine(1, 0, 1, 7, olc::YELLOW);
		DrawLine(2, 0, 2, 7, olc::CYAN);
		DrawLine(3, 0, 3, 7, olc::MAGENTA);
		DrawLine(4, 0, 4, 7, olc::RED);
		DrawLine(5, 0, 5, 7, olc::BLUE);
		DrawLine(6, 0, 6, 7, olc::BLACK);
		
		return true;
	}
};

int main()
{
	BreakOut demo;
	if (demo.Construct(7, 7, 50, 50))
		demo.Start();
	return 0;
}