#pragma once
#include <vector>
#include <string>

class Question; // Forward declaration. Faster than including Question

class Quiz {
public:
	~Quiz();
	void add(); //add a single question
	void clear(); //clear questions
	void list() const; //questions vector not changed in this function
	void save(const char* filename) const; //save questions to file
	void load(const char* filename); //load questions from file
	void take(int questionCount) const; //take the quiz
private:
	std::vector<Question*> questions; //store Question objects
};

std::string getInput(); //get user input
