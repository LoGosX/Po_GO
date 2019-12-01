#pragma once
#include <iostream>

#include "SFML/Graphics.hpp"
#include "RenderSystem.h"
#include "Engine.h"
#include "Button.h"
#include "RestartButton.h"
#include "GoBackButton.h"



RenderSystem::RenderSystem(Engine* engine, int window_width, int window_height, const char* window_title) : _engine(engine), _window_width(window_width), _window_height(window_height), _window_title(window_title)
{
    _window.reset(new sf::RenderWindow(sf::VideoMode(window_width, window_height), window_title));
	_gb.reset(new GraphicalBoard(5, 400, 400, 10, &_textures_manager));
	initSprites();
	auto _current_player_button = new Button;
	_current_player_button->setPosition({0.75F * window_width, 0.1F * window_height});
	_current_player_button->setDisplayText("Current player: ");
	_current_player_button->setTextColor(sf::Color::Black);
	_current_player_button->setFillColor(sf::Color(0,0,0,0));
	_current_player_button->setFont(_font_manager.getAsset(_font_name));
	_buttons.emplace_back(_current_player_button);
	_buttons_hovered.push_back(false);

	auto _restart_button = new RestartButton(_engine);
	_restart_button->setPosition({0.75F * window_width, 0.25F * window_height});
	_restart_button->setDisplayText("\n        Restart");
	_restart_button->setTextColor(sf::Color::Black);
	_restart_button->setFillColor(sf::Color::Red);
	_restart_button->setFont(_font_manager.getAsset(_font_name));
	_buttons.emplace_back(_restart_button);
	_buttons_hovered.push_back(false);

	auto _go_back_button = new GoBackButton(_engine);
	_go_back_button->setPosition({0.75F * window_width, 0.4F * window_height});
	_go_back_button->setDisplayText("\n      Undo move");
	_go_back_button->setTextColor(sf::Color::Black);
	_go_back_button->setFillColor(sf::Color::Magenta);
	_go_back_button->setFont(_font_manager.getAsset(_font_name));
	_buttons.emplace_back(_go_back_button);
	_buttons_hovered.push_back(false);

	auto _black_score_btn = new Button;
	_black_score_btn->setPosition({0.75F * window_width, 0.6F * window_height});
	_black_score_btn->setDisplayText("     Black's score: ");
	_black_score_btn->setTextColor(sf::Color::Black);
	_black_score_btn->setFillColor(sf::Color(0,0,0,0));
	_black_score_btn->setFont(_font_manager.getAsset(_font_name));
	_buttons.emplace_back(_black_score_btn);
	auto _white_score_btn = new Button;
	_white_score_btn->setPosition({0.75F * window_width, 0.7F * window_height});
	_white_score_btn->setDisplayText("     White's score: ");
	_white_score_btn->setTextColor(sf::Color::Black);
	_white_score_btn->setFillColor(sf::Color(0,0,0,0));
	_white_score_btn->setFont(_font_manager.getAsset(_font_name));
	_buttons.emplace_back(_white_score_btn);
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
	_window->clear(sf::Color::Cyan);
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
				_last_mouse_local_position = _current_mouse_local_position = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
				auto r = _gb->canPlaceStone(_current_mouse_local_position.x, _current_mouse_local_position.y);
				bool white = _engine->getCurrentPlayer();
				if(r.first)
					_engine->tryPlaceStone(r.second.first, r.second.second);
				for(auto& b : _buttons)
				{
					if(b->pointInside(sf::Vector2f(_current_mouse_local_position)))
						b->onClick();
				}
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
				_mouse_down = false;
		}

		auto mp = _window->mapPixelToCoords(sf::Mouse::getPosition(*_window));
		for(int i = 0; i < _buttons.size(); i++)
		{
			if(_buttons[i]->pointInside(sf::Vector2f(mp)))
			{
				if(!_buttons_hovered[i])
				{
					_buttons[i]->onHover();
					_buttons_hovered[i] = true;
				}
			}else{
				if(_buttons_hovered[i])
					_buttons[i]->onHoverLeave();
				_buttons_hovered[i] = false;
			}
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


	_buttons[_buttons.size() - 2]->setDisplayText("Black's score: " + std::to_string(_engine->getScores().first));
	_buttons.back()->setDisplayText("White's score: " + std::to_string(_engine->getScores().second));
	for(auto& b : _buttons)
		_window->draw(*b);

	auto cp = (_engine->getCurrentPlayer() == 0 ? _gb->getBlackStoneShape() : _gb->getWhiteStoneShape());
	cp.setRadius(25);
	cp.setPosition(_buttons[0]->getPosition() + sf::Vector2f(225, 20));
	_window->draw(cp);
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
	font.loadFromFile("../assets/arial.ttf");
	_font_manager.addAsset(_font_name, std::move(font));
}