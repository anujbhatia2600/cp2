#include "cal.h"


string memeberInfoFileName = "Member.txt";
string intakeFileName = "Intake.txt";


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

	while(atof(cal.c_str()) < 0 || atof(cal.c_str()) > 1000)
	{
		cout << "\nERROR!, Please enter a valid number" << endl;
		if(atof(cal.c_str()) < 0)
			cout << "Enter calories (more than 0): ";
		else
			cout << "Enter calories (less than 1000): ";
		cin >> cal;
	}

	//asking for confirmation of this input now!

	cout << "\n" << name << "\t" << cal << endl;
	cout << "Are you happy with his input? (Y/N) " << endl;
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
		cout << setw(20) << setw(20);
		cout << left;
		cout << m[i].food << "\t" << m[i].cal << endl;
	}
}

int search(Cal * m, int size, string name)
{
	for(int i = 0; i < size; i++)
	{
		if(m[i].food.find(name)!=-1)
		{
			int x = m[i].food.length();
			string c="";
			for (int j=0;j<x;j++)
			{
				if(m[i].food[j]==',')
				{//if it is anything that isnt a number or an alphabet then it completes the word and checks if that c==word
					if(c==name)
					{
						return i;
					}
					c="";
				}
				else
				{
					c+=m[i].food[j];//if the character of the line is alphabet or number then it adds it to the string
				}
			}
			if(c==name)
			{
				return i;
			}
		}

	}
	return -1;
}

void deleteFood(Cal * &m, int &size)
{
	for(int i = 1; i < size; i++)
	{
		cout << "[" << i << "] " << m[i].food << "\t" <<m[i].cal << endl;
	}

	int dec;
	cout << "Choose the number of item you want to delete: ";
	cin >> dec;
	while(dec < 1 || dec >= size)
	{
		cout << "Enter a valid number: ";
		cin >> dec;
	}
	Cal * d = new Cal[size-1];
	int i=0;
	while(i!=size-1){
		if(i==dec)
		{
			continue;
		}
		else
		{
			d[i].food=m[i].food;
			d[i].cal=m[i].cal;
			i++;
		}
	}
	size=size-1;
	delete [] m;
	m=d;
	saveDailyIntake(m,size);
	cout << "The item has been deleted\n" << endl;

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

void addFoodToIntake(Cal * &intake, int &intakesize,Cal * database, int databasesize, string nameToFind)
{
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
	cout<<database[index].food<<" has been added to the daily intake\n"<<endl;
}

double addingTotalIntake(Cal * intake, int size)
{
	double total;

	if(size==1)
	{
		return 0;
	}
	for(int i = 1; i < size; i++)
	{
		total += atof( intake[i].cal.c_str());
	}
	return total;
}

void updateDailyIntake(Cal *&intake, int size, Cal * database, int databaseSize)
{

	if(size == 1)
	{
		cout << "Your list is empty and no items are available to be updated\n" << endl;
		return;
	}
	for(int i = 1; i < size; i++)
	{
		cout << "[" << i << "] " << intake[i].food << "\t" <<intake[i].cal << endl;
	}

	int dec;
	cout << "Choose the number of item you want to edit: ";
	cin >> dec;
	while(dec < 0 || dec >= size)
	{
		cout << "Enter a valid number: ";
		cin >> dec;
	}

	string foodname; string cal;
	cout <<"Enter the food you want to replace it with: ";
	cin >> foodname;

	int lengthOfName = foodname.length();

	while(lengthOfName < 2)
	{
		cout << "\nERROR!, Please enter a valid name" << endl;
		cout << "Enter a name (more than 1 letter): ";
		cin >> foodname;
		lengthOfName = foodname.length();
	}

	transform(foodname.begin(),foodname.end(),foodname.begin(),::toupper);

	int index = search(database, databaseSize, foodname);
	if(index != -1)
	{
		cout << "\n" << database[index].food << "\t" << database[index].cal << endl;
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
			cout << "The list has been updated\n" << endl;
			intake[dec].food = database[index].food;
			intake[dec].cal = database[index].cal;
			saveDailyIntake(intake,size);
		}
		else
		{
			cout << "\nInput again" << endl;
			updateDailyIntake(intake, size, database, databaseSize);
		}
	}
	else
	{
		cout << "Enter the number of calories " << foodname << " contains: ";
		cin >> cal;

		while(atof(cal.c_str()) < 0 || atof(cal.c_str()) > 1000)
		{
			cout << "\nERROR!, Please enter a valid number" << endl;
			if(atof(cal.c_str()) < 0)
				cout << "Enter calories (more than 0): ";
			else
				cout << "Enter calories (less than 1000): ";
			cin >> cal;
		}

		intake[dec].food = foodname;
		intake[dec].cal = cal;
		saveDailyIntake(intake,size);
		cout << "The list has been updated\n" << endl;

	}

}
void resetIntake(Cal * &intake, int &size )
{
	size=1;
	Cal * intakeNew = new Cal [size];//always going to add only 1 element so +1

	for(int i = 0; i < size; i++)
	{
		intakeNew[i] = intake[i];
	}

	delete [] intake;
	intake = intakeNew;
	saveDailyIntake(intake,size);
}

