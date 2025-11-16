#pragma once
#ifndef JACO_CARDS_H
#define JACO_CARDS_H
#include <vector>
#include <string>
#include <random>
#include <iostream>

/**
 * @class Cards
 * @brief Represents a standard deck of playing cards and provides card utility functions.
 *
 * This class manages a deck of 52 cards, allows shuffling, dealing,
 * printing card suits and values, and accessing card information.
 */
class Cards {
    public:

        /**
         * @enum Suit
         * @brief Enumerates the four card suits.
         */
        enum class Suit{
            Clubs,      ///< Clubs
            Diamons,    ///< Diamonds
            Hearts,     ///< Hearts
            Spades      ///< Spades
        };

        /**
         * @enum Value
         * @brief Enumerates card face values.
         *
         * Values follow Blackjack conventions:
         * - Ace is counted as 1 (can represent 11 in gameplay logic)
         * - Jack, Queen, and King map to 10 for Blackjack scoring
         */
        enum class Value{
            Ace = 1,    ///< Ace (1 or 11).
            Two, 
            Three,
            Four, 
            Five,
            Six,
            Seven,
            Eight,
            Nine,
            Ten,
            Jack = 11,  ///< Jack -> worth 10.
            Queen = 12, ///< Queen -> worth 10.
            King = 13   ///< King -> worth 10.
        };

        /**
         * @struct Card
         * @brief Represents a single playing card with suit and value.
         */
        struct Card{
            Suit suit;  ///< Suit of the card.
            Value fig;  ///< Face value of the card.
        };
        
        /**
         * @brief Constructs a full deck of 52 cards.
         *
         * Initializes the @ref Deck vector with one instance of each card in a
         * standard deck.
         */
        Cards();

        /**
         * @brief Randomly shuffles the deck.
         *
         * Uses std::shuffle with a random engine to ensure an unbiased shuffle.
         */
        void shuffleCards();

        /**
         * @brief Prints all cards currently in the deck to stdout.
         *
         * Useful for debugging or visual verification of deck contents.
         */
        void showCards() const;

        /**
         * @brief Deals the top card from the deck.
         *
         * Removes the first card in @ref Deck and returns it.
         *
         * @return Card The dealt card.
         */
        Card giveCard();

        /**
         * @brief Converts a suit enum into a printable string.
         *
         * @param s The card suit to convert.
         * @return std::string A human-readable suit name.
         */
        static std::string PrintSuit(Suit s);

        /**
         * @brief Converts a value enum into a printable string.
         *
         * @param f The card value to convert.
         * @return std::string A human-readable value name.
         */
        static std::string PrintFig(Value f);

        /**
         * @brief Container storing the current deck of cards.
         *
         * Represents the full card set, possibly altered by shuffling
         * or dealing operations.
         */
        std::vector<Card> Deck;

    private:
        /**
         * @brief Number of cards in a standard deck.
         */
        static const int kCardsPerDeck = 52; 
};

#endif 