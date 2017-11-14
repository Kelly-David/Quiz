#include "Player.h"

void Player::printPlayer(){
	string playerString = player_score + " - " + player_name + " - " + player_time + "\n";
	cout << player_score << " -- " << player_name << "\n" << endl;
}

string Player::getPlayer(){
	string playerString = player_score + " - " + player_name + " - " + player_time + "\n";
	return playerString;
}
