#pragma once

#include "OnHoverButton.h"

class Engine;

class GoBackButton : public OnHoverButton {

    Engine* _engine;

public:
    GoBackButton(Engine*);

    /**
     * @brief Goes back oe turn
     * 
     */
    void onClick() override;
};