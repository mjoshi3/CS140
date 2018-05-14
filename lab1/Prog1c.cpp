#include <iostream>
using namespace std;
/* Prog1c.cpp
 *    Author:  Marvin Joshi
 *    Date:    August 30, 2017
 *
 *      This program uses a class called Stats to read the values 
 *      that was enetered in by the user. It then prints out the 
 *      total of numbers enetered, the sum of all the numbers, 
 *      the minimum number enetered, and the maximum number enetered.
 **/
class Stats
{
	int numbers; //total amount of numbers entered in by the user
	int sum;    //sum of all of the numbers
	int min;   //smallest number entered in by the user
	int max;  //largest amount entered in by the user
	public:
	void push(int);
	void print();
};
int main ()
{
	int num1;
	Stats A;
	A.push( num1);
	A.print();
}
void Stats::push (int num)
{
numbers=0;
sum=0;
min=0;
max=0;

//Reads in the numbers entered
	 while(cin>>num)
	{
	    numbers ++;
	    if(numbers ==1)
	    {
	       min = num;	
		   max = num;
	    }
// Calculates the sum of all the numbers		
	 sum +=num;
//Finds the minimum and maximum numbers entered
	 if(num>max)
	 {
	    max = num;
	 }
	 if(num<min)
	 {
		 min = num;
	 }
	}
}

void Stats::print()
{	
//Prints the total numbers read, the sum, the min and the max
	cout<<"N = "<<numbers<<endl;
    cout<<"sum = "<<sum<<endl;
    cout<<"min = "<<min<<endl;
    cout<<"max = "<<max<<endl;
}
