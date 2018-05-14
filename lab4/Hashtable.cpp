#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<fstream>
#include <string>
#include<sstream>
#include<ostream>
/* Hashtable.cpp
   Author:  Marvin Joshi
   Date:    October 13,2017

   This program reads in a text file and takes all the punction 
   out of it. It then takes each word in the text file and
   inserts them into a hash table. Then the user is allowed to 
   enter a word and the program searches through the hashtable
   and prints out where the string was found.  
   */
using namespace std;
typedef unsigned int uint;

class hash_table {
	public:
		hash_table();
		void insert(const string& , int lineNumber);//insert strings into hash table
		const vector<int> & find(string & key)  ;//finds line numbers where key is in


	private:
		struct key_line
		{
			public:
				vector<int> lineNumbers;//lineNumbrs of the key
				string key;

				bool inuse()//checks if key is already being used
				{
					if (key =="")
					{
						return false;
					}
					return true;	 
				}
				bool operator ==(const string & word)
				{
					return key ==word;
				}
		};

		int hash(const string &);
		int nextprime(int);
		int qprobe(const string &);
		void resize();
		int num_inuse;
		int max_inuse;
		vector<key_line> table;
};


hash_table::hash_table() {
	int N = 23;
	table.assign(N, key_line());
	num_inuse = 0;
	max_inuse = N/2; 
}


void hash_table::insert(const string &key, int lineNumber) {

	int index = qprobe(key);
	if (table[index].inuse() == false) {
		table[index].key =  key;
		table[index].lineNumbers.push_back(lineNumber);
		if (++num_inuse >= max_inuse)
			resize();
	}
	else if( std::find(table[index].lineNumbers.begin(),table[index].lineNumbers.end(), lineNumber)==table[index].lineNumbers.end())//checks if key is in hash table
	{
    table[index].lineNumbers.push_back(lineNumber);//inserts line number if key is already in hash table
	}

}



int hash_table::nextprime(int N) {
	int i = 1;
	while (i*i <= N) {
		if (N%i == 0) { N++; i = 1; }
		i++;
	}
	return max(3,N);
}


int hash_table::qprobe(const string &key) {
	int index = hash(key);
	int k = 0;
	while ( table[index].inuse() &&!(table[index] == key)){ //uses the key_line class to see if key already exists
		index += 2*(++k) - 1;
		index = index % table.size();
	}
	return index;
}


void hash_table::resize() {
	vector<key_line> tmp_table;
	for (int i=0; i<(int)table.size(); i++) {
		if (table[i].inuse())
			tmp_table.push_back(table[i]);
	}
	int N = nextprime(2*table.size());
	table.assign(N, key_line());
	num_inuse = 0;
	max_inuse = N/2;
	for (int i=0; i<(int)tmp_table.size(); i++) {
		key_line &key1 = tmp_table[i];
		table[ qprobe(key1.key) ] = key1;
		num_inuse++;
	}
}

int hash_table::hash(const string &key)
{
	int index = 0;
	const char *c = key.c_str();
	while (*c)
		index = ((index << 5) | (index >> 27)) + *c++;
	return (uint)index % table.size();
}

const vector<int> &hash_table::find(string & key) {
	int index = qprobe(key);
	return table[index].lineNumbers;//returns the line numbers where the key is in
}
int main(int argc, char *argv[]) {
	hash_table table;
	string word, word2, search;
	vector <string> line;
	vector <string> line2;
	ifstream file;
	stringstream ss;
	string::iterator myIterator;
	int lineNum = 1;
	if(argc ==2 )//checks to see if user has included a text file
	{
		file.open(argv[1]);//opens the text file
	}
	else
	{
		cerr << "usage: ./hashtable textfile" << endl;
		exit(1);
	}

	while (getline (file, word))//extracts lines from the text file
	{

		line.push_back(word);//vector with senetences that contain punctuation
		line2.push_back(word);//vector that will contain the sentences without punctuation

		for(myIterator = line2[lineNum-1].begin();myIterator!=line2[lineNum-1].end();++myIterator)
		{
			if(ispunct(*myIterator))//checks if sentences contains punctuation
			{
				*myIterator = ' ';//sets punctuation with to blank spaces
			}
		}
		ss.str(line2[lineNum-1]);//
		while (ss >> word2)//intakes word from each string
		{
			table.insert(word2, lineNum);//inserts word into the hash table
		}

		lineNum++;//increments the line numbers
		ss.clear();//clears the string steam


	}
	file.close( );
	cout<<"find> ";
	while(cin>>search)//lets the user enter word to be searched
	{
		vector<int> foundLine;

		foundLine = table.find(search);//looks through the hash table to find word user entered
		for(int i = 0; i < foundLine.size(); i++)
		{

			cout<< foundLine[i] <<": "<< line[foundLine[i]-1] <<endl;//prints out where the word is found
		} 

		cout<<"find> ";
	}
}
