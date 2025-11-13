/*
*
* Jaco_table.cc
*
*/

#include "jaco_table.h"
#include "dealer.h"

// Class Cards for common deck from which players and dealer draw cards
//Constructor para las 52 cartas
Cards::Cards(){
    //Recorremos la pinta
    for(int i=0; i < 4; ++i){
        //Recorremos todos los valores
        for(int j=0; j < 13; ++j){
            //J+1 porque el enum comienza en 1
            Card c = {static_cast<Suit>(i), static_cast<Value>(j+1)};
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

// Class Jaco_table 

//----------Return cards in player's hand-----------
Jaco_table::Hand GetHand(int player_index, int hand_index) {
    return Players[player_index].PlayerHand[hand_index].cards;
}
//----------Return number of hands for player-----------
int Jaco_table::GetNumberOfHands(int player_index) {
    return Players[player_index].PlayerHand.size();
}
//----------Return player's current bet-----------
int Jaco_table::GetPlayerCurrentBet(int player_index,int hand_index) {
    return Players[player_index].current_bet;
}
//----------Return player's money-----------
int Jaco_table::GetPlayerMoney(int player_index) {
    return Players[player_index].player_money;
}
//----------Return croupier's money-----------
int Jaco_table::CroupierMoney() const {
    return Croupier.money;
}



