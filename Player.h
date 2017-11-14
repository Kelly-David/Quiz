//Players header file
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>    
#include <fstream>
#include <sstream>
#include <string>
#include "time.h"
#include "windows.h"
#include <stdlib.h>   
#include <random>

using namespace std;

class Player {
private:
	std::string player_score;
	std::string player_name;
	std::string player_time;

public:
	// Constructor
	Player() {
	}
	Player(std::string a, std::string b, std::string c) {
		player_score = a;
		player_name = b;
		player_time = c;
	}
	string getScore() const { return player_score; }
	void printPlayer();
	string getPlayer();
	bool operator<(Player rhs) { return stoi(player_score) < stoi(rhs.player_score); }
};