#pragma once
#include <string>
#include <iostream>

const int WRONG_ANS = 3;
//not advised to use namespace in headers

class Question {
public:
	Question();
	Question(const std::string& qT, const std::string& cA, const std::string* wA);
	const std::string& getQuestion() const { return questionText; }
	const std::string& getCorrectAns() const { return correctAns; }
	const std::string* getWrongAns() const { return wrongAns; }
	friend std::ostream& operator<<(std::ostream& out, const Question& q); //for reading from file. Project requirement
	friend std::istream& operator>>(std::istream& in, Question& q); //writing to file
private:
	std::string questionText;
	std::string correctAns;
	std::string wrongAns[WRONG_ANS];
};
