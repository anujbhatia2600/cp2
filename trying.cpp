#include <iostream>
#include <string>
#include <fstream>
using namespace std;

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
	return i;
}

int main() 
{
	cout << countItems();
} 

