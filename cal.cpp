#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
using namespace std;

string memeberInfoFileName = "Member.txt";
string intakeFileName = "Intake.txt";
struct Person
{
	string name;
    double height;
    int age;
    double weight;
    bool gender; //male is true, and female is false
};


struct Cal
{
	string food;
	string cal;
};


int countDailyIntakeFile()
{
	ifstream fin(intakeFileName.c_str());
	if(fin.fail())
	{
		return 0;
	}
	
	string temp; int i = 0;
	
	while (getline(fin,temp))
	{	
		i++;
	}
	fin.close();
	return i;
}


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
		foodItems[i].cal = calFood;//converting string to double is must as its calories
		
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
		if(i != num-1)
			fout << foodItems[i].food << ";" << foodItems[i].cal << endl;
		else
			fout << foodItems[i].food << ";" << foodItems[i].cal;
	}
	
}

void addFood(Cal * &foodItems, int &size, string name)
{

	int lengthOfName = name.length();
	
	while(lengthOfName < 2)
	{
		cout << "\nERROR!, Please enter a valid name" << endl;
		cout << "Enter a name (more than 1 letter): ";
		cin >> name;
		lengthOfName = name.length();
	}
	
	string cal;
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
		//write a code which will add this added food item to the persons daily intake list*
		transform(foodItems[size-1].food.begin(),foodItems[size-1].food.end(),foodItems[size-1].food.begin(),::toupper);
		saveDatabase(foodItems, size);
		
		cout << "You've entered: \n" << name << "\t" << cal <<endl;
		cout << "This new entry has been saved to the main database!" << endl;
	}
	else
	{
		cout << "\nInput again" << endl;
		addFood(foodItems, size,name);
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
		if(m[i].food.find(name)!=-1)
			return i;
	}
	return -1;
}
/*
void deleteFood(Cal * &m, int &size)
{
	string foodToDel;
	cin >> foodToDel;
	
	if(search(foodToDel)!= -1)
	{
		
		size--;
	}
}
*/

void loadMemberInfo(Person & x)
{
	ifstream fin(memeberInfoFileName.c_str());
	
	if(fin.fail())
	{
		cout <<"File doesn't exist" <<endl;
		exit(1);
	}
	string name; double height;	int age; double weight; char gender; bool genderBool = false;
	if(fin.peek() == std::ifstream::traits_type::eof())
	{
		cout<<"Please enter you Name: ";
		cin>>name;
		cout<<endl;
		cout<<"Please enter you Height(cm): ";
		cin>>height;
		cout<<endl;
		cout<<"Please enter you Age: ";
		cin>>age;
		cout<<endl;
		cout<<"Please enter you Weight(kg): ";
		cin>>weight;
		cout<<endl;
		cout<<"Please enter you Gender(M/F): ";
		cin>>gender;
		if(gender == 'F' || gender == 'f')
		{
			genderBool = false;
		}
		cout<<endl;
		
		x.name = name;
		x.height = height;
		x.age = age;
		x.weight = weight;
		x.gender = genderBool;
		return ;//have to exit otherwise it will try to find a file
	}
	else
	{
		while(fin >> name >> height >> age >> weight >> gender )
		{
			x.name = name;
			x.height = height;
			x.age = age;
			x.weight = weight;
			x.gender = gender;
		}
	}
	
	fin.close();
}

int Calculator(Person x)
{
	double cal;
	if(x.gender==false)
	{
		cal=10*(x.weight)+6.25*(x.height)-5*(x.age)-161;
	}
	else
	{
		cal=10*(x.weight)+6.25*(x.height)-5*(x.age)+5;	
	}
	return (int)cal;
}

void loadDailyIntake(Cal * &intake)
{
	ifstream fin(intakeFileName.c_str());
	
	if(fin.fail())
	{
		cout << "File doesn't exist" << endl;
		exit(1);
	}

	string name; string calFood; int i = 0;
	while (getline(fin, name, ';'))
	{	
		getline(fin, calFood);
	
		intake[i].food = name;
		intake[i].cal = calFood;//converting string to double is must as its calories
		i++;
	}
	fin.close();

}

void saveMemberInfo(Person x)
{
	ofstream fout(memeberInfoFileName.c_str());
	
	fout << x.name << endl;
	fout << x.height << endl;
	fout << x.age << endl;
	fout << x.weight << endl;
	fout << x.gender << endl;
	
	fout.close();
}


void saveDailyIntake(Cal * intake, int num)
{
	ofstream fout (intakeFileName.c_str());
	if(fout.fail())
	{
		cout << "Error in opening the file!" << endl;
		exit(1);
	}
	
	for(int i = 0; i < num; i++)
	{
		if(i !=  num-1)
			fout << intake[i].food << ";" << intake[i].cal << endl;
		else
			fout << intake[i].food << ";" << intake[i].cal;
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

void addFoodToIntake(Cal * &intake, int &intakesize,Cal * database, int databasesize)
{
	string nameToFind;
	cout << "Enter food name: ";
	getline(cin,nameToFind);
	transform(nameToFind.begin(),nameToFind.end(),nameToFind.begin(),::toupper);
	
	int index=search(database,databasesize,nameToFind);
	growIntakeDatabase(intake, intakesize);
		
	if(index!=-1)//write the argument
	{
		intake[intakesize-1].food = database[index].food ;//we need to load the main database array
		intake[intakesize-1].cal =database[index].cal ;//how should we access the main database array?
		saveDailyIntake(intake,intakesize);//adding to the intakefile
	}
	else
	{
		addFood(database, databasesize, nameToFind);
		intake[intakesize-1].food = database[databasesize-1].food ;//we need to load the main database array
		intake[intakesize-1].cal =database[databasesize-1].cal ;//how should we access the main database array?
		saveDailyIntake(intake,intakesize);//adding to the intakefile
		saveDatabase(database,databasesize);
	}
}


int main()
{
	int numberOfFoodItems = countItems();
	Cal * foodItems = new Cal [numberOfFoodItems];//array will contain the name and calories
	
	int counterIntake = countDailyIntakeFile();
	Cal * dailyIntake = new Cal [counterIntake];//array will contain the name and calories
	
	loadCalDatabase(foodItems);
	loadDailyIntake(dailyIntake);
	
	printList(foodItems, numberOfFoodItems);
	
	addFoodToIntake(dailyIntake,counterIntake, foodItems, numberOfFoodItems);
	printList(dailyIntake, counterIntake);

}

