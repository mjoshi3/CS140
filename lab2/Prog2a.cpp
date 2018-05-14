#include <cstdlib>
#include <iostream>
#include <iomanip>
#include<sstream>
#include <string.h>
#include <string>
/* Prog2a.cpp
   Author:  Marvin Joshi
   Date:    September 14,2017

   This program randomizes a deck of cards and generates 
   cards unitl all the face cards have been dealto fone suit. 
   The program checks that cards dealt by using two for loops 
   cto check the suit and face of each card. After all the face 
   cards of one suit have been printed, the program prints out
   a two dimensional array of all the cards and marks the last
   suit that was dealt with two **.
   */

using namespace std;

const string face[] = { "Ace", "2", "3", "4", "5", "6", "7",
                        "8", "9", "10", "Jack", "Queen", "King" }; 
const string suit[] = { "Clubs", "Diamonds", "Hearts", "Spades" };

string random_card(bool verbose=false) {
	string card;

	card = face[ rand()%13 ];
	card += " of ";
	card += suit[ rand()%4 ];

	if (verbose)
	  cout << card << "\n";

	return card;
}

int main(int argc, char *argv[])
{
	bool verbose = false;
	int seedvalue = 0;

	for (int i=1; i<argc; i++) {
	  string option = argv[i];
	  if (option.compare(0,6,"-seed=") == 0) {
	    seedvalue = atoi(&argv[i][6]);
	  } else if (option.compare("-verbose") == 0) {
	    verbose = true;
	  } else 
	    cout << "option " << argv[i] << " ignored\n";
	}

	srand(seedvalue);
	int table [4][13] = {0}  ;
  // declare a table called deck that keeps track of
	// card faces dealt for each suit -- initialize to 0
string lastCard;
string last;
do{
	
	  string card = random_card(verbose);
	  stringstream ss;//uses a string stream to seperate the face and suit into seperate strings
	  string first;
	  string middle;
	  string third;
	  ss<<card;
	  ss>>first>>middle>>third;
	  for (int i = 0; i<4;i++)
	  {	
		if(third == suit[i])//matches the suit of each card
		{
	    	for (int j = 0;j<13;j++)
			{
				if (first == face[j])//matches the face of each card
				{
					table[i][j] += 1;//increaments the spot on the array that corresponds to the card dealt
				}
            }
        }
	  }
	
		last = third;//marks the face of the card dealt

	
}	
//checks to make aure all the face cards of one suit is dealt
 while((table[0][10]==0||table[0][11]==0||table[0][12]==0)&&(table[1][10]==0
        ||table[1][11]==0||table[1][12]==0)&&(table[2][10]==0||table[2][11]==0
        ||table[2][12]==0)&&(table[3][10]==0||table[3][11]==0||table[3][12]==0));

       
	  // reverse engineer card suit and face

      // break out of loop if stopping criteria met
	

	// print formatted table contents to stdout
int num = 0;
//cout<<lastCard;
  for (num = 0;num<4;num++)//prints out the array
  {
	cout<<setw(8)<<suit[num]<<" :";
	
		for (int j = 0; j<13;j++)
		{
	
			cout<<setw(4)<<table[num][j];
		}
		if (last == suit[num])//prints out the two stars next to the suit of the last card dealt
		{
		    cout<<" **";
		}
	

	
  cout<<endl;
	
}
}

