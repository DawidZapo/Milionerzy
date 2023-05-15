#include "Question.h"
#include <stdlib.h>
#include <iostream>
bool validateAnswer(string choice); // waliduje odpowiedz podana przez uzytkownia pod katem co wpisal uzytkownik, uzytkownik wprowadza stringa
// po czym rozwazany jest tylko pierwszy znak w ciagu. Jesli rowna sie a, b, c lub d, zwraca prawde
bool validateCorrectAnswer(Question question, string choice); // walidacja odpowiedzi pod katem jej poprawnosci z odpowiedzia pytania
bool validateHelp(string choice);
void loadEasyQuestionBase(vector<Question>& questionsEasy); // wczytywanie bazy pytan
void loadMediumQuestionBase(vector<Question> &questionsMedium); //wczytywanie bazy pytan
void loadHardQuestionBase(vector<Question>& questionsHard); // wczytywanie bazy pytan
void askQuestion(vector<Question>& questionsList, int& points, bool &isGameOver, string name,
    bool& isAskTheAudienceTaken, bool& isFiftyFiftyTaken, bool& isAnotherQuestionTaken); //funkcja zadajaca pytanie
string getPlayerName();
string getRandomCorrectMessage(string name);
void printHelloMessage();
bool validateKindOfHelp(string help, bool& isFiftyFiftyTaken, bool& isAskTheAudienceTaken, bool& isAnotherQuestionTaken);
void printRules(string name);
string getRandomIncorrectMessage(string name);
string getTheCurrentPrizeSum(int points);

