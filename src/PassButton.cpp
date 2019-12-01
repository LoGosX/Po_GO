#include "PassButton.h"
#include "Engine.h"

PassButton::PassButton(Engine* e) : _engine(e) {}

void PassButton::onClick() {
    _engine->passTurn();
}