#include "cal.h"


string memeberInfoFileName = "Member.txt";
string intakeFileName = "Intake.txt";


int countDailyIntakeFile()//function to count the number of items present in the Intake file
{
	ifstream fin(intakeFileName.c_str());//opening the Intake file
	if(fin.fail())
	{
		return 0;
	}

	string temp; 
	int i = 0;
	while (getline(fin,temp))
	{
		i++;//counter to count the number lines
	}
	fin.close();
	return i;//returns the number of lines
}
void spacetocomma(string &x)// a function to convert the spaces to commas so that it can be added to the calfile and the intake file for easy searching and deleting
{
	int y=x.length();
	for (int i=0;i<y;i++){
		if(x[i]==' '){
			x[i]=',';
		}
	}
}

int countItems()//counts the number of items present in the main database i.e. Calfile
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

void loadCalDatabase(Cal * &foodItems)//loading from the main database i.e Calfile
{
	ifstream fin("CalFile.txt");

	if(fin.fail())
	{
		cout << "Error in opening file" << endl;
		exit(1);
	}
	// stored the inputs in the file wherein the name of the food is separated by ; and hence the delimiter in the getline is ;

	string temp; 
	string calFood;
	int i = 0;
	while (getline(fin, temp, ';'))
	{
		getline(fin, calFood);//gets the calories of the corresponding food item

		foodItems[i].food = temp;//storing it into the array of the struct
		foodItems[i].cal = calFood;

		i++;
	}
	fin.close();


}

void growDatabase(Cal * &intake, int & inSize)
{
	Cal * intakeNew = new Cal [inSize +1];//increasing the size of the dynamic array by 1 as it is called every time the addFood function is called

	for(int i = 0; i < inSize; i++)
	{
		intakeNew[i] = intake[i];
	}

	delete[] intake;

	intake = intakeNew;
	inSize += 1;//incrementing the size
}


void saveDatabase(Cal * foodItems, int num)//saves the array of the food into the database file i.e. CalFile
{
	ofstream fout("CalFile.txt");
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
	fout.close();
}

void addFood(Cal * &foodItems, int &size, string name)//function to add a new food item to the database file
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
	cout << "\nEnter the number of calories the food contains: ";//asks the user for corresponding calories of the new item he/she wants to add
	cin >> cal;

	while(atof(cal.c_str()) < 0 || atof(cal.c_str()) > 1000)//validation
	{
		cout << "\nERROR!, Please enter a valid number" << endl;
		if(atof(cal.c_str()) < 0)
			cout << "Enter calories (more than 0): ";
		else
			cout << "Enter calories (less than 1000): ";
		cin >> cal;
	}

	//confirms the input of the user

	cout << "\n" << name << "\t" << cal << endl;
	cout << "Are you happy with his input? (Y/N): ";
	char charDec;
	cin >> charDec;// stores the following further as a bool by converting the char into a bool

	while(charDec != 'y' && charDec != 'Y' && charDec != 'n' && charDec != 'N' )
	{
		cout << "\nPlease enter a valid input (Y/N): ";
		cin >> charDec;
	}

	bool decision = false;

	if(charDec == 'y' || charDec == 'Y')
	{	
		decision = true;
	}

	if(decision)
	{
		//if the user inputs 'Y' then the database needs to be grown and hence the growDatabse function is called
		growDatabase(foodItems, size);//size will get updated
		
		foodItems[size-1].food = name;//stores the new values to the struct array
		foodItems[size-1].cal = cal;
		transform(foodItems[size-1].food.begin(),foodItems[size-1].food.end(),foodItems[size-1].food.begin(),::toupper);//converts the line to upper case
		saveDatabase(foodItems, size);//updates the new values into the main database file by calling the saveDatabase function
		cout << "You've entered: \n" << name << "\t" << cal <<endl;
		cout << "This new entry has been saved to the main database!" << endl;
	}
	else
	{
		cout << "\nInput again" << endl;//asks the user to input another input if he/she feels that the input might be incorrect
		addFood(foodItems, size,name);
	}
}

void printList(Cal * m, int size)//function the print all the items present in the intake file
{
	for(int i = 0; i < size; i++)
	{
		cout << setw(20) << setw(20);
		cout << left;
		cout << m[i].food << "\t" << m[i].cal << endl;
	}
}

