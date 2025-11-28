#include "NewBJ/jaco_game.h"
#include "NewBJ/jaco_player.h"
#include <algorithm>
#include <iostream>

namespace {

  /**
   * @brief Helper to stringify bet results.
   */
  const char* ResultToString(ITable::RoundEndInfo::BetResult result) {
    switch (result) {
      case ITable::RoundEndInfo::BetResult::Win:
        return "Win";
      case ITable::RoundEndInfo::BetResult::Lose:
        return "Lose";
      case ITable::RoundEndInfo::BetResult::Tie:
        return "Tie";
      default:
        return "Unknown";
    }
  }

}  // namespace

jaco_game::jaco_game(const jaco_rules& rules, std::vector<jaco_player>& players)
    : rules_(rules), players_(players), table_(rules_, players_) {}

/**
 * @brief Runs a simplified automatic game round using jaco_table and player decisions.
 */
void jaco_game::PlayGame() {
  table_.StartRound();

  // Place a minimum bet for each player if possible.
  for (int player_index = 0; player_index < static_cast<int>(players_.size());
       ++player_index) {
    const int player_money = table_.GetPlayerMoney(player_index);
    const int bet = std::min(rules_.MinimumInitialBet(), player_money);
    if (bet <= 0 ||
        table_.PlayInitialBet(player_index, bet) != ITable::Result::Ok) {
      std::cout << "Player " << player_index
                << " cannot place an initial bet.\n";
      continue;
    }
  }

  // Offer insurance if dealer shows an Ace.
  if (table_.GetDealerCard().value_ == ITable::Value::ACE) {
    for (int player_index = 0;
         player_index < static_cast<int>(players_.size()); ++player_index) {
      auto& player = players_.at(player_index);
      if (player.DecideUseSafe(table_, player_index)) {
        table_.PlaySafeBet(player_index);
      }
    }
  }

  // Auto-play each player's hands: hit until soft threshold 17.
  for (int player_index = 0; player_index < static_cast<int>(players_.size());
       ++player_index) {
    auto& player = players_.at(player_index);
    const int hand_count = table_.GetNumberOfHands(player_index);
    for (int hand = 0; hand < hand_count; ++hand) {
      while (true) {
        const auto action =
            player.DecidePlayerAction(table_, player_index, hand);
        if (table_.ApplyPlayerAction(player_index, hand, action) !=
            ITable::Result::Ok) {
          break;
        }
        // Stop if standing or busted.
        const int score = player.HandScore(hand);
        if (action == ITable::Action::Stand ||
            score > rules_.GetWinPoint()) {
          break;
        }
      }
      // Stand if done with hits
      table_.ApplyPlayerAction(player_index, hand, ITable::Action::Stand);
    }
  }

  const auto info = table_.FinishRound();
  std::cout << "Round finished. Dealer delta: " << info.croupier_money_delta
            << "\n";
  /**
   * @todo Show dealer hand cards
   */
  for (size_t i = 0; i < info.player_money_delta.size(); ++i) {
    // Print player money changes
    std::cout << "\nPlayer " << i << " money change: "
              << info.player_money_delta[i] << "\n";
    // Print hand cards
    players_[i].ShowHand();
    std::cout << "\n";
    if (i < info.winners.size()) {
      for (size_t hand = 0; hand < info.winners[i].size(); ++hand) {
        std::cout << "  Hand " << hand << ": "
                  << ResultToString(info.winners[i][hand]) << "\n";
      }
    }
  }
}
