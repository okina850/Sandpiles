#include <iostream>
#include <string>
#include "output.h"
#include "Abel.h"

using namespace std;
using namespace output_functions;
using namespace abel;

void createNewSandpile() {
	unsigned int ih;
	unsigned int n;
	cout << "Please write the number of initial height:0,1,2,3,4" << endl;
	while (true) {
		cin >> ih;

		try {
			if (cin.fail()) throw 1;
			if (!(0 <= ih && ih <= 4)) throw 0;

			break;
		}
		catch (int e) {
			switch (e) {
				case 0:cout << "Between 0 and 4, please" << endl;
					break;
				case 1:cout << "Type an integer,please." <<endl;
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
			if (cin.fail()) throw 1;
			if (!(0 <= ih)) throw 0;

			break;
		}
		catch (int e) {
			switch (e) {
			case 0:cout << "Greater than or equal to 0, please" << endl;
				break;
			case 1:cout << "Type an integer,please." << endl;
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

void continuePreviousSandpile() {


}



int main()
{	
	
	while (true){
		cout << "Command? quit,new,load" << endl;
		string command; cin >> command;
		
		if (command == "quit") return 1;
		
		if (command == "new") createNewSandpile();
		
		if (command == "load") continuePreviousSandpile();
		
		/*
		char _end;
		cout << endl << "Enter any character to quit ";
		cin >> _end;

		return 1;
		*/
	}

	
}