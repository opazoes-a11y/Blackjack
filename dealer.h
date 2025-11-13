#include "player.h"

class Dealer : public Player {
    public:
        Dealer();
        int money;
        void showCard() const;
        void Show() const;
};