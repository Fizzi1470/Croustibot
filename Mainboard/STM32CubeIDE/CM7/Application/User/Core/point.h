#ifndef CUSTOMPOINT_HPP
#define CUSTOMPOINT_HPP

#include "main.h"
#include <touchgfx/widgets/canvas/CanvasWidget.hpp>
#include <touchgfx/widgets/canvas/Canvas.hpp>

class CustomPoint : public touchgfx::CanvasWidget
{
public:
    CustomPoint() : x(0), y(0) {} // Position initiale à (0,0)

    void setPosition(int newX, int newY)
    {
        x = newX;
        y = newY;
        invalidate(); // Rafraîchir l'affichage
    }

    virtual touchgfx::Rect getMinimalRect() const override
    {
        return touchgfx::Rect(x, y, 2, 2); // Taille minimale du point
    }

protected:
    virtual bool drawCanvasWidget(const touchgfx::Rect& invalidatedArea) const override
    {
        //touchgfx::Canvas canvas(this, invalidatedArea);
        //canvas.moveTo(x, y);
        //canvas.lineTo(x+1, y+1); // Un petit point de 1 pixel
        //return canvas.render();
    }

private:
    int x, y;
};

#endif // CUSTOMPOINT_HPP
