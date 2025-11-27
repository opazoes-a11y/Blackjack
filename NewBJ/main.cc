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
  // Clear leftover newline from the game mode prompt before using getline.
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  while (true) {
    game.PlayGame();

    std::cout << "\nPlay another round? (y/n): ";
    std::string ans;
    std::getline(std::cin, ans);
    if (ans.empty() ||
        (ans[0] != 'y' && ans[0] != 'Y' && ans[0] != 's' && ans[0] != 'S')) {
        break;
    }
  }
  return 0;
}
