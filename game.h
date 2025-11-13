#include "jaco_table.h"

class Game {
    public:
        Game();
        void Start();
    private:
        //Variables de estado del juego
        Cards deck_;
        Player player_;
        Dealer dealer_;
        bool round_over = false;
        //Metodos para el flujo de juego
        void DealInitial();
        void PlayerTurn();
        void DealerTurn();
        void ShowState() const;
        void ShowResult();
};