#include "OnHoverButton.h"


void OnHoverButton::onHover() {
    auto c = _shape.getFillColor();
    c.a = 127;
    _shape.setFillColor(c);
} 


void OnHoverButton::onHoverLeave() {
    auto c = _shape.getFillColor();
    c.a = 255;
    _shape.setFillColor(c);
} 