#pragma once
#ifndef JACO_CARDS_CC
#define JACO_CARDS_CC
#include "NewBJ/cards.h"

/**
 * @brief Constructs a full deck of 52 unique cards.
 *
 * This implementation iterates through all suit and value combinations
 * and fills the Deck vector accordingly. The Value enum starts at 1,
 * therefore the inner loop uses (j+1) when constructing the card.
 */
Cards::Cards(){
    for(int i=0; i < 4; ++i){       // Iterate through suits.
        for(int j=0; j < 13; ++j){  // Iterate through values.
            //J+1 because the enum starts at 1.
            Card c = {static_cast<Suit>(i), static_cast<Value>(j+1)};
            Deck.push_back(c);
        }
    }
}

/**
 * @brief Shuffles the deck using a random Mersenne Twister engine.
 *
 * Creates a random_device seed and passes it to std::mt19937,
 * then applies std::shuffle on the Deck container.
 */
void Cards::shuffleCards(){
    std::random_device rd;
    std::mt19937 gen(rd()); //Random seed
    std::shuffle(Deck.begin(), Deck.end(), gen);

}

/**
 * @brief Prints all cards in the deck to standard output.
 *
 * Each card is displayed as "<value> of <suit>" using
 * Cards::PrintFig() and Cards::PrintSuit().
 */
void Cards::showCards() const {
    for(const auto c : Deck){
        std::cout << PrintFig(c.fig) << " of " << PrintSuit(c.suit) << std::endl;
    }
}

/**
 * @brief Converts a Suit enum value into a readable string.
 *
 * @param s The suit to convert.
 * @return std::string Human-readable name for the suit.
 */
std::string Cards::PrintSuit(Suit s){
    switch(s){
        case Suit::Clubs: return "Clubs"; break;
        case Suit::Diamons: return "Diamonds"; break;
        case Suit::Hearts: return "Hearts"; break;
        case Suit::Spades: return "Spades"; break;
    }
    return "";
}

/**
 * @brief Converts a Value enum into a readable string.
 *
 * @param f The card value.
 * @return std::string Human-readable name for the value.
 */
std::string Cards::PrintFig(Value f){
    switch(f){
        case Value::Ace: return "Ace"; break;
        case Value::Two: return "Two"; break;
        case Value::Three: return "Three"; break;
        case Value::Four: return "Four"; break;
        case Value::Five: return "Five"; break;
        case Value::Six: return "Six"; break;
        case Value::Seven: return "Seven"; break;
        case Value::Eight: return "Eight"; break;
        case Value::Nine: return "Nine"; break;
        case Value::Ten: return "Ten"; break;
        case Value::Jack : return "Jack"; break;
        case Value::Queen: return "Queen"; break;
        case Value::King: return "King"; break;
    }
    return "";
}

/**
 * @brief Removes and returns the top card from the deck.
 *
 * This implementation takes the last card in the Deck vector (LIFO)
 * and removes it before returning it. If the deck is empty, a default
 * Card is returned and a warning is printed.
 *
 * @return Card The dealt card, or an empty Card{} if deck is empty.
 */
Cards::Card Cards::giveCard(){
    if(!Deck.empty()){
        //Take last element from deck
        Card YourCard = Deck.back();
        //Erase element
        Deck.pop_back();
        return YourCard;
    }else {
        std::cout << "No cards left in deck." << std::endl;
        return Card{};
    }
}

#endif JACO_CARDS_CC