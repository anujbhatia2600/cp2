#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include "cal.h"
using namespace std;

int main()
{
	int numberOfFoodItems = countItems();
	Cal * foodItems = new Cal [numberOfFoodItems];//database array

	int counterIntake = countDailyIntakeFile();
	Cal * dailyIntake = new Cal [counterIntake];//array will contain the name and calories

	Person x; //creating person
	loadMemberInfo(x);//loading the person information
	
	double dailyReq = Calculator(x); //calculates optimum calories for the person according to its info
	cout << "You should aim to reach " << dailyReq << " calories everyday!" << endl; //telling the person how much is there optimum cal
	
	loadDailyIntake(dailyIntake);
	loadCalDatabase(foodItems);

	bool continues = true; // this is for exiting the do loop
	
	do{
		cout << "\n";
		cout << "[ A ]  To add meals to your daily intake" << endl;
		cout << "[ D ]  Delete an item from todays intake" << endl;
		cout << "[ L ]  List today's intake" << endl;
		cout << "[ I ]  Print my information" << endl;
		cout << "[ P ]  Print today's total calorie intake" << endl;
		cout << "[ U ]  Update todays intake" << endl;
		cout << "[ X ]  Update your information" << endl;
		cout << "[ R ]  Reset today's daily intake" << endl;
		cout << "[ Q ]  To quit" << endl;

		cout << "\n\t\t\t\t Enter one letter for your option:  ";
		char choice;
		cin >> choice;

		if(choice >= 'A' && choice <= 'Z')
			choice += 32; //converting the char into lower case!
		
		switch(choice)
		{
			case 'a':
			{
				string nameToFind;
				cout << "Enter food name: ";
				cin.ignore(); //need this for getline to work and not escape this getline
				getline(cin, nameToFind);
				spacetocomma(nameToFind);
				addFoodToIntake(dailyIntake, counterIntake, foodItems, numberOfFoodItems, nameToFind);
				break; 
			}
			case 'd':
			{
				deleteFood(dailyIntake,counterIntake);
				break;
			}
			case 'l':
			{
				printList(dailyIntake,counterIntake);
				break;
			}
			case 'i':
			{
				cout << "Name: "<< x.name << endl;
				cout << "Age: "<< x.age << " years"<<  endl;
				cout << "Weight: "<< x.weight << " kgs" << endl;
				cout << "Height: "<< x.height << " cm" << endl;
				string g = "Male";
				if (x.gender == false) //as gender is a boolean, we need this if statement
					g = "Female";
				cout << "Gender: "<< g << "\n"<< endl;
				break;
			}
			case 'p':
			{
				dailyReq=Calculator(x);
				double m = addingTotalIntake(dailyIntake, counterIntake);
				cout << "Your total calories are: " << m << endl;
				if(dailyReq - m >= 0)
					cout << "You have " << dailyReq - m << " left for the day" << endl; //telling the user how many calories are left for the day
				else
				{
					cout << "WARNING, you have exceeded your requirement for the day!"; //warning!
				}
				break;
			}
			case 'r':
			{
				resetIntake(dailyIntake, counterIntake);
				cout << "Your list is empty now!\n" << endl;
				break;
			}
			case 'u':
			{
				updateDailyIntake(dailyIntake, counterIntake, foodItems, numberOfFoodItems);
				break;
			}
			case 'x':
			{
				updatePersonInfo(x);
				dailyReq = Calculator(x);//updating the dailyReq according to the change in person
				cout << "Now you should aim to reach " << dailyReq << " calories everyday!" << endl;
				break;
			}
			case 'q':
			{
				continues = false;
				break;
			}
			default:
			{
				cout << "Invalid choice."; //if they input something other than the required input, it is considered invalid
				break;
			}
		}
	}while(continues);
}
