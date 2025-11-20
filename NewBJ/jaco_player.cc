#pragma once
#ifndef JACO_PLAYER_CC
#define JACO_PLAYER_CC
#include "NewBJ/jaco_player.h"

// Initialize to 0 variable static next_player_index to auto-increment player IDs
int jaco_player::next_player_index = 0;

void jaco_player::AddCard(const Cards::Card& card, int hand_index){
	if(PlayerHand.empty()){
		std::cout << "Error: No hand initialized for player " << player_index << std::endl;
		return;
	} else if(PlayerHand.size() == 1){
		PlayerHand[0].cards.push_back(card);
		return;
	}
	PlayerHand[hand_index].cards.push_back(card);
	return;
}

/**
 * @brief Prints hand's cards and scores for each hand.
 * 
 * First iterates through player's hands and then iterates all cards
 * in each hand to print them to standard output using @ref Cards::PrintFig and
 * @ref Cards::PrintSuit, along with each hand score using @ref HandScore
 */
void jaco_player::ShowHand() const{
	std::cout << "Player " << player_index << "'s hands: " << std::endl;
	for(const auto& hand : PlayerHand){
		std::cout << " Hand " << hand.hand_index << ":" << std::endl;
		for(const auto &c : hand.cards){
			std::cout << "   " << Cards::PrintFig(c.fig) << " of " << Cards::PrintSuit(c.suit) << std::endl;
		}
		std::cout << "  Score: " << HandScore(hand.hand_index) << std::endl;
	}
}

void jaco_player::InitHand(Cards& deck){
	PlayerHand.clear(); //Erase hands
	//Create first hand
	Hand first_hand;
	first_hand.hand_index = 0;
	//Add two cards from the deck
	first_hand.cards.push_back( deck.giveCard() );
	first_hand.cards.push_back( deck.giveCard() );
	// Add hand to PlayerHand
	PlayerHand.push_back(first_hand);
}

int jaco_player::HandScore(int hand_index) const{
	int score = 0;
	int aces = 0;
	// Iterate though cards in the specified hand
	for(auto& c : PlayerHand[hand_index].cards){
		// Add score according to card value
		switch(c.fig){
			case Cards::Value::Ace: 	score+=11; ++aces;
				break;
			case Cards::Value::Two:  	score+=2;  break;  
			case Cards::Value::Three: 	score+=3;  break;
			case Cards::Value::Four: 	score+=4;  break;
			case Cards::Value::Five: 	score+=5;  break;
			case Cards::Value::Six: 	score+=6;  break;
			case Cards::Value::Seven: 	score+=7;  break;
			case Cards::Value::Eight: 	score+=8;  break;
			case Cards::Value::Nine: 	score+=9;  break;
			case Cards::Value::Ten: 	score+=10; break;
			case Cards::Value::Jack : 	score+=10; break;
			case Cards::Value::Queen: 	score+=10; break;
			case Cards::Value::King: 	score+=10; break;
		}
	}
	//Adjust Aces if score > rules_.GetWinPoint()
	while(score > rules_.GetWinPoint() && aces > 0){
		score -= 10;
		--aces;
	}
	return score;
}




#endif // JACO_PLAYER_CC