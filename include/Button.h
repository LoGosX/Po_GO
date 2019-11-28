#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button : public sf::Drawable {

    std::function<void()> _on_click;
    std::string _display_text;
    sf::Font* _font {nullptr};
    sf::RectangleShape _shape;
    sf::Text _text;
public:
    Button();

    /**
     * @brief Set the font of the text
     * 
     * @param font
     */
    void setFont(sf::Font* font);
    /**
     * @brief Set the text to display
     * 
     * @param text 
     */
    void setDisplayText(std::string text);
    /**
     * @brief Sets the size of the button. The text has 10% margin in every direction
     * 
     * @param w width of the button
     * @param h height of the button
     */
    void setSize(float w, float h);

    /**
     * @brief Sets the outline thicnkess of the button
     * 
     * @param t thickness
     */
    void setOutlineThickness(float t);
    
    /**
     * @brief Sets the color of the button
     * 
     * @param c sf::Color
     */
    void setFillColor(sf::Color c);

    /**
     * @brief Sets the color of button's outline
     * 
     * @param c sf::Color
     */
    void setOutlineColor(sf::Color c);


    template<typename T>
    /**
     * @brief Defines what should happen on button click
     * 
     * @param on_click A callable object
     */
    void setOnClick(T&& on_clink);

    /**
     * @brief Sets the position of the button
     * 
     * @param position New position of the button
     */
    void setPosition(sf::Vector2f position); 

    /**
     * @brief Triggers a callable that was assigned to this button
     * 
     */
    void click();

    /**
     * @brief Checks if the point lies inside this button
     * 
     * @param point Point in 2D space
     * @return true Point is inside button
     * @return false Point is not inside button
     */
    bool pointInside(sf::Vector2f point) const;

    /**
     * @brief Draws button's shape and button's text on given RenderTarget
     * 
     */
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

template<typename T>
void Button::setOnClick(T&& t) {  _on_click = std::forward<T>(t); }
