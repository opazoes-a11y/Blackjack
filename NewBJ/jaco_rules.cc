#include "NewBJ/jaco_rules.h"

jaco_rules::GameType jaco_rules::GetGameMode(){
    // Print instructions
    std::cout << "Select game_mode: " << std::endl;
    std::cout << "  [1]-Classic [2]-Round(Blackjack=20) [3]-Extreme(Black)" << std::endl;
    // Integer g_m to store player's answer
    int g_m;
    // Store integer in g_m
    std::cin >> g_m;
    // Return GameType according to answer
    switch(g_m){
        case 1: 
            return GameType::CLASSIC;
        case 2:
            return GameType::ROUND;
        case 3:
            return GameType::EXTREME;
    }
}


