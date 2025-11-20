#include "NewBJ/jaco_table.h"

/**
 * @brief Builds the table, initializes dealer money and reserves player slots.
 * @param rules Rule set controlling limits and thresholds.
 */
jaco_table::jaco_table(const jaco_rules& rules)
    : rules_(rules),
      deck_(),
      players_(),
      dealer_hand_(),
      dealer_money_(rules.InitialDealerMoney()),
      initial_bets_(),
      safe_bets_(),
      hands_bets_() {
  players_.reserve(ITable::kMaxPlayers);
}

/**
 * @brief Converts a card from internal deck format to interface format.
 * @param card Card in @ref Cards representation.
 * @return Mapped card compatible with ITable consumers.
 */
ITable::Card jaco_table::ConvertCard(const Cards::Card& card) const {
  ITable::Card converted{};
  converted.value_ = static_cast<ITable::Value>(static_cast<int>(card.fig));
  switch (card.suit) {
    case Cards::Suit::Clubs:
      converted.suit_ = ITable::Suit::CLUBS;
      break;
    case Cards::Suit::Diamons:
      converted.suit_ = ITable::Suit::DIAMONDS;
      break;
    case Cards::Suit::Hearts:
      converted.suit_ = ITable::Suit::HEARTS;
      break;
    case Cards::Suit::Spades:
      converted.suit_ = ITable::Suit::SPADES;
      break;
  }
  return converted;
}

/**
 * @brief Computes dealer hand score, adjusting aces to avoid bust if possible.
 * @return Total dealer score.
 */
