#pragma once
#ifndef JACO_GAME_H
#define JACO_GAME_H
#include "Interface/igame.h"

class jaco_game : public IGame {
public:
    void PlayGame() override;
};

#endif // JACO_GAME_H
