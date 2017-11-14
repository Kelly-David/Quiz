/*
Advanced Programming Lab 5 :: Quiz
David Kelly C00192316
Date: 24/01/2017
*/
#pragma warning(disable : 4996)

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
#include "Player.h"
#include "Question.h"

using namespace std;

//Global
string guess; //Answer user inputs for question.
int total;  //Total score.

sf::RenderWindow window(sf::VideoMode(800, 400), "Quiz");
sf::Font font;
sf::Text textQuestion("Question", font);
sf::Text textA("a", font);
sf::Text textB("b", font);
sf::Text textC("c", font);
sf::Text textD("d", font);
sf::Text players("Players", font);
sf::Text correct("Correct", font);
sf::Text incorrect("Incorrect", font);
sf::Text result("Result : ", font);


void recordScore(string pname) {
	fstream leaderboard;
	leaderboard.open("score.txt", ios::app);
	if (leaderboard.is_open()) {
		time_t now = time(NULL);
		time_t t = time(NULL);
		struct tm * ptm;
		time(&t);
		ptm = gmtime(&t);
		char buffer[80];
		strftime(buffer, 80, "%I:%M%p", ptm);
		string nowT = buffer;

		// convert now to string form
		leaderboard << total << "," << pname << "," << nowT << "," << "\n";
		leaderboard.close();
		cout << "Successfully written to file:: " << nowT << "," << pname << "," << total << endl << flush;
	}
	else cout << "Unable to open file" << endl << std::flush;
	leaderboard.close();
}


