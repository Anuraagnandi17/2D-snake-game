#include <iostream>
#include <conio.h>
#include <windows.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
using namespace std;
bool gameOver;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;
class level{
    public:
    int le;
    public:
    level(){
    int le = 0;
    }
    int wid(int le){
        int width = 20*le;
        return width;
    }
    int len(int le){
        int lenght = 10*le;
        return lenght;
    }
	int sped(int le){
		int speed = 100 - 33*le;
		return speed;
	}
	bool wallrestrict(int le){
		if (le == 3){
			return true;
		}
		else {
			return false;
		}
	}
};
void Setup(int width, int height)
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw(int width, int height)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    for (int i = 0; i<(width-2)/2; i++){
        cout<<" ";
    }
    cout<<"SNAKE 2D"<<endl;
	for (int i = 0; i < (width/2)+2; i++)
		cout << "[]";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "[]";
			if (i == y && j == x)
				cout << "@";
			else if (i == fruitY && j == fruitX)
				cout << "*";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "O";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
				

			if (j == width - 1)
				cout << "[]";
		}
		cout << endl;
	}

	for (int i = 0; i < (width/2)+2; i++)
		cout << "[]";
	cout << endl;
	cout << "Score:" << score << endl;
}
void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 75:
			dir = LEFT;
			break;
		case 77:
			dir = RIGHT;
			break;
		case 72:
			dir = UP;
			break;
		case 80:
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic(int width, int height, bool walls)
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
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
	if (walls){
	if (x > width-1 || x < 0 || y > height-1 || y < 0)
		gameOver = true;
	}
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;

	for (int i = 0; i < nTail; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitX && y == fruitY)
	{
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}
int main()
{
    level l;
    level(le);
    cout<<"****************************Welcome to SNAKE 2D!*****************************"<<endl;
	cout<<"\n";
	cout<<"BASIC INSTRUCTIONS - (@-SNAKE HEAD), (O - SNAKE TAIL), ([]-WALL), (* - FRUIT)"<<endl;
	cout<<"\n";
	cout<<"Use arrow keys to control snake, and press 'x' to end the game."<<endl;
	cout<<"\n";
    cout<<"Choose level - "<<endl;
	cout<<"\n";
    cout<<"Level 1 - EASY, grid of (10,10) and no wall restiction"<<endl;
    cout<<"Level 2 - MEDIUM, grid of (20,20) and no wall restiction"<<endl;
    cout<<"Level 3 - HARD, grid of (30,30) with wall restiction"<<endl;
    cout<<"\n";
	cout<<"Your option : ";
    cin>>l.le;
    int width = l.wid(l.le);
    int length = l.len(l.le);
	int spedd = l.sped(l.le);
	bool walls = l.wallrestrict(l.le);
	system("cls");
	Setup(width,length);
	while (!gameOver)
	{
		Draw(width, length);
		Input();
		Logic(width, length, walls);
		Sleep(spedd); 
	}
	system("cls");
    while (gameOver){
        cout<<"GAMEOVER! "<<endl;
		cout<<"Your score was : "<<score<<endl;
		cout<<"Please restart the app to play again!"<<endl;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    }
	
}