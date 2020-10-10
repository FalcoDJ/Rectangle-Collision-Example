#ifndef TGE_SHAPES_HPP
#define TGE_SHAPES_HPP

#include "Vector.hpp"
#include <cmath>

template <class num>
struct Rect
{
    public:

    Vector<num> pos, vel, size;
    Vector<num> center()
    {
        num centerX = pos.x + size.x / 2;
        num centerY = pos.y + size.y / 2;
        return Vector<num>({centerX, centerY});
    }
    num right()
    {
        return pos.x + size.x;
    }
    num bottom()
    {
        return pos.y + size.y;
    }

    Rect();

    //Define positions
    Rect(Vector<num> _pos) : pos(_pos) {}

    //Define entire rectangle
    Rect(Vector<num> _pos, Vector<num> _size) : pos(_pos), size(_size) {}

    //Define the whole Rectangle with a velocity
    Rect(Vector<num> _pos, Vector<num> _size, Vector<num> _vel) : pos(_pos), size(_size), vel(_vel) {}

    bool detectCollision(Rect Targ,  float ElapsedTime);
    bool detectCollisionX(Rect Targ, float ElapsedTime);
    bool detectCollisionY(Rect Targ, float ElapsedTime);
};

typedef Rect<int>          RectI;
typedef Rect<float>        RectF;
typedef Rect<double>       RectD;
typedef Rect<unsigned int> RectU;

template <class num>
bool Rect<num>::detectCollision(Rect Targ, float ElapsedTime)
{
    if (detectCollisionX(Targ, ElapsedTime) && detectCollisionY(Targ, ElapsedTime))
    {
        num Hd = center().x - Targ.center().x;
        num Vd = center().y - Targ.center().y;
        num Aw = (size.x + Targ.size.x) * 0.5;
        num Ah = (size.y + Targ.size.y) * 0.5;

        num overlap_x = Aw - std::abs(Hd);
        num overlap_y = Ah - std::abs(Vd);

        if (overlap_x < overlap_y)
        {
            //If collision happens on X axis
            vel.x = Targ.vel.x;
            
            if (Hd > 0)
            {
                pos.x += Targ.right() - pos.x;
            }
            else
            {
                pos.x -= right() - Targ.pos.x;
            }
            
        }
        else
        {
            //If collision happens on Y axis
            vel.y = Targ.vel.y;
            
            if (Vd > 0)
            {
                pos.y += Targ.bottom() - pos.y;
            }
            else
            {
                pos.y -= bottom() - Targ.pos.y;
            }
        }
        
        return true;
    }

    return false;
}

template <class num>
bool Rect<num>::detectCollisionX(Rect Targ, float ElapsedTime)
{
    if (vel.x > 0)
    return (pos.x + vel.x * ElapsedTime <= Targ.pos.x + Targ.size.x && Targ.pos.x + Targ.vel.x * ElapsedTime <= pos.x + size.x);
    //else
    return (pos.x <= Targ.pos.x + Targ.size.x + Targ.vel.x * ElapsedTime && Targ.pos.x <= pos.x + size.x + vel.x * ElapsedTime);
}

template <class num>
bool Rect<num>::detectCollisionY(Rect Targ, float ElapsedTime)
{
    if (vel.y > 0)
    return (pos.y + vel.y * ElapsedTime <= Targ.pos.y + Targ.size.y && Targ.pos.y + Targ.vel.y * ElapsedTime <= pos.y + size.y);
    //else
    return (pos.y <= Targ.pos.y + Targ.size.y + Targ.vel.y * ElapsedTime && Targ.pos.y <= pos.y + size.y + vel.y * ElapsedTime);
}

#endif