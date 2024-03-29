#pragma once

#include "OnHoverButton.h"

class Engine;

class RestartButton : public OnHoverButton {

    Engine* _engine;

public:
    RestartButton(Engine*);

    /**
     * @brief Restarts game on click
     * 
     */
    void onClick() override;
};