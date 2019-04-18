#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
using namespace std;

struct Cal
{
	string food;
	double cal;
};

int countItems()
{
	ifstream fin("CalFile.txt");
	
	string temp;
	int i = 0;
	while (getline(fin, temp, ';'))
	{	
		i++;
	}
	fin.close();
	return i-1;
}

void loadCalDatabase(Cal * &foodItems)//loading from the main database
{	
	ifstream fin("CalFile.txt");
	
	if(fin.fail())
	{
		cout << "Error in opening file" << endl;
		exit(1);
	}

	
	string temp; string calFood;
	int i = 0;
	while (getline(fin, temp, ';'))
	{	
		getline(fin, calFood);
		
		foodItems[i].food = temp;
		foodItems[i].cal = stod(calFood);//converting string to double is must as its calories
		
		i++;
	}
	fin.close();
	

}

void growDatabase(Cal * &intake, int & inSize)
{
	Cal * intakeNew = new Cal [inSize +1];//always going to add only 1 element so +1
	
	for(int i = 0; i < inSize; i++)
	{
		intakeNew[i] = intake[i];
	}
	
	delete [] intake;
	
	intake = intakeNew;
	inSize += 1;//incrementing the size
}


void saveDatabase(Cal * foodItems, int num)//saving the updated list to the database
{
	ofstream fout ("CalFile.txt");
	if(fout.fail())
	{
		cout << "Error in opening the file!" << endl;
		exit(1);
	}
	
	for(int i = 0; i < num; i++)
	{
		fout << foodItems[i].food << ";" << foodItems[i].cal << endl;
	}
	
}

void addFood(Cal * &foodItems, int &size)
{
	string name;
	cout << "Enter a food name: ";
	cin >> name;
	int lengthOfName = name.length();
	
	while(lengthOfName < 2)
	{
		cout << "\nERROR!, Please enter a valid name" << endl;
		cout << "Enter a name (more than 1 letter): ";
		cin >> name;
		lengthOfName = name.length();
	}
	
	double cal;
	cout << "\nEnter the number of calories the food contains: ";
	cin >> cal;
	
	//asking for confirmation of this input now!
	
	cout << "\n" << name << "\t" << cal << endl;
	cout << "Are you happy with his input? (Y/N) ";
	char charDec;
	cin >> charDec;//taking a char and will convert to bool then
	
	while(charDec != 'y' && charDec != 'Y' && charDec != 'n' && charDec != 'N' )
	{
		cout << "\nPlease enter a valid input (Y/N): ";
		cin >> charDec;
	}
	
	bool decision = false;
	
	if(charDec == 'y' || charDec == 'Y')
	{	decision = true;
	}
	
	if(decision)
	{
		//number of elements is the case here
		growDatabase(foodItems, size);//size will get updated
	
		foodItems[size-1].food = name;
		foodItems[size-1].cal = cal;	
		//write a code which will add this added food item to the persons daily intake list
		transform(foodItems[size-1].food.begin(),foodItems[size-1].food.end(),foodItems[size-1].food.begin(),::toupper);
		saveDatabase(foodItems, size);
		
		cout << "You've entered: \n" << name << "\t" << cal <<endl;
		cout << "This new entry has been saved to the main database!" << endl;
	}
	else
	{
		cout << "\nInput again" << endl;
		addFood(foodItems, size);
	}
}

void printList(Cal * m, int size)
{
	for(int i = 0; i < size; i++)
	{
		cout << m[i].food << "\t" << m[i].cal << endl;
	}
}

int search(Cal * m, int size, string name)
{
	for(int i = 0; i < size; i++)
	{
		if(m[i].food == name)
			return i;
	}
	return -1;
}

void deleteFood(Cal * &m, int &size)
{
	string foodToDel;
	cin >> foodToDel;
	
	if(search(foodToDel)!= -1)
	{
		
		size--;
	}
}

int main()
{
	int numberOfFoodItems = countItems();
	Cal * foodItems = new Cal [numberOfFoodItems];//array will contain the name and calories
	
	loadCalDatabase(foodItems);
	
	printList(foodItems, numberOfFoodItems);
	
	addFood(foodItems, numberOfFoodItems);
	
	
	printList(foodItems, numberOfFoodItems);
}