// z bazy pytan nalezy usunac polskie znaki, mimo moich wypocin nie potrafilem zrobic aby kod wczytywal polskie znaki z bazy
// dodano 2/3 kola pomocnicze
// nalezy dodac jeszcze trzecie ostatnie kolo, ktore bedzie ponownie losowac pytanie dla uczestnika (gdzie help == "3" , wiersz: 445)
// nalezy dodac jeszcze flagi ktore beda oznaczac ktore kola uczestnik wykorzystal i ktore nie pozwola mu znowy wykorzystac pomocy

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
    printHelloMessage();
    string name = getPlayerName();
    system("cls");
    printRules(name);
    string anyLetter;
    cout << "Wcisnij jakikolwiek klawisz aby zaczac []!" << endl;
    cin >> anyLetter;
    system("cls");
    
    // ponizej przykladowy mechanizm zadawania pytania
    bool isAskTheAudienceTaken = false; // zmienna sluzace do zaznaczenia czy dana pomoc zostala juz udzielona podczas gry
    bool isFiftyFiftyTaken = false; // zmienna sluzace do zaznaczenia czy dana pomoc zostala juz udzielona podczas gry
    bool isAnotherQuestionTaken = false; // zmienna sluzace do zaznaczenia czy dana pomoc zostala juz udzielona podczas gry
    bool isGameOver = false;
    int points = 0;
    int random;
    while (!isGameOver) { // petla ktora zadaje pytania dopoki nie bedzie konca gry

        if (points < 2) {
            askQuestion(questionsEasy, points, isGameOver, name, isAskTheAudienceTaken, isFiftyFiftyTaken, isAnotherQuestionTaken); // zadawanie pytania z latwej puli
        }
        else if (points < 10) {
            askQuestion(questionsMedium, points, isGameOver, name, isAskTheAudienceTaken, isFiftyFiftyTaken, isAnotherQuestionTaken); // zadawanie pytania z sredniej puli
        }
        else {
            askQuestion(questionsHard, points, isGameOver, name, isAskTheAudienceTaken, isFiftyFiftyTaken, isAnotherQuestionTaken); // zadawanie pytania z ciezkiej puli
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
bool validateHelp(string choice) {
    choice = choice.substr(0, 1);
    if (choice == "T" || choice == "t") {
        return true;
    }
    else return false;
}
void askQuestion(vector<Question> &questionsList, int &points, bool &isGameOver, string name,
    bool& isAskTheAudienceTaken, bool& isFiftyFiftyTaken, bool& isAnotherQuestionTaken) { // funkcja zadawajaca pytania, walidujaca odpowiedz, all in one
    srand(time(NULL));
    string choice;
    int random;
    do {
        random = rand() % questionsList.size();
    } while (questionsList.at(random).isAlreadyAsked()); // sprawdza czy wylosowane pytanie sie nie powtorzylo

    questionsList.at(random).displayQuestion();

    if (!isFiftyFiftyTaken || !isAskTheAudienceTaken || !isAnotherQuestionTaken) {
        cout << "\nJesli chcesz skorzystac z kol ratunkowych, wcisnij [T], jesli nie [N] " << endl;
        cin >> choice;

        if (validateHelp(choice)) {
            string textHelp = (!isFiftyFiftyTaken) ? "[1] - 50/50\n" : "[1] - 50/50 [WYKORZYSTANE]\n";
            cout << textHelp;
            textHelp = (!isAskTheAudienceTaken) ? "[2] - Pytanie do publicznosci\n" : "[2] - Pytanie do publicznosc [WYKORZYSTANE]\n";
            cout << textHelp;
            textHelp = (!isAnotherQuestionTaken) ? "[3] - Ponowne losowanie pytania\n" : "[3] - Ponowne losowanie pytania [WYKORZYSTANE]\n";
            cout << textHelp;
            cout << "Wcisnij " << ((!isFiftyFiftyTaken) ? "[1] " : "[X] ") << ((!isAskTheAudienceTaken) ? "[2] " : "[X] ") <<
                ((!isAnotherQuestionTaken) ? "[3] " : "[X] ") << endl;
            
            string help;
            do {
                cin >> help;
            } while (validateKindOfHelp(help, isFiftyFiftyTaken, isAskTheAudienceTaken, isAnotherQuestionTaken));


            if (help == "1") {
                system("cls");
                questionsList.at(random).displayFiftyFiftyQuestion();
                cout << "\nPodaj swoja odpowiedz: " << endl;
                do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
                    cin >> choice;

                } while (!validateAnswer(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole

                //walidacja odpowidzi pod katem jej poprawnosci
                if (validateCorrectAnswer(questionsList.at(random), choice)) {
                    cout << getRandomCorrectMessage(name) << endl;
                    points++; // dodanie punktu 
                    cout << getTheCurrentPrizeSum(points) << endl;

                    if (points == 12) {
                        isGameOver = true;
                        cout << "Wygrales milion zlotych!" << endl;
                    }
                    cout << "Wcisnij jakikolwiek klawisz aby kontynuowac: []" << endl;
                    string anyLetter;
                    cin >> anyLetter;
                    system("cls");
                }
                else {
                    string prize;
                    if (points >= 7) {
                        prize = "40 000zl";
                    }
                    else if (points >= 2) {
                        prize = "1 000zl";
                    }
                    else {
                        prize = "0zl";
                    }
                    cout << getRandomIncorrectMessage(name) << endl;
                    cout << "Wygrywasz: " << prize << endl;
                    isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
                }
                isFiftyFiftyTaken = true; // zaznacza, ze kolo ratunkowe zostalo uzyte
                questionsList.at(random).setAsked(true); // zaznacza ze pytanie zostalo juz wylosowane    
            }
            else if(help == "2"){
                system("cls");
                questionsList.at(random).displayQuestion();
                questionsList.at(random).displayAskTheAudienceAnswers();

                cout << "\nPodaj swoja odpowiedz: [a] [b] [c] [d]" << endl;
                do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
                    cin >> choice;

                } while (!validateAnswer(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole

                //walidacja odpowidzi pod katem jej poprawnosci
                if (validateCorrectAnswer(questionsList.at(random), choice)) {
                    cout << getRandomCorrectMessage(name) << endl;
                    points++; // dodanie punktu 
                    cout << getTheCurrentPrizeSum(points) << endl;
                    if (points == 12) {
                        cout << "Wygrales milion zlotych!" << endl;
                        isGameOver = true;
                    }
                    cout << "Wcisnij jakikolwiek klawisz aby kontynuowac: []" << endl;
                    string anyLetter;
                    cin >> anyLetter;
                    system("cls");
                }
                else {
                    string prize;
                    if (points >= 7) {
                        prize = "40 000zl";
                    }
                    else if (points >= 2) {
                        prize = "1 000zl";
                    }
                    else {
                        prize = "0zl";
                    }
                    cout << getRandomIncorrectMessage(name) << endl;
                    cout << "Wygrywasz: " << prize << endl;
                    isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
                }
                isAskTheAudienceTaken = true;
                questionsList.at(random).setAsked(true); // zaznacza ze pytanie zostalo juz wylosowane 
            }
            else if (help == "3") {
                system("cls");
                questionsList.at(random).setAsked(true); // zaznacza ze pytanie zostalo juz wylosowane 
                int anotherRandom = rand() % (questionsList.size());

                questionsList.at(anotherRandom).displayQuestion();
               
                cout << "\nPodaj swoja odpowiedz: [a] [b] [c] [d]" << endl;
                do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
                    cin >> choice;

                } while (!validateAnswer(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole

                //walidacja odpowidzi pod katem jej poprawnosci
                if (validateCorrectAnswer(questionsList.at(anotherRandom), choice)) {
                    cout << getRandomCorrectMessage(name) << endl;
                    points++; // dodanie punktu 
                    cout << getTheCurrentPrizeSum(points) << endl;
                    if (points == 12) {
                        cout << "Wygrales milion zlotych!" << endl;
                        isGameOver = true;
                    }
                    cout << "Wcisnij jakikolwiek klawisz aby kontynuowac: []" << endl;
                    string anyLetter;
                    cin >> anyLetter;
                    system("cls");
                }
                else {
                    string prize;
                    if (points >= 7) {
                        prize = "40 000zl";
                    }
                    else if (points >= 2) {
                        prize = "1 000zl";
                    }
                    else {
                        prize = "0zl";
                    }
                    cout << getRandomIncorrectMessage(name) << endl;
                    cout << "Wygrywasz: " << prize << endl;
                    isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
                }
                isAnotherQuestionTaken = true;
                questionsList.at(anotherRandom).setAsked(true);
            }
            else {
                cout << "Error" << endl;
            }


        }
        else {
        system("cls");
        questionsList.at(random).displayQuestion();
        cout << "\nPodaj swoja odpowiedz: [a] [b] [c] [d]" << endl;
        do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
            cin >> choice;

        } while (!validateAnswer(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole

        //walidacja odpowidzi pod katem jej poprawnosci
        if (validateCorrectAnswer(questionsList.at(random), choice)) {
            cout << getRandomCorrectMessage(name) << endl;
            points++; // dodanie punktu 
            cout << getTheCurrentPrizeSum(points) << endl;
            cout << "\n";
            if (points == 12) {
                cout << "Wygrales milion zlotych!" << endl;
                isGameOver = true;
            }
            cout << "Wcisnij jakikolwiek klawisz aby kontynuowac: []" << endl;
            string anyLetter;
            cin >> anyLetter;
            system("cls");
        }
        else {
            string prize;
            if (points >= 7) {
                prize = "40 000zl";
            }
            else if (points >= 2) {
                prize = "1 000zl";
            }
            else {
                prize = "0zl";
            }
            cout << getRandomIncorrectMessage(name) << endl;
            cout << "Wygrywasz: " << prize << endl;
            isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
        }
        questionsList.at(random).setAsked(true); // zaznacza ze pytanie zostalo juz wylosowane  
}
    }
    else {
    system("cls");
    questionsList.at(random).displayQuestion();
    cout << "\nPodaj swoja odpowiedz: [a] [b] [c] [d]" << endl;
    do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
        cin >> choice;

    } while (!validateAnswer(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole

    //walidacja odpowidzi pod katem jej poprawnosci
    if (validateCorrectAnswer(questionsList.at(random), choice)) {
        cout << getRandomCorrectMessage(name) << endl;
        points++; // dodanie punktu 
        cout << getTheCurrentPrizeSum(points) << endl;
        cout << "\n";
        if (points == 12) {
            cout << "Wygrales milion zlotych!" << endl;
            isGameOver = true;
        }
        cout << "Wcisnij jakikolwiek klawisz aby kontynuowac: []" << endl;
        string anyLetter;
        cin >> anyLetter;
        system("cls");
    }
    else {
        string prize;
        if (points >= 7) {
            prize = "40 000zl";
        }
        else if (points >= 2) {
            prize = "1 000zl";
        }
        else {
            prize = "0zl";
        }
        cout << getRandomIncorrectMessage(name) << endl;
        cout << "Wygrywasz: " << prize << endl;
        isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
    }
    questionsList.at(random).setAsked(true); // zaznacza ze pytanie zostalo juz wylosowane  
    }
    






    /*
    cout << "\nJesli chcesz skorzystac z kol ratunkowych, wcisnij [T], jesli nie [N] " << endl;
    cin >> choice;
    
    if (validateHelp(choice)) {
        cout << "Wcisnij: [1] [2] [3] " << endl;
        cout << "1 - 50/50\n2 - Pytanie do publicznosci\n3 - Ponowne losowanie pytania" << endl;
        string help;
        do {
            cin >> help;
        } while (validateKindOfHelp(help));
        
        if (help == "1") {
            system("cls");
            questionsList.at(random).displayFiftyFiftyQuestion();
            cout << "\nPodaj swoja odpowiedz: " << endl;
            do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
                cin >> choice;

            } while (!validateAnswer(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole

            //walidacja odpowidzi pod katem jej poprawnosci
            if (validateCorrectAnswer(questionsList.at(random), choice)) {
                cout << getRandomCorrectMessage(name) << endl;
                points++; // dodanie punktu 
                switch (points) { //wypisanie sumy jaka na chwile obecna posiada uzytkownik
                case 0:
                    cout << "Obecnie posiadasz: ";
                    cout << "0zl" << endl;
                    break;
                case 1:
                    cout << "Obecnie posiadasz: ";
                    cout << "500zl" << endl;
                    break;
                case 2:
                    cout << "Obecnie posiadasz: ";
                    cout << "1000zl" << endl;
                    break;
                case 3:
                    cout << "Obecnie posiadasz: ";
                    cout << "2000zl" << endl;
                    break;
                case 4:
                    cout << "Obecnie posiadasz: ";
                    cout << "5000zl" << endl;
                    break;
                case 5:
                    cout << "Obecnie posiadasz: ";
                    cout << "10 000zl" << endl;
                    break;
                case 6:
                    cout << "Obecnie posiadasz: ";
                    cout << "20 000zl" << endl;
                    break;
                case 7:
                    cout << "Obecnie posiadasz: ";
                    cout << "40 000zl" << endl;
                    break;
                case 8:
                    cout << "Obecnie posiadasz: ";
                    cout << "75 000zl" << endl;
                    break;
                case 9:
                    cout << "Obecnie posiadasz: ";
                    cout << "125 000zl" << endl;
                    break;
                case 10:
                    cout << "Obecnie posiadasz: ";
                    cout << "250 000zl" << endl;
                    break;
                case 11:
                    cout << "Obecnie posiadasz: ";
                    cout << "500 000zl" << endl;
                    break;
                case 12:
                    cout << "Obecnie posiadasz: ";
                    cout << "1 000 000zl" << endl;
                    break;
                }
                if (points == 12) isGameOver = true;
                cout << "Wcisnij jakikolwiek klawisz aby kontynuowac: []" << endl;
                string anyLetter;
                cin >> anyLetter;
                system("cls");
            }
            else {
                string prize;
                if (points >= 7) {
                    prize = "40 000zl";
                }
                else if (points >= 2) {
                    prize = "1 000zl";
                }
                else {
                    prize = "0zl";
                }
                cout << getRandomIncorrectMessage(name) << endl;
                cout << "Wygrywasz: " << prize << endl;
                isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
            }

            questionsList.at(random).setAsked(true); // zaznacza ze pytanie zostalo juz wylosowane    
        }
        else if (help == "2") {
            system("cls");
            questionsList.at(random).displayQuestion();
            questionsList.at(random).displayAskTheAudienceAnswers();

            cout << "\nPodaj swoja odpowiedz: [a] [b] [c] [d]" << endl;
            do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
                cin >> choice;

            } while (!validateAnswer(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole

            //walidacja odpowidzi pod katem jej poprawnosci
            if (validateCorrectAnswer(questionsList.at(random), choice)) {
                cout << getRandomCorrectMessage(name) << endl;
                points++; // dodanie punktu 
                switch (points) { //wypisanie sumy jaka na chwile obecna posiada uzytkownik
                case 0:
                    cout << "Obecnie posiadasz: ";
                    cout << "0zl" << endl;
                    break;
                case 1:
                    cout << "Obecnie posiadasz: ";
                    cout << "500zl" << endl;
                    break;
                case 2:
                    cout << "Obecnie posiadasz: ";
                    cout << "1000zl" << endl;
                    break;
                case 3:
                    cout << "Obecnie posiadasz: ";
                    cout << "2000zl" << endl;
                    break;
                case 4:
                    cout << "Obecnie posiadasz: ";
                    cout << "5000zl" << endl;
                    break;
                case 5:
                    cout << "Obecnie posiadasz: ";
                    cout << "10 000zl" << endl;
                    break;
                case 6:
                    cout << "Obecnie posiadasz: ";
                    cout << "20 000zl" << endl;
                    break;
                case 7:
                    cout << "Obecnie posiadasz: ";
                    cout << "40 000zl" << endl;
                    break;
                case 8:
                    cout << "Obecnie posiadasz: ";
                    cout << "75 000zl" << endl;
                    break;
                case 9:
                    cout << "Obecnie posiadasz: ";
                    cout << "125 000zl" << endl;
                    break;
                case 10:
                    cout << "Obecnie posiadasz: ";
                    cout << "250 000zl" << endl;
                    break;
                case 11:
                    cout << "Obecnie posiadasz: ";
                    cout << "500 000zl" << endl;
                    break;
                case 12:
                    cout << "Obecnie posiadasz: ";
                    cout << "1 000 000zl" << endl;
                    break;
                }
                if (points == 12) isGameOver = true;
                cout << "Wcisnij jakikolwiek klawisz aby kontynuowac: []" << endl;
                string anyLetter;
                cin >> anyLetter;
                system("cls");
            }
            else {
                string prize;
                if (points >= 7) {
                    prize = "40 000zl";
                }
                else if (points >= 2) {
                    prize = "1 000zl";
                }
                else {
                    prize = "0zl";
                }
                cout << getRandomIncorrectMessage(name) << endl;
                cout << "Wygrywasz: " << prize << endl;
                isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
            }
            questionsList.at(random).setAsked(true); // zaznacza ze pytanie zostalo juz wylosowane    


        }
        else if (help == "3") {

        }
        else {
            cout << "Error, help not found";
        }
        
    }
    else {
        system("cls");
        questionsList.at(random).displayQuestion();
        cout << "\nPodaj swoja odpowiedz: [a] [b] [c] [d]" << endl;
        do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
            cin >> choice;

        } while (!validateAnswer(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole

        //walidacja odpowidzi pod katem jej poprawnosci
        if (validateCorrectAnswer(questionsList.at(random), choice)) {
            cout << getRandomCorrectMessage(name) << endl;
            points++; // dodanie punktu 
            switch (points) { //wypisanie sumy jaka na chwile obecna posiada uzytkownik
            case 0:
                cout << "Obecnie posiadasz: ";
                cout << "0zl" << endl;
                break;
            case 1:
                cout << "Obecnie posiadasz: ";
                cout << "500zl" << endl;
                break;
            case 2:
                cout << "Obecnie posiadasz: ";
                cout << "1000zl" << endl;
                break;
            case 3:
                cout << "Obecnie posiadasz: ";
                cout << "2000zl" << endl;
                break;
            case 4:
                cout << "Obecnie posiadasz: ";
                cout << "5000zl" << endl;
                break;
            case 5:
                cout << "Obecnie posiadasz: ";
                cout << "10 000zl" << endl;
                break;
            case 6:
                cout << "Obecnie posiadasz: ";
                cout << "20 000zl" << endl;
                break;
            case 7:
                cout << "Obecnie posiadasz: ";
                cout << "40 000zl" << endl;
                break;
            case 8:
                cout << "Obecnie posiadasz: ";
                cout << "75 000zl" << endl;
                break;
            case 9:
                cout << "Obecnie posiadasz: ";
                cout << "125 000zl" << endl;
                break;
            case 10:
                cout << "Obecnie posiadasz: ";
                cout << "250 000zl" << endl;
                break;
            case 11:
                cout << "Obecnie posiadasz: ";
                cout << "500 000zl" << endl;
                break;
            case 12:
                cout << "Obecnie posiadasz: ";
                cout << "1 000 000zl" << endl;
                break;
            }
            cout << "\n";
            if (points == 12) isGameOver = true;
            cout << "Wcisnij jakikolwiek klawisz aby kontynuowac: []" << endl;
            string anyLetter;
            cin >> anyLetter;
            system("cls");
        }
        else {
            string prize;
            if (points >= 7) {
                prize = "40 000zl";
            }
            else if (points >= 2) {
                prize = "1 000zl";
            }
            else {
                prize = "0zl";
            }
            cout << getRandomIncorrectMessage(name) << endl;
            cout << "Wygrywasz: " << prize << endl;
            isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
        }
        questionsList.at(random).setAsked(true); // zaznacza ze pytanie zostalo juz wylosowane    
    }
    */
    

}
string getPlayerName() {
    string name;
    cout << "Podaj swoje imie: ";
    cin >> name;
    return name;
}
void printRules(string name) {
    cout << "Witaj " << name << " w grze milionerzy!" << endl << endl;
    cout << "Podczas gry bedziesz mial do dyspozycji 3 kola ratunkowe:\n\n1)50/50\n2)Pytanie do publicznosci\n3)Ponowne losowanie pytania\n\n";
  
}
string getRandomCorrectMessage(string name) {
    srand(time(NULL));
    int number = rand() % 7;
    switch (number) {
    case 0:
         return "Niestety jest to czas na przerwe, wracamy do was za pare minut!\n[...]\nWitam was tu Huber Urbanski Milionerzy, " + name + " jest to poprawna odpowiedz!";
         break;
    case 1:
        return "To jest prawidlowa odpowiedz!";
        break;
    case 2:
        return name + " ... to jest prawidlowa odpowiedz!";
        break;
    case 3:
        return "Niestety, " + name + ", ale gramy dalej!";
        break;
    case 4:
        return "Zgadza sie " + name + " to jest prawidlowa odpowiedz!";
        break;
    case 5:
        return "Jest to wlasciwa odpowiedz, gratulacje!";
        break;
    case 6:
        return "Gratulacja! Prawidlowa odpowiedz";
        break;
    default:
        return "Poprawna odpowiedz!";
    }
}
string getRandomIncorrectMessage(string name) {
    srand(time(NULL));
    int number = rand() % 3;
    switch (number) {
    case 0:
        return "Niestety " + name + " ale jest to nieprawidlowa odpowiedz...";
        break;
    case 1:
        return "Bardzo mi przykro " + name + " ale to nie jest wlasciwa odpowiedz...";
        break;
    case 2:
        return "Twoja odpowiedz niestety nie jest poprawna....";
        break;
    default:
        return "Niestety jest to bledna odpowiedz";
        break;
    }
}
void printHelloMessage() {
    cout << "----------------- Milionerzy -----------------" << endl;
    cout << "---------------- Wtiaj w grze ----------------" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "------- Dawid Zapotoczny & Krystian Rys ------" << endl;
    cout << "----------------------------------------------" << endl;
}
bool validateKindOfHelp(string help, bool& isFiftyFiftyTaken, bool& isAskTheAudienceTaken, bool& isAnotherQuestionTaken) {
    help = help.substr(0, 1);
    if (help == "1" || help == "2" || help == "3") {
        if (help == "1" && !isFiftyFiftyTaken) {
            return false;
        }
        else if (help == "2" && !isAskTheAudienceTaken) {
            return false;
        }
        else if (help == "3" && !isAnotherQuestionTaken) {
            return false;
        }
        else {
            cout << "Te kolo ratunkowe zostalo juz uzyte" << endl;
            return true;
        }
    }
    else return true;
}
string getTheCurrentPrizeSum(int points) {
    string text = "Obecnie posiadasz ";
    switch (points) { //wypisanie sumy jaka na chwile obecna posiada uzytkownik
    case 0:
        return text + "0zl";
        break;
    case 1:
        return text + "500zl";
        break;
    case 2:
        return text + "1 000zl";
        break;
    case 3:
        return text + "2 000zl";
        break;
    case 4:
        return text + "5 000zl";
        break;
    case 5:
        return text + "10 000zl";
        break;
    case 6:
        return text + "20 000zl";
        break;
    case 7:
        return text + "40 000zl";
        break;
    case 8:
        return text + "75 000zl";
        break;
    case 9:
        return text + "125 000zl";
        break;
    case 10:
        return text + "250 000zl";
        break;
    case 11:
        return text + "500 000zl";
        break;
    case 12:
        return text + "1000 000zl";
        break;
    }
}