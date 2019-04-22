#include <iostream>
#include <string>
#include <fstream>
#include<algorithm>
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
	double cal;
};
int countDailyIntakeFile()
{
	ifstream fin(intakeFileName.c_str());
	if(fin.fail()){
		return 0;
	}
	string temp;
	int i = 0;
	while (getline(fin,temp))
	{	
		i++;
	}
	fin.close();
	return i-1;
}

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
double Calculator(Person x)
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
	return cal;
}
void loadDailyIntake(Cal * &intake)
{
	ifstream fin(intakeFileName.c_str());
	
	if(fin.fail())
	{
		cout << "Error in opening file" << endl;
		exit(1);
	}
	
	string temp; string calFood; int i = 0;
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
	ofstream fout(memeberInfoFileName.c_str());
	
	fout << x.name << endl;
	fout << x.height << endl;
	fout << x.age << endl;
	fout << x.weight << endl;
	fout << x.gender << endl;
	
	fout.close();
}

/*void saveDailyIntake(Cal * intake, int num)
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

void addFoodToIntake(Cal * &intake, int &intakesize,Cal * database, int databasesize)
{
	string nameToFind;
	getline(cin,nameToFind);
	transform(nameToFind.begin(),nameToFind.end(),nameToFind.begin(),::toupper);
	int index=search(database,databasesize,nameToFind);
	if(index!=-1)//write the argument
	{
		growIntakeDatabase(intake, intakesize);
		intake[size-1].food = database[index].food ;//we need to load the main database array
		intake[size-1].cal =database[index].cal ;//how should we access the main database array?
		saveDailyIntake(intake,intakesize);//adding to the intakefile
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
*/
int main()
{	
	int intakesize = countDailyIntakeFile();
	Cal * dailyIntake [intakesize];
	Person x;
	loadMemberInfo(x);
	saveMemberInfo(x);
	
	
}
