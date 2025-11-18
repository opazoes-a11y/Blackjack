#pragma once
#ifndef JACO_PLAYER_H
#define JACO_PLAYER_H
#include "Interface/iplayer.h"
#include "NewBJ/jaco_rules.h"
#include "NewBJ/cards.h"
/**
 * @class Jaco_player
 * @brief Represents a Blackjack player with hand management and betting logic.
 *
 * This class implements the IPlayer interface and stores all the state
 * associated with a single player: money, current bet, and their hands.
 * It also provides helper methods for hand scoring and basic Blackjack
 * conditions such as bust and Blackjack detection.
 */
class jaco_player : public IPlayer {
    public:
        /**
         * @brief Constructs a player with a given index and initial money.
         *
         * Initializes the player identifier, starting money using
         * @param jaco_rules::kPlayerStartMoney, and sets the current bet to zero.
         * Uses @param next_player_index as static int to increment value
         * when a player is created.
         *
         * @param player_index Index of the player at the table.
         */
        jaco_player(int player_index, 
                    const jaco_rules& rules) 
            : player_index(next_player_index++), 
            player_money(jaco_rules::kPlayerStartMoney), 
            current_bet(0),
            rules_(rules) {}
        
        /**
         * @brief Shared player index (used as an identifier counter).
         *
         * This static member can be used to generate or track the current
         * player index across multiple instances.
         */
        static int next_player_index;

        /**
         * @brief Unique identifier for the player at the table.
         *
         * Assigned automatically using @ref next_player_index during construction.
         */
        int player_index;

        /**
         * @brief Current amount of money the player owns.
         */
        int player_money;

        /**
         * @brief Amount of money the player has currently bet in the active round.
         */
        int current_bet;

        /**
         * @brief Checks if the player still has any money left.
         *
         * @return true if @ref player_money is greater than zero, false otherwise.
         */
        bool HasMoney() const{ return player_money > 0; }

        /**
         * @brief Checks if the player currently has split hands.
         *
         * A split is considered to have occurred when the player holds more than
         * one active hand in @ref PlayerHand.
         *
         * @return true if the player has more than one hand, false otherwise.
         */
        bool IsHandSplitted() const { return PlayerHand.size() > 1; }

        /**
         * @brief Adds a card to the active hand of the player from the deck.
         *
         * This function determines which hand receives the card (considering split
         * scenarios) and pushes the card into that hand.
         *
         * @param card The card to be added.
         */
        void AddCard(const Cards::Card &card);

        /**
         * @brief Prints all player hands and their cards to standard output.
         *
         * Primarily used for console-based visualization and debugging.
         */
        void ShowHand() const;

        /**
         * @brief Initializes the player's hand(s) at the start of the round.
         *
         * Draws the initial number of cards from the provided deck and sets up
         * the player's first hand.
         *
         * @param deck The deck from which cards are drawn.
         */
        void InitHand(Cards& deck);

        /**
         * @struct Hand
         * @brief Represents a single Blackjack hand held by the player.
         *
         * Each hand contains its own vector of cards and an index. When the
         * player splits, multiple Hand instances are stored in @ref PlayerHand.
         */
        typedef struct {
            std::vector<Cards::Card> cards;
            int hand_index;
        } Hand;

        /**
         * @brief Collection of all active hands owned by the player.
         *
         * Normally contains one hand, but may contain multiple if the
         * player performs a split.
         */
        std::vector<Hand> PlayerHand;

        /**
         * @brief Computes the total score of the player's current hand.
         *
         * The score calculation follows Blackjack rules, including proper
         * handling of Aces (1 or 11 depending on optimal value).
         *
         * @return int The computed hand score.
         */
        int HandScore() const;

        /**
         * @brief Determines if the player should draw another card.
         *
         * Default behavior: draw while the score is below 17.
         *
         * @return true if another card should be drawn, otherwise false.
         */
        bool NeedCard() const{ return HandScore() < 17; } 

        /**
         * @brief Checks whether the player has exceeded 21.
         *
         * @return true if the hand score is greater than 21, false otherwise.
         */
        bool isBust() const { return HandScore() > 21; }

        /**
         * @brief Checks whether the player has a natural Blackjack.
         *
         * A natural Blackjack occurs when the player has exactly two cards
         * in a single hand and the total score equals to the game mode definition
         * of blackjack (Classic=21, Round=20 and Extreme=25).
         *
         * @return true if the player has Blackjack, false otherwise.
         */
        bool isBlackjack() const { 
            return PlayerHand.size() == 1 && 
                                    PlayerHand[0].cards.size() == 2 && 
                                    HandScore() == rules_.GetWinPoint(); 
        }
        
        /**
         * @brief Decides the action to take for a specific hand.
         *
         * This function implements the decision logic for a given player and hand
         * based on the current table state. It returns one of the allowed actions
         * such as Stand, Hit, Double, or Split.
         *
         * @param table Reference to the game table containing the current game state.
         * @param player_index Index of the player making the decision.
         * @param hand_index Index of the hand to decide the action for.
         * @return ITable::Action The chosen action for this hand.
         */
        virtual ITable::Action DecidePlayerAction(const ITable& table, int player_index, int hand_index) override;
        
        /**
         * @brief Decides the initial bet amount for a new round.
         *
         * The decision may depend on the player's current money, table state,
         * or any strategy implemented in this method.
         *
         * @param table Reference to the game table containing the current game state.
         * @param player_index Index of the player placing the bet.
         * @return int The amount of the initial bet.
         */
        virtual int DecideInitialBet(const ITable& table, int player_index) override;
        
        /**
         * @brief Decides whether to use the safe/insurance option.
         *
         * This method is called when the dealer shows an Ace and the rules
         * allow an insurance (safe) bet.
         *
         * @param table Reference to the game table containing the current game state.
         * @param player_index Index of the player making the decision.
         * @return true if the player chooses to use the safe option, false otherwise.
         */
        virtual bool DecideUseSafe(const ITable& table, int player_index) override;

        virtual ~jaco_player() = default;

    private:

        /**
         * @brief Default destructor.
         */
        const jaco_rules& rules_;
};

#endif // JACO_PLAYER_H