int search(Cal * m, int size, string name)//search function to check whether the item already exists in the main database and hence returns true or false
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
				{//breaks a word on whenever it finds a comma as the input we take is edited by the spacetocomma function to add commas instead of spaces 
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

void deleteFood(Cal * &m, int &size)// a function that allows the user to delete an existing entry in the daily intake file
{
	for(int i = 1; i < size; i++)
	{
		cout << "[" << i << "] " << m[i].food << "\t" <<m[i].cal << endl;
	}
	int dec;
	cout << "Choose the number of the item you want to delete: ";
	cin >> dec;
	while(dec < 1 || dec >= size)//validation to check if that many entries exist in the intake file
	{
		cout << "Enter a valid number: ";
		cin >> dec;
	}	
	Cal * d = new Cal[size-1];//makes a temp new dynamic array
	int i=0,j=0;
	while(j!=size){
		if(j==dec)// if that particular element need to be deleted then it skips adding it to the temp dynamic array
		{
			j++;			
			continue;
		}
		else
		{
			d[i].food=m[j].food;
			d[i].cal=m[j].cal;
			i++;
			j++;
		}
	}
	size=size-1;
	delete [] m;//deletes the existing the dynamic array
	m=d;//making the new array to the old array
	saveDailyIntake(m,size);//updating the intake file
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
	if(fin.peek() == std::ifstream::traits_type::eof())//checks if the file of the member is empty and hence asks for the details of the member
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
		while(fin >> name >> height >> age >> weight >> gender )//takes the inputs from the file and stores it into the struct
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
		cal=10*(x.weight)+6.25*(x.height)-5*(x.age)-161;//finds the optimum calorie intake for the females
	}
	else
	{
		cal=10*(x.weight)+6.25*(x.height)-5*(x.age)+5;//finds the optimum calorie intake for the males
	}
	return (int)cal;//casts the optimum calories into int
}

void loadDailyIntake(Cal * &intake)//function to load the exisiting values in the dailyintake files into the cal struct 
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
		intake[i].cal = calFood;
		i++;
	}
	fin.close();
}

void saveMemberInfo(Person x)//save the info of the person into the member files
{
	ofstream fout(memeberInfoFileName.c_str());

	fout << x.name << endl;
	fout << x.height << endl;
	fout << x.age << endl;
	fout << x.weight << endl;
	fout << x.gender << endl;

	fout.close();
}


void saveDailyIntake(Cal * intake, int num)// save the cal struct array into the intake file
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
	Cal * intakeNew = new Cal [inSize +1];//as the size of the array needs to increase only by one as it is being called everytime a new item is added to daily intake

	for(int i = 0; i < inSize; i++)
	{
		intakeNew[i] = intake[i];//copies all the existing elements into a temp dynamic array
	}

	delete [] intake;
	intake = intakeNew;//equating the temp array to the existing main array
	inSize += 1;//increasing the size variable
}

void addFoodToIntake(Cal * &intake, int &intakesize,Cal * database, int databasesize, string nameToFind)
{
	transform(nameToFind.begin(),nameToFind.end(),nameToFind.begin(),::toupper);//makes the inut string to upper case

	int index=search(database,databasesize,nameToFind);//gets the index of the ocation of the item in the array of cal
	growIntakeDatabase(intake, intakesize);//increases the size of the dynamic array

	if(index!=-1)
	{
		intake[intakesize-1].food = database[index].food ;//if it is found in the database then it stores the values into the intake struct
		intake[intakesize-1].cal =database[index].cal ;
		saveDailyIntake(intake,intakesize);//updates the intake file
	}
	else
	{
		addFood(database, databasesize, nameToFind);//else it asks the user to add a new value to the database and further stores it into the intake struct
		intake[intakesize-1].food = database[databasesize-1].food ;//stores the values of the newly added item into the intake struct
		intake[intakesize-1].cal =database[databasesize-1].cal ;
		
		saveDailyIntake(intake,intakesize);//saves the values into the intake file
		saveDatabase(database,databasesize);//saves the values into the main database i.e. calfile
	}
	
	cout<<intake[intakesize-1].food<<" has been added to the daily intake\n"<<endl;
}

double addingTotalIntake(Cal * intake, int size)//function to find the number calories the person has already intaken in the day so far
{
	double total = 0;

	if(size==1)
	{
		return 0;
	}
	for(int i = 1; i < size; i++)
	{
		total += atof( intake[i].cal.c_str() );
	}
	return total;
}

