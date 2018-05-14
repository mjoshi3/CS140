#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
/* Sudoku.cpp
Author:  Marvin Joshi
Date:    October 20,2017

This program reads in a text file that contains the indices
and values of some cells in the puzzle.The text is put into
a two dimensional array. The program then checks to make
sure each grid index is valid and each value is valid.Next, 
for each cell that has a value of zero, the program finds 
values that could valid for that cell. Then using recursion
the program solves the puzzle and checks to make sure each 
row, column, and box is valid.
*/
using namespace std;

class sudoku {
	public:
		sudoku();

		void solve();

		void read(const char *);
		void write(const char *);
		void write(const char *, const char *);

	private:
		int solve(int row, int col);

		// various support functions 
		bool error_check_value(int num);//checks to make sure each values in the array is between num and 9
		bool error_check_uniqueness();//checks to make sure each value in a row, column and 3x3 box is valid
		bool unique_column(int row, int col);//checks to see each column is valid
		bool unique_row(int row, int col);//checks to see if each row is valid
		bool unique_box(int row, int col);//checks to see if each 3x3 box is valid
		vector<int> valid_values(int row, int col);//stores the values that could be possible for each cell

		void display();

		int game[9][9];
};

sudoku::sudoku() { 
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++)
			game[i][j] = 0;
	}
}

void sudoku::solve() {
	cout << "SOLVE\n";

	solve( 0,0);//calls the solve function starting at the beginning
	// call recursive computation

	display();

	bool check1;
	check1=  error_check_value(1);//checks to make sure each cell value is between 1 and 9
	if(check1 == true)
	{
		check1 = error_check_uniqueness();//cekcs each row,col,box
		if(check1 == false)
		{
			exit(0);//exits program if error detected
		}
	}
	else
	{
		exit(0);//exits program if error detected
	}

	// error check data values
	// error check uniqueness
	// exit if errors detected
}

void sudoku::read(const char *fname) {
	cout << "READ\n";
	bool check1 = true;
	ifstream fin(fname);

	int i, j, v;

	while (fin >> i >> j >> v) {
		if(!(i<9 && i>=0 && j<9 && j>=0))//checks to make sure valid indices
		{
			cerr<<i<<" "<<j<<" "<<v<<" illegal grid index"<<endl;//outputs errors
			check1 = false;
		}
		// error check grid indices
		game[i][j] = v;
	}
	if(check1 == false)
	{
		exit(0);
	}

	fin.close();

	display();
	// exit if bad grid indices
	bool check =  error_check_value(0);//checks to make each cell value is between 0 and 9
	if(check == true)
	{
		check = error_check_uniqueness();//checks each row, col, and box is valid
		if(check == false)
		{
			exit(0);//exits if error is detected
		}
	}
	else
	{
		exit(0);//exits if error is detected
	}

	// error check data values
	//error_check_uniqueness();
	// error check uniqueness
	// exit if errors detected
}

void sudoku::write(const char *fname) {
	ofstream fout(fname);

	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (0 < game[i][j]) {
				fout << i << " "
					<< j << " "
					<< game[i][j] << "\n";
			}
		}
	}

	fout.close();
}

void sudoku::write(const char *fname, const char *addon) {
	int N1 = strlen(fname);
	int N2 = strlen(addon);

	char *n_fname = new char[N1+N2+2];

	// strip .txt suffix, then concatenate _addon.txt
	strncpy(n_fname, fname, N1-4);
	strcpy(n_fname+N1-4, "_");
	strcpy(n_fname+N1-3, addon);
	strcpy(n_fname+N1-3+N2, ".txt");

	write(n_fname);

	delete [] n_fname;
}

void sudoku::display() {
	cout << "| ----------------------------- |\n";
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (j%3 == 0) 
				cout << "|";
			cout << "  " << game[i][j];
		}
		cout << "  |\n";
		if (i%3 == 2)
			cout << "| ----------------------------- |\n";
	}
}

int sudoku::solve(int row, int col) {
	for(row = 0;row<9;row++)
	{
		for(col = 0;col<9;col++)
		{
			if(game[row][col] ==0)//only inserts value into cell if previous value is 0
			{
				vector<int> validValues = valid_values(row,col);;//stores valid values of each cell into vector
				vector<int>::iterator Iterator;
				for (Iterator = validValues.begin();Iterator != validValues.end();++Iterator)//iterates through vector
				{
					game[row][col] = *Iterator;//sets cell to value
					if(solve(row, col) ==1)//goes through puzzle to try and solve puzzle and outputs a 1 if values are valid
					{
						return 1;
					}
				}
				game[row][col] = 0;//if no value in vector is found to be true, value of cell is set back to 0
				return 0;
			}


			if(row ==8 &&col ==8)//if we reach end out the puzzle
				return 1;//returs true
		}}
	// if solution found, 
	//   return solution-found
	//
	// set cell index (i,j)
	// determine valid values 
	// if no valid values left,
	//   return road-to-nowhere
	//
	// iterate thru valid values 
	//   game[i][j] = next value
	//   if solve(arguments) == solution-found
	//     return solution-found
	//
	// reset: game[i][j] = 0
	// return road-to-nowhere
}

