#include <iostream>
#include "output.h"
#include "Abel.h"

using namespace std;
using namespace output_functions;
using namespace abel;


int main()
{	
	unsigned int ih;
	unsigned int n;
	cout << "Plese write the number of initial height to be set" <<endl;
	cin >> ih;
	cout << "Please write the number of grains on the origin" << endl;
	cin >> n;

	//double t = abel::MoveStandard(n);
	double t = abel::MoveStandard_1Step(n,ih);

	cout <<"Done in " << t << " seconds" << endl;

	char _end;
	cout << endl << "Enter any character to quit ";
	cin >> _end;

	return 1;
}