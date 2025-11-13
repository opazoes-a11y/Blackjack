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

        struct RoundEndInfo {
            Hand croupier_hand;
            std::vector<bool> winners;
            std::vector<int> player_money_delta; // El dinero ganado por el jugador en esta ronda(no se pierde aqui
                                        // , porque el dinero ya se ha quitado al hacer la apuesta).
            int croupier_money_delta; // El dinero ganado o perdido por el croupier en esta ronda
        };

        static const int kMaxBet = 10000;
        static const int kMinBet = 100;
        static const int kPlayerStartMoney = 4000;
        static const int kCroupierStartMoney = 100000;
        static const int kCroupierStop = 17;
        static const int kMaxPlayers = 7; // Si se os agotan las cartas en una ronda, bajad el maximo de jugadores

        //! Devuelve la mano hand_index de player_index. si el jugador solo tiene una
        //! mano coger hand_index == 1 es un error
        virtual Hand GetHand(int player_index,int hand_index) const = 0;

        //! Devuelve el numero de manos actual de player_index
        virtual int GetNumberOfHands(int player_index) const = 0;

        //! Devuelve la apuesta total actual de la mano hand_index del jujador player_index
        virtual int GetPlayerCurrentBet(int player_index,int hand_index) const = 0;
        //! Devuelve la el dinero restante no apostado de player_index
        virtual int GetPlayerMoney(int player_index) const = 0;
        //! Devuelve el dinero que player_index ha apostado en su apuesta inicial
        virtual int GetPlayerInitialBet(int player_index) const = 0;

        //! Devuelve la carta visible del croupier
        virtual Card GetDealerCard() const = 0;

        //! Devuelve la carta visible del croupier
        virtual int CroupierMoney() const = 0;

        // Dealer es parte de la mesa, no tiene elecciones propias mas alla de aplicar las reglas
        virtual void DealCard(int player_index,int hand_index) = 0;

        virtual Result SetPlayerInitialBet(int player_index,int money) = 0;
        virtual Result PlaySafeBet(int player_index) = 0;
        virtual Result ApplyPlayerAction(int player_index,int hand_index,Action action) = 0;


        //! Prepara el principio de ronda
        //!
        //! Baraja el mazo
        //! Reparte las cartas iniciales a cada jugador
        //! Reparte una carta al croupier
        virtual void StartRound() = 0;

        //! Calcula el final de ronda
        //!
        //! Juega el croupier
        //! Resolver si cada jugador gana o pierde
        //! Resolver quien gana las apuestas
        //! Limpiar manos y devolver cartas al mazo si es necesario
        virtual RoundEndInfo FinishRound() = 0;
        
        virtual ~ITable() = default;

};