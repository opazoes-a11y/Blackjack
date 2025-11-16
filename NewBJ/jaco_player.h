#include "Interface/iplayer.h"
#include "NewBJ/jaco_rules.h"
#include "NewBJ/cards.h"

class Jaco_player : public IPlayer {
    public:
        // Constructor to set initial values
        Jaco_player(int player_index) : player_index(player_index), player_money(jaco_rules::kPlayerStartMoney), current_bet(0) {}

        // Identifier and init variables for players
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
        // Interface functions ····················································
        /**
         * @brief Decides the action to take for a specific hand.
         *
         * @param table Reference to the game table containing current game state
         * @param player_index Index of the player making the decision
         * @param hand_index Index of the hand to decide action for (supports split hands)
         * @return ITable::Action The action chosen (e.g., hit, stand, double down, split)
         */
        virtual ITable::Action DecidePlayerAction(const ITable& table, int player_index, int hand_index) override;

        /**
         * @brief Decides the initial bet amount for a round.
         *
         * @param table Reference to the game table containing current game state
         * @param player_index Index of the player making the bet
         * @return int The bet amount to place
         */
        virtual int DecideInitialBet(const ITable& table, int player_index) override;

        /**
         * @brief Decides whether to use a safe/insurance option when the dealer gets an ace.
         *
         * @param table Reference to the game table containing current game state
         * @param player_index Index of the player making the decision
         * @return bool True if the player wants to use the safe option, false otherwise
         */
        virtual bool DecideUseSafe(const ITable& table, int player_index) override;

        ~Jaco_player() = default;
};