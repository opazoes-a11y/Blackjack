#include "game.h"
#include <iostream>
#include <string>

int main() {
    while (true) {
        std::cout << "\n------------Blackjack------------\n";
        Game g;
        g.Start();

        std::cout << "\n   Play again? (y/n)";
        std::string ans;
        std::getline(std::cin, ans);
        if (ans.empty() || (ans[0] != 'y' && ans[0] != 'S')) break;
        std::cout << "\n-----------------------------\n";
    }
    return 0;
}