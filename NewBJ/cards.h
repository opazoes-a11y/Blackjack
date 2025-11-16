#pragma once
#ifndef JACO_CARDS_H
#define JACO_CARDS_H
#include <vector>
#include <string>
#include <random>
#include <iostream>

class Cards {
    public:
        enum class Suit{
            Clubs, //trebol
            Diamons, //Diamante
            Hearts,
            Spades //Picas
        };

        enum class Value{
            Ace = 1, //11 or 1
            Two, 
            Three,
            Four, 
            Five,
            Six,
            Seven,
            Eight,
            Nine,
            Ten,
            Jack = 11, //10
            Queen = 12, //10
            King = 13 //10
        };
        struct Card{
            Suit suit;
            Value fig;
        };
        Cards();
        void shuffleCards();
        void showCards() const;
        Card giveCard();
        static std::string PrintSuit(Suit s);
        static std::string PrintFig(Value f);
        std::vector<Card> Deck;
    private:
        static const int kCardsPerDeck = 52; 
};

#endif 