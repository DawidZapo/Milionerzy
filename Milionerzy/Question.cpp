#include "Question.h"

Question::Question(string questionContent, string answer1, string answer2, string answer3, string answer4, char correctAnswer) {
	this->questionContent = questionContent;
	this->answer1 = answer1;
	this->answer2 = answer2;
	this->answer3 = answer3;
	this->answer4 = answer4;
	this->correctAnswer = correctAnswer;
	this->alreadyAsked = false;
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
	cout << "A: " << setw(25) <<  answer1 << setw(3) << " B: " << setw(25) << answer2 << endl
		<< "C: " << setw(25) << answer3  << setw(3) << " D: " << setw(25) << answer4 << endl;
}

void Question::displayFiftyFiftyQuestion() {
	srand(time(NULL));
	int number = rand() % 3;
	if (correctAnswer == 'A' || correctAnswer == 'a') {
		switch (number) {
		case 0:
			cout << questionContent << endl;
			cout << "A: " << setw(25) << answer1 << setw(3) << " B: " << setw(25) << "------" << endl
				<< "C: " << setw(25) << "-------" << setw(3) << " D: " << setw(25) << answer4 << endl;
			break;
		case 1:
			cout << questionContent << endl;
			cout << "A: " << setw(25) << answer1 << setw(3) << " B: " << setw(25) << "------" << endl
				<< "C: " << setw(25) << answer3 << setw(3) << " D: " << setw(25) << "------" << endl;
			break;
		case 2:
			cout << questionContent << endl;
			cout << "A: " << setw(25) << answer1 << setw(3) << " B: " << setw(25) << answer2 << endl
				<< "C: " << setw(25) << "-----" << setw(3) << " D: " << setw(25) << "-----" << endl;
			break;
		}
	}
	else if (correctAnswer == 'B' || correctAnswer == 'b') {
		switch (number) {
		case 0:
			cout << questionContent << endl;
			cout << "A: " << setw(25) << answer1 << setw(3) << " B: " << setw(25) << answer2 << endl
				<< "C: " << setw(25) << "-------" << setw(3) << " D: " << setw(25) << "-----" << endl;
			break;
		case 1:
			cout << questionContent << endl;
			cout << "A: " << setw(25) << "-----" << setw(3) << " B: " << setw(25) << answer2 << endl
				<< "C: " << setw(25) << answer3 << setw(3) << " D: " << setw(25) << "------" << endl;
			break;
		case 2:
			cout << questionContent << endl;
			cout << "A: " << setw(25) << "-----" << setw(3) << " B: " << setw(25) << answer2 << endl
				<< "C: " << setw(25) << "-----" << setw(3) << " D: " << setw(25) << answer4 << endl;
			break;
		}
	}
	else if (correctAnswer == 'C' || correctAnswer == 'c') {
		switch (number) {
		case 0:
			cout << questionContent << endl;
			cout << "A: " << setw(25) << answer1 << setw(3) << " B: " << setw(25) << "------" << endl
				<< "C: " << setw(25) << answer3 << setw(3) << " D: " << setw(25) << "-----" << endl;
			break;
		case 1:
			cout << questionContent << endl;
			cout << "A: " << setw(25) << "-------" << setw(3) << " B: " << setw(25) << "------" << endl
				<< "C: " << setw(25) << answer3 << setw(3) << " D: " << setw(25) << answer4 << endl;
			break;
		case 2:
			cout << questionContent << endl;
			cout << "A: " << setw(25) << "------" << setw(3) << " B: " << setw(25) << answer2 << endl
				<< "C: " << setw(25) << answer3 << setw(3) << " D: " << setw(25) << "-----" << endl;
			break;
		}
	}
	else if (correctAnswer == 'D' || correctAnswer == 'd') {
		switch (number) {
		case 0:
			cout << questionContent << endl;
			cout << "A: " << setw(25) << answer1 << setw(3) << " B: " << setw(25) << "------" << endl
				<< "C: " << setw(25) << "-------" << setw(3) << " D: " << setw(25) << answer4 << endl;
			break;
		case 1:
			cout << questionContent << endl;
			cout << "A: " << setw(25) << "------" << setw(3) << " B: " << setw(25) << "------" << endl
				<< "C: " << setw(25) << answer3 << setw(3) << " D: " << setw(25) << answer4 << endl;
			break;
		case 2:
			cout << questionContent << endl;
			cout << "A: " << setw(25) << "------" << setw(3) << " B: " << setw(25) << answer2 << endl
				<< "C: " << setw(25) << "------" << setw(3) << " D: " << setw(25) << answer4 << endl;
			break;
		}
	}
	else {
		cout << "Error" << endl;
	}
}

void Question::displayAskTheAudienceAnswers() {
	srand(time(NULL));
	int temp;
	int numbers[4];
	numbers[0] = rand() % 97 + 1;
	numbers[1] = rand() % (100 - numbers[0]);
	numbers[2] = rand() % (100 - numbers[0] - numbers[1]);
	numbers[3] = 100 - numbers[0] - numbers[1] - numbers[2];
	
	for (int i = 0; i < 4; i++) { // szybkie sortowanie, pierwszy element tablicy bedzie najwiekszy, czyli pierwszy elemetn powedruje do
		for (int j = 0; j < 4; j++) { // odpowiedniej odpowiedzi
			if (numbers[i] > numbers[j]) {
				temp = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = temp;
			}
		}
	}
	

	if (correctAnswer == 'A' || correctAnswer == 'a') { // skoro odpowiedz A jest prawidlowa to pierwszy element wedruje do odpowiedzi A
		cout << "A: " << numbers[0] << "%" << endl;
		cout << "B: " << numbers[1] << "%" << endl;
		cout << "C: " << numbers[2] << "%" << endl;
		cout << "D: " << numbers[3] << "%" << endl;
	}
	else if (correctAnswer == 'B' || correctAnswer == 'b') { // skoro odpowiedz B jest prawidlowa to pierwszy element wedruje do odpowiedzi B
		cout << "A: " << numbers[1] << "%" << endl;
		cout << "B: " << numbers[0] << "%" << endl;
		cout << "C: " << numbers[2] << "%" << endl;
		cout << "D: " << numbers[3] << "%" << endl;
	}
	else if (correctAnswer == 'C' || correctAnswer == 'c') {
		cout << "A: " << numbers[2] << "%" << endl;
		cout << "B: " << numbers[1] << "%" << endl;
		cout << "C: " << numbers[0] << "%" << endl;
		cout << "D: " << numbers[3] << "%" << endl;
	}
	else if (correctAnswer == 'D' || correctAnswer == 'd') {
		cout << "A: " << numbers[3] << "%" << endl;
		cout << "B: " << numbers[1] << "%" << endl;
		cout << "C: " << numbers[2] << "%" << endl;
		cout << "D: " << numbers[0] << "%" << endl;
	}
	else {
		cout << "ERROR" << endl;
	}

}

bool Question::isAlreadyAsked() {
	return alreadyAsked;
}
void Question::setAsked(bool flag) {
	this->alreadyAsked = flag;
}