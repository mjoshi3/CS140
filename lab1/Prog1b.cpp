#include<iostream>
using namespace std;
/* Prog1c.cpp
**    Author:  Marvin Joshi
**    Date:    August 30, 2017
**
**      This program reads numbers enetered in by the user and 
**		finds the total numbers entered, the sum, the min, and
**		the max.
**
*/

int main()
{
	int numbers = 0, num1;
	int sum = 0;
	int min = 0;
	int max = 0;
	while(cin>>num1)
		{
					
		numbers ++;
		if(numbers ==1)//Sets the the first entered to the min and the max
		{
			min = num1;
			max = num1;
		}
		sum +=num1;
		if(num1>max)//compares the current and previous number read to find min
		{
			max = num1;
		}
		if(num1<min)//compares the current and previous number read to find max
		{
			min = num1;
		}
}	

	cout<<"N = "<<numbers<<endl;//outputs all the inforamtion
	cout<<"sum = "<<sum<<endl;
	cout<<"min = "<<min<<endl;
	cout<<"max = "<<max<<endl;
	}
