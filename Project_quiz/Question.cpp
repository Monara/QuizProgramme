#include "Question.h"

using namespace std;

Question::Question() {} //strings automatically set to empty. Default constructor

Question::Question(const string& qT, const string& cA, const string* wA) { //Question constructor

	questionText = qT;
	correctAns = cA;
	
	for (int i = 0; i < WRONG_ANS; i++) {
	
		wrongAns[i] = wA[i];
	}
}

ostream& operator<<(ostream& out, const Question& q) {

	out << q.getQuestion() << endl;
	out << q.getCorrectAns() << endl;

	for (int j = 0; j < WRONG_ANS; j++) {
	
		out << q.getWrongAns()[j] << endl;
	}
	
	return out;
}

istream& operator>>(std::istream& in, Question& q) {

	getline(in, q.questionText);
	getline(in, q.correctAns);

	for (int i = 0; i < WRONG_ANS; i++) {
	
		getline(in, q.wrongAns[i]);
	}
	
	return in;
}
