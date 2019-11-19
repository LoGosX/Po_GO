#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

template<typename T>
class AssetManager;

class GraphicalBoard : public sf::Drawable
{
    std::vector<std::pair<int, int>> _white_stones_positons;
    std::vector<std::pair<int, int>> _black_stones_positons;

    float _board_size;
    float _board_position_x {0};
    float _board_position_y {0};
    float _pixel_w;
    float _pixel_h;
    float _cell_pixel_w;
    float _cell_pixel_h;
    float _stone_radius;
    const char* _white_stone_key {"white_stone"};
    const char* _black_stone_key {"black_stone"};
    const char* _board5x5_key {"board5x5"};
    const char* _board9x9_key {"board9x9"};
    AssetManager<sf::Texture>* _textures_manager;

    void _drawBoard(sf::RenderTarget& target) const;
    void _drawStones(sf::RenderTarget& target) const;
public:

    /**
     * @brief Construct a new Graphical Board object
     * 
     * @param board_size Size of the game board (created board has size x size positions to put stones at)
     * @param board_pixel_width What should be the pixel width of the board
     * @param board_pixel_height What should be the pixel height of the board
     * @param stone_radius What the stone_pixel_radius should be
     * @param sprites AssetManager containing sprites
     */
    GraphicalBoard(float board_size, float board_pixel_width, float board_pixel_height, float stone_radius, AssetManager<sf::Texture>* textures);
    
    
    /**
     * @brief Tries to place a stone at the specified location of the mouse
     * 
     * @param mouse_x Mouse's x coordinate in window's coordinates
     * @param mouse_y Mouse's y coordinate in window's coordinates
     * @return std::pair<bool, std::pair<int,int>> First element of the pair tells us if the move was correct (mouse within the board) and second element is a pair of (row, column) that stone could be placed on
     */
    std::pair<bool, std::pair<int,int>> canPlaceStone(float mouse_x, float mouse_y);

    /**
     * @brief Place stone on the board
     * 
     * @param row Which row
     * @param col Which column
     * @param white_stone Which stone (black (false) or white (true))
     */
    void placeStone(int row, int col, bool white_stone);

    /**
     * @brief Draws board and stones
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * @brief Deletes all pieces from the board
     * 
     */
    void clean();
};