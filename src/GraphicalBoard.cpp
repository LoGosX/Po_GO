#include "GraphicalBoard.h"
#include "AssetsManager.h"
#include <iostream>

GraphicalBoard::GraphicalBoard(float bs, float bpw, float bph, float sr, AssetManager<sf::Texture>* tm) : 
    _board_size(bs), _pixel_w(bpw), _pixel_h(bph), _stone_radius(sr), _textures_manager(tm), _cell_pixel_w (bpw / bs), _cell_pixel_h(bph / bs)
{
    _stone_radius = _cell_pixel_w / 5.F;

    _white_stone.setRadius(_stone_radius);
    _white_stone.setOrigin({_stone_radius, _stone_radius});
    _white_stone.setOutlineColor(sf::Color::Black);
    _white_stone.setOutlineThickness(5.F);
    _white_stone.setFillColor(sf::Color::White);

    _black_stone.setRadius(_stone_radius);
    _black_stone.setOrigin({_stone_radius, _stone_radius});
    _black_stone.setOutlineColor(sf::Color::Black);
    _black_stone.setOutlineThickness(5.F);
    _black_stone.setFillColor(sf::Color::Black);

}

std::pair<bool, std::pair<int,int>> GraphicalBoard::canPlaceStone(float mx, float my)
{
    float x = mx - _board_position_x - 0.5F * _cell_pixel_w;
    float y = my - _board_position_y - 0.5F * _cell_pixel_h;
    float col = x / _cell_pixel_w;    
    float row = y / _cell_pixel_h;
    int c = round(col);
    int r = round(row);
    //check if click is withing 1/4 of cell radius
    if((c - col) * (c - col) > 1.F / 16)
        return {false, {-1,-1}};
    if((r - row) * (r - row) > 1.F/ 16)
        return {false, {-1,-1}};
    if(r < 0 || c < 0 || r >= _board_size || c >= _board_size)
        return {false, {-1, -1}};
    return {true, {r,c}};
}

void GraphicalBoard::placeStone(int r, int c, bool ws)
{
    if(ws)
        _white_stones_positons.emplace_back(r,c);   
    else
        _black_stones_positons.emplace_back(r,c);
}

void GraphicalBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    _drawBoard(target);
    _drawStones(target);
}

void GraphicalBoard::_drawBoard(sf::RenderTarget& target) const {
   
   sf::RectangleShape background;
   background.setFillColor(sf::Color::Yellow);
   background.setSize({_pixel_w, _pixel_h});
   target.draw(background);
   sf::RectangleShape horizontal_line;
   horizontal_line.setFillColor(sf::Color::Black);
   horizontal_line.setSize({_pixel_w - _cell_pixel_w, 5.F});
   auto vertical_line = horizontal_line;
   vertical_line.setSize({5.F, _pixel_h - _cell_pixel_h});
   float dx = _pixel_w / _board_size, dy = _pixel_h / _board_size;
   for(int i = 0; i < _board_size; i++)
   {
       horizontal_line.setPosition(0.5F * _cell_pixel_w, 0.5F * _cell_pixel_h + dy * i);
       vertical_line.setPosition(0.5F * _cell_pixel_w + dx * i, 0.5F * _cell_pixel_h);
       target.draw(horizontal_line);
       target.draw(vertical_line);
   }
}

void GraphicalBoard::_drawStones(sf::RenderTarget& target) const {
    auto stone = _white_stone;
    for(auto pos : _white_stones_positons)
    {
        stone.setPosition(pos.second * _cell_pixel_w + 0.5F * _cell_pixel_w, pos.first * _cell_pixel_h + 0.5F * _cell_pixel_h);
        target.draw(stone);
    }
    stone = _black_stone;
    for(auto pos : _black_stones_positons)
    {
        stone.setPosition((pos.second + .5F) * _cell_pixel_w , (pos.first + .5F) * _cell_pixel_h);
        target.draw(stone);
    }
}

sf::CircleShape GraphicalBoard::getWhiteStoneShape() const {
    return _white_stone;
}
sf::CircleShape GraphicalBoard::getBlackStoneShape() const {
    return _black_stone;
}
void GraphicalBoard::clean()
{
    _white_stones_positons.clear();
    _black_stones_positons.clear();
}