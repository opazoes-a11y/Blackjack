#include "Interface/iplayer.h"
#include "NewBJ/jaco_rules.h"
#include "NewBJ/cards.h"

/**
 * @class Jaco_player
 * @brief Represents a Blackjack player with hand management and betting logic.
 *
 * This class implements the IPlayer interface, storing player state such as
 * money, current bet, and card hands. It also provides helper methods for
 * scoring, checking Blackjack conditions, and interacting with the game table.
 */
class Jaco_player : public IPlayer {
    public:

        /**
         * @brief Constructs a player with an index and initial money.
         *
         * Initializes the player identifier, starting money using
         * jaco_rules::kPlayerStartMoney, and sets the current bet to zero.
         *
         * @param player_index Unique identifier for this player at the table.
         */
        Jaco_player(int player_index) : player_index(player_index), player_money(jaco_rules::kPlayerStartMoney), current_bet(0) {}

        /**
         * @brief Player identifier at the table.
         *
         * This index is used to reference the player in the ITable interface.
         */
        int player_index;

        /**
         * @brief Current amount of money owned by the player.
         */
        int player_money;

        /**
         * @brief Current bet placed by the player in the ongoing round.
         */
        int current_bet;

        /**
         * @brief Checks if the player still has money.
         * @return true if the player has more than 0 money, false otherwise.
         */
        bool HasMoney() const{ return player_money > 0;}

        /**
         * @brief Checks if the player's hand has been split.
         *
         * A split occurs when the player has more than one active hand.
         *
         * @return true if the player has more than one hand, false otherwise.
         */
        bool IsHandSplitted() const { return PlayerHand.size() > 1; }

        // ----------------- Hand management helpers -----------------

        /**
         * @brief Adds a card to the active hand.
         *
         * The exact behavior (which hand is used) depends on the implementation
         * in the source file.
         *
         * @param card Card to be added to the player's hand.
         */
        void AddCard(const Cards::Card &card);

        /**
         * @brief Prints the player's hand(s) to standard output.
         *
         * Useful for debugging and showing the cards held by the player.
         * in console.
         */
        void ShowHand() const;

        /**
         * @brief Initializes the player's hand by drawing initial cards.
         *
         * Typically draws the starting number of cards from the deck according to
         * the rules. Default is 2 cards per player at start.
         *
         * @param deck Reference to the deck used to deal cards.
         */
        void InitHand(Cards& deck);

        /**
         * @struct Hand
         * @brief Represents a single hand of cards held by the player.
         *
         * Supports multiple hands when the player splits.
         */
        typedef struct {
            std::vector<Cards::Card> cards; ///< Cards in this hand.
            int hand_index;                 ///< Index of this hand for split logic.
        } Hand;

        /**
         * @brief Collection of all hands currently owned by the player.
         *
         * When the player splits, this vector stores multiple independent hands.
         */
        std::vector<Hand> PlayerHand;

        /**
         * @brief Calculates the score of the player's hand.
         *
         * The scoring rules should follow Blackjack conventions (e.g., Ace can be
         * counted as 1 or 11). The exact behavior depends on the implementation.
         *
         * @return int Total score of the current hand.
         */
        int HandScore() const;

        /**
         * @brief Determines if the player should draw another card.
         *
         * Default behavior: the player takes cards until reaching at least 17.
         *
         * @return true if the player wants/needs another card, false otherwise.
         */
        bool NeedCard() const{ return HandScore() < 17; }


        /**
         * @brief Checks if the player has busted (score over 21).
         * @return true if the player's score exceeds 21, false otherwise.
         */
        bool isBust() const { return HandScore() > 21; }

        /**
         * @brief Checks if the player has a natural Blackjack.
         *
         * A Blackjack occurs when the player has exactly one hand, that hand
         * has exactly two cards, and the hand score equals 21.
         *
         * @return true if the player has Blackjack, false otherwise.
         */
        bool isBlackjack() const {
            return PlayerHand.size() == 1 &&
                PlayerHand[0].cards.size() == 2 &&
                HandScore() == 21;
        }

    // ----------------- IPlayer interface implementation -----------------
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

        /**
         * @brief Default virtual destructor.
         */
        ~Jaco_player() = default;
};