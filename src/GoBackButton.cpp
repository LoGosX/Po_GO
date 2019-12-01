#include "GoBackButton.h"
#include "Engine.h"

GoBackButton::GoBackButton(Engine* en) : _engine(en) {}

void GoBackButton::onClick() {
    _engine->goBackOneMove();
}