#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <ostream>
#include <map>
#include <numeric> 
/* Sudoku.cpp
Author:  Marvin Joshi
Date:    November 22,2017

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

class name_t
{
	public:
		void set(string &first, string &last);
		bool operator<(const name_t & rhs) const
		{
			return fullname < rhs.fullname;
		} 
		void print_name(int num)const;
		string & getName()
		{
			return fullname;
		}
	private:
		string firstname;
		string lastname;
		string fullname;
};

void name_t::set(string &first, string &last)
{
	firstname = first;
	lastname = last;
	fullname = lastname + ", " + firstname + " ";
}

void name_t::print_name(int num)const
{
	cout << fullname;
	for(int i = fullname.length();i<=(num+2+2);i++)
	{
		cout<<".";
	} 
	cout<<" ";
}

class labscores_t
{
	public:
		void add_data(int num);
		void set_stats();
		void print_labscores();
		vector<int>& getScores()
		{
			return scores; 
		}

	private:
		vector<int>scores;
		double mean;
		int median;
};



void labscores_t::add_data(int num)
{
	scores.push_back(num);
}

void labscores_t::set_stats()
{
	mean = 0.0;
	//vector<int>::iterator it;
	sort(scores.begin(),scores.end());
	int init = 0;
	mean += (double)accumulate(scores.begin(), scores.end(), init)/scores.size();
	int middle = (scores.size()-1)/2;
	for (vector<int>::iterator it=scores.begin(); it!=scores.begin()+middle+1; ++it)
	{
		median = *it;
	}
	
}

void labscores_t::print_labscores()
{
	for (vector<int>::iterator it=scores.begin(); it!=scores.end(); ++it)
	{
		cout<<right<<setw(2)<< *it<<" ";
	}
	cout<<":"<<setw(3)<<right<<median<<" ";
	cout<<fixed<<setprecision(1)<<left<<setw(3)<<mean<<endl;
	scores.clear();
}

int main(int argc, char *argv[]) 
{

	ifstream file;
	string firstName,lastName;
	stringstream ss;
	string line;
	int lengthLarge,length = 0;
	//int num;
	if ((argc != 3) ||(strcmp(argv[1], "-byname") != 0) ) 
	{
		cerr << "usage: labscores -byname|byrank|top10 datafile.txt";
		exit(0);
	}

	else
	{
		file.open(argv[2]);
	}
       typedef map<name_t,labscores_t> mymap;
       mymap A;
       typedef mymap::iterator Iterator;
       Iterator it = A.begin();

	//	vector <int> numbers;

	while(getline(file, line))
	{
	        name_t n;
		labscores_t l;
		ss.str(line);
		while(ss>>firstName>>lastName)
		{
		  int num;
			length = firstName.size() + lastName.size();
			if(lengthLarge<length)
			{
				lengthLarge = length;
			}
			n.set(firstName,lastName);
			//n.print_name(lengthLarge);
			while(ss>>num)
			{
				l.add_data(num);
			}    
			l.set_stats();
			A.insert(make_pair< name_t,labscores_t>(n ,l ));

			//	l.print_labscores();
			//	numbers.clear();
		}
		ss.clear();
	}
	file.close();
	for ( it = A.begin(); it!=A.end(); ++it)
	{
	   it->first.print_name(lengthLarge);
	  it->second.print_labscores();
	}	
} 

/*

class heap_t()
{
  heap_t();
  bool empty(){
  if(data.size() = 0)
  return true;
  return false;}
  void add_data(const map_iterator_t &);
  void heapify(){
  make_heap(data.begin(),data.end());}//class make heap
  map_iterator_t extract_top();
 private:
  struct data_t{
map_iterator_t
bool operator<(const data_t & rhs) const
{
	return fullname < rhs.fullname;
} };
  vector<data_t>data;

};
*/
