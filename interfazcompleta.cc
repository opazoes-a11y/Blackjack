#include <vector>


class ITable {
    public:
        enum class Action {
            Stand,
            Hit,
            Double,
            Split
        };

        enum class Result {
            Ok,
            Illegal
        };
        enum class Value {
            ACE = 1,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            NINE,
            TEN,
            JACK,
            QUEEN,
            KING,
            end
        };

        enum class Suit {
            HEARTS,
            CLUBS,
            SPADES,
            DIAMONDS,
            end
        };

        struct Card {
            Value value_;
            Suit suit_;
        };

        using Hand = std::vector<Card>;

        class RoundEndInfo {
            Hand croupier_hand;
            std::vector<bool> winners;
            std::vector<int> money_delta; // El dinero ganado por el jugador en esta ronda(no se pierde aqui
                                        // , porque el dinero ya se ha quitado al hacer la apuesta).
            int money_delta; // El dinero ganado o perdido por el croupier en esta ronda
        };

        static const int kMaxBet = 10000;
        static const int kMinBet = 100;
        static const int kPlayerStartMoney = 4000;
        static const int kCroupierStartMoney = 100000;
        static const int kCroupierStop = 17;
        static const int kMaxPlayers = 7; // Si se os agotan las cartas en una ronda, bajad el maximo de jugadores

        virtual Hand GetHand(int player_index,int hand_index) const = 0;
        virtual int GetNumberOfHands(int player_index) const = 0;

        virtual int GetPlayerCurrentBet(int player_index,int hand_index) const = 0;
        virtual int GetPlayerMoney(int player_index) const = 0;
        virtual void SetPlayerInitialBet(int player_index,int money) const = 0;

        virtual Card GetDealerCard() const = 0;

        virtual int CroupierMoney() const = 0;

        // Dealer es parte de la mesa, no tiene elecciones propias mas alla de aplicar las reglas
        virtual void DealCard(int player_index,int hand_index) = 0;

        virtual void PlaySafeBet(int player_index) = 0;
        virtual Result ApplyPlayerAction(int player_index,int hand_index,Action action) = 0;


        virtual void StartRound() = 0;

        virtual RoundEndInfo FinishRound() = 0;
        
        virtual ~ITable() = default;

};

class BaseRules {
    public:
        virtual int GetWinPoint() { return 21; }
        virtual int NumberOfDecks() { return 1; }
        virtual int InitialCards() { return 2; }
        virtual bool PlayFirstEvenPlayers() { return false; }
        virtual ~BaseRules() = default;
};

class DifferentWinRules : public BaseRules {
    public:
        DifferentWinRules(int winpoints) : winpoints_{winpoints} {}
        virtual int GetWinPoint() override { return winpoints_; }
    private:
    int winpoints_;
};


class TwoDecksRules : public DifferentWinRules {
    public:
        TwoDecksRules() : DifferentWinRules{25} {}
        virtual int NumberOfDecks() override { return 2; }
        virtual int InitialCards() override { return 3; }
};

class RoundRules : public DifferentWinRules {
    public:
        RoundRules() : DifferentWinRules{20} {}
};

class IPlayer {
    public:
        virtual ITable::Action DecidePlayerAction(const ITable& table, int player_index, int hand_index) = 0;
        virtual int DecideInitialBet(const ITable& table, int player_index) = 0;
        virtual bool DecideUseSafe(const ITable& table, int player_index) = 0;

        virtual ~IPlayer() = default;
};

class IGame {
    public:
        virtual void PlayGame() = 0;
};

class MyTable: public ITable {

};

class MyPlayer: public IPlayer {

};
class MyGame: public IGame {

};

int main() {
    RoundRules rules;

    MyTable t{rules};
    MyPlayer p1{rules},p2{rules},p3{rules},p4{rules};
    JuanitoPlayer p5{rules},p6{rules},p7{rules};
    MyGame g{rules,t,p1,p2,p3,p4,p5,p6,p7};

    g.PlayGame();








    do {// RONDA
        // APUESTA INICIAL
        // REPARTIR CARTAS A JUGADORES
        // REPARTIR CARTA AL CROUPIER
        IF croupier as
            POR CADA JUGADOR
                PREGUNTAR SEGURO
        POR CADA JUGADOR
            EL JUGADOR HACE ACCIONES HASTA QUE PARA O SE PASA
                SI SE PARTE LA MANO, JUEGAS UN TURNO COMPLETO POR CADA MANO
        JUEGA EL CROUPIER
        SE VALORA VICTORIA/DERROTA
        SE REPARTE EL DINERO
        SE LIMPIA LA MESA
    } while (COMPROBAR CONDICIONES DE VICTORIA/DERROTA);
}


        // CheckPlayersLeft
        // CleanHands
        // CleanBets
        // PlaceInitialBet
        // Shuffle
        // Deal 2 cards per player
        // Deal 1 card to dealer

    // InsuranceOffer
        // Player is asked if they want insurance, in case of an ace

    // Fpr each player they can do actions until they overflow or stand
    // PlayerTurn
        // Player is given the board to check and
        // reply with an action
        // Stand
        // Hit
        // Double
        // Split

    // When all players have stood, dealer draws out cards up to their max



    ShuffleCards
    PlaceBet
    MinBet
    MaxBet

    DealerStop

    PlayerCount

    
    