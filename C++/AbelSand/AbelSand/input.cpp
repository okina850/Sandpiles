#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "input.h"

using namespace input_functions;
using namespace std;

unsigned int** input_functions::ParseCSVToArray(string filename) {
	ifstream csv_file;
	csv_file.open(filename);
	
	string line;
	vector<vector<unsigned int>> arr2d;
	while (getline(csv_file, line)) {
		string val;
		vector<unsigned int> row;
		stringstream s(line);
		while (getline(s, val, ',')) {
			row.push_back(stoi(val));
		}
		arr2d.push_back(row);
	}
	csv_file.close();

	size_t sizeOfCSV = arr2d.size();
	cout << "arr2d size:" << arr2d.size() << " arr2d.at(0).at(0)" << arr2d.at(0).at(0) <<endl;

	unsigned int** z_lat = new unsigned int* [sizeOfCSV];

	for (size_t k = 0; k < sizeOfCSV; ++k) {
		z_lat[k] = new unsigned int[sizeOfCSV];

		for (size_t i = 0; i < sizeOfCSV; ++i) {
			z_lat[k][i] = arr2d.at(k).at(i);
		}
	}
	cout << "z_lat size:" << sizeof(z_lat) << " z_lat[10][10]:" << z_lat[10][10]  << endl;


	return z_lat;
}