#pragma once
#include <iostream>
#include<iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <Windows.h>
using namespace std;

class Question
{
private:
	char correctAnswer;
	string answer1;
	string answer2;
	string answer3;
	string answer4;
	string questionContent;
	bool alreadyAsked;


public:
	Question() {}
	Question(string questionContent, string answer1, string answer2, string answer3, string answer4, char correctAnswer);
	~Question();
	char getCorrectAnswer();
	string getAnswer1();
	string getAnswer2();
	string getAnswer3();
	string getAnswer4();
	string getQuestionContent();
	void setCorrectAnswer(char correctAnswer);
	void setAnswer1(string answer1);
	void setAnswer2(string answer2);
	void setAnswer3(string answer3);
	void setAnswer4(string answer4);
	void setQuestionContent(string questionContent);
	void displayQuestion(); // wyswietla tresc pytania oraz odpowiedzi
	void displayFiftyFiftyQuestion(); // wyswietla pytanie gdy kolo 50/50 jest wziete
	void displayAskTheAudienceAnswers(); // wyswietla procenty jakie publicznosc mogla udzielic
	void displayPhoneToFriend();
	bool isAlreadyAsked();
	void setAsked(bool flag);

	
};

