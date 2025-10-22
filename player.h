#include "cards.h"

class Player{
    public:
        void AddCard(const Cards::Card &card);
        void ShowHand() const;
        void InitHand(Cards& deck);
        std::vector<Cards::Card> Hand; 
        int HandScore() const;
        bool NeedCard() const{ return HandScore() < 17; } //Take card until 17 or more
        bool isBust() const { return HandScore() > 21; } //Player loses
        bool isBlackjack() const { return Hand.size() == 2 && HandScore() == 21; }
};