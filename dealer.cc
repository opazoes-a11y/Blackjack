#include "dealer.h"
#include <iostream>

void Dealer::showCard() const{
    const auto& c = Hand.front();
    std::cout << "   Visible card: " << Cards::PrintFig(c.fig) << " of " << Cards::PrintSuit(c.suit) << std::endl;
}

void Dealer::Show() const{
    std::cout << "Dealer hand: " << std::endl;
    for(const auto &c : Hand){
        std::cout << "   " << Cards::PrintFig(c.fig) << " of " << Cards::PrintSuit(c.suit) << std::endl;
    }
    std::cout << "   Score: "<< Dealer::HandScore() << std::endl;
}