int jaco_table::DealerHandScore() const {
  int score = 0;
  int aces = 0;
  for (const auto& card : dealer_hand_) {
    // Map interface values to blackjack totals.
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
  // Convert aces from 11 to 1 while busting.
  while (score > rules_.GetWinPoint() && aces > 0) {
    score -= 10;
    --aces;
  }
  return score;
}

/**
 * @brief Ensures internal storage exists for requested player index.
 * @param player_index Index to satisfy.
 */
void jaco_table::EnsurePlayer(int player_index) {
  while (static_cast<int>(players_.size()) <= player_index) {
    // Parallel vectors grow together to keep indices aligned.
    players_.emplace_back(static_cast<int>(players_.size()), rules_);
    initial_bets_.push_back(0);
    safe_bets_.push_back(0);
    hands_bets_.push_back({0});
  }
}

/**
 * @brief Expands bet vector to match current number of player hands.
 * @param player_index Player who may have split.
 */
void jaco_table::EnsureHandBets(int player_index) {
  if (player_index < 0 || player_index >= static_cast<int>(players_.size())) {
    return;
  }
  auto& bets = hands_bets_[player_index];
  const auto hand_count = players_[player_index].PlayerHand.size();
  if (bets.size() < hand_count) {
    // Propagate existing bet to new split hand or initialize to zero.
    bets.resize(hand_count, bets.empty() ? 0 : bets.front());
  }
}

/**
 * @brief Returns specified player hand mapped to interface cards.
 * @param player_index Player index.
 * @param hand_index Hand index.
 * @return Hand vector ready for observers.
 */
ITable::Hand jaco_table::GetHand(int player_index, int hand_index) const {
  if (player_index < 0 || player_index >= static_cast<int>(players_.size())) {
    return {};
  }
  const auto& player = players_[player_index];
  if (hand_index < 0 ||
      hand_index >= static_cast<int>(player.PlayerHand.size())) {
    return {};
  }
  ITable::Hand hand;
  for (const auto& card : player.PlayerHand[hand_index].cards) {
    hand.push_back(ConvertCard(card));
  }
  return hand;
}

/**
 * @brief Counts active hands for a player.
 * @param player_index Player index.
 * @return Number of hands or 0 on invalid index.
 */
int jaco_table::GetNumberOfHands(int player_index) const {
  if (player_index < 0 || player_index >= static_cast<int>(players_.size())) {
    return 0;
  }
  return static_cast<int>(players_[player_index].PlayerHand.size());
}

/**
 * @brief Retrieves wager assigned to a specific hand.
 * @param player_index Player index.
 * @param hand_index Hand index.
 * @return Current bet amount or 0 on error.
 */
int jaco_table::GetPlayerCurrentBet(int player_index,
                                    int hand_index) const {
  if (player_index < 0 || player_index >= static_cast<int>(players_.size())) {
    return 0;
  }
  if (hand_index < 0 ||
      hand_index >= static_cast<int>(hands_bets_[player_index].size())) {
    return 0;
  }
  return hands_bets_[player_index][hand_index];
}

/**
 * @brief Provides remaining money of a player.
 * @param player_index Player to query.
 * @return Available bankroll or 0 on invalid index.
 */
int jaco_table::GetPlayerMoney(int player_index) const {
  if (player_index < 0 || player_index >= static_cast<int>(players_.size())) {
    return 0;
  }
  return players_[player_index].player_money;
}

/**
 * @brief Returns initial wager placed by player.
 * @param player_index Player index.
 * @return Initial bet or 0 if not set/invalid index.
 */
int jaco_table::GetPlayerInitialBet(int player_index) const {
  if (player_index < 0 || player_index >= static_cast<int>(players_.size())) {
    return 0;
  }
  return initial_bets_[player_index];
}

/**
 * @brief Returns dealer's first card (face-up).
 */
ITable::Card jaco_table::GetDealerCard() const {
  if (dealer_hand_.empty()) {
    return ITable::Card{};
  }
  return dealer_hand_.front();
}

/**
 * @brief Gets current dealer money.
 */
int jaco_table::DealerMoney() const { return dealer_money_; }

/**
 * @brief Draws a card from deck and adds it to player hand.
 */
void jaco_table::DealCard(int player_index, int hand_index) {
  EnsurePlayer(player_index);
  auto& player = players_[player_index];
  if (hand_index < 0 ||
      hand_index >= static_cast<int>(player.PlayerHand.size())) {
    return;
  }
  player.AddCard(deck_.giveCard(), hand_index);
  EnsureHandBets(player_index);
}

/**
 * @brief Validates and records an initial bet, initializing hand if needed.
 * @param player_index Player placing the bet.
 * @param money Bet amount.
 * @return Ok if accepted, Illegal otherwise.
 */
ITable::Result jaco_table::PlayInitialBet(int player_index, int money) {
  EnsurePlayer(player_index);
  auto& player = players_[player_index];
  if (money < rules_.MinimumInitialBet() ||
      money > rules_.MaximumInitialBet() ||
      money > player.player_money) {
    return Result::Illegal;
  }

  player.player_money -= money;
  player.current_bet = money;
  initial_bets_[player_index] = money;
  hands_bets_[player_index].assign(1, money);
  safe_bets_[player_index] = 0;

  if (player.PlayerHand.empty()) {
    player.InitHand(deck_);
    EnsureHandBets(player_index);
  }

  return Result::Ok;
}

/**
 * @brief Places insurance bet equal to half initial bet when available.
 * @param player_index Target player.
 * @return Ok on success, Illegal if unavailable or lacks funds.
 */
ITable::Result jaco_table::PlaySafeBet(int player_index) {
  EnsurePlayer(player_index);
  auto& player = players_[player_index];
  const int base_bet = initial_bets_[player_index];
  const int safe_bet = base_bet / 2;
  if (safe_bet <= 0 || safe_bet > player.player_money) {
    return Result::Illegal;
  }
  player.player_money -= safe_bet;
  safe_bets_[player_index] = safe_bet;
  return Result::Ok;
}

/**
 * @brief Executes action requested by player on the given hand.
 * @param player_index Player performing action.
 * @param hand_index Hand to affect.
 * @param action Action to apply.
 * @return Ok if applied, Illegal if constraints violated.
 */
ITable::Result jaco_table::ApplyPlayerAction(int player_index, int hand_index,
                                             Action action) {
  EnsurePlayer(player_index);
  auto& player = players_[player_index];
  if (hand_index < 0 ||
      hand_index >= static_cast<int>(player.PlayerHand.size())) {
    return Result::Illegal;
  }

  EnsureHandBets(player_index);
  switch (action) {
    case Action::Stand:
      return Result::Ok;
    case Action::Hit:
      DealCard(player_index, hand_index);
      return Result::Ok;
    case Action::Double: {
      const int current_bet = hands_bets_[player_index][hand_index];
      if (current_bet <= 0 || player.player_money < current_bet) {
        return Result::Illegal;
      }
      // Double the stake and take exactly one extra card.
      player.player_money -= current_bet;
      hands_bets_[player_index][hand_index] += current_bet;
      DealCard(player_index, hand_index);
      return Result::Ok;
    }
    case Action::Split: {
      auto& hand = player.PlayerHand[hand_index];
      if (hand.cards.size() != 2 ||
          hand.cards[0].fig != hand.cards[1].fig) {
        return Result::Illegal;
      }
      const int current_bet = hands_bets_[player_index][hand_index];
      if (current_bet <= 0 || player.player_money < current_bet) {
        return Result::Illegal;
      }

      // Pay the duplicated bet for the new hand.
      player.player_money -= current_bet;

      // Move one card to the new hand and keep the other.
      jaco_player::Hand new_hand;
      new_hand.hand_index = static_cast<int>(player.PlayerHand.size());
      new_hand.cards.push_back(hand.cards.back());
      hand.cards.pop_back();

      player.PlayerHand.push_back(new_hand);
      hands_bets_[player_index].push_back(current_bet);

      DealCard(player_index, hand_index);
      DealCard(player_index, new_hand.hand_index);
      return Result::Ok;
    }
  }
  return Result::Illegal;
}

/**
 * @brief Prepares a new round resetting deck, dealer card and player state.
 */
void jaco_table::StartRound() {
  deck_ = Cards();
  deck_.shuffleCards();
  dealer_hand_.clear();
  dealer_hand_.push_back(ConvertCard(deck_.giveCard()));

  for (size_t i = 0; i < players_.size(); ++i) {
    players_[i].InitHand(deck_);
    initial_bets_[i] = 0;
    safe_bets_[i] = 0;
    hands_bets_[i].assign(1, 0);
    players_[i].current_bet = 0;
  }
}

/**
 * @brief Resolves dealer play, calculates payouts and resets table state.
 * @return RoundEndInfo summarizing results and money changes.
 */
ITable::RoundEndInfo jaco_table::FinishRound() {
  // Dealer plays their hand according to the rules
  while (DealerHandScore() < rules_.DealerStop()) {
    dealer_hand_.push_back(ConvertCard(deck_.giveCard()));
  }

  ITable::RoundEndInfo result;
  result.dealer_hand = dealer_hand_;
  result.winners.resize(players_.size());
  result.player_money_delta.assign(players_.size(), 0);
  result.croupier_money_delta = 0;

  const int dealer_score = DealerHandScore();
  const bool dealer_blackjack =
      dealer_hand_.size() == 2 && dealer_score == rules_.GetWinPoint();
  const bool dealer_bust = dealer_score > rules_.GetWinPoint();

  for (size_t i = 0; i < players_.size(); ++i) {
    EnsureHandBets(static_cast<int>(i));
    auto& player = players_[i];
    auto& bets = hands_bets_[i];
    result.winners[i].resize(player.PlayerHand.size(),
                             ITable::RoundEndInfo::BetResult::Tie);

    for (size_t h = 0; h < player.PlayerHand.size(); ++h) {
      const int bet = (h < bets.size()) ? bets[h] : 0;
      int payout = 0;
      auto hand_result = ITable::RoundEndInfo::BetResult::Tie;

      const int player_score = player.HandScore(static_cast<int>(h));
      const bool player_bust = player.isBust(static_cast<int>(h));
      const bool player_blackjack = player.isBlackjack(static_cast<int>(h));

      if (player_bust) {
        hand_result = ITable::RoundEndInfo::BetResult::Lose;
      } else if (dealer_blackjack) {
        if (player_blackjack) {
          payout = bet;
          hand_result = ITable::RoundEndInfo::BetResult::Tie;
        } else {
          hand_result = ITable::RoundEndInfo::BetResult::Lose;
        }
      } else if (dealer_bust) {
        // Dealer bust -> player wins 1:1.
        payout = bet * 2;
        hand_result = ITable::RoundEndInfo::BetResult::Win;
      } else if (player_score > dealer_score) {
        // Regular win (blackjack premium not modeled).
        payout = bet * 2;
        hand_result = ITable::RoundEndInfo::BetResult::Win;
      } else if (player_score < dealer_score) {
        hand_result = ITable::RoundEndInfo::BetResult::Lose;
      } else {
        payout = bet;
        hand_result = ITable::RoundEndInfo::BetResult::Tie;
      }

      player.player_money += payout;
      result.player_money_delta[i] += payout;
      result.croupier_money_delta += (bet - payout);
      result.winners[i][h] = hand_result;
    }

    // Resolve safe/insurance bet
    if (safe_bets_[i] > 0) {
      const int bet = safe_bets_[i];
      int payout = 0;
      if (dealer_blackjack) {
        // Insurance pays 2:1 plus returning stake (3x total back).
        payout = bet * 3;
      }
      player.player_money += payout;
      result.player_money_delta[i] += payout;
      result.croupier_money_delta += (bet - payout);
    }

    // Reset player state for next round
    player.PlayerHand.clear();
    player.current_bet = 0;
    initial_bets_[i] = 0;
    safe_bets_[i] = 0;
    bets.assign(1, 0);
  }

  dealer_money_ += result.croupier_money_delta;
  dealer_hand_.clear();

  return result;
}

