/* 
Quiz
Object-Oriented Programming in Smart Systems
January 2020
*/

#include "Quiz.h" //not using Question directly in the main, no include
#include <iostream>

const char* QUIZ_FILE = "quizFile.txt";
const int Q_FOR_QUIZ = 5; //number of questions to be taken in the quiz

using namespace std;


int main()
{
	Quiz quiz;
	cout << "Welcome to the quiz programme!\n";
	quiz.load(QUIZ_FILE); //preload the questions from file

	while(true) {
		
		cout << "\nTo take the quiz, enter \"take\".\n" //take the quiz with questions in vector
			<< "To add a new question, enter \"add\".\n" // add question to vector
			<< "To save questions, enter \"save\".\n" //save questions in vector to file
			<< "To load questions, enter \"load\".\n" //load questions to vector from file
			<< "To list all questions, enter \"list\".\n" //lists questions in vector
			<< "To clear all questions, enter \"clear\".\n" //clears questions from vector
			<< "To quit the programme, enter \"quit\".\n";

		string userChoice = getInput();

		if (userChoice == "quit") {
		
			cout << "Quitting programme...";
			break;
		}

		else if (userChoice == "take") {
		
			quiz.take(Q_FOR_QUIZ);
		}

		else if (userChoice == "add") {
		
			quiz.add();
		}

		else if (userChoice == "save") {
		
			quiz.save(QUIZ_FILE);
		}

		else if (userChoice == "load") {
		
			quiz.load(QUIZ_FILE);
		}

		else if (userChoice == "list") {
		
			cout << "Listing all questions...\n";
			quiz.list();
		}

		else if (userChoice == "clear") {
		
			quiz.clear();
			cout << "Questions cleared.\n";
		}

		else { //if input doesn't match any command
		
			cout << "Invalid option. \n";
		}
	}
	//destructor clears the questions
	return 0;
}
