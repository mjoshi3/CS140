#include<cmath>
#include<iomanip>
#include<iostream>
#include<algorithm>
#include<vector>
/* Prime2.cpp
   Author:  Marvin Joshi
   Date:    October 1,2017

   This program reads a number by the user and checks if it is
   prime. The program creates a list of prime numbers from 2
   and stops adding to the list when you reach the next prime
   number after the number entered in by the user.
   */
using namespace std;

class isprime {
  public:
  isprime() { primeNumber.push_back(2); }//pushes to into the list
  bool operator()(int);
   
  private:
  vector <int>primeNumber;
  typedef vector<int>::iterator Iterator;//creates iterator to go through primeNUmber list
  void look(int number); //inserts prime numbers into a list
};
void isprime::look(int number)
{
int num;
int back = 3;
if(primeNumber.back() == 2)
{
  back = 3;
}
else
{
  back = primeNumber.back()+1;//sets the number to test to a number 1 more than the back of the prime list
}
if(number>primeNumber.back()){//checks if prime number has already been entered
do
{
  
  num =primeNumber.back(); 
  bool prime = true;
  for(int j=2;j<=sqrt(back) ;j++)//checks if number if prime or not
  {
    if(back % j == 0)
    {
      prime=false;
      break;
    }
  }  
  if(prime) 
  {
    primeNumber.push_back(back);
  }  
  back++;
} while(num<=number);
}

}

bool isprime::operator()(int number)
{

 look(number);

  
  for(Iterator p =primeNumber.begin();p!=primeNumber.end();++p)//searches through the list
  {
 
    if(number == *p)//if number is found in prime list
	  {
	    return true;
	  }
  }
 
 return false;
}

int main()
{
	isprime pcheck;
	int number;

	while ( cin>>number ) {//reads in number form user
	  if (pcheck(number))//if number is prime
	    cout << number<<" is a prime number"<<endl;	}
}
