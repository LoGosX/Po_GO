#pragma once

#include "Button.h"

class Engine;

class OnHoverButton : public Button {

    Engine* _engine;

public:
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