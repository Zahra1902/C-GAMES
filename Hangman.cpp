#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class SecretWord {
private:
    vector<string> secretWords;
    string word;
    string state;

public:
    SecretWord();
    bool isCorrectGuess(char guess);
    void updateState(char guess);
    string getState();
    string getWord();
    string getHint();
    bool isComplete();
};

SecretWord::SecretWord() {
    secretWords = {"espresso", "latte", "americano", "cappuccino", "mocha"};
    srand(time(0));
    int random_index = rand() % secretWords.size();
    word = secretWords[random_index];
    state = string(word.length(), '-');
}

bool SecretWord::isCorrectGuess(char guess) {
    return word.find(guess) != string::npos;
}

void SecretWord::updateState(char guess) {
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == guess) {
            state[i] = guess;
        }
    }
}

string SecretWord::getState() {
    return state;
}

string SecretWord::getWord() {
    return word;
}

string SecretWord::getHint() {
    return "The word is a type of coffee.";
}

bool SecretWord::isComplete() {
    return state == word;
}

class HangmanGame: public SecretWord
{
private:
    SecretWord* secretWord;
    int guessesLeft;
    vector<string> hangmanImage;
    string hint;

public:
    HangmanGame();
    ~HangmanGame();
    void playGame();
};

HangmanGame::HangmanGame() {
    secretWord = new SecretWord();
    guessesLeft = 10;
    hangmanImage = {
        "  _________",
        "  |       |",
        "  |       |",
        "  |       O",
        "  |       |",
        "  |      /|\\",
        "  |     / | \\",
        "  |      / \\",
        "  |     /   \\",
        "  |",
        "__|__"
    };
    hint = secretWord->getHint();
}

HangmanGame::~HangmanGame() {
    delete secretWord;
}

void HangmanGame::playGame() {
    while (guessesLeft > 0 && !secretWord->isComplete()) {
        char guess;
        cout << "Guess a letter: ";
        cin >> guess;

        bool correctGuess = secretWord->isCorrectGuess(guess);

        if (correctGuess) {
            secretWord->updateState(guess);
            cout << "Correct guess! You have " << guessesLeft << " guesses left.\n";
        } else {
            guessesLeft--;
            cout << "Incorrect guess! You have " << guessesLeft << " guesses left.\n";
        }

        cout << secretWord->getState() << endl;

        for (int i = 0; i < 10 - guessesLeft; i++) {
            cout << hangmanImage[i] << endl;
        }

        if (guessesLeft == 7) {
            cout << "\nHint: " << hint << endl;
        }
    }

    if (secretWord->isComplete()) {
        cout << "Congratulations! You won!" << endl;
    } else {
        cout << "You lost! The word was " << secretWord->getWord() << endl;
    }
}

int main() {
    HangmanGame game;
    game.playGame();
    return 0;
}
