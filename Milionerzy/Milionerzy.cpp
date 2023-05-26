#include "Question.h"
#include <iostream>
bool validateChoice(string choice); // waliduje odpowiedz podana przez uzytkownia pod katem co wpisal uzytkownik, uzytkownik wprowadza stringa
// po czym rozwazany jest tylko pierwszy znak w ciagu. Jesli rowna sie a, b, c lub d, zwraca prawde
bool validateChoice(string choice, bool& isFiftyFiftyTaken, bool& isAskTheAudienceTaken, bool& isAnotherQuestionTaken, bool& isPhoneToFriendTaken);
bool validateCorrectAnswer(Question question, string choice); // walidacja odpowiedzi pod katem jej poprawnosci z odpowiedzia pytania
bool validateHelp(string choice);
void loadEasyQuestionBase(vector<Question>& questionsEasy); // wczytywanie bazy pytan
void loadMediumQuestionBase(vector<Question> &questionsMedium); //wczytywanie bazy pytan
void loadHardQuestionBase(vector<Question>& questionsHard); // wczytywanie bazy pytan
void writeYourOwnYestions(); //walidacja odpowiedzi jakie pytanie chce zadan uczestnik
void writeQuestionToFile(string choice); //wpisuje pytanie do odpowiedniego pliku z pytaniami na bazie jego decyzji
void askQuestion(vector<Question>& questionsList, int& points, bool &isGameOver, string name,
    bool& isAskTheAudienceTaken, bool& isFiftyFiftyTaken, bool& isAnotherQuestionTaken,bool& isPhoneToFriendTaken); //funkcja zadajaca pytanie
string getPlayerName();
string getRandomCorrectMessage(string name);
void printHelloMessage();
bool validateKindOfHelp(string help, bool& isFiftyFiftyTaken, bool& isAskTheAudienceTaken, bool& isAnotherQuestionTaken,bool &isPhoneToFriendTaken);
void printRules(string name);
string getRandomIncorrectMessage(string name);
string getTheCurrentPrizeSum(int points);

// z bazy pytan nalezy usunac polskie znaki, mimo moich wypocin nie potrafilem zrobic aby kod wczytywal polskie znaki z bazy
// dodano 3/3 kola pomocnicze
// mozna dodac jedynie zmiany kosmetyczne, aplikacja jest juz grywalna

int main()
{
    bool play = true;
    vector<Question> questionsEasy; // przykladowa lista (taka ulepszona tablica) gdzie beda dodawane pytania, ta lista ma lepsze metody przez co latwiej dodac nowe pytania, taka ala dynamiczna tablica dla klasy/struktur
    vector<Question> questionsMedium; // tu pytania srednie
    vector<Question> questionsHard; // tu pytania ciezkie
    Question tempQuestion = Question(); // zmienna tymczasowo sluzaca jako referencja do zapisu pytania do listy
    printHelloMessage();
    string name = getPlayerName();
    string choice;
    system("cls");
    cout << "Czy chcesz dodac swoje autorskie pytania?\nWprowadz: [T] lub [N]\n";
    do {
        getline(cin, choice);
        choice = choice.substr(0, 1);
    } while (choice != "T" && choice != "t" && choice != "n" && choice != "N");

    if (choice == "t" || choice == "T") writeYourOwnYestions();

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
    
    while (play)
    {

        system("cls");
        printRules(name);
        string anyLetter;
        cout << "Wcisnij jakikolwiek klawisz i zatwierdz enterem aby zaczac []!" << endl;
        cin >> anyLetter;
        system("cls");

        // ponizej przykladowy mechanizm zadawania pytania
        bool isAskTheAudienceTaken = false; // zmienna sluzace do zaznaczenia czy dana pomoc zostala juz udzielona podczas gry
        bool isFiftyFiftyTaken = false; // zmienna sluzace do zaznaczenia czy dana pomoc zostala juz udzielona podczas gry
        bool isAnotherQuestionTaken = false; // zmienna sluzace do zaznaczenia czy dana pomoc zostala juz udzielona podczas gry
        bool isPhoneToFriendTaken = false; // zmienna sluzaca do zaznaczania czy dana pomoc zostala juz udzielona podczas gry
        bool isGameOver = false;
        int points = 0;

        while (!isGameOver) { // petla ktora zadaje pytania dopoki nie bedzie konca gry

            if (points < 2) {
                askQuestion(questionsEasy, points, isGameOver, name, isAskTheAudienceTaken, isFiftyFiftyTaken, isAnotherQuestionTaken, isPhoneToFriendTaken); // zadawanie pytania z latwej puli
            }
            else if (points < 10) {
                askQuestion(questionsMedium, points, isGameOver, name, isAskTheAudienceTaken, isFiftyFiftyTaken, isAnotherQuestionTaken, isPhoneToFriendTaken); // zadawanie pytania z sredniej puli
            }
            else {
                askQuestion(questionsHard, points, isGameOver, name, isAskTheAudienceTaken, isFiftyFiftyTaken, isAnotherQuestionTaken, isPhoneToFriendTaken); // zadawanie pytania z ciezkiej puli
            }

        }
        string letter;
        cout << "Jesli chcesz rozpoczac gre jeszcze raz wciscnij [T] jesli nie wcisnij [N] i zatwierdz enterem" << endl;
        do
        {
            getline(cin, letter);
            letter = letter.substr(0, 1);
        } while (letter != "T" && letter != "t" && letter != "n" && letter != "N");
        
            
        system("cls");
        if (letter == "t" || letter == "T")
        {
            
            for (int i = 0; questionsEasy.size()>i; i++)
            {
                questionsEasy[i].setAsked(false);
            }
            for (int i = 0; questionsMedium.size()>i; i++)
            {
                questionsMedium[i].setAsked(false);
            }
            for (int i = 0; questionsHard.size()>i; i++)
            {
                questionsHard[i].setAsked(false);
            }
            
        }
        else {
            play = false;
        }
        
        
    }
}
    

