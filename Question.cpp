#include "Question.h"

void Question::setValues(string q, string a1, string a2, string a3, string a4, string ca, int pa){
	Question_Text = q;
	answer_1 = a1;
	answer_2 = a2;
	answer_3 = a3;
	answer_4 = a4;
	correct_answer = ca;
	Question_Score = pa;
}

string Question::askQuestion()
{
	std::cout << "\n";
	std::cout << Question_Text << "\n";
	std::cout << "a. " << answer_1 << "\n";
	std::cout << "b. " << answer_2 << "\n";
	std::cout << "c. " << answer_3 << "\n";
	std::cout << "d. " << answer_4 << "\n";
	std::cout << "\n";
	
	string questionString = Question_Text + "\n" + answer_1 + "\n" + answer_2 + "\n" + 
													answer_3 + "\n" + answer_4 + "\n";

	return questionString;
}

bool Question::getAnswer(string in)
{
	if (in.compare(correct_answer) == 0) {
		return true;
	}
	return false;
}
