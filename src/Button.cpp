#include "Button.h"

Button::Button() {
    _shape.setSize({200, 100});
    _text.setCharacterSize(25);
    _text.setPosition({0, 0});
}

void Button::setFont(sf::Font* font) { 
    _font = font; 
    _text.setFont(*_font);    
}

void Button::setDisplayText(std::string text) { 
    _display_text = text; 
    _text.setString(text);
}

sf::Vector2f Button::getPosition() const {
    return _shape.getPosition();
}

void Button::setSize(float w, float h) { _shape.setSize({w,h}); }

void Button::setOutlineThickness(float t) { _shape.setOutlineThickness(t); }

void Button::setFillColor(sf::Color c) { _shape.setFillColor(c); }

void Button::setTextColor(sf::Color c) { _text.setColor(c); }

void Button::setOutlineColor(sf::Color c) { _shape.setOutlineColor(c); }

void Button::onClick() {  }

void Button::onHover() {  }

void Button::onHoverLeave() {  }

bool Button::pointInside(sf::Vector2f point) const { 
    return _shape.getPosition().x < point.x && point.x < _shape.getPosition().x + _shape.getSize().x
        &&  _shape.getPosition().y < point.y && point.y < _shape.getPosition().y + _shape.getSize().y;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_shape);
    target.draw(_text);
}

void Button::setPosition(sf::Vector2f x) {
    _shape.setPosition(x);
    _text.setPosition(x);
}