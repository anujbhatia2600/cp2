#ifndef CAL_H
#define CAL_H
#include<iostream>
int countDailyIntakeFile();
int countItems();
void loadCalDatabase(Cal * &);
void growDatabase(Cal * &, int & );
void saveDatabase(Cal *, int);
void addFood(Cal * &, int &, string);
void printList(Cal * , int );
int search(Cal * , int , string );
void loadMemberInfo(Person & );
int Calculator(Person );
void loadDailyIntake(Cal * &);
void saveMemberInfo(Person );
void saveDailyIntake(Cal * , int );
void growIntakeDatabase(Cal * &, int & );
void addFoodToIntake(Cal * &, int &,Cal *, int);

#endif