int main() {

	int menuItem = 0;
	bool menuDisplay = true;
	bool gamePaused = false;
	string name = "";
	fstream quizFile("questions.txt", ios::in);

	//Vector of questions
	vector<Question> qvector;
	string line;
	string delimiter = ",";
	//Get Questions from file
	if (quizFile.is_open())
	{
		while (getline(quizFile, line))
		{
			size_t pos = 0;
			std::string token;
			string sarray[7];
			int i = 0;
			while ((pos = line.find(delimiter)) != std::string::npos)
			{
				token = line.substr(0, pos);
				sarray[i] = token;
				i++;
				line.erase(0, pos + delimiter.length());
			}
			Question q = Question(sarray[0], sarray[1], sarray[2], sarray[3], sarray[4], sarray[5], std::stoi(sarray[6]));
			qvector.push_back(q);
		}
		quizFile.close();
	}
	//Shuffle the questions
	std::mt19937 r{ std::random_device{}() };
	std::shuffle(qvector.begin(), qvector.end(), r);

	// Declare and load a font
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");

	//Create all text
	// Create a text - Main Menu
	sf::Text textPlay("1: PLAY", font);
	textPlay.setCharacterSize(20);
	textPlay.setStyle(sf::Text::Underlined);
	textPlay.setFillColor(sf::Color::Green);
	textPlay.setPosition(10, 0);

	sf::Text textScore("2: HIGH SCORE", font);
	textScore.setCharacterSize(20);
	textScore.setStyle(sf::Text::Underlined);
	textScore.setFillColor(sf::Color::Green);
	textScore.setPosition(10, (textPlay.getPosition().y + 20));

	sf::Text textExit("3: EXIT", font);
	textExit.setCharacterSize(20);
	textExit.setStyle(sf::Text::Underlined);
	textExit.setFillColor(sf::Color::Green);
	textExit.setPosition(10, (textScore.getPosition().y + 20));

	// Create a text - Questions
	textQuestion.setCharacterSize(20);
	textQuestion.setStyle(sf::Text::Underlined);
	textQuestion.setFillColor(sf::Color::Green);
	textQuestion.setPosition(10, (textExit.getPosition().y + 20));

	textA.setCharacterSize(20);
	textA.setStyle(sf::Text::Underlined);
	textA.setFillColor(sf::Color::Red);
	textA.setPosition(10, (textQuestion.getPosition().y + 20));

	textB.setCharacterSize(20);
	textB.setStyle(sf::Text::Underlined);
	textB.setFillColor(sf::Color::Red);
	textB.setPosition(10, (textA.getPosition().y + 20));

	textC.setCharacterSize(20);
	textC.setStyle(sf::Text::Underlined);
	textC.setFillColor(sf::Color::Red);
	textC.setPosition(10, (textB.getPosition().y + 20));

	textD.setCharacterSize(20);
	textD.setStyle(sf::Text::Underlined);
	textD.setFillColor(sf::Color::Red);
	textD.setPosition(10, (textC.getPosition().y + 20));

	// Create a text - Players
	players.setCharacterSize(20);
	players.setStyle(sf::Text::Underlined);
	players.setFillColor(sf::Color::Blue);
	players.setPosition(10, 0);

	// Create a text - Correct
	correct.setCharacterSize(20);
	correct.setStyle(sf::Text::Underlined);
	correct.setFillColor(sf::Color::Magenta);
	correct.setPosition(100, 0);

	// Create a text - Incorrect
	incorrect.setCharacterSize(20);
	incorrect.setStyle(sf::Text::Underlined);
	incorrect.setFillColor(sf::Color::White);
	incorrect.setPosition(100, 0);

	// Create a text - Result
	result.setCharacterSize(30);
	result.setStyle(sf::Text::Underlined);
	result.setFillColor(sf::Color::Yellow);
	result.setPosition(100, 0);

	while (window.isOpen()) {
		// Check if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// Menu Select 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			menuDisplay = false;
			menuItem = 1;
			total = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			menuDisplay = false;
			menuItem = 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			menuDisplay = false;
			window.close();

		}
		while (menuItem == 1) {
			for (int i = 0; i < 10; i++) {
				string q = qvector[i].askQuestion();
				textQuestion.setString(q);
				window.clear();
				window.draw(textQuestion);
				window.display();
				string guess = "";
				std::cout << "What is your answer?" << "\n";
				getline(cin, guess);
				window.clear();
				
				if (qvector[i].getAnswer(guess)) {
					window.draw(correct);
					total = total + 1;
				}
				else {
					window.draw(incorrect);
				}
				window.draw(textQuestion);
				window.display();
				
				Sleep(1000);
			}
			menuItem = 0;
			window.clear();
			string resString = "Results : " + to_string(total) + "\nEnter your name...";
			result.setString(resString);
			window.draw(result);
			window.display();
			std::cout << "What's your name?\n";
			std::cin >> name;
			recordScore(name);
			menuDisplay = true;
		}


		while (menuItem == 2) {
			//Vector of players
			vector<Player> pvector;
			string line;
			string delimiter = ",";
			//Get Players from file
			ifstream myReadFile;
			myReadFile.open("score.txt");
			if (myReadFile.is_open()) {
				while (getline(myReadFile, line)) {
					size_t pos = 0;
					std::string token;
					string parray[3];
					int i = 0;
					while ((pos = line.find(delimiter)) != std::string::npos)
					{
						token = line.substr(0, pos);
						parray[i] = token;
						i++;
						line.erase(0, pos + delimiter.length());
					}
					Player p = Player(parray[0], parray[1], parray[2]);
					pvector.push_back(p);
				}
				myReadFile.close();
			}
			//Sort vector
			std::sort(pvector.begin(), pvector.end());
			std::reverse(pvector.begin(), pvector.end());
			//Get top five scores
			string topFive = "";
			for (int i = 0; i < 5; i++) {
				topFive = topFive + pvector[i].getPlayer();
			}
			players.setString(topFive);
			window.clear();
			window.draw(players);
			window.display();
			//std::cin.ignore();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				menuDisplay = true;
				menuItem = 0;
			}

		}
		// Clear the screen and draw all the shapes
		window.clear();

		// Draw Menu
		if (menuDisplay == true) {
			window.draw(textPlay);
			window.draw(textScore);
			window.draw(textExit);
		}
		// Draw Question
		if (menuItem == 1) {

		}

		window.display();


	}






	return 0;
}