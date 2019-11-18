#pragma once
#include <iostream>

#include "SFML/Graphics.hpp"
#include "RenderSystem.h"
#include "Engine.h"




RenderSystem::RenderSystem(Engine* engine, int window_width, int window_height, const char* window_title) : _engine(engine), window_width(window_width), window_height(window_height), window_title(window_title)
{
    _window = std::unique_ptr<sf::RenderWindow>();
    _window->create(sf::VideoMode(window_width, window_height), window_title);
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
	_window->clear();
	return true;
}


bool RenderSystem::handleInput()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			_window->close();
            return;
		}
		
		// catch the resize events
		if (event.type == sf::Event::Resized)
		{
			//TODO: update the view to the new size of the window
		}

		if (event.type == sf::Event::KeyPressed)
        {
            
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
		_sprites_manager.addAsset(x[0], std::move(s));
    }
}