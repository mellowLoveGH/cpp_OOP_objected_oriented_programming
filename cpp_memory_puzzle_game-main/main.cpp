//#include "stdafx.h" 
#include <iostream> 
#include <thread> 
#include <time.h>

using namespace std;

//randomize the matrix, randomly shuffle the cards from A to H
void randomizeMtx(char mat[4][4]) {
	//initialize the random function, use time as seed for randomization
	srand((unsigned)time(NULL));
	for (int i = 0; i < 16; i++)
	{
		//get two random positions
		int index1 = rand() % 16;
		int r1 = index1 / 4;
		int c1 = index1 % 4;
		//
		int index2 = rand() % 16;
		int r2 = index2 / 4;
		int c2 = index2 % 4;

		//exchange positions
		char ch = mat[r1][c1];
		mat[r1][c1] = mat[r2][c2];
		mat[r2][c2] = ch;
	}
}

//print out the two-dimensional array
void print(char mat[4][4]) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//for the showM matrix which is used to be demonstrated on the console
//the parameters, two positions, two characters on the chosen cards
//if the two flipped cards are the same, showM matrix will record them
//the return value means if there is necessary to flip back
bool chooseCards(int x1, int y1, int x2, int y2, char ch1, char ch2, char showM[4][4]) {
	if (ch1 == ch2) {
		showM[x1][y1] = ch1;
		showM[x2][y2] = ch2;

		return false;
	}
	else {
		return true;
	}
}

bool win(char showM[4][4]) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (showM[i][j] == 'X')
				return false;
		}
	}
	return true;
}

int main() { 
	const int N = 4;

	//the matrix that hold the cards information with initialization
	char mat[N][N] = { 
		{'A', 'A', 'B', 'B'},
		{'C', 'C', 'D', 'D'},
		{'E', 'E', 'F', 'F'},
		{'G', 'G', 'H', 'H'} 
	};

	//randomly shuffled
	randomizeMtx(mat);
	//here the mat could be printed on the console
	print(mat); 

	//showM matrix used to record cards if the flipped two are the same
	char showM[N][N] = {
		{'X', 'X', 'X', 'X'},
		{'X', 'X', 'X', 'X'},
		{'X', 'X', 'X', 'X'},
		{'X', 'X', 'X', 'X'}
	};
	
	//calculate how many moves it takes
	int moves = 0;
	//get the entering infomation from user
	while(true) { 
		//print showM info
		print(showM);
		cout << "Choose two cards (or 'q' to quit the game): " << "";

		//get the input information from user
		int x1, y1, x2, y2;
		char ch;
		cin >> ch;
		//if the first input character is 'q', game over
		//or game continues
		if (ch == 'q') {
			break;
		}
		else {
			x1 = ch - '0';
		}		
		cin >> y1;
		cin >> x2;
		cin >> y2;

		//cout << x1 << ", " << y1 << "\n" << x2 << ", " << y2 << endl;
		//get the characters on the chosen cards
		char ch1 = mat[x1][y1];
		char ch2 = mat[x2][y2];
		bool flipback = chooseCards(x1, y1, x2, y2, ch1, ch2, showM);

		//if it is necessary to flip back
		if (flipback) {
			//print the flipped cards on the console
			showM[x1][y1] = ch1;
			showM[x2][y2] = ch2;
			print(showM);
			//after 3 seconds, clear console
			this_thread::sleep_for(3s);
			system("CLS");
			//flip back
			showM[x1][y1] = 'X';
			showM[x2][y2] = 'X';
		}

		moves++;
		if (win(showM)) {
			cout << "Congratulations! You solved the puzzle in " << moves << " moves" << endl;
			break;
		}
		else {
			//cout << "Congratulations! You solved the puzzle in " << moves << " moves" << endl;
		}
		
	} 
	//system("pause");

	return 0;
}