bool sudoku::error_check_value(int num){
	bool check = true;
	for(int i = 0;i<9;i++)
	{
		for(int j = 0;j<9;j++)
		{
			if ((game[i][j] < num) || (game[i][j] > 9))//checks to see if if cell calue is between num and 9
			{
				cerr<<i<<" "<<j<<" "<<game[i][j]<<" illegal data value"<<endl;//outsputs error if cell is not in between num and 9
				check = false;
			}
		}
	}
	return check;


}  

bool sudoku:: error_check_uniqueness(){
	bool check1 = true;
	bool check2 = true;
	bool check3 = true;
	bool finalCheck = true;
	for(int i = 0;i<9;i++)
	{
		for(int j = 0;j<9;j++)
		{
			if(game[i][j] !=0){//does the next part of code only if cell value is not 0
				check1 = unique_row(i,j);//checks to make sure row is unique 
				if(check1 == false)//if error is detected
				{
					cerr<<i<<" "<<j<<" "<<game[i][j]<<" illegal non-unique value"<<endl;//outputs error if value is not valid in row
				}
				else
				{
					check2 = unique_column(i,j);//checks to make sure each column is unique
					if(check2 == false)
					{
						cerr<<i<<" "<<j<<" "<<game[i][j]<<" illegal non-unique value"<<endl;//outputs error if value is not valid in column
					}
					else
					{
						check3 = unique_box(i,j);//checks to make sure each box is valid
						if(check3 == false)
						{
							cerr<<i<<" "<<j<<" "<<game[i][j]<<" illegal non-unique value"<<endl;//outputs error if value is not valid in box
						}
					}
				}
			}
			if(check1 ==false ||check2 == false || check3 == false)//if any error is detected
			{
				finalCheck = false;// returns false
			}
		}
	}
	return finalCheck;; 
}
bool sudoku:: unique_row(int row, int col){
	bool check=true;
	for (int i = 0; i < 9; i++){
		if (i != col){
			if (game[row][i] == game[row][col] ){//checks to make sure if another cell in the row is not the same value as the value of the row and col from the parameters of the function
				check = false;
			}
		}
	}

	return check;
}  
bool sudoku:: unique_column(int row, int col){
	bool check=true;
	for (int i = 0; i < 9; i++){
		if (i != row){
			if (game[i][col] == game[row][col] ){//checks to make sure if another cell in the col is not the same value as the value of the row and col from the paramaters of the function
				check = false;
			}
		}
	}
	return check;	
}
bool sudoku:: unique_box(int row, int col){
	bool check=true;
	int boxRow = row/3;
	int boxCol = col/3;
	boxRow = boxRow*3;
	boxCol = boxCol*3;
	for (int i = boxRow; i < boxRow+ 3; i++)//starting at the beginning of 3x3 box that contains the row and col from the paramaters of the function
	{
		for (int j = boxCol; j < boxCol+ 3; j++)
		{
			if ((i == row && j == col)==false)
			{
				if (game[row][col] == game[i][j] )//checks to make sure if another cell in the box is not the same value as the value of the row and col from the parameters of the function
				{
					check = false;
				}
			}
		}
	}
	return check;	
}
vector<int> sudoku::valid_values(int row, int col){
	vector<int> values;
	for(int i = 1;i<10;i++)//going from values 1-9
	{
		game[row][col] = i;//inserts the value into the cell
		if ((unique_row(row,col)==true) && (unique_column(row,col)==true) && (unique_box(row, col)==true))//checks to see if value of cell is unique for each row col and 3x3 box
		{  
			values.push_back(i);//insert value into the array
		}
	}
	game[row][col] = 0;//sets value of cell back to 0
	return values;//returns the vector

}



int main(int argc, char *argv[]) {
	srand(time(NULL));

	if ((argc != 3) ||
			(strcmp(argv[1], "-s") != 0) ||
			strstr(argv[argc-1], ".txt") == NULL) {
		cerr << "usage: Sudoku -s game.txt\n";
		exit(0);
	}

	sudoku sudoku_game;

	if (strcmp(argv[1], "-s") == 0)
	{
		sudoku_game.read(argv[2]);
		sudoku_game.solve();
		sudoku_game.write(argv[2], "solved");
	}
}
