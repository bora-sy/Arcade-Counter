#include "Interaction/Components/Bitmap.h"

void Bitmap::Draw()
{
    Display::DrawBitmap(this->pos, this->bitmap, this->size, this->color, anchor);
}

Bitmap::Bitmap(){}

Bitmap::Bitmap(Point _p, const uint8_t* _bitmap, Size _size, Color _color, RelativePoint _anchor)
{
    this->pos = _p;
    this->bitmap = _bitmap;
    this->size = _size;
    this->anchor = _anchor;
    this->color = _color;
}

Bitmap::Bitmap(RelativePoint _rp, const uint8_t* _bitmap, Size _size, Color _color, RelativePoint _anchor)
{
    this->pos = _rp.ToPoint(Display::displaySize);
    this->bitmap = _bitmap;
    this->size = _size;
    this->anchor = _anchor;
    this->color = _color;
}