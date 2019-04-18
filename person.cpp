#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Person
{
	string name;
    double height;
    int age;
    double weight;
    bool gender; //male is true, and female is false
    Cal dailyIntake[]
};

int numberOfMembers;
Person familyMembers [numberOfMembers];

void loadMembers()
{
	ifstream fin("FamMembers.txt");
	
	if(fin.fail())
	{
		cout <<"Error in opening the file" <<endl;
		exit(1);
	}
	
	String temp;
	double height;
	int age;
	double weight;
	bool gender;
	
	
		
}
