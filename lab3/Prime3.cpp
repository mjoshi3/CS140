#include<cmath>
#include<iomanip>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<stdlib.h>
/* Prime3.cpp
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
  vector <int> primeNumber;
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
}    while(num<=number);
}

}

bool isprime::operator()(int number)
{
  look(number);
  bool prime;
  prime = binary_search (primeNumber.begin(), primeNumber.end(), number);//returns true if prime, false otherwise
 return prime;
 
  
}

int random_number()//gives a random number between 1-100
{
  int randomNum = rand() %100 +1;
	return randomNum;
}

int main(int argc, char *argv[])
{
	int N;
  if(argv[1] == NULL)//checks if user included a number; if not, number is set to 10
  {
    N= 10;
  }
  else
  {
  N= atoi(argv[1]);
  }      
  
	srand(N);
  
	vector< int > randomVector(N);//creates a vector of the number entered in by the user
	vector< int > boolVector(N);//creates a vector that will contain boolean numbers
  isprime isPrime1;//an instance of the class isprime

  generate (randomVector.begin(), randomVector.end(),random_number);//inserts random numebers into the randomVecotr

  transform( randomVector.begin(), randomVector.end(),boolVector.begin(), isPrime1);//inserts the prime numbers repersented by a 1 into the boolVector
  
	int c = count( boolVector.begin(), boolVector.end(),true);//counts the number of prime numbers

	cout << "Sequence contains "<<c<<" prime numbers."<<endl;

}
