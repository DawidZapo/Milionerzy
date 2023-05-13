#include "Question.h"
bool validateAnswer(string choice); // waliduje odpowiedz podana przez uzytkownia pod katem co wpisal uzytkownik, uzytkownik wprowadza stringa
// po czym rozwazany jest tylko pierwszy znak w ciagu. Jesli rowna sie a, b, c lub d, zwraca prawde
bool validateCorrectAnswer(Question question, string choice); // walidacja odpowiedzi pod katem jej poprawnosci z odpowiedzia pytania
void loadEasyQuestionBase(vector<Question>& questionsEasy); // wczytywanie bazy pytan
void loadMediumQuestionBase(vector<Question> &questionsMedium); //wczytywanie bazy pytan
void loadHardQuestionBase(vector<Question>& questionsHard); // wczytywanie bazy pytan
void askQuestion(vector<Question>& questionsList, int& points, bool &isGameOver); //funkcja zadajaca pytanie

// z bazy pytan nalezy usunac polskie znaki, mimo moich wypocin nie potrafilem zrobic aby kod wczytywal polskie znaki z bazy
// nalezy dodac jeszcze prosty mechanizm z pytaniem czy uczestnik chce kontynuowac gre czy odejsc z gry z suma niegwarantowana przed kolejnym pytaniem
// nalezy dodac jeszcze flage ktora bedzie aktywowana kiedy uczestnik przekroczy sume gwarantowana
// nalezy dodac jeszcze funckje kol pomocniczych.

