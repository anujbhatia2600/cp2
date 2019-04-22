#include <iostream>
#include <string>
#include <fstream>

using namespace std;
string memeberInfoFileName = "Member.txt";
string intakeFileName = "Intake.txt"
struct Person
{
	string name;
    double height;
    int age;
    double weight;
    bool gender; //male is true, and female is false
};

int countDailyIntakeFile()
{
	ifstream fin(intakeFileName);
	
	string temp;
	int i = 0;
	while (getline(fin))
	{	
		i++;
	}
	fin.close();
	return i-1;
}

void loadMemberInfo(Person & x)
{
	ifstream fin(memeberInfoFileName);
		
	if(fin.fail())
	{
		cout <<"Error in opening the file" <<endl;
		exit(1);
	}
	
	string temp; double height;	int age; double weight; bool gender;
	
	while(fin >> temp >> height >> age >> weight >> gender )
	{
		x.name = name;
		x.height = height;
		x.age = age;
		x.weight = weight;
		x.gender = gender;
	}
	
	fin.close();
}

void loadDailyIntake(Cal * &intake)
{
	ifstream fin(intakeFileName);
	
	if(fin.fail())
	{
		cout << "Error in opening file" << endl;
		exit(1);
	}
	
	string temp; string calFood;
	while (getline(fin, temp, ';'))
	{	
		getline(fin, calFood);
		
		intake[i].food = temp;
		intake[i].cal = stod(calFood);//converting string to double is must as its calories
		
		i++;
	}
	fin.close();

}

void saveMemberInfo(Person x)
{
	ofstream fout(memeberInfoFileName);
	
	fout << x.name << endl;
	fout << x.height << endl;
	fout << x.age << endl;
	fout << x.weight << endl;
	fout << x.gender << endl;
	
	fout.close();
}

void saveDailyIntake(Cal * intake, int num)
{
	ofstream fout (intakeFileName);
	if(fout.fail())
	{
		cout << "Error in opening the file!" << endl;
		exit(1);
	}
	
	for(int i = 0; i < num; i++)
	{
		fout << foodItems[i].food << ";" << foodItems[i].cal << endl;
	}
	
	fout.close();
}

void growIntakeDatabase(Cal * &intake, int & inSize)
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

void addFoodToIntake(Cal * &intake, int &size)
{
	string nameToFind;
	
	if(search())//write the argument
	{
		growIntakeDatabase(intake, size);
		int index = search();
		intake[size-1].food = ;//we need to load the main database array
		intake[size-1].cal = ;//how should we access the main database array?
		
		transform(intake[size-1].food.begin(),intake[size-1].food.end(),intake[size-1].food.begin(),::toupper);
		saveDailyIntake();
		
	}
	
}

void printList(Cal * m, int size)
{
	for(int i = 0; i < size; i++)
	{
		cout << m[i].food << "\t" << m[i].cal << endl;
	}
}

double countCal(Cal* m, int size)
{
	int total = 0;
	
	for(int i = 0; i < size; i++)
	{
		total += m[i].cal;
	}
	return total;
}

int main()
{	
	int size = countDailyIntakeFile();
	Cal * dailyIntake [size];
	
	
}
