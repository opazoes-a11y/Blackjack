#include "cards.h"
#include <random>
#include <algorithm>
#include <iostream>

//Constructor para las 52 cartas
Cards::Cards(){
    //Recorremos la pinta
    for(int i=0; i < 4; ++i){
        //Recorremos todos los valores
        for(int j=0; j < 13; ++j){
            //J+1 porque el enum comienza en 1
            Card c = {static_cast<Suit>(i), static_cast<Figure>(j+1)};
            Deck.push_back(c);
        }
    }
}

void Cards::shuffleCards(){
    std::random_device rd;
    std::mt19937 gen(rd()); //Random seed
    std::shuffle(Deck.begin(), Deck.end(), gen);

}

void Cards::showCards() const {
    for(const auto c : Deck){
        std::cout << PrintFig(c.fig) << " of " << PrintSuit(c.suit) << std::endl;
    }
}

std::string Cards::PrintSuit(Suit s){
    switch(s){
        case Suit::Clubs: return "Clubs"; break;
        case Suit::Diamons: return "Diamonds"; break;
        case Suit::Hearts: return "Hearts"; break;
        case Suit::Spades: return "Spades"; break;
    }
    return "";
}

std::string Cards::PrintFig(Figure f){
    switch(f){
        case Figure::Ace: return "Ace"; break;
        case Figure::Two: return "Two"; break;
        case Figure::Three: return "Three"; break;
        case Figure::Four: return "Four"; break;
        case Figure::Five: return "Five"; break;
        case Figure::Six: return "Six"; break;
        case Figure::Seven: return "Seven"; break;
        case Figure::Eight: return "Eight"; break;
        case Figure::Nine: return "Nine"; break;
        case Figure::Ten: return "Ten"; break;
        case Figure::Jack : return "Jack"; break;
        case Figure::Queen: return "Queen"; break;
        case Figure::King: return "King"; break;
    }
    return "";
}

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



