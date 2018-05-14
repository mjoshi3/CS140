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
/* Labscores2.cpp
Author:  Marvin Joshi
Date:    December 5,2017

This program reads in a text file that contains names and
labscores. The classname_t organizes the names in in order
by using the overloaded operator. The labscores_t class 
sets the mean and median of each object. The heap_t class
acts as max heap and sets the data in largest score order,
by using the overloaded operator. The main funciton inserts 
each name and labscore into a map and depending on the
second arguement passed, the program organizes the data
in byname order, byrank order or top10 order. 
*/
using namespace std;

class name_t
{
	public:
		void set(string &first, string &last);
		bool operator<(const name_t & rhs) const//overloads the < operator
		{
			return fullname < rhs.fullname;//checks to see whcih fullname is larger
		} 
		void print_name(int num)const;
		string & getName()  
		{
			return fullname;//returns the fullname
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
	fullname = lastname + ", " + firstname + " ";//combines the first name and last name together
}

void name_t::print_name(int num)const
{
	cout << fullname;
	for(int i = fullname.length();i<=(num+2+2);i++)
	{
		cout<<".";//prints the right amount of dots after each persons name
	} 
	cout<<" ";
}

class labscores_t
{
	public:
		void add_data(int num);//funciton to insert labscore into vector
		void set_stats();//function for setting the median and mean
		void print_labscores();//print function for labscores
		double &getMean()
		{
			return mean;//returns the mean
		}
		int & getMedian()
		{
			return median;//returns the median
		}

	private:
		vector<int>scores;
		double mean;
		int median;
};



void labscores_t::add_data(int num)
{
	scores.push_back(num);//inserts each labscore to the vector
}

void labscores_t::set_stats()
{
	mean = 0.0;
	sort(scores.begin(),scores.end());//sorts the numbers in order of smallest to largest
	int init = 0;
	mean += (double)accumulate(scores.begin(), scores.end(), init)/scores.size();//sets the mean number
	int middle = (scores.size()-1)/2;//finds the middle number location
	for (vector<int>::iterator it=scores.begin(); it!=scores.begin()+middle+1; ++it)
	{
		median = *it;//sets the median to the right number
	}

}

void labscores_t::print_labscores()
{
	for (vector<int>::iterator it=scores.begin(); it!=scores.end(); ++it)
	{
		cout<<right<<setw(2)<< *it<<" ";
	}
	cout<<":"<<setw(3)<<right<<median<<" ";//prints the medain
	cout<<fixed<<setprecision(1)<<left<<setw(3)<<mean<<endl;//prints the mean
	scores.clear();//clears the vecotr
}
typedef map<name_t,labscores_t> mymap;
typedef mymap::iterator Iterator;
class heap_t
{
	private:

		struct data_t{
			public:
				Iterator it;   
				bool operator<(const data_t & rhs) const//overloads the < operator
				{
					if ((it->second.getMean() == rhs.it->second.getMean())&&(it->second.getMedian() == rhs.it->second.getMedian()))//checks to see if median and mean are equal 
						return !(it->first < rhs.it->first);//checks which name is larger
					else if (it->second.getMean() == rhs.it->second.getMean())//if the two means are equal
						return it->second.getMedian() < rhs.it->second.getMedian();//checks to see which medain is higher
					else
						return it->second.getMean() < rhs.it->second.getMean();//checks to see which mean is higher

				}

		};
		vector<data_t>data;//vector of data_t objects

	public:
		bool empty()
		{
			if(data.size() == 0)//checks to see if vector size if 0
				return true;
			return false;
		}
		void add_data(const map<name_t,labscores_t>::iterator & It)
		{
			data_t temp;
			temp.it = It;
			data.push_back(temp);//pushes the iterator into vector
		}

		void heapify()
		{
			make_heap(data.begin(),data.end());//makes the max heap
		}
		Iterator extract_top()
		{
			data_t temp;
			temp =data.front();//gets the top most object
			pop_heap(data.begin(), data.end());//sends object to the back
			data.pop_back();//deletes back object
			return temp.it;//returns iterator of top object of heap
    }

};

int main(int argc, char *argv[]) 
{
	heap_t h;
	ifstream file;
	string firstName,lastName;
	stringstream ss;
	string line;
	int lengthLarge,length = 0;
	mymap A;
	Iterator it;
	int max=0;
	int num;
	if ((argc == 3)&&((strcmp(argv[1], "-byname") == 0)||(strcmp(argv[1], "-byrank") == 0)||(strcmp(argv[1], "-top10") == 0) )) //if valid argv statements
		{
			file.open(argv[2]);//opens the file
		}	
	else
	{
		cerr << "usage: labscores -byname|byrank|top10 datafile.txt"<<endl;//pritns error statement
		exit(0);
	}
	while(getline(file, line))//checks to see if anything is in file
	{
		name_t n;
		labscores_t l;
		ss.str(line);
		while(ss>>firstName>>lastName)//extracts first and last name
		{
			int num;
			length = firstName.size() + lastName.size();
			if(lengthLarge<length)//checks to see if name length is the largest seen
			{
				lengthLarge = length;//sets the max length
			}
			n.set(firstName,lastName);//combines the first and last name together
			while(ss>>num)//extracts scores if possible
			{
				l.add_data(num);//add each labscore in vector
			}    
			l.set_stats();//computes the median and mean
			A.insert(make_pair< name_t,labscores_t>(n ,l ));//inserts name and labscores in map
		}
		ss.clear();//clears strin stream after labscores have been extracted
	}
	file.close();//closes file
	if ((strcmp(argv[1], "-byrank") == 0) ||(strcmp(argv[1], "-top10") == 0) )//if argv[1] is top10 or by rank
	{
		if((strcmp(argv[1], "-top10") == 0))//if top10 is called for
			max = 10;//sets printing limit to ten
		for ( it = A.begin(); it!=A.end(); ++it)
		{
			h.add_data(it);//inserts map of each person in heap
		}

		h.heapify();
		//for ( it = A.begin(); it!=A.end(); ++it)
		while(!h.empty()){//while heap is not empty
   Iterator temp;
			temp = h.extract_top();//gets the top item of the heap
			temp->first.print_name(lengthLarge);//prints the name
			temp->second.print_labscores();//prints the lab scores
			if(max == 10) //if printing top 10
				num++;//increments till we reach 10
			if(num == 10)
				exit(0);//exits once it reaches ten

		}
		exit(0);
	}
	for ( it = A.begin(); it!=A.end(); ++it)
	{
		it->first.print_name(lengthLarge);//print name in byname order
		it->second.print_labscores();//print labscores for each name
	}
}







