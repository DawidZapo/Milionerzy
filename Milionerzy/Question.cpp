#include "Question.h"

Question::Question(string questionContent, string answer1, string answer2, string answer3, string answer4, char correctAnswer) {
	this->questionContent = questionContent;
	this->answer1 = answer1;
	this->answer2 = answer2;
	this->answer3 = answer3;
	this->answer4 = answer4;
	this->correctAnswer = correctAnswer;
}
Question::~Question(){}
char Question::getCorrectAnswer() {
	return correctAnswer;
}
string Question::getAnswer1() {
	return answer1;
}
string Question::getAnswer2() {
	return answer2;
}
string Question::getAnswer3() {
	return answer3;
}
string Question::getAnswer4() {
	return answer4;
}
string Question::getQuestionContent() {
	return questionContent;
}
void Question::setCorrectAnswer(char correctAnswer) {
	this->correctAnswer = correctAnswer;
}
void Question::setAnswer1(string answer1) {
	this->answer1 = answer1;
}
void Question::setAnswer2(string answer2) {
	this->answer2 = answer2;
}
void Question::setAnswer3(string answer3) {
	this->answer3 = answer3;
}
void Question::setAnswer4(string answer4) {
	this->answer4 = answer4;
}
void Question::setQuestionContent(string questionContent) {
	this->questionContent = questionContent;
}
void Question::displayQuestion() {
	cout << questionContent << endl;
	cout << "A: " << setw(10) <<  answer1 << setw(3) << " B: " << setw(10) << answer2 << endl
		<< "C: " << setw(10) << answer3  << setw(3) << " D: " << setw(10) << answer4 << endl;
}