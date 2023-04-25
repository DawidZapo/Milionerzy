#include "Question.h"
bool validateAnswer(string choice); // waliduje odpowiedz podana przez uzytkownia pod katem co wpisal uzytkownik, uzytkownik wprowadza stringa
// po czym rozwazany jest tylko pierwszy znak w ciagu. Jesli rowna sie a, b, c lub d, zwraca prawde
bool validateCorrectAnswer(Question question, string choice); // walidacja odpowiedzi pod katem jej poprawnosci z odpowiedzia pytania
int main()
{
    vector<Question> questionsEasy; // przykladowa lista (taka ulepszona tablica) gdzie beda dodawane pytania, ta lista ma lepsze metody przez co latwiej dodac nowe pytania, taka ala dynamiczna tablica dla klasy/struktur
    vector<Question> questionsMedium; // tu pytania srednie
    vector<Question> questionsHard; // tu pytania ciezkie
    Question tempQuestion = Question(); // zmienna tymczasowo sluzaca jako referencja do zapisu pytania do listy

	fstream plik; //Przykladowy mechanizm czytania pytan z bazy pytan pliku tekstowego, czyta dopoki nie skonczy sie file
    plik.open("questionsEasy.txt", ios::in); // ta procedure trzeba powtorzyc zarowno dla questionsMedium jaki i questionsHard
    if (plik.good() == false)
	{
		cout << "Plik nie istnieje" << endl;
		exit(0);
	}
    string line;
	int lineNumber = 1;
    int i = 0;
    char tempChar;
	while (getline(plik, line))
	{
        switch (lineNumber)
        {
        case 1: tempQuestion.setQuestionContent(line);
            break;

        case 2: tempQuestion.setAnswer1(line);
            break;

        case 3: tempQuestion.setAnswer2(line);
            break;

        case 4: tempQuestion.setAnswer3(line);
            break;

        case 5: tempQuestion.setAnswer4(line);
            break;
        
        case 6: tempQuestion.setCorrectAnswer(tempChar = line[0]);
            break;
        }
        if (lineNumber == 6) {
            lineNumber = 0;
            questionsEasy.push_back(tempQuestion); // zapisanie/dodanie pytania do listy 
            i++;
        }
        lineNumber++;
    }
    plik.close();
   
    for (int i = 0; i < questionsEasy.size(); i++) { // wypisanie wszystkich pytan oraz odpowiedzi dla questionsEasy przeczytanych w pliku .txt
        questionsEasy.at(i).displayQuestion();
        cout << questionsEasy.at(i).getCorrectAnswer() << endl << endl;
    }
    // ponizej przykladowy mechanizm zadawania pytania
    string choice;
    
    questionsEasy.at(0).displayQuestion();
    do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
        cin >> choice;

    } while (!validateAnswer(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole
    
    //walidacja odpowidzi pod katem jej poprawnosci
    if (validateCorrectAnswer(questionsEasy.at(0), choice)) cout << "Poprawna!" << endl;
    else cout << "Niepoprawna" << endl;
}

bool validateAnswer(string choice) {
    choice = choice.substr(0, 1);
    if (choice != "A" && choice != "B" && choice != "C" && choice != "D" &&
        choice != "a" && choice != "b" && choice != "c" && choice != "d") return false;
    else return true;
}
bool validateCorrectAnswer(Question question, string choice) {
    char choiceChar = choice[0];

    if (toupper(choiceChar) == question.getCorrectAnswer()) { //sprawdzenie czy choiceChar jest poprawna odpowiedzia
        return true;
    }
    else {
        return false;
    }
}
