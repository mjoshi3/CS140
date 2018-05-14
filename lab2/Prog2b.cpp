
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include<sstream>
#include <string.h>
#include <string>
/* Prog2b.cpp
   Author:  Marvin Joshi
   Date:    September 26,2017

   This program randomizes a deck of cards and prints out all
   the cards that are generated into its specific list. If a 
   duplicate comes, the card get inserted to the front of the 
   list. The card stop generating once the all the face cards
   of one suit are printed out. 
   */

using namespace std;

const string face[] = { "Ace", "2", "3", "4", "5", "6", "7",
                        "8", "9", "10", "Jack", "Queen", "King" }; 
const string suit[] = { "Clubs", "Diamonds", "Hearts", "Spades" };
class list {
 struct node {
 node(int data=0);
 int data;
 node *next;
 };
 public:
 list();
 ~list();
 void insert(int i);
 friend ostream & operator<<(ostream &out, list& list1);

 private:
 int N;
 node *head;
};
list::node::node(int n_data) {
 data = n_data;
 next = NULL;
}
list::list() {
 head = new node;
 head->next = NULL;
 N = 0;
}
list::~list()
{
 node *p = head;
 node *temp;
while(p!=0){
 
 temp = p->next;
 delete temp; 
 p=p->next;
 }

head = 0;
delete head;


}


void list::insert(int i) //inserts a card into a list
{

node *q = head;
node *p = head->next;
while(p!=NULL)
{  


		if (p->data == i)//checks if card has already been dealt
		{
			q->next = p->next;
			p->next = head->next;
			head->next = p;
			return;
		    
		}
   p = p -> next;
    q = q->next;
	
}
node *o = new node(i);//adds card to list if not already there
q->next = o;
o->next = NULL;
N++;
}



ostream& operator<<(ostream& out, list& list1)
{
  list::node *p2 = list1.head->next;
  while(p2)
  {
  
    out<<face[p2-> data];//prints the data that is connected to each list
    out<<" ";
    p2 = p2->next;
 }
 return out;
 }



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
	list card_list [4];//creates a list for each suit
 card_list [0]=  list();
  card_list [1]=  list();
   card_list [2]=  list();
    card_list [3]=  list();
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
        
					card_list[i].insert(j);//inserts a card into a specific list
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
	cout<<setw(8)<<suit[num]<<" : ";
	cout<<card_list[num];//print out the cards of each list
		
		if (last == suit[num])//prints out the two stars next to the suit of the last card dealt
		{
		    cout<<"**";
		}
	

	
  cout<<endl;
	
}
}