void updatePersonInfo(Person &x)
{
	bool continues = true; // this is for exiting the do loop

	do{
		cout << "\n";
		cout << "[ 1 ]  Change name" << endl;
		cout << "[ 2 ]  Change weight" << endl;
		cout << "[ 3 ]  Change height" << endl;
		cout << "[ 4 ]  Change age" << endl;
		cout << "[ 5 ]  Change gender" << endl;
		cout << "[ 6 ]  To quit" << endl;

		cout << "\n\t\t\t\t Enter one number for your option:  ";
		char choice;
		cin >> choice;

		switch(choice)
		{
			case '1':
			{
				string name; cout << "Enter the name: "; cin >> name;
				int lengthOfName = name.length();

				while(lengthOfName < 2)
				{
					cout << "\nERROR!, Please enter a valid name" << endl;
					cout << "Enter a name (more than 1 letter): ";
					cin >> name;
					lengthOfName = name.length();
				}

				x.name = name;
				saveMemberInfo(x);
				return;
			}
			case '2':
			{
				double weight; cout << "Enter the weight: "; cin >> weight;

				while(weight < 40 || weight > 400)
				{
					cout << "\nERROR!, Please enter a valid weight" << endl;
					cout << "Enter weight (40 < weight < 400): ";
					cin >> weight;
				}

				x.weight = weight;
				saveMemberInfo(x);

				return;
			}
			case '3':
			{
				double height; cout << "Enter the height: "; cin >> height;

				while(height < 100 || height > 300)
				{
					cout << "\nERROR!, Please enter a valid height" << endl;
					cout << "Enter height (100 < height < 300 in cm): ";
					cin >> height;
				}

				x.height = height;
				saveMemberInfo(x);


				return;
			}
			case '4':
			{
				int age; cout << "Enter the age: "; cin >> age;

				while(age < 10 || age > 80)
				{
					cout << "\nERROR!, Please enter a valid age" << endl;
					cout << "Enter age (10 < age < 80): ";
					cin >> age;
				}

				x.age = age;
				saveMemberInfo(x);

				return;
			}
			case '5':
			{
				char genderChar; cout << "Enter the gender: "; cin >> genderChar;

				while(genderChar != 'm' && genderChar != 'f' && genderChar != 'M' && genderChar != 'F')
				{
					cout << "\nERROR!, Please enter a valid gender" << endl;
					cout << "Enter gender (M or F): ";
					cin >> genderChar;
				}
				bool gender = true;
				if (genderChar == 'f' || genderChar == 'F')
					gender = false;

				x.gender = gender;
				return;
			}
			default:
			{
				cout << "Invalid choice.";
				break;
			}
		}
	}while(continues);

}
