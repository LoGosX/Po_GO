#pragma once
#include <memory>
#include "SFML/Graphics.hpp"
#include "AssetsManager.h"
#include "GraphicalBoard.h"

class Engine;

class RenderSystem
{
	std::unique_ptr<GraphicalBoard> _gb;
	std::unique_ptr<sf::RenderWindow> _window;
	Engine* _engine;
  	AssetManager<sf::Texture> _textures_manager;

	bool _mouse_down{ false };
	bool _mouse_moved{ false };
	bool window_open{ false };
	sf::Vector2i _last_mouse_local_position, _current_mouse_local_position;
	int _window_width;
	int _window_height;
	const char* _window_title;

	void initSprites();
public:
	RenderSystem(Engine* engine, int window_width, int window_height, const char* window_title);
	~RenderSystem();

	void initGraphicalBoard(int board_size, int board_pixel_w, int board_pixel_h);

	bool isWindowOpen() const;
	bool draw();
	bool display();
	bool clear();
	bool handleInput();
};