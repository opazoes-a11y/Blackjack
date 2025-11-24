#pragma once
#ifndef JACO_GAME_H
#define JACO_GAME_H
#include "Interface/igame.h"
#include "NewBJ/jaco_table.h"
#include <vector>

class jaco_game : public IGame {
public:
    jaco_game(const jaco_rules& rules, std::vector<jaco_player>& players);
    void PlayGame() override;

private:
    const jaco_rules& rules_;
    std::vector<jaco_player>& players_;
    jaco_table table_;
};

#endif // JACO_GAME_H
