#include "NewBJ/jaco_game.h"
#include "NewBJ/jaco_player.h"
#include <iostream>
#include <string>

/**
 * @brief Entry point for the NewBJ Blackjack simulation.
 *
 * Prompts the user for game mode via jaco_rules, plays a round using
 * the auto-player logic, and optionally repeats while the user agrees.
 */
int main() {
  bool playing = true;
  while (playing) {
    jaco_game game;
    game.PlayGame();

    std::cout << "\nPlay another round? (y/n): ";
    std::string ans;
    std::getline(std::cin, ans);
    if (ans.empty() ||
        (ans[0] != 'y' && ans[0] != 'Y' && ans[0] != 's' && ans[0] != 'S')) {
        playing = false;
    }
  }
  return 0;
}
