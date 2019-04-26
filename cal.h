#ifndef CAL_H
#define CAL_H
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iomanip>


using namespace std;
struct Person //structure of a person
{
	string name;
    double height;
    int age;
    double weight;
    bool gender; //male is true, and female is false
};

struct Cal //structure of a calorie
{
	string food;
	string cal; //made this string as its easy to use, will convert to double when we need to add!
};

//listing all function prototypes
int countDailyIntakeFile();
int countItems();
void loadCalDatabase(Cal * &);
void growDatabase(Cal * &, int & );
void saveDatabase(Cal *, int);
void addFood(Cal * &, int &, string);
void printList(Cal * , int );
int search(Cal * , int , string );
void deleteFood(Cal * &, int &);
void loadMemberInfo(Person & );
int Calculator(Person );
void loadDailyIntake(Cal * &);
void saveMemberInfo(Person );
void saveDailyIntake(Cal * , int );
void growIntakeDatabase(Cal * &, int & );
void addFoodToIntake(Cal * &, int &,Cal *, int , string);
double addingTotalIntake(Cal * , int );
void updateDailyIntake(Cal *&, int , Cal * , int );
void resetIntake(Cal * &, int & );
void updatePersonInfo(Person &x);

#endif
