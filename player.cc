#include "player.h"
#include <iostream>

int Player::HandScore() const{
    int score = 0;
    int aces = 0;
    for(auto& h : Player::Hand){
        switch(h.fig){
            case Cards::Figure::Ace: 
                score+=11;
                ++aces;
                break;
            case Cards::Figure::Two:  score+=2; break;  
            case Cards::Figure::Three: score+=3; break;
            case Cards::Figure::Four: score+=4; break;
            case Cards::Figure::Five: score+=5; break;
            case Cards::Figure::Six: score+=6; break;
            case Cards::Figure::Seven: score+=7; break;
            case Cards::Figure::Eight: score+=8; break;
            case Cards::Figure::Nine: score+=9; break;
            case Cards::Figure::Ten: score+=10; break;
            case Cards::Figure::Jack : score+=10; break;
            case Cards::Figure::Queen: score+=10; break;
            case Cards::Figure::King: score+=10; break;
        }
    }
    //Adjust Aces if score > 21
    if(score > 21 && aces > 0){
        score -= 10;
        --aces;
    }
    return score;
}

void Player::AddCard(const Cards::Card &card){
    Hand.push_back(card);
}

void Player::ShowHand() const{
    std::cout << "Player's hand: " << std::endl;

    for(const auto &c : Hand){
        std::cout << "   " << Cards::PrintFig(c.fig) << " of " << Cards::PrintSuit(c.suit) << std::endl;
    }
    std::cout << "Score: " << Player::HandScore() << std::endl;
}

void Player::InitHand(Cards& deck){
    Hand.clear(); //Erase hand
    //Add two cards from the deck
    AddCard(deck.giveCard());
    AddCard(deck.giveCard());
}