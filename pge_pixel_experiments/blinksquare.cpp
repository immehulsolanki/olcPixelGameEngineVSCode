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
		DrawLine(0, 0, 10, 0, olc::YELLOW); //x1,y1, x2,y2, color
		FillRect(2, 7, 3, 2, olc::GREEN ); //x1,y1(topleft corner), width,height, color
		// we can also use ScreenHeight() - 20 and ScreenWidth() - 10 functions.
        FillCircle({5,5}, 1, olc::CYAN);
		return true;
	}
};

int main()
{
	BreakOut demo;
	if (demo.Construct(10, 10, 50, 50))
		demo.Start();
	return 0;
}