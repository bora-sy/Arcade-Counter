#pragma once
#include <PagedView.h>

class Bitmap : public PageComponent
{
private:
    const uint8_t* bitmap;
    Size size;
    Color color;

public:
    void Draw() override;
    Bitmap();
    Bitmap(Point _p, const uint8_t* _bitmap, Size _size, Color _color, RelativePoint _anchor = RelativePoint(0,0));

    Bitmap(RelativePoint _rp, const uint8_t* _bitmap, Size _size, Color _color, RelativePoint _anchor = RelativePoint(0,0));
};