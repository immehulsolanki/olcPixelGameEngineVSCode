#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class BreakOut : public olc::PixelGameEngine
{
public:
	BreakOut()
	{
		sAppName = "Pixel_Experiments";
	}

private: // just for varialbles declaration all work will be done in bool OnUserUpdate(float fElapsedTime) override
	float batposX = 3.0f;
	float batWidth = 15.0f;
	float batSpeed = 25.0f; // small value will take more time to get int 1 and thus will slow the x pos. value and batspeed.
	/* ==== batSpeed = 25.0f ====
	the fBatSpeed value indicates how many pixels the object will move per second. 
	It's currently set at 0.1, which is very slow, it would take 10 seconds to move 1 pixel! 
	Since the arena is about 500 pixels across, I want it to take about 2 seconds for 
	player to full cross it, so thats speed = distance / time, speed = 50/2, so 25 pixels/s. 
	Let's change the fBatSpeed value to 25.
	*/

	olc::vd2d vBall = {10.0f, 10.0f}; //olc 2d data type. initial or default values. note:its center coords.
	olc::vd2d vBallVelocity = {10.0f, 9.0f}; // initial values as velocity.
	float vballRadius = 1.0f; // its radius to check boundry of ball.

public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Erase previous frame
		Clear(olc::DARK_BLUE);

		//bPressed - Is true only for the frame the button is pressed, all other frames it is false.
		//bHeld - Is true for all frames the button is held down in, including the first frame along with bPressed, All other frames it is false.
		//bReleased - Is true only for the frame the button is released, all other frames it is false.
		// increament x value by 1
		if(GetKey(olc::Key::LEFT).bHeld) batposX -= batSpeed * fElapsedTime;
		if(GetKey(olc::Key::RIGHT).bHeld) batposX += batSpeed * fElapsedTime;
		/* ====== fElapsedTime =====
		fElapsedTime represents the previous frame duration in seconds, 
		so a value of 0.002 would be 2 milliseconds.
		So let's look at the physics of moving an object again. 
		Consider A = acceleration, V = velocity and P = position. 
		The amount the velocity (speed) changes per frame is based upon acceleration:
		V = V + A * fElapsedTime
		The amount the position changes due to velocity is:
		P = P + V * fElapsedTime
		In our simple example game, I don't need accelerations, my objects will start and 
		stop moving instantaneously (breaks the laws of physics, but it's ok, it's a game!).
		Therefore I'll update the bat's position with constant velocities:
		*/

		//Make sure value not exceed outside the screen so lock the x value within screen width
		// on left side we can track by value x only
		if(batposX < 2) batposX = 2.0f;
		// on right side we need x+bat width also, and we will lcok at last pixal value - batwidth which gives x point.
		if(batposX + batWidth > float(ScreenWidth()) - 2.0f) batposX = float(ScreenWidth()) - 2.f - batWidth;

		// mouse: 0 = left button, 1 = right button and 2 = middle button
		// to locate ball with click on mouse in screen.
		if(GetMouse(0).bHeld){
			//vBall = { float( GetMouseX() ), float( GetMouseY() )}; // just get mouse x,y and apply to vBall x,y.
		}
		 
		/*
		Going back to very basic physics, we know that:
		speed = distance / time
		Rearranging for distance:
		distance = speed * time
		*/ 
		vBall +=  vBallVelocity * fElapsedTime; // just vel. vector will added to x,y values and location will change.
		// felap is ps delay in ms will controll constant speed with respect to fps.

		// Mousewheel will give positive and negative number.
		// simple track the value change in + or - direction and increament value by 1.0f.
		//if( GetMouseWheel() > 0 ) vballRadius += 1.0f;
		//if( GetMouseWheel() < 0 ) vballRadius -= 1.0f;

		//lock our ball radius min and max values so it cant exceed.
		if(vballRadius < 1.0f) vballRadius = 1.0f;
		if(vballRadius > 10.0f) vballRadius = 10.0f;

		// check wall hit and bounce back Note: vBallx y is its center coords.
		// check LEFT wall by x,y values because pixels counted from left as 0-max
		// we will track Ball x,y value because it is actual position.
		// then we will use 'velocty' vector with -1 muliplication which will simply convert it's
		// equal - value and then in aboce code we already mul with ball x,y.
		// inshort we track ball x,y and update its velocity vector.
		// X controls left and right movement.
		if(vBall.x <= 3.0f) vBallVelocity.x *= -1.0f;
		if(vBall.y <= 3.0f) vBallVelocity.y *= -1.0f; // Top wall and also bounce back to up direction 
		// if hit on left wall

		// similarly right wall means ScreenWidth - 3 px. or if we have max value 50px put directly.
		if(vBall.x >= float( ScreenWidth() ) - 3.0f ) vBallVelocity.x *= -1.0f; 
				
		//if(vBall.y >= float( ScreenWidth() ) - 3.0f ) vBallVelocity.y *= -1.0f; 

		// check bat by its x. left corner is x and right corner is x + batwidth.
		// we took y here because its comman to send ball up.
		if( (vBall.y >= float( ScreenWidth() ) - 3.0f ) && (vBall.x > batposX) && (vBall.x < batposX + batWidth) ) 
		vBallVelocity.y *= -1.0f;
		// vBall.x > batx means fron top y is and  when its down y increase but it should not bigger then batx = 47.
		// vBall.x < batx + w means anywhere on bat from bats current x + its width. so check if its outside bat.
		// i.e x 47 and 47+3 = 50 so if 51 then ball must fall.
		// Draw Boundary
		DrawLine(1, 1, ScreenWidth()-2, 1, olc::YELLOW); //x1,y1, x2,y2, color
		DrawLine(1, 1, 1, ScreenHeight()-2, olc::YELLOW);
		DrawLine(ScreenWidth()-2, 1, ScreenWidth()-2, ScreenHeight()-2, olc::YELLOW);
		// ScreenWidth() = lastpixel + 1 same for height.
		
		// this will simply draw the shape with given x,y vlaues.
		FillRect(int(batposX), 47, int(batWidth), 2, olc::GREEN ); //x1,y1(topleft corner), width,height, color
		// we can also use ScreenHeight() - 20 and ScreenWidth() - 10 functions.
        FillCircle(vBall, int(vballRadius), olc::CYAN); //{centerX, centerY, radius, color}



		return true;
	}
};

int main()
{
	BreakOut demo;
	if (demo.Construct(50, 50, 10, 10))
		demo.Start();
	return 0;
}