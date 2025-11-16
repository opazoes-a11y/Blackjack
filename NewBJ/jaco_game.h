#pragma once
#ifndef JACO_GAME_H
#define JACO_GAME_H
#include "Interface/igame.h"

class JGame : public IGame {
    void PlayGame() override;
};

#endif // JACO_GAME_H