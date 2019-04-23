#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "cal.h"

using namespace std;

int main()
{
	int numberOfFoodItems = countItems();
	Cal * foodItems = new Cal [numberOfFoodItems];//array will contain the name and calories
	
	int counterIntake = countDailyIntakeFile();
	Cal * dailyIntake = new Cal [counterIntake];//array will contain the name and calories
	
	loadCalDatabase(foodItems);
	loadDailyIntake(dailyIntake);
	
	
	bool continues = true; // this is for exiting the do loop
	
	do{
		cout << "\n";		
		cout << "[ A ]  To add meals to your daily intake" << endl;
		cout << "[ L ]  List today's intake" << endl;
		cout << "[ P ]  Print today's total calorie intake" << endl;
		cout << "[ Q ]  To quit" << endl;
		
		cout << "\n\t\t\t\t Enter one letter for your option:  ";
		char choice;
		cin >> choice;//convert the char into lower case!
		//
		//
		
		switch(choice)
		{
			case 'a':
			{
				
				addFoodToIntake(dailyIntake, counterIntake, foodItems, numberOfFoodItems);
				break; //case 1 break
			}
			case 'l':
			{
				printList(dailyIntake,counterIntake);
				break; //case 2 break
			}
			case 'p':
			{
				double x = addingTotalIntake(dailyIntake, counterIntake);
				cout << "Your total calories are: " << x << endl;
				break;
			}
			case 'q':
			{
				continues = false;
				break;
			}
			default:
			{
				cout << "Invalid choice.";
				break;
			}
		}
	}while(continues);
}
