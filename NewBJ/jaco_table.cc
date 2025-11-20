#include "NewBJ/jaco_table.h"

ITable::Hand jaco_table::GetHand(int player_index, int hand_index){

}

int jaco_table::GetNumberOfHands(int player_index) const {

}

int jaco_table::GetPlayerCurrentBet(int player_index,int hand_index) const{

}

int jaco_table::GetPlayerMoney(int player_index) const{

}

int jaco_table::GetPlayerInitialBet(int player_index) const{

}

ITable::Card jaco_table::GetDealerCard() const{

}

int jaco_table::DealerMoney() const{

}

void jaco_table::DealCard(int player_index,int hand_index){

}

ITable::Result jaco_table::PlayInitialBet(int player_index,int money){

}

ITable::Result jaco_table::PlaySafeBet(int player_index){

}

ITable::Result jaco_table::ApplyPlayerAction(int player_index,int hand_index,Action action){

}

void jaco_table::StartRound(){

}

ITable::RoundEndInfo jaco_table::FinishRound(){
    
}







