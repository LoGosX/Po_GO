#include "RestartButton.h"
#include "Engine.h"
RestartButton::RestartButton(Engine* engine) : _engine(engine) {}

void RestartButton::onClick() {
    _engine->restart();
}