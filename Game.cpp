#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Shapes.hpp"
#include "Vector.hpp"


class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Rectangle Collision example!";
	}

public:

    olc::Pixel b1Color;

    RectF b1 = RectF({120,100}, {24,24});//Player
    RectF b2 = RectF({16,16}, {224, 16});//Top
    RectF b3 = RectF({16,208}, {224, 16});//Bottom
    RectF b4 = RectF({16,64}, {16, 112});//Left
    RectF b5 = RectF({224,64}, {16, 112});//Right
    RectF b6 = RectF({120,120}, {16, 16}); //Middle
    

public:
	bool OnUserCreate() override
	{
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
        if (GetElapsedTime() > 0.016)
        {
            Vector<float> vMouse = { float(GetMouseX()), float(GetMouseY()) };

        if (GetMouse(0).bHeld) //Move player towards the mouse
            b1.vel += ((vMouse - b1.pos).norm() * 100.0f ) * GetElapsedTime();

        if(GetMouse(1).bPressed) //Random size for player if Right Click
        {
            float w = rand() % 32;
            float h = rand() % 32;

            if (w < 16) w += 8;
            if (h < 16) h += 8;

            b1 = RectF({b1.center().x - w / 2, b1.center().y - h / 2}, {w, h}, b1.vel);
        }   

        b2.pos += b2.vel * GetElapsedTime(); //Updating position before collision
        b3.pos += b3.vel * GetElapsedTime(); //detection fixes the overlapping bug.
        b4.pos += b4.vel * GetElapsedTime();
        b5.pos += b4.vel * GetElapsedTime();
        b1.pos += b1.vel * GetElapsedTime(); 

        b1Color = olc::RED;

        if (b1.detectCollision(b2, GetElapsedTime())
        ||  b1.detectCollision(b3, GetElapsedTime())
        ||  b1.detectCollision(b4, GetElapsedTime())
        ||  b1.detectCollision(b5, GetElapsedTime())
        ||  b1.detectCollision(b6, GetElapsedTime()))
        {
            b1Color = olc::GREEN;
        }

        

		// 0-------------------0
        // | Draw              |
        // 0-------------------0
        Clear(olc::BLACK);

        FillRect({b2.pos.x, b2.pos.y}, {b2.size.x, b2.size.y});

        FillRect({b3.pos.x, b3.pos.y}, {b3.size.x, b3.size.y});

        FillRect({b4.pos.x, b4.pos.y}, {b4.size.x, b4.size.y});

        FillRect({b5.pos.x, b5.pos.y}, {b5.size.x, b5.size.y});

        FillRect({b6.pos.x, b6.pos.y}, {b6.size.x, b6.size.y});

        FillRect({b1.pos.x, b1.pos.y}, {b1.size.x, b1.size.y}, b1Color);

        DrawLine(vMouse.x, vMouse.y, b1.pos.x + b1.size.x / 2, b1.pos.y + b1.size.y / 2);

        // #####################
        }
			
		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}
