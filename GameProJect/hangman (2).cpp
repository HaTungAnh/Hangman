#include <iostream>
#include <ctime>
#define MAX_GUESS_COUNT 7

using namespace std;

const string WORD[] = {"cAT", "doG", "duCk", "Hello", "Hi", "Book", "leagUe", "chaNge"};

string tolower(const string& WORD)
{
    string out = string(WORD.length(),' ');
    for (int i = 0; i < WORD.length(); i++)
    {
        out[i] = tolower(WORD[i]);
    }
    return out;
}

string chooseWord() // tao 1 file chua cac tu tieng anh r doc file day ra dung ham random
{
    int index = rand() % (sizeof(WORD)/sizeof(string)); // kich thuoc cua mang = sizeof(tenbien)/sizeof(kieudulieu)
    return tolower(WORD[index]);
}

void initGame(string& secretWord,string& guessWord,int& badGuessCount) // khoi tao game
{
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

void renderGame(const char input, const string& secretWord,const string& guessWord,int badGuessCount) // in ra man hinh
{
    for (int i = 0; i < 10; i++)
    {
        cout << endl;                             // xoa man hinh
    }
    cout << SCREEN[badGuessCount] << endl;
    cout << secretWord << " " << guessWord << " " << badGuessCount << endl;
}

char getInput() // nhap vao ky tu va in ra ky tu dau tien (de phong truong hop lo~ nhap vao nhieu ky tu)
{
    string input;
    cin >> input;
    return tolower(input[0]);
}

bool contains(char c,const string& word)   // ham` nay` tim 1 ky tu xem co trong chuoi hay k
{
    return (word.find(c) != string::npos);
}

void update(char input,const string& secretWord,string& guessWord) /// thay doi gia tri guessWord tai vi tri doan dung
{
    for (int i = 0; i < secretWord.length(); i++)
    {
        if (input == secretWord[i])
        {
            guessWord[i] = input;
        }
    }
}

void updateGame(char input,const string& secretWord,string& guessWord,int& badGuessCount)
{
    if (contains(input, secretWord))
    {
        update(input, secretWord, guessWord);
    } else
    {
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

//int main()
//{
//    srand(time(0));  // tao hat giong, neu k co thi may tinh se tu tinh ra 1 hat giong mac dinh
//    string secretWord; // khi do se thuat toan se chi la gia? ngau~ nhien vi moi hat giong khac nhau se chi ra dc ngau nhien khac nhau
//    string guessWord; // cung 1 hat giong thi cung 1 ngau nhien
//    int badGuessCount; // vi vay chung ta dung ham lenh kia de tao hat giong theo thoi gian tren may tinh cta
//    char input;
//    initGame(secretWord, guessWord, badGuessCount);
//    do {
//        renderGame(input, secretWord, guessWord, badGuessCount);
//        input = getInput();
//        updateGame(input, secretWord, guessWord, badGuessCount);
//    } while (!gameOver(secretWord, guessWord, badGuessCount));
//    renderGame(input, secretWord, guessWord, badGuessCount);
//    displayResult(secretWord, guessWord);
//    
//    return 0;
//}