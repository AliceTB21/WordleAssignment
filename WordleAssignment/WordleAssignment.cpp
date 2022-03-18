#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define BACKGROUND(color,text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"
using namespace std;

string convertToUpper(string input)
{
    string newInput = input;
    for (int i = 0; i < input.length(); i++)
    {
        newInput[i] = toupper(input[i]);
    }

    return newInput;
}
enum class BackgroundColor : int
{
    Green = 42,
    Yellow = 43,
    Grey = 100
};
string GetWord(string fileName)
{
    ifstream wordFile(fileName);
    string word;
    vector<string> wordCollection;
    if (wordFile.is_open())
    {
        while (getline(wordFile, word))
        {
            wordCollection.push_back(word);
        }
    }
    else wordFile.close();
    srand(time(NULL));

    string randomWord = wordCollection[rand() % wordCollection.size()];
    return randomWord;
}
bool checkvalid(string input)
{
    bool validInput = true;
    for (int i = 0; i < input.length(); i++)
    {
        if (!isalpha(input[i]) || isspace(input[i]) || input.length() != 5 || input.length() == 0)
        {
            validInput = false;
        }
    }

    return validInput;
}
int game()
{
    string input;
    vector<string> guessedWords;
    string word = GetWord("words.txt");
    int guesses = 0;
    bool hasWon = false;
    bool gameOver = false;

    while (!gameOver)
    {
        cout << "Input guess: ";
        cin >> input;
        input = convertToUpper(input);
        if (!checkvalid(input))
        {
            cout << "\nInvalid input, try again" << endl;
        }
        else
        {
            guessedWords.push_back(input);
            guesses++;
            system("cls");
            cout << "Guess: " << guesses << endl;
            for (string i : guessedWords)
            {
                for (int l = 0; l < i.length(); l++)
                {
                    string wordToCheck = i;
                    size_t checkedWord = word.find(wordToCheck[l]);
                    if (wordToCheck[l] == word[l])
                    {
                        cout << BACKGROUND(BackgroundColor::Green, wordToCheck[l]);
                    }
                    else if (checkedWord != string::npos)
                    {
                        cout << BACKGROUND(BackgroundColor::Yellow, wordToCheck[l]);
                    }
                    else
                    {
                        cout << BACKGROUND(BackgroundColor::Grey, wordToCheck[l]);
                    }

                }
                if (i == word)
                {
                    hasWon = true;
                    gameOver = true;
                }
                cout << endl;
            }
            if (guesses == 6)
            {
                gameOver = true;
            }

        }

    }
    if (hasWon)
    {
        cout << "Congratulations! You guessed the word." << endl;
    }
    else
    {
        cout << "You failed to guess the word in 6 guesses. The word was: " << word << endl;
    }
    

    while (true)
    {
        cout << "Do you want to play again? y/n or yes/no" << endl;
        cin >> input;
        if (input == "y" || input == "yes")
        {
            system("cls");
            game();
        }
        else if (input == "n" || input == "no")
        {
            exit(0);
        }
        else
        {
            cout << "Invalid reply" << endl;
        }
    }


    return 0;
}

int main()
{
    cout << "Welcome! Guess the 5 letter word." << endl;
    game();
    return 0;
}