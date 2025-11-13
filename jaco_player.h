#include "iplayer.h"
#include "jaco_table.h"

class Jaco_player : public IPlayer {
    public:
        // Constructor to set initial values
        Jaco_player(int player_index) : player_index(player_index), player_money(ITable::kPlayerStartMoney), current_bet(0) {}
        // Identifier variables for players
        int player_index;
        int player_money;
        int current_bet;
        bool HasMoney() const{ return player_money > 0;}
        bool IsHandSplitted() const { return PlayerHand.size() > 1; }

        // Original functions
        void AddCard(const Cards::Card &card);
        void ShowHand() const;
        void InitHand(Cards& deck);

        // Individual hand struct
        typedef struct {
            std::vector<Cards::Card> cards;
            int hand_index;
        } Hand;
        // Vector of multiple hands if split
        std::vector<Hand> PlayerHand;


        int HandScore() const;
        bool NeedCard() const{ return HandScore() < 17; } //Take card until 17 or more
        bool isBust() const { return HandScore() > 21; } //Player loses
        bool isBlackjack() const { return PlayerHand.size() == 1 && 
                                    PlayerHand[0].cards.size() == 2 && 
                                    HandScore() == 21; }
        // Interface functions
        virtual ITable::Action DecidePlayerAction(const ITable& table, int player_index, int hand_index) override;
        virtual int DecideInitialBet(const ITable& table, int player_index) override;
        virtual bool DecideUseSafe(const ITable& table, int player_index) override;

        virtual ~Jaco_player() = default;
};