#pragma once

#include "Button.h"

class Engine;

class RestartButton : public Button {

    Engine* _engine;

public:
    RestartButton(Engine*);

    /**
     * @brief Restarts game on click
     * 
     */
    void onClick() override;

    /**
     * @brief Makes button a little transparent on hover
     * 
     */
    void onHover() override;

    /**
     * @brief returns button to default opacity
     * 
     */
    void onHoverLeave() override;

};