bool validateChoice(string choice) {
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
    bool& isAskTheAudienceTaken, bool& isFiftyFiftyTaken, bool& isAnotherQuestionTaken,bool& isPhoneToFriendTaken) { // funkcja zadawajaca pytania, walidujaca odpowiedz, all in one
    srand(time(NULL));
    string choice;
    int random;
    do {
        random = rand() % questionsList.size();
    } while (questionsList.at(random).isAlreadyAsked()); // sprawdza czy wylosowane pytanie sie nie powtorzylo

    questionsList.at(random).displayQuestion();

    cout << "Wcisnij: [a] [b] [c] [d]" << endl;
    
    if (!isFiftyFiftyTaken || !isAskTheAudienceTaken || !isAnotherQuestionTaken || !isPhoneToFriendTaken) {
        cout << "Albo:" << endl;
        cout << ((!isFiftyFiftyTaken) ? "[1] - 50/50 " : "[X] - 50/50 [WYKORZYSTANE] ") << endl <<
            ((!isAskTheAudienceTaken) ? "[2] - Pytanie do publicznosci " : "[X] - Pytanie do publicznosci [WYKORZYSTANE] ") << endl <<
            ((!isAnotherQuestionTaken) ? "[3] - Ponowne losowanie pytania " : "[X] - Ponowne losowanie pytania [WYKORZYSTANE] ") << endl <<
            ((!isPhoneToFriendTaken) ? "[4] - Telefon do przyjaciela " : "[X] - Telefon do przyjaciela[WYKORZYSTANE]") << endl;
    }
    
    
    do {
        cin >> choice;
    } while (validateChoice(choice, isFiftyFiftyTaken, isAskTheAudienceTaken, isAnotherQuestionTaken,isPhoneToFriendTaken));
    
    choice = choice.substr(0, 1);
    
    if (choice == "1") {
        system("cls");
        questionsList.at(random).displayFiftyFiftyQuestion();
        cout << "\nPodaj swoja odpowiedz: " << endl;
        do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
            cin >> choice;

        } while (!validateChoice(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole

        //walidacja odpowidzi pod katem jej poprawnosci
        if (validateCorrectAnswer(questionsList.at(random), choice)) {
            cout << getRandomCorrectMessage(name) << endl;
            points++; // dodanie punktu 
            cout << getTheCurrentPrizeSum(points) << endl;

            if (points == 12) {
                isGameOver = true;
                cout << "Wygrales milion zlotych!" << endl;
            }
            cout << "Wcisnij jakikolwiek klawisz i zatwierdz enterem aby kontynuowac: []" << endl;
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
            cout << "Prawidlowa odpowiedzia jest: " << questionsList.at(random).getCorrectAnswer() << endl;
            cout << "Wygrywasz: " << prize << endl;
            isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
        }
        isFiftyFiftyTaken = true; // zaznacza, ze kolo ratunkowe zostalo uzyte
        questionsList.at(random).setAsked(true); // zaznacza ze pytanie zostalo juz wylosowane 
    }
    else if (choice == "2") {
        system("cls");
        questionsList.at(random).displayQuestion();
        questionsList.at(random).displayAskTheAudienceAnswers();

        cout << "\nPodaj swoja odpowiedz: [a] [b] [c] [d]" << endl;
        do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
            cin >> choice;

        } while (!validateChoice(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole

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
            cout << "Prawidlowa odpowiedzia jest: " << questionsList.at(random).getCorrectAnswer() << endl;
            cout << "Wygrywasz: " << prize << endl;
            isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
        }
        isAskTheAudienceTaken = true;
        questionsList.at(random).setAsked(true); // zaznacza ze pytanie zostalo juz wylosowane 
    }
    else if (choice == "3") {
        system("cls");
        questionsList.at(random).setAsked(true); // zaznacza ze pytanie zostalo juz wylosowane 
        int anotherRandom = rand() % (questionsList.size());

        questionsList.at(anotherRandom).displayQuestion();

        cout << "\nPodaj swoja odpowiedz: [a] [b] [c] [d]" << endl;
        do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
            cin >> choice;

        } while (!validateChoice(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole

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
            cout << "Prawidlowa odpowiedzia jest: " << questionsList.at(anotherRandom).getCorrectAnswer() << endl;
            cout << "Wygrywasz: " << prize << endl;
            isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
        }
        isAnotherQuestionTaken = true;
        questionsList.at(anotherRandom).setAsked(true);
    }
    else if (choice == "4") {
        system("cls");
        questionsList.at(random).displayQuestion();
        questionsList.at(random).displayPhoneToFriend();
        cout << "\nPodaj swoja odpowiedz: " << endl;
        do { // pobieranie odpowiedzi przez uzytkownika, docelowo mozna zamknac to w funkcji 
            cin >> choice;

        } while (!validateChoice(choice)); // walidacja odpowiedzi przez uzytkownika pod katem co uzytkownik wpisal w konsole
        //walidacja odpowidzi pod katem jej poprawnosci
        if (validateCorrectAnswer(questionsList.at(random), choice)) {
            cout << getRandomCorrectMessage(name) << endl;
            points++; // dodanie punktu 
            cout << getTheCurrentPrizeSum(points) << endl;

            if (points == 12) {
            isGameOver = true;
            cout << "Wygrales milion zlotych!" << endl;
            }
        cout << "Wcisnij jakikolwiek klawisz i zatwierdz enterem aby kontynuowac: []" << endl;
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
            cout << "Prawidlową odpowiedzia jest: " << questionsList.at(random).getCorrectAnswer() << endl;
            cout << "Wygrywasz: " << prize << endl;
            isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
        }
        isPhoneToFriendTaken = true;
        questionsList.at(random).setAsked(true);

    }
    else {
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
        cout << "Prawidlowa odpowiedzia jest: " << questionsList.at(random).getCorrectAnswer() << endl;
        cout << "Wygrywasz: " << prize << endl;
        isGameOver = true; // wyjscie z gry poprzez niepoprawna odpowiedz
    }
        questionsList.at(random).setAsked(true); // zaznacza ze pytanie zostalo juz wylosowane  
    }
    
    //ponizej stary mechanizm,
    /*
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
    cout << "Podczas gry bedziesz mial do dyspozycji 4 kola ratunkowe:\n\n1)50/50\n2)Pytanie do publicznosci\n3)Ponowne losowanie pytania\n4)Telefon do przyjaciela\n\n";
  
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
bool validateKindOfHelp(string help, bool& isFiftyFiftyTaken, bool& isAskTheAudienceTaken, bool& isAnotherQuestionTaken,bool& isPhoneToFriendTaken) {
    help = help.substr(0, 1);
    if (help == "1" || help == "2" || help == "3" || help == "4" ){
        if (help == "1" && !isFiftyFiftyTaken) {
            return false;
        }
        else if (help == "2" && !isAskTheAudienceTaken) {
            return false;
        }
        else if (help == "3" && !isAnotherQuestionTaken) {
            return false;
        }
        else if (help == "4" && !isPhoneToFriendTaken)
        {
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
    default:
        return "ERROR";
        break;
    }
}
bool validateChoice(string choice, bool& isFiftyFiftyTaken, bool& isAskTheAudienceTaken, bool& isAnotherQuestionTaken, bool& isPhoneToFriendTaken) {
    choice = choice.substr(0, 1);
    
    if (choice == "1" || choice == "2" || choice == "3" || choice == "4") {
        if (choice == "1" && !isFiftyFiftyTaken) {
            return false;
        }
        else if (choice == "2" && !isAskTheAudienceTaken) {
            return false;
        }
        else if (choice == "3" && !isAnotherQuestionTaken) {
            return false;
        }
        else if (choice == "4" && !isPhoneToFriendTaken)
        {
            return false;
        }
        else {
            cout << "Te kolo ratunkowe zostalo juz uzyte" << endl;
            return true;
        }
    }
    else if (choice == "A" || choice == "B" || choice == "C" || choice == "D" || choice == "a" || choice == "b" || choice == "c" || choice == "d") {
        return false;
    }
    else {
        cout << "Wcisnij: [a] [b] [c] [d]" << endl;
        cout << "Albo:" << endl;
        cout << ((!isFiftyFiftyTaken) ? "[1] - 50/50 " : "[X] - 50/50 [WYKORZYSTANE] ") << endl <<
            ((!isAskTheAudienceTaken) ? "[2] - Pytanie do publicznosci " : "[X] - Pytanie do publicznosci [WYKORZYSTANE] ") << endl <<
            ((!isAnotherQuestionTaken) ? "[3] - Ponowne losowanie pytania " : "[X] - Ponowne losowanie pytania [WYKORZYSTANE] ") << endl <<
            ((!isPhoneToFriendTaken) ? "[4] - Telefon do przyjaciela " : "[X] - Telefon do przyjaciela [WYKORZYSTANE]") << endl;
        return true;
    }
}
void writeYourOwnYestions() {
    
    system("cls");
    string choice;
    string anotherChoice;
    
    do {
        system("cls");
        cout << "Jak bardzo trudne pytanie chcesz dopisac?\nWcisnij:\n[1] - Latwe\n[2] - Srednie\n[3] - Trudne\n";
        do {
            getline(cin, choice);
            choice = choice.substr(0, 1);
        } while (choice != "1" && choice != "2" && choice != "3");
        writeQuestionToFile(choice);

        cout << "Czy chcesz dodac kolejne pytanie? [T] [N]\n";
        getline(cin, anotherChoice);
        anotherChoice = anotherChoice.substr(0, 1);
    } while (anotherChoice == "T" || anotherChoice == "t");
}
void writeQuestionToFile(string choice) {
    string fileName;
    if (choice == "3") fileName = "questionsHard.txt";
    else if (choice == "2") fileName = "questionsMedium.txt";
    else fileName = "questionsEasy.txt";

    fstream file;
    file.open(fileName, ios::in);
    string line;
    bool insertEnter = false;

    // ponizej mechanizm sprawdza czy trzeba dodac znak nowej linii w celu poprawnego zapisu pliku .txt
    if (file.good() == false) {
        cout << "ERROR";
    }
    else {
        while (getline(file, line)) {

        }
        cout << line << endl;
        if (line[0] == 'A' || line[0] == 'B' || line[0] == 'C' || line[0] == 'D') insertEnter = true;
        else insertEnter = false;
    }

    file.close();

    //ponizej funkcja wypisujaca pytanie do odpowiedniego pliku .txt
    file.open(fileName, ios::app);
    string content;
    string answer;
    string correctAnswer;
    
    if (file.good() == false) {
        cout << "ERROR" << endl;
    }
    else {
        if (insertEnter) file << "\n";
        cout << "Wprowadz tresc pytania: \n";
        getline(cin, content);
        file << content << endl;

        cout << "Wprowadz mozliwa odpowiedz [1/4 - A]: \n";
        getline(cin, answer);
        file << answer << endl;

        cout << "Wprowadz mozliwa odpowiedz [2/4 - B]: \n";
        getline(cin, answer);
        file << answer << endl;

        cout << "Wprowadz mozliwa odpowiedz [3/4 - C]: \n";
        getline(cin, answer);
        file << answer << endl;

        cout << "Wprowadz mozliwa odpowiedz [4/4 - D]: \n";
        getline(cin, answer);
        file << answer << endl;

        cout << "Wprowadz poprawna odpowiedz [A] [B] [C] [D]: \n";
        getline(cin, correctAnswer);
        correctAnswer = correctAnswer.substr(0, 1);
        correctAnswer = toupper(correctAnswer[0]);

        file << correctAnswer << endl;

        cout << "Pytanie zostalo poprawnie dodane!\n";
    }

    file.close();
}