int main()
{
    vector<Question> questionsEasy; // przykladowa lista (taka ulepszona tablica) gdzie beda dodawane pytania, ta lista ma lepsze metody przez co latwiej dodac nowe pytania, taka ala dynamiczna tablica dla klasy/struktur
    vector<Question> questionsMedium; // tu pytania srednie
    vector<Question> questionsHard; // tu pytania ciezkie
    Question tempQuestion = Question(); // zmienna tymczasowo sluzaca jako referencja do zapisu pytania do listy

    loadEasyQuestionBase(questionsEasy); //wczytywanie baz pytan
    loadMediumQuestionBase(questionsMedium);
    loadHardQuestionBase(questionsHard);
   /*
    cout << "EASY QUESTIONS" << endl;
    for (int i = 0; i < questionsEasy.size(); i++) { // wypisanie wszystkich pytan oraz odpowiedzi dla questionsEasy przeczytanych w pliku .txt
        questionsEasy.at(i).displayQuestion();      // zastosowanie tylko chwilowe by zobaczyc czy baza pytan sie wczytala
        cout << questionsEasy.at(i).getCorrectAnswer() << endl << endl;
    }
    cout << "MEDIUM QUESTIONS" << endl;
    for (int i = 0; i < questionsMedium.size(); i++) { // wypisanie wszystkich pytan oraz odpowiedzi dla questionsEasy przeczytanych w pliku .txt
        questionsMedium.at(i).displayQuestion();      // zastosowanie tylko chwilowe by zobaczyc czy baza pytan sie wczytala
        cout << questionsMedium.at(i).getCorrectAnswer() << endl << endl;
    }
    cout << "HARD QUESTIONS" << endl;
    for (int i = 0; i < questionsHard.size(); i++) { // wypisanie wszystkich pytan oraz odpowiedzi dla questionsEasy przeczytanych w pliku .txt
        questionsHard.at(i).displayQuestion();      // zastosowanie tylko chwilowe by zobaczyc czy baza pytan sie wczytala
        cout << questionsHard.at(i).getCorrectAnswer() << endl << endl;
    }
    */
    
    // ponizej przykladowy mechanizm zadawania pytania
    bool isGameOver = false;
    int points = 0;
    int random;
    while (!isGameOver) { // petla ktora zadaje pytania dopoki nie bedzie konca gry

        if (points < 2) {
            askQuestion(questionsEasy, points, isGameOver); // zadawanie pytania z latwej puli
        }
        else if (points < 10) {
            askQuestion(questionsMedium, points, isGameOver); // zadawanie pytania z sredniej puli
        }
        else {
            askQuestion(questionsHard, points, isGameOver); // zadawanie pytania z ciezkiej puli
        }
       
    }
    
    
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
void loadEasyQuestionBase(vector<Question>& questionsEasy) {
    Question tempQuestion = Question();
    fstream file1; //Przykladowy mechanizm czytania pytan z bazy pytan pliku tekstowego, czyta dopoki nie skonczy sie file
    file1.open("questionsEasy.txt", ios::in); // ta procedure trzeba powtorzyc zarowno dla questionsMedium jaki i questionsHard
    if (file1.good() == false)
    {
        cout << "Plik nie istnieje" << endl;
        exit(0);
    }
    string line;
    int lineNumber = 1;
    int i = 0;
    char tempChar;
    while (getline(file1, line))
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
        tempQuestion.setAsked(false);
        if (lineNumber == 6) {
            lineNumber = 0;
            questionsEasy.push_back(tempQuestion); // zapisanie/dodanie pytania do listy 
            i++;
        }
        lineNumber++;
    }
    file1.close();
}
void loadMediumQuestionBase(vector<Question>& questionsMedium) {
    Question tempQuestion = Question();
    fstream file1; //Przykladowy mechanizm czytania pytan z bazy pytan pliku tekstowego, czyta dopoki nie skonczy sie file
    file1.open("questionsMedium.txt", ios::in); // ta procedure trzeba powtorzyc zarowno dla questionsMedium jaki i questionsHard
    if (file1.good() == false)
    {
        cout << "Plik nie istnieje" << endl;
        exit(0);
    }
    string line;
    int lineNumber = 1;
    int i = 0;
    char tempChar;
    while (getline(file1, line))
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
        tempQuestion.setAsked(false);
        if (lineNumber == 6) {
            lineNumber = 0;
            questionsMedium.push_back(tempQuestion); // zapisanie/dodanie pytania do listy 
            i++;
        }
        lineNumber++;
    }
    file1.close();
}
void loadHardQuestionBase(vector<Question>& questionsHard) {
    Question tempQuestion = Question();
    fstream file1; //Przykladowy mechanizm czytania pytan z bazy pytan pliku tekstowego, czyta dopoki nie skonczy sie file
    file1.open("questionsHard.txt", ios::in); // ta procedure trzeba powtorzyc zarowno dla questionsMedium jaki i questionsHard
    if (file1.good() == false)
    {
        cout << "Plik nie istnieje" << endl;
        exit(0);
    }
    string line;
    int lineNumber = 1;
    int i = 0;
    char tempChar;
    while (getline(file1, line))
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
        tempQuestion.setAsked(false);
        if (lineNumber == 6) {
            lineNumber = 0;
            questionsHard.push_back(tempQuestion); // zapisanie/dodanie pytania do listy 
            i++;
        }
        lineNumber++;
    }
    file1.close();
}
void askQuestion(vector<Question> &questionsList, int &points, bool &isGameOver) { // funkcja zadawajaca pytania, walidujaca odpowiedz, all in one
    srand(time(NULL));
    string choice;
    int random;
    do {
        random = rand() % questionsList.size();
    } while (questionsList.at(random).isAlreadyAsked()); // sprawdza czy wylosowane pytanie sie nie powtorzylo

    questionsList.at(random).displayQuestion();
    do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
        cin >> choice;

    } while (!validateAnswer(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole

    //walidacja odpowidzi pod katem jej poprawnosci
    if (validateCorrectAnswer(questionsList.at(random), choice)) {
        cout << "Poprawna!" << endl;
        points++; // dodanie punktu 
        if (points == 12) isGameOver = true;
    }
    else {
        cout << "Niepoprawna" << endl;
        isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
    }

    questionsList.at(random).setAsked(true); // zaznacza ze pytanie zostalo juz wylosowane
    
    
        switch (points) { //wypisanie sumy jaka na chwile obecna posiada uzytkownik
        case 0:
            cout << "0zl" << endl;
            break;
        case 1:
            cout << "500zl" << endl;
            break;
        case 2:
            cout << "1000zl" << endl;
            break;
        case 3:
            cout << "2000zl" << endl;
            break;
        case 4:
            cout << "5000zl" << endl;
            break;
        case 5:
            cout << "10 000zl" << endl;
            break;
         case 6:
            cout << "20 000zl" << endl;
            break;
        case 7:
            cout << "40 000zl" << endl;
            break;
        case 8:
            cout << "75 000zl" << endl;
            break;
        case 9:
            cout << "125 000zl" << endl;
            break;
        case 10:
            cout << "250 000zl" << endl;
            break;
        case 11:
            cout << "500 000zl" << endl;
            break;
        case 12:
            cout << "1 000 000zl" << endl;
            break;
        }
        
       
    
    

}
