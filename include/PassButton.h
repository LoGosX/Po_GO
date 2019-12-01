#pragma once
#include "OnHoverButton.h"

class Engine;

class PassButton : public OnHoverButton {
    Engine* _engine;
public:
    PassButton(Engine*);
    void onClick() override;
};