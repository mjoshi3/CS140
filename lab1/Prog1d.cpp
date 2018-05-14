#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<cctype>
#include<string>
using namespace std;
/* Prog1d.cpp
 *    Author:  Marvin Joshi
 *    Date:    September 6, 2017
 *
 *      THis program encodes and decodes rhat is entered in by the  
 *      user and increased each character by a number entered in by 
 *      the user. 
 *      
 **/
void encode(string& line ,  int size )
{
	char letter;
	int j = 0;
	for (int i = 0; i<line.length();i++)
	{
		if(isalpha(line.at(i)))//checks if character is an alphabetical letter
		{
			if(islower(line.at(i)))//checks if lower case
			{
				for (int j = 0;j<size;j++)
				{
					line.at(i)+=1;//moves letter up the alphabelt
					if (islower(line.at(i)))
					{}
					else
					{
						line.at(i) ='a';//sets character to 'a' if letter passes lower case 'z'
					}
				}
			}


			else if(isupper(line.at(i)))//checks if character is upper case
			{	
				for(int j=0; j<size;j++)
				{
					line.at(i)+=1;
					if (isupper(line.at(i)))
					{}
					else
					{
						line.at(i) ='A';//sets character to 'a' if letter passses upper case 'Z'
					}
				}			
			}
		}
		cout<<line.at(i);
	}
	cout<<endl;
}

void decode(string& line, int size)
{
	char letter;
	int j = 0;
	for (int i = 0; i<line.length();i++)
	{
		if(isalpha(line.at(i)))//checks if character is an alphabetical letter
		{
			if(islower(line.at(i)))//checks if lower case
			{
				for (int j = 0;j<size;j++)
				{
					line.at(i)-=1;//moves letter down alphabet 
					if (islower(line.at(i)))
					{}
					else
					{
						line.at(i) ='z';//sets character to 'z' if letter passes lower case 'a'
					}
				}
			}


			else if(isupper(line.at(i)))//checks if upper case
			{
				for(int j=0; j<size;j++)
				{
					line.at(i)-=1;
					if (isupper(line.at(i)))
					{}
					else
					{
						line.at(i) ='Z';//sets character to 'Z' if letter passes upper case 'a'
					}
				}
			}
		}
		cout<<line.at(i);
	}
	cout<<endl;

}


int main (int argc, char * argv[])
{	
	int num = 0;
	
	string line;

 while(1)
 {
	if (argc == 3)
	{
    num = atoi(argv[2]);//changes character from argv[2] to number
  if((num>=0&&num<10)==false)
  {
    cout<<"Usage: ./prog1d -decode|encode 0-9"<<endl;
    exit(0);
  }
		if (strcmp(argv[1],"-decode")==0)//if user enters in "-decode" then continues
		{

			for(int i = 0;i<10;i++)
			{
				if (num ==i)
				{	
					getline(cin,line);//takes in line entered in by user
					decode (line, num);//sends line to be decoded
				}
			}
      
      
      
		}
		else if (strcmp(argv[1], "-encode")==0)//checks to see if user enters in "_encode"
		{

			for (int i = 0; i<10;i++)
			{
				if(num == i)
				{	
					getline(cin, line);//takes in line entered in by user
					encode(line, num);//sends line to be encoded
				}
			}
     
      
		}
		else
    {
      cerr<<"Usage: ./prog1d -decode|encode 0-9"<<endl;
    }
	
	
	
  }
  else 
  {
    cout<<"Usage: ./prog1d -decode|encode 0-9"<<endl;//prints out error if not enough arguements
    exit(0);
  }
}
}
