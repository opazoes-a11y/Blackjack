#include "game.h"
#include <iostream>
#include <string>

//Game constructor
Game::Game() : deck_(), player_(), dealer_(), round_over(false) {}



void Game::Start(){
    round_over = false;
    //init var
    deck_.shuffleCards();
    player_.InitHand(deck_);
    dealer_.InitHand(deck_);

    ShowState();

    if (player_.isBlackjack() || dealer_.isBlackjack()) {
        std::cout << "\nDealer's hand: \n";
        dealer_.Show();
        ShowResult();
        return;
    }

    PlayerTurn();
    if (round_over) { ShowResult(); return; }

    DealerTurn();
    ShowResult();
}

void Game::PlayerTurn() {
    while (true) {
        //Check if player has more than 21 -> isBust
        if (player_.isBust()) { 
            //Show score
            std::cout << "\nPlayer busted with "
            << std::to_string(player_.HandScore())
            << " points.\n"; 
            round_over = true; 
            return; 
        }
        std::cout << "\n[H]it o [S]tand? ";
        //Interacción con el usuario
        std::string cmd; 
        std::getline(std::cin, cmd);
        //Player takes one card
        if (!cmd.empty() && (cmd[0]=='h'||cmd[0]=='H')) {
            player_.AddCard(deck_.giveCard());
            player_.ShowHand();
        } else if (!cmd.empty() && (cmd[0]=='s'||cmd[0]=='S')) {
            break;
        } else {
            std::cout << "Press H to Hit and S to stand.\n";
        }
    }
}

void Game::DealerTurn() {
    dealer_.Show();
    while (dealer_.HandScore() < 17) {
        std::cout << "Dealer takes one card.\n";
        dealer_.AddCard(deck_.giveCard());
        dealer_.Show();
    }
}

void Game::ShowState() const {
    player_.ShowHand();
    std::cout << "\nDealer's visible card:\n";
    dealer_.showCard();
}

void Game::ShowResult(){
    int playerScore = player_.HandScore();
    int dealerScore = dealer_.HandScore();
    
    std::cout << "\nResult:\n";
    std::cout << "   Player: " << playerScore << " - Dealer: " << dealerScore << "\n   ";
    //blackjack cases
    if (player_.isBlackjack() && dealer_.isBlackjack()) { std::cout << "Tie: both blackjack.\n"; return; }
    if (player_.isBlackjack()) { std::cout << "Player wins with blackjack.\n"; return; }
    if (dealer_.isBlackjack()) { std::cout << "Dealer wins. Player loses.\n"; return; }
    //other cases
    if (playerScore > 21) std::cout << "Overflow 21. Player loses.\n";
    else if (dealerScore > 21) std::cout << "Dealer overflow 21. Player wins.\n";
    else if (playerScore > dealerScore) std::cout << "Player wins.\n";
    else if (playerScore < dealerScore) std::cout << "Player loses\n";
    else std::cout << "Tie.\n";
}