#include "RestartButton.h"
#include "Engine.h"
RestartButton::RestartButton(Engine* engine) : _engine(engine) {}

void RestartButton::onClick() {
    _engine->restart();
}

void RestartButton::onHover() {
    auto c = _shape.getFillColor();
    c.a = 127;
    _shape.setFillColor(c);
} 


void RestartButton::onHoverLeave() {
    auto c = _shape.getFillColor();
    c.a = 255;
    _shape.setFillColor(c);
} 