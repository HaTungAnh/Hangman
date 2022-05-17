#include <iostream>
#include <ctime>    
#include <fstream>
#include <vector>
#include <algorithm>  
#define MAX_GUESS_COUNT 7

using namespace std;

ifstream file("C:\\Users\\LENOVO\\Desktop\\SDL2.0\\Project\\Hangman\\SecretWord.txt");
vector<string> WORD;

string tolower(const string& WORD)
{
    string out = string(WORD.length(),' ');
    for (int i = 0; i < WORD.length(); i++)
    {
        out[i] = tolower(WORD[i]);
    }
    return out;
}

string chooseWord()
{
    int index = rand() % (WORD.size()); 
    return tolower(WORD[index]);
}

void initGame(string& secretWord,string& guessWord,int& badGuessCount) 
{
    string word;
    while (file >> word)
    {
        WORD.push_back(word);
    }
    secretWord = chooseWord(); // random
    guessWord = string(secretWord.length(), '-'); // -----
    badGuessCount = 0;
}

const string SCREEN[] = {
         "   -------------    \n" 
         "   |                \n" 
         "   |                \n" 
         "   |                \n" 
         "   |                \n" 
         "   |     \n" 
         " -----   \n",

         "   -------------    \n" 
         "   |           |    \n" 
         "   |                \n" 
         "   |                \n" 
         "   |                \n" 
         "   |     \n" 
         " -----   \n",

         "   -------------    \n" 
         "   |           |    \n" 
         "   |           O    \n" 
         "   |                \n" 
         "   |                \n" 
         "   |     \n" 
         " -----   \n",
         "   -------------    \n" 
         "   |           |    \n" 
         "   |           O    \n" 
         "   |           |    \n" 
         "   |                \n" 
         "   |     \n" 
         " -----   \n",

         "   -------------    \n" 
         "   |           |    \n" 
         "   |           O    \n" 
         "   |          /|    \n" 
         "   |                \n" 
         "   |     \n" 
         " -----   \n",

         "   -------------    \n" 
         "   |           |    \n" 
         "   |           O    \n" 
         "   |          /|\\  \n" 
         "   |                \n" 
         "   |     \n" 
         " -----   \n",
         "   -------------    \n" 
         "   |           |    \n" 
         "   |           O    \n" 
         "   |          /|\\  \n" 
         "   |          /     \n" 
         "   |     \n" 
         " -----   \n",

         "   -------------    \n" 
         "   |           |    \n" 
         "   |           O    \n" 
         "   |          /|\\  \n" 
         "   |          / \\  \n" 
         "   |     \n" 
         " -----   \n",
};

void renderGame(const char input, const string& secretWord,const string& guessWord,int badGuessCount, string& wrongGuess) // in ra man hinh
{
    for (int i = 0; i < 100; i++)
    {
        cout << endl;                             
    }
    cout << SCREEN[badGuessCount] << endl;
    cout << "SecretWord: " << guessWord << " " << secretWord << endl;
    cout << badGuessCount << " "  << wrongGuess << endl;
}

char getInput() 
{
    string input;
    cin >> input;
    return tolower(input[0]);
}

bool contains(char c,const string& word)   
{
    return (word.find(c) != string::npos);
}

void update(char input,const string& secretWord,string& guessWord) 
{
    for (int i = 0; i < secretWord.length(); i++)
    {
        if (input == secretWord[i])
        {
            guessWord[i] = input;
        }
    }
}

void updateGame(char input,const string& secretWord,string& guessWord,int& badGuessCount, string& wrongGuess)
{
    
    if (contains(input, secretWord))
    {
        update(input, secretWord, guessWord);
    } else
    {
        if(contains(input, wrongGuess))
        {
            wrongGuess = wrongGuess + input + " ";
        }
        badGuessCount++;
    }
}

bool gameOver(const string& secretWord,const string& guessWord,int badGuessCount)
{
    return (secretWord == guessWord) || (badGuessCount >= MAX_GUESS_COUNT);
}

void displayResult(const string& secretWord,const string& guessWord)
{
    if (secretWord == guessWord)
    {
        cout << "You won!" << endl;
    } else
    {
        cout << "You lost!" << endl;
    }
}

int main()
{
    string wrongGuess;
    srand(time(0));  
    string secretWord; 
    string guessWord; 
    int badGuessCount; 
    char input;
    initGame(secretWord, guessWord, badGuessCount);
    do {
        renderGame(input, secretWord, guessWord, badGuessCount, wrongGuess);
        input = getInput();
        updateGame(input, secretWord, guessWord, badGuessCount, wrongGuess);
    } while (!gameOver(secretWord, guessWord, badGuessCount));
    renderGame(input, secretWord, guessWord, badGuessCount, wrongGuess);
    displayResult(secretWord, guessWord);
    file.close();
    return 0;
}