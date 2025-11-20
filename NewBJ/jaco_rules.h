#pragma once
#ifndef JACO_RULES_H
#define JACO_RULES_H
#include <iostream>
#include "Interface/irules.h"

/**
 * @class jaco_rules
 * @brief Implements customizable Blackjack rule sets based on selected game mode.
 *
 * The class extends BaseRules and overrides several rule-related methods
 * depending on the game mode chosen by the user (Classic, Round, Extreme).
 */
class jaco_rules : public BaseRules{
public:
    /**
     * @name Rule constants
     * @brief Default configuration values for the Blackjack game.
     *
     * These constants define the base numerical rules for the game,
     * including money settings, deck configuration, and dealer behavior.
     */
    ///@{
    static constexpr int kPlayerStartMoney   = 4000;    ///< Starting money for each player
    static constexpr int kInitialDealerMoney = 100000;  ///< Starting money for the dealer
    static constexpr int kMinimunInitialBet  = 100;     ///< Minimum allowed initial bet
    static constexpr int kMaximumInitialBet  = 10000;   ///< Maximum allowed initial bet
    static constexpr int kDealerStop         = 17;      ///< Score at which the dealer stops dealing cards
    static constexpr int kInitialCards       = 2;       ///< Number of cards dealt initially to each player
    ///@}

    /**
     * @enum GameType
     * @brief Defines the different game rule modes available.
     *
     * Each mode modifies core Blackjack behaviors such as the
     * winning threshold or number of decks used.
     */
    enum class GameType {
        CLASSIC, ///< Classic Blackjack with winning score at 21 with 1 deck.
        ROUND,   ///< Variat with Blackjack winning score at 20 with 1 deck.
        EXTREME  ///< Variant with 2 decks and winning score at 25.
    };

    jaco_rules(){
        GameRules = GetGameMode();
    }

    /**
     * @brief Asks the user to select a game mode.
     *
     * This function prints a menu to the console and returns the
     * selected game mode. The caller is responsible for storing
     * the result in @ref GameRules.
     *
     * @return GameType The selected game mode.
     */
    GameType GetGameMode();

    /**
     * @brief Gets the winning point threshold.
     * @return int The score needed to win (default: 21)
     */
    int GetWinPoint() const override{
        switch(GameRules){
            case GameType::CLASSIC:
                return 21;
            case GameType::ROUND:
                return 20;
            case GameType::EXTREME:
                return 25;
        }
        return 21;
    }

    /**
     * @brief Gets the number of card decks used in the game.
     * @return int Number of decks (default: 1)
     */
    int NumberOfDecks() const override{
        switch(GameRules){
            case GameType::CLASSIC:
                return 1;
            case GameType::ROUND:
                return 1;
                break;
            case GameType::EXTREME:
                return 2;
        }
        return 1;
    }

    /**
     * @brief Gets the number of cards dealt to each player at the start.
     * @return int Number of initial cards (default: 2)
     */
    int InitialCards() const override{ return kInitialCards; }

    /**
     * @brief Gets the initial amount of money for each player.
     * @return int The starting money amount for players
     */
    int InitialPlayerMoney() const override{ return kPlayerStartMoney; }

    /**
     * @brief Gets the initial amount of money for the dealer.
     * @return int The starting money amount for the dealer
     */
    int InitialDealerMoney() const override{ return kInitialDealerMoney; }

    /**
     * @brief Gets the minimum initial bet.
     * @return int The minimum initial bet amount
     */
    int MinimumInitialBet() const override{ return kMinimunInitialBet; }

    /**
     * @brief Gets the maximum initial bet.
     * @return int The maximum initial bet amount
     */
    int MaximumInitialBet() const override{ return kMaximumInitialBet; }

    /**
     * @brief Gets the dealer's stop threshold.
     * @return int The score at which the dealer must stop drawing cards (default: 17)
     */
    int DealerStop() const override{ return kDealerStop; }

    ~jaco_rules() = default; 

private:
    /**
     * @brief Stores the active game mode selected by the user.
     *
     * This value determines the behavior of rule-dependent functions
     * such as @ref GetWinPoint() and @ref NumberOfDecks().
     */
    GameType GameRules;
};


#endif // JACO_RULES_H