void updateDailyIntake(Cal *&intake, int size, Cal * database, int databaseSize)//function to update the values in the exisiting database
{

	if(size == 1)
	{
		cout << "Your list is empty and no items are available to be updated\n" << endl;//validation to check if there are elements present in the daily intake
		return;
	}
	for(int i = 1; i < size; i++)
	{
		cout << "[" << i << "] " << intake[i].food << "\t" <<intake[i].cal << endl;//gives a list to the user for the item to be updated
	}

	int dec;
	cout << "Choose the number of item you want to edit: ";
	cin >> dec;
	while(dec < 0 || dec >= size)
	{
		cout << "Enter a valid number: ";//validation to check the entered number is actually present
		cin >> dec;
	}

	string foodname; string cal;
	cout <<"Enter the food you want to replace it with: ";//asks for the value to be replaced with 
	cin >> foodname;

	int lengthOfName = foodname.length();

	while(lengthOfName < 2)
	{
		cout << "\nERROR!, Please enter a valid name" << endl;//validation for the value entered
		cout << "Enter a name (more than 1 letter): ";
		cin >> foodname;
		lengthOfName = foodname.length();
	}

	transform(foodname.begin(),foodname.end(),foodname.begin(),::toupper);//cahnges the entered name to uppercase

	int index = search(database, databaseSize, foodname);//looks up in the main database
	if(index != -1)
	{
		cout << "\n" << database[index].food << "\t" << database[index].cal << endl;//if it exists replaces it
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
		cout << "Enter the number of calories " << foodname << " contains: ";//else it asks for the calories as it is a new item
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
void resetIntake(Cal * &intake, int &size )//a function that marks the begining of the day. If called deletes all the existing files
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

void updatePersonInfo(Person &x)//function to update the information of the person 
{
	bool continues = true; // this is for exiting the do loop
	//menu for changing the information of the member
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
				string name; cout << "Enter the name: "; cin >> name;//cahnges the name of the member
				int lengthOfName = name.length();

				while(lengthOfName < 2)//validation for the name of the member
				{
					cout << "\nERROR!, Please enter a valid name" << endl;
					cout << "Enter a name (more than 1 letter): ";
					cin >> name;
					lengthOfName = name.length();
				}
				x.name = name;
				saveMemberInfo(x);//updates the file
				return;
			}
			case '2':
			{
				double weight;
				cout << "Enter the weight: "; //changes the weight of the member
				cin >> weight;
				while(weight < 40 || weight > 400)//validation for the weight
				{
					cout << "\nERROR!, Please enter a valid weight" << endl;
					cout << "Enter weight (40 < weight < 400): ";
					cin >> weight;
				}

				x.weight = weight;
				saveMemberInfo(x);//updates the member file

				return;
			}
			case '3':
			{
				double height;
				cout << "Enter the height: ";//changes the height of the member
				cin >> height;

				while(height < 100 || height > 300)
				{
					cout << "\nERROR!, Please enter a valid height" << endl;//validation of the height entered by the user
					cout << "Enter height (100 < height < 300 in cm): ";
					cin >> height;
				}

				x.height = height;
				saveMemberInfo(x);//update the member file


				return;
			}
			case '4':
			{
				int age;
				cout << "Enter the age: ";
				cin >> age;//inputs the age to be updates to

				while(age < 10 || age > 80)
				{
					cout << "\nERROR!, Please enter a valid age" << endl;//validation for the age entered by the user
					cout << "Enter age (10 < age < 80): ";
					cin >> age;
				}

				x.age = age;
				saveMemberInfo(x);//updates the member file

				return;
			}
			case '5':
			{
				char genderChar; cout << "Enter the gender: "; cin >> genderChar;

				while(genderChar != 'm' && genderChar != 'f' && genderChar != 'M' && genderChar != 'F')//validation for the gender input of the user
				{
					cout << "\nERROR!, Please enter a valid gender" << endl;
					cout << "Enter gender (M or F): ";
					cin >> genderChar;
				}
				bool gender = true;
				if (genderChar == 'f' || genderChar == 'F')
					gender = false;

				x.gender = gender;
				saveMemberInfo(x);//updates the information of the user into the member file
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
