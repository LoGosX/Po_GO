#pragma once
#include <iostream>

#include "SFML/Graphics.hpp"
#include "RenderSystem.h"
#include "Engine.h"




RenderSystem::RenderSystem(Engine* engine, int window_width, int window_height, const char* window_title) : _engine(engine), _window_width(window_width), _window_height(window_height), _window_title(window_title)
{
    _window.reset(new sf::RenderWindow(sf::VideoMode(window_width, window_height), window_title));
	_gb.reset(new GraphicalBoard(5, 400, 400, 10, &_textures_manager));
	initSprites();
}


RenderSystem::~RenderSystem()
{
}


bool RenderSystem::isWindowOpen() const
{
	return _window->isOpen();
}

bool RenderSystem::display()
{
	_window->display();
	return true;
}

bool RenderSystem::clear()
{
	_window->clear(sf::Color::White);
	return true;
}

void RenderSystem::initGraphicalBoard(int board_size, int board_pixel_w, int board_pixel_h)
{
	_gb.reset(new GraphicalBoard(board_size, board_pixel_w, board_pixel_h, 10, &_textures_manager));
}


bool RenderSystem::handleInput()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_window->close();
            return false;
		}
		
		// catch the resize events
		if (event.type == sf::Event::Resized)
		{
			//TODO: update the view to the new size of the window
		}

		if (event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
			{
				_window->close();
				return false;
			}
        }
			
		if (event.type == sf::Event::MouseMoved)
		{
			_mouse_moved = true;
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				_mouse_down = true;
				_last_mouse_local_position = _current_mouse_local_position = sf::Mouse::getPosition(*_window);
				auto r = _gb->canPlaceStone(_current_mouse_local_position.x, _current_mouse_local_position.y);
				bool white = _engine->getCurrentPlayer();
				if(r.first)
					_engine->tryPlaceStone(r.second.first, r.second.second);
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				_mouse_down = false;
		}
	}

	_mouse_moved = false;
	return true;
}



bool RenderSystem::draw()
{
	_gb->clean();
	for(auto [r, c] : _engine->getWhiteStonesPositions())
		_gb->placeStone(r, c, true);
	for(auto [r, c] : _engine->getBlackStonesPositions())
		_gb->placeStone(r, c, false);
	_window->draw(*_gb);
	return true;
}


void RenderSystem::initSprites()
{
	std::vector<std::vector<std::string>> to_load = {
        {"black_stone", "../assets/black_stone.PNG"},
        {"white_stone", "../assets/white_stone.PNG"},
        {"board5x5", "../assets/board5x5.PNG"},
        {"board9x9", "../assets/board5x5.PNG"},
        {"board13x13", "../assets/board13x13.PNG"},
        {"board19x19", "../assets/board19x19.PNG"}
    };
    for(auto& x : to_load)
    {
        sf::Texture text;
        text.loadFromFile(x[1]);
		sf::Sprite s;
		s.setTexture(text);
        _textures_manager.addAsset(x[0], std::move(text));
    }
	sf::Font font;
	font.loadFromFile("arial.tff");
	_font_manager.addAsset(_font_name, std::move(font));

}