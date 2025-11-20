#pragma once
#ifndef JACO_TABLE_H
#define JACO_TABLE_H
#include "Interface/itable.h"
#include "NewBJ/jaco_player"

/**
 * @class jaco_table
 * @brief Concrete implementation of the ITable interface for a Blackjack game.
 *
 * This class manages the state of the Blackjack table, including player hands,
 * bets, dealer hand and money, and the flow of each round. It provides the
 * concrete behavior for all methods defined in the ITable interface:
 * dealing cards, starting and finishing rounds, and applying player actions.
 */
class jaco_table : public ITable {
    public:

    /**
     * @brief Gets a specific hand for a player.
     *
     * @param player_index Index of the player
     * @param hand_index Index of the hand
     * @return Hand The requested hand
     */
    Hand GetHand(int player_index, int hand_index) const override;

    /**
     * @brief Gets the current number of hands for a player.
     *
     * @param player_index Index of the player
     * @return int Number of hands the player currently has
     */
    int GetNumberOfHands(int player_index) const override;

    /**
     * @brief Gets the current total bet for a specific hand.
     *
     * @param player_index Index of the player
     * @param hand_index Index of the hand
     * @return int The current bet amount for this hand
     */
    int GetPlayerCurrentBet(int player_index,int hand_index) const override;

    /**
     * @brief Gets the remaining unbet money for a player.
     *
     * @param player_index Index of the player
     * @return int The player's remaining money not currently bet
     */
    int GetPlayerMoney(int player_index) const override;

    /**
     * @brief Gets the initial bet amount placed by a player.
     *
     * @param player_index Index of the player
     * @return int The money the player bet in their initial bet
     */
    int GetPlayerInitialBet(int player_index) const override;

    /**
     * @brief Gets the dealer's visible card.
     *
     * @return Card The dealer's face-up card
     */
    Card GetDealerCard() const override;

    /**
     * @brief Gets the dealer's current money.
     *
     * @return int The dealer's money amount
     */
    int DealerMoney() const override;

    /**
     * @brief Deals a card to a specific player hand.
     *
     * The dealer is part of the table and has no choices beyond applying the rules.
     *
     * @param player_index Index of the player receiving the card
     * @param hand_index Index of the hand receiving the card
     */
    void DealCard(int player_index,int hand_index) override;

    /**
     * @brief Places an initial bet for a player.
     *
     * @param player_index Index of the player placing the bet
     * @param money Amount of money to bet
     * @return Result Ok if the bet was valid, Illegal otherwise
     */
    Result PlayInitialBet(int player_index,int money) override;

    /**
     * @brief Places a safe/insurance bet for a player.
     *
     * @param player_index Index of the player placing the safe bet
     * @return Result Ok if the bet was valid, Illegal otherwise
     */
    Result PlaySafeBet(int player_index) override;

    /**
     * @brief Applies a player action to a specific hand.
     *
     * @param player_index Index of the player taking the action
     * @param hand_index Index of the hand to apply the action to
     * @param action The action to perform (Stand, Hit, Double, Split)
     * @return Result Ok if the action was valid, Illegal otherwise
     */
    Result ApplyPlayerAction(int player_index,int hand_index,Action action) override;

    /**
     * @brief Prepares the start of a round.
     *
     * This method performs the following operations:
     * - Shuffles the deck
     * - Deals one card to the dealer
     */
    void StartRound() override;

    /**
     * @brief Calculates the end of a round.
     *
     * This method performs the following operations:
     * - Plays the dealer's hand according to rules
     * - Determines whether each player wins or loses
     * - Resolves bet winnings
     * - Clears hands, clears bets, and returns cards to the deck if necessary
     *
     * @return RoundEndInfo Information about the round results
     */
    RoundEndInfo FinishRound() override;
};

#endif // JACO_TABLE_H