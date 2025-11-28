#include "NewBJ/jaco_game.h"
#include "NewBJ/jaco_player.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>

/**
 * @brief Entry point for the NewBJ Blackjack simulation.
 *
 * Prompts the user for game mode via jaco_rules, plays a round using
 * the auto-player logic, and optionally repeats while the user agrees.
 */
int main() {
  jaco_rules rules;
  std::vector<jaco_player> players;
  players.reserve(4);
  for (int i = 0; i < 4; ++i) {
    players.emplace_back(i, rules);
  }

  jaco_game game(rules, players);
  
  while (!game.IsGameOver()) {
    game.PlayGame();
  }
  return 0;
}
