//Questions header file
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

class Question
{
private:
	string Question_Text;
	string answer_1;
	string answer_2;
	string answer_3;
	string answer_4;

	string correct_answer;
	int Question_Score;

public:
	// Constructor
	Question() {
	}
	Question(string a, string b, string c, string d, string e, string f, int g) {
		Question_Text = a;
		answer_1 = b;
		answer_2 = c;
		answer_3 = d;
		answer_4 = e;
		correct_answer = f;
		Question_Score = g;
	}
	void setValues(string, string, string, string, string, string, int);
	string askQuestion();
	bool getAnswer(string);
};

