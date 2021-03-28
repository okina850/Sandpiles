#include <iostream>
#include <string>
#include <fstream>
#include "output.h"
#include "Abel.h"
#include "input.h"

using namespace std;
using namespace output_functions;
using namespace input_functions;
using namespace abel;

void createNewSandpile() {
	unsigned int ih;
	unsigned int n;
	cout << "Please write the number of initial height:0,1,2,3,4" << endl;
	while (true) {
		cin >> ih;

		try {
			if (cin.fail()) throw 0;
			if (!(0 <= ih && ih <= 4)) throw 1;

			break;
		}
		catch (int e) {
			switch (e) {
				case 0:cout << "Type an integer,please." << endl;
					break;
				case 1:cout << "Between 0 and 4, please" <<endl;
					break;
			}
		}

		cin.clear();
		cin.ignore(1024,'\n');
		continue;

	}

	cout << "Please write the number of grains to add:0,1,2,..." << endl;
	while (true) {
		cin >> n;

		try {
			if (cin.fail()) throw 0;
			if (!(0 <= ih)) throw 1;

			break;
		}
		catch (int e) {
			switch (e) {
			case 0:cout << "Type an integer,please." << endl;
				break;
			case 1:cout << "Greater than or equal to 0, please" << endl;
				break;
			}
		}

		cin.clear();
		cin.ignore(1024, '\n');
		continue;

	}

	double t = abel::MoveStandard(n,ih);
	//double t = abel::MoveStandard_1Step(n, ih);

	cout << "Done in " << t << " seconds" << endl;
}
void test() {
	ifstream csv_file;
	string filename;
	cout << "Type the name of .csv file you want to parse" << endl;

	while (true) {
		try {
			cin >> filename;
			csv_file.open(filename);

			if (csv_file.fail()) {
				throw "No such file exists";
			}

			break;
		}
		catch (string e) {
			cout << e << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
	}

	unsigned int** z_lat = input_functions::ParseCSVToArray(filename);
	unsigned int sum = 0;
	for (size_t i = 0; i < 1025; i++)
	{
		for (size_t j = 0; j < 1025; j++)
		{
			sum += z_lat[i][j];
		}
	}
	cout << "added:" << sum - 2*1025*1025 << endl;
  
}
void continuePreviousSandpile() {
	ifstream csv_file;
    string filename;
	cout << "Type the name of .csv file you want to parse" << endl;
	
	while (true) {
		try {
			cin >> filename;
			csv_file.open(filename);

			if (csv_file.fail()) {
				throw "No such file exists";
			}
			
			break;
		}
		catch (string e) {
			cout << e << endl;
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
	}

	unsigned int** z_lat = input_functions::ParseCSVToArray(filename);

	int n;
	cout << "Please write the number of grains to add:0,1,2,..." << endl;
	while (true) {
		cin >> n;

		try {
			if (cin.fail()) throw 0;
			//if (!(0 <= ih)) throw 1;

			break;
		}
		catch (int e) {
			switch (e) {
			case 0:cout << "Type an integer,please." << endl;
				break;
			case 1:cout << "Greater than or equal to 0, please" << endl;
				break;
			}
		}

		cin.clear();
		cin.ignore(1024, '\n');
		continue;

	}

	ahaha(n,z_lat);
	//ahaha2(n, z_lat);
}



int main()
{	
	
	while (true){
		cout << "Command? quit,new,load" << endl;
		string command; cin >> command;
		
		if (command == "quit") return 1;
		
		if (command == "new") createNewSandpile();
		
		if (command == "load") {
			continuePreviousSandpile(); 
		}
		if (command == "test") {
			test();
		}
		
		/*
		char _end;
		cout << endl << "Enter any character to quit ";
		cin >> _end;

		return 1;
		*/
	}

	
}