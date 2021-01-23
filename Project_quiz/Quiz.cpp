#include "Quiz.h"
#include "Question.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Quiz::~Quiz() {

	clear();
}

void Quiz::add() {

	string userQuestion;
	string userCorrectAns;
	string userWrongAns[WRONG_ANS];

	cout << "Enter a new question:\n";
	userQuestion = getInput();
	cout << "You inserted question: " << userQuestion << endl;

	cout << "Insert the correct answer:\n";
	userCorrectAns = getInput();
	cout << "You inserted correct answer: " << userCorrectAns << endl;

	for (int i = 0; i < WRONG_ANS; i++) { //ask for needed no of wrong answers

		cout << "Insert a wrong answer:\n";
		userWrongAns[i] = getInput();
	}

	cout << "You inserted wrong answers:\n"; //print all inserted wrong answers

	for (int i = 0; i < WRONG_ANS; i++) {
	
		cout << userWrongAns[i] << endl;
	}

	Question* newQuestion = new Question(userQuestion, userCorrectAns, userWrongAns);
	questions.push_back(newQuestion);

	cout << "Question added.\n";
}

void Quiz::clear() {

	for (size_t i = 0; i < questions.size(); i++) { //delete Question objects
	
		delete questions[i];
	}
	
	questions.clear();//make vector empty
}

void Quiz::list() const {

	if (questions.empty()) {
	
		cout << "No questions found.\n"; //if nothing in the vector
	}

	else {

		for (size_t i = 0; i < questions.size(); i++) {
		
			cout << i + 1 << ". " << questions[i]->getQuestion() << endl; //lists questions (arrow because of pointers)
		}
	}
}

void Quiz::save(const char* filename) const {

	ofstream file;
	file.open(filename, ios::out | ios::trunc); //trunc to get rid of old content in the file

	if (file.is_open()) { //open file and write vector contents to file

		for (size_t i = 0; i < questions.size(); i++) {

			file << *questions[i]; //overloaded operator. Writing to file
		}
		
		cout << "File " << filename << " updated.\n";
		file.close();
	}

	else {
		cout << "Unable to save to file " << filename << ".\n";
	}
}

void Quiz::load(const char* filename) {

	clear(); //to avoid doubling if called twice
	ifstream file;
	file.open(filename, ios::in);

	if (file.is_open()) {

		while (!file.eof() && !file.fail()) { //read question and answers from file

			Question* newQuestion = new Question(); //empty question

			file >> *newQuestion; //reading into Question

			if (!file.fail()) { //if no fail in reading from file, load onto vector

				questions.push_back(newQuestion);
			}

			else {
				delete newQuestion; //in case of error, delete object
			}
		}
		
		cout << questions.size() << " questions loaded.\n";
		file.close();
	}
	
	else {
		cout << "Unable to open file " << filename << ".\n";
	}
}

void Quiz::take(int questionCount) const { // take quiz

	vector<Question*> vcopy(questions); //copy constructor: copied vector for changing it

	if (vcopy.size() < questionCount) { //check if enough questions exist
	
		cout << "Add " << questionCount - vcopy.size() << " more questions to take the quiz.\n";
	}

	else {

		int rounds = 0;
		int score = 0;

		while (rounds < questionCount) {

			int randIndex = rand() % vcopy.size(); //getting random vector item

			cout << endl << vcopy[randIndex]->getQuestion() << endl; //print the random question

			//put all the wrong answers in a vector and change their order
			vector<const string*> answers;

			for (int i = 0; i < WRONG_ANS; i++) {
			
				answers.push_back(&vcopy[randIndex]->getWrongAns()[i]);
			}

			random_shuffle(answers.begin(), answers.end());
			int randAns = rand() % answers.size();
			answers[randAns] = &vcopy[randIndex]->getCorrectAns(); //replace a random wrong answer with the correct one

			for (size_t i = 0; i < answers.size(); i++) { //print the answer vector
			
				cout << i + 1 << ") " << *answers[i] << endl;
			}

			int userAns = 0;

			while (true) { //to get a valid answer

				cout << "Enter your answer number:\n";
				cin >> noskipws >> userAns; //doesn't skip whitespace

				if (!cin.fail() && userAns >= 1 && userAns <= WRONG_ANS && cin.get() == '\n') {
				
					//answer has to be a number in range of options, only one number entered!
					break;
				}

				cout << "Invalid option.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			if (userAns - 1 == randAns) { //if user answer and correct answer position correspond
			
				cout << "Correct!\n";
				score++;
			}

			else {
				cout << "Incorrect!\n";
			}

			vcopy.erase(vcopy.begin() + randIndex); //erase the asked question from question vector copy
			rounds++;
		}
		
		cout << "Your score is " << score << " out of " << questionCount << ".\n";
	}
}

string getInput() {

	string input;

	while (true) {

		if (cin.fail()) {
		
			cin.clear(); //clearing the fail 
			//ignores everything - max stream - until enter. Stream pointer moves to end of old input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		getline(cin, input);

		if (input.empty()) {
		
			cout << "Invalid input. Try again." << endl;
		}
		else {
			return input;
		}
	}
}
