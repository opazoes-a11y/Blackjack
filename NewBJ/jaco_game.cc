#include "NewBJ/jaco_game.h"
#include "NewBJ/jaco_table.h"
#include "NewBJ/jaco_player.h"
#include <algorithm>
#include <iostream>

namespace {

  /**
   * @brief Computes Blackjack score for an interface hand with ace softening.
   * @param hand Hand in ITable representation.
   * @param rules Rule set providing win point.
   * @return Hand total value.
   */
  int HandScore(const ITable::Hand& hand, const jaco_rules& rules) {
    int score = 0;
    int aces = 0;
    for (const auto& card : hand) {
      switch (card.value_) {
        case ITable::Value::ACE:
          score += 11;
          ++aces;
          break;
        case ITable::Value::TWO:
          score += 2;
          break;
        case ITable::Value::THREE:
          score += 3;
          break;
        case ITable::Value::FOUR:
          score += 4;
          break;
        case ITable::Value::FIVE:
          score += 5;
          break;
        case ITable::Value::SIX:
          score += 6;
          break;
        case ITable::Value::SEVEN:
          score += 7;
          break;
        case ITable::Value::EIGHT:
          score += 8;
          break;
        case ITable::Value::NINE:
          score += 9;
          break;
        case ITable::Value::TEN:
        case ITable::Value::JACK:
        case ITable::Value::QUEEN:
        case ITable::Value::KING:
          score += 10;
          break;
        default:
          break;
      }
    }
    while (score > rules.GetWinPoint() && aces > 0) {
      score -= 10;
      --aces;
    }
    return score;
  }

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

/**
 * @brief Convert interface hands into a jaco_player structure for decisions.
 * @param table Source table to read state from.
 * @param player_index Player index to sync.
 * @param decider Player instance to populate.
 */
static void SyncDecisionPlayer(const ITable& table,
                               int player_index,
                               jaco_player& decider) {
  decider.PlayerHand.clear();
  const int hand_count = table.GetNumberOfHands(player_index);
  for (int h = 0; h < hand_count; ++h) {
    jaco_player::Hand hand;
    hand.hand_index = h;
    const auto t_hand = table.GetHand(player_index, h);
    for (const auto& card : t_hand) {
      Cards::Card c{};
      c.fig = static_cast<Cards::Value>(static_cast<int>(card.value_));
      switch (card.suit_) {
        case ITable::Suit::HEARTS: c.suit = Cards::Suit::Hearts; break;
        case ITable::Suit::CLUBS: c.suit = Cards::Suit::Clubs; break;
        case ITable::Suit::SPADES: c.suit = Cards::Suit::Spades; break;
        case ITable::Suit::DIAMONDS: c.suit = Cards::Suit::Diamons; break;
        default: break;
      }
      hand.cards.push_back(c);
    }
    decider.PlayerHand.push_back(hand);
  }
}

/**
 * @brief Runs a simplified automatic game round using jaco_table and player decisions.
 */
void jaco_game::PlayGame() {
  jaco_rules rules;
  jaco_table table(rules);
  jaco_player decision_player(0, rules);
  const int player_index = 0;

  table.StartRound();

  // Place a minimum bet if possible.
  const int player_money = decision_player.player_money;
  const int bet = std::min(rules.MinimumInitialBet(), player_money);
  if (bet <= 0 ||
      table.PlayInitialBet(player_index, bet) != ITable::Result::Ok) {
    std::cout << "Player cannot place an initial bet.\n";
    return;
  }

  // Offer insurance if dealer shows an Ace.
  if (table.GetDealerCard().value_ == ITable::Value::ACE) {
    // Use player's decision logic to choose insurance.
    decision_player.player_money = table.GetPlayerMoney(player_index);
    if (decision_player.DecideUseSafe(table, player_index)) {
      table.PlaySafeBet(player_index);
    }
  }

  // Auto-play each hand: hit until soft threshold 17.
  for (int hand = 0; hand < table.GetNumberOfHands(player_index); ++hand) {
    while (true) {
      SyncDecisionPlayer(table, player_index, decision_player);
      decision_player.player_money = table.GetPlayerMoney(player_index);
      const auto action =
          decision_player.DecidePlayerAction(table, player_index, hand);
      if (table.ApplyPlayerAction(player_index, hand, action) !=
          ITable::Result::Ok) {
        break;
      }
      // Stop if standing or busted.
      const int score = HandScore(table.GetHand(player_index, hand), rules);
      if (action == ITable::Action::Stand || score > rules.GetWinPoint()) {
        break;
      }
    }
    // Explicitly stand once done with hits.
    table.ApplyPlayerAction(player_index, hand, ITable::Action::Stand);
  }

  const auto info = table.FinishRound();
  std::cout << "Round finished. Dealer delta: " << info.croupier_money_delta
            << "\n";
  if (!info.player_money_delta.empty()) {
    std::cout << "Player money change: " << info.player_money_delta[0] << "\n";
  }

  if (!info.winners.empty()) {
    for (size_t hand = 0; hand < info.winners[0].size(); ++hand) {
      std::cout << "Hand " << hand << ": "
                << ResultToString(info.winners[0][hand]) << "\n";
    }
  }
}
