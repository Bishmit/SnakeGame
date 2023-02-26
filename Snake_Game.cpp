#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
int Score = 0; 
char play = 'y'; 
char dot = char(254);
char l = char(196);
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score = 0;
int scoreMultiple7 = 0;
int tailx[100], taily[100]; int ntail;

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    
    
}
void Draw()
{
    system("cls");
    for (int i = 0; i <= width + 1; i++) 
        cout << l;
        cout << endl;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0)
                    cout << "|";
                if (i == y && j == x)
                    cout << "O";
                else if (i == fruitY && j == fruitX) {
                    cout << dot;
                }
                else if (scoreMultiple7 == 0 && j == fruitX && i == fruitY) {
                    cout << dot;
                }
                else
                {
                    bool print = false; 
                    for (int t = 0; t < ntail; t++) {
                        if (tailx[t] == j && taily[t] == i) {
                            cout << "o";
                            print = true;
                        }
                        
                    }
                    if (!print) cout << " ";
                }
               

                if (j == width - 1)
                    cout << "|";

            }
            cout << endl;
        }
    
    for (int i = 0; i <= width + 1; i++) 
        cout << l;
        cout << endl;
        cout << "Score: " << score << endl;

    
}
void reset_game() {
    score = 0;
    gameOver = false;
    score = 0;
    play = 'y';
    x = width / 2; y = height / 2; 
    ntail = 0; 
}
void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void gameover_msg() {
    cout << "\nGame-Over...\nDo you want to play again\ny/n: ";
    cin >> play;
}
void Logic()
{
    int prevx = tailx[0]; int prevy = taily[0];
    int prev2x, prev2y;
    tailx[0] = x; taily[0] = y; 
    for (int i = 1; i < ntail; i++) {
        prev2x = tailx[i]; prev2y = taily[i];
        tailx[i] = prevx; taily[i] = prevy;
        prevx = prev2x; prevy = prev2y; 

    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    // to make the snake teleport through wall
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // to make snake die if it eats it's own body
    for (int i = 1; i < ntail; i++) {
        if (tailx[i] == x && taily[i] == y)
            gameOver = true;
    }

    bool printAsterisk = false;
    if (x == fruitX && y == fruitY) {
        if (dot == '*') {
            score += 50;
            dot = char(254);
        }
        else {
            score += 10;
       }
        fruitX = rand() % width;
        fruitY = rand() % height;
        ntail++;
        if (score % 6 == 0 && score != 0 && !printAsterisk) {
            scoreMultiple7++;
            fruitX = rand() % width;
            fruitY = rand() % height;
            dot = '*';
            printAsterisk = true; // set the flag to true
        }
        else if (score % 6 != 0 || score == 0) {
            dot = char(254); // set the dot back to the usual symbol
            printAsterisk = false; // reset the flag
        }
        
       
    }

      
}

void Homescreen_msg() {
    cout << "\n\n\t\t===============SNAKE_GAME=================" << endl << endl;
    cout << "\t    By the guidance of my friend kushal, chatGPT and Youtube" << endl << endl;
    cout << "\t\t      Press any key to get started" << endl;
    play = _getch(); 
    
}
int main()
{
    while (play =='y') {
        system("cls");
        Homescreen_msg();
        Setup();
        reset_game();
        while (!gameOver)
        {   
            Draw();
            Input();
            Logic();
            Sleep(50);
        }
        gameover_msg();
    }
    return 0;
}
