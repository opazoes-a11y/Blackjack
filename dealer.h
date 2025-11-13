#include "jaco_player.h"

class Dealer : public Jaco_player {
    public:
        Dealer();
        int money;
        void showCard() const;
        void Show() const;
};