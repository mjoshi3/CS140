#include <cmath>
#include <iostream>
#include <iomanip>
/* Prime1.cpp
   Author:  Marvin Joshi
   Date:    October 1,2017

   This program reads a number by the user and check if it is
   prime. The bool function checks if the number entered in
   is prime by going through a for loop that stops going once
   you reach the square root of the number.
   */
   
using namespace std;

bool isprime(int number) 
{
	int val;
	bool num = true;
	val = sqrt(number);
  while(number == 1)//since 1 is not prime we make it not prime
  return false;
	for(int i =2; i<=val;i++)//loop through to see if prime
	{
		if(number%i == 0)//if remainder is 0
		{
			return false;//number is not prime
		}
	}
	return true;//if no divisible number is found, number is prime

};

int main()
{
	int number;

	while ( cin>>number ) {//reads in numbers
	  if (isprime(number))//checks is number is prime or not
	    cout << number<<" is a prime number"<<endl;
	}
}
