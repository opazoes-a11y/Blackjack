#include "itable.h"
#include "dealer.h"
#include <vector>
#include <string>

// Class for common deck from which players and dealer draw cards
class Cards {
    public:
        enum class Suit{
            Clubs, //trebol
            Diamons, //Diamante
            Hearts,
            Spades //Picas
        };

        enum class Value{
            Ace = 1, //11 or 1
            Two, 
            Three,
            Four, 
            Five,
            Six,
            Seven,
            Eight,
            Nine,
            Ten,
            Jack = 11, //10
            Queen = 12, //10
            King = 13 //10
        };
        struct Card{
            Suit suit;
            Value fig;
        };
        Cards();
        void shuffleCards();
        void showCards() const;
        Card giveCard();
        static std::string PrintSuit(Suit s);
        static std::string PrintFig(Value f);
        std::vector<Card> Deck;
    private:
        static const int kCardsPerDeck = 52; 
};

class Jaco_table : public ITable {
    public:
        std::vector<Jaco_player> Players;
        Dealer Croupier;
        Cards Deck;

        virtual Hand GetHand(int player_index, int hand_index) const = 0;
        virtual int GetNumberOfHands(int player_index) const = 0;

        virtual int GetPlayerCurrentBet(int player_index,int hand_index) const = 0;
        virtual int GetPlayerMoney(int player_index) const = 0;
        virtual int CroupierMoney() const = 0;

        virtual ITable::Result SetPlayerInitialBet(int player_index,int money) const = 0;

        virtual ITable::Card GetDealerCard() const = 0;


        // Dealer es parte de la mesa, no tiene elecciones propias mas alla de aplicar las reglas
        virtual void DealCard(int player_index,int hand_index) = 0;

        virtual ITable::Result PlaySafeBet(int player_index) = 0;
        virtual Result ApplyPlayerAction(int player_index,int hand_index,Action action) = 0;

        virtual void StartRound() = 0;

        virtual ITable::RoundEndInfo FinishRound() = 0;
        
        virtual ~Jaco_table() = default;
};
