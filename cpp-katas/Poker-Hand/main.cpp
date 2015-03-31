//Author - Sourabh S Joshi
#include <iostream>
#include <fstream>
#include <vector>
#include "poker-hand.h"
using namespace std;
int main() 
{
    unsigned int win_count = 0; //number of times player 1 won
    std::string line;
    std::ifstream file("poker.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            std::string pl1 = line.substr(0, 14);
            std::string pl2 = line.substr(15, 28);

            Pokerhand p1(pl1);
            Pokerhand p2(pl2);

            std::vector<std::pair<int, Pokerhand> > players;
            players.push_back(make_pair(1, p1));
            players.push_back(make_pair(2, p2));

            int winner = PlayPokerHands(players);
            if (winner == 1) {
                win_count++;
            }
        }
        file.close();
        std::cout << "Player 1 won " << win_count << " times." << std::endl;
    } else {
        std::cout << "Unable to open poker.txt" << std::endl;
    }

    return 0;
}

