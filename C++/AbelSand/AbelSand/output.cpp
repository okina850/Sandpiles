#include <iostream>
#include <fstream>
#include <string>

#include "output.h"

using namespace output_functions;
using namespace std;

std::string rtrim(std::string src,string wantToTrim)
{
	// trimするとき削除する文字
	std::string trimCharacters = wantToTrim;

	// trimするとき削除する文字以外の最末尾の文字の位置を取得します。
	size_t pos = src.find_last_not_of(trimCharacters);

	// trimするとき削除する文字以外の文字列を切り出します。
	std::string dst = src.substr(0, pos + 1);
	return dst;
}

//template<typename T_array>
BoxCoord output_functions::TrimmedArray(bool ** a, int sz1, int sz2)
{
    // trim any zero row/columns from the borders of a and return the resulting rectangle

	output_functions::BoxCoord x;
	x.i1 = -1; 
	x.i2 = -1; 
	x.j1 = -1; 
	x.j2 = -1;

	bool q = false;

	for (int i = 0; i < sz1; ++i){
		q = false;
		for (int j = 0; j < sz2; ++j)
			if (a[i][j] != 0){
				q = true;
				x.i1 = i;
				break;
			}
		if (q == true)
			break;
	}

	// i2
	for (int i = sz1 - 1; i >= 0; --i){
		q = false;
		for (int j = 0; j < sz2; ++j)
			if (a[i][j] != 0){
				q = true;
				x.i2 = i;
				break;
			}
		if (q == true)
			break;
	}
	
	// j1
	for (int j = 0; j < sz2; ++j){
		q = false;
		for (int i = 0; i < sz1; ++i)
			if (a[i][j] != 0){
				q = true;
				x.j1 = j;
				break;
			}
		if (q == true)
			break;
	}
	
	// j2
	for (int j = sz2 - 1; j >= 0; --j){
		q = false;
		for (int i = 0; i < sz1; ++i)
			if (a[i][j] != 0){
				q = true;
				x.j2 = j;
				break;
			}
		if (q == true)
			break;
	}
	

	return x;

}

//template<typename T_array>
void output_functions::ArrayToCSV(unsigned int ** z_lat, bool ** visited, int i1, int i2, int j1, int j2, const char* filename)
{
	string file = string(filename);

	// check if the file exists
	ifstream fcheck;
	while (true) {
		fcheck.open(file);
		if (!fcheck.fail()) {//already exists
			fcheck.close();
			file = rtrim(file,".csv") + "(" + "another" + ")" + ".csv";
		}
		else {//not exists
			fcheck.close();
			break;
		}
	}
	
	// given the box [i1, i2]x[j1,j2] in the array T_array, saves the box into a csv file

	ofstream csv_file;
	string row_data = "";

	csv_file.open(file);
	
	for (int i = i1; i <= i2; ++i){
		row_data = "";
		for (int j = j1; j <= j2 - 1; ++j)
			if (visited[i][j] == true)
				row_data += std::to_string(static_cast <unsigned long long>(z_lat[i][j])) + ",";
			else
				row_data += "-1,";

		if (visited[i][j2] == true)
			row_data += std::to_string(static_cast <unsigned long long>(z_lat[i][j2])) + "\n";
		else
			row_data +=  "-1\n";

		csv_file << row_data;
	}

	csv_file.close();
}

void output_functions::ArrayToJSON(unsigned int** z_lat, bool** visited, int i1, int i2, int j1, int j2, const char* filename) {

}

template<typename T_array>
void output_functions::ArrayToCSV(T_array ** a, int sz1, int sz2, const char* filename)
{
	string file = string(filename);

	// check if the file exists
	ifstream fcheck;
	while (true) {
		fcheck.open(file);
		if (!fcheck.fail()) {//already exists
			fcheck.close();
			file = rtrim(file, ".csv") + "(" + "another" + ")" + ".csv";
		}
		else {//not exists
			fcheck.close();
			break;
		}
	}
	// outputs the array a into csv file with the given filename

	ofstream csv_file;
	string row_data = "";

	csv_file.open(file);

	for (int i = 0; i < sz1; ++i){
		row_data = "";
		for (int j = 0; j < sz2 - 1; ++j)
			row_data = row_data + std::to_string(static_cast <unsigned long long>(a[i][j])) + ",";

		row_data = row_data + std::to_string(static_cast <unsigned long long>(a[i][sz2 - 1])) + "\n";
		
		csv_file << row_data;
	}

	csv_file.close();
}

void output_functions::NonTrimmmingArrayToCSV(unsigned int** z_lat, int sz1, int sz2, const char* filename)
{
	string file = string(filename);
	
	// check if the file exists
	ifstream fcheck;
	while (true) {
		fcheck.open(file);
		if (!fcheck.fail()) {//already exists
			fcheck.close();
			file = rtrim(file, ".csv") + "(" + "another" + ")" + ".csv";
		}
		else {//not exists
			fcheck.close();
			break;
		}
	}
	// outputs the array a into csv file with the given filename

	ofstream csv_file;
	string row_data = "";
	
	csv_file.open(file);

	for (int i = 0; i < sz1; ++i) {
		row_data = "";
		for (int j = 0; j < sz2 - 1; ++j) {
			row_data = row_data + std::to_string(static_cast <unsigned long long>(z_lat[i][j])) + ",";
		}
		row_data = row_data + std::to_string(static_cast <unsigned long long>(z_lat[i][sz2 - 1])) + "\n";

		csv_file << row_data;
	}

	csv_file.close();
}

void output_functions::NonTrimmmingArrayToPPM(unsigned int** z_lat, int sz1, int sz2, const char* filename) {

	string file = string(filename);

	// check if the file exists
	ifstream fcheck;
	while (true) {
		fcheck.open(file);
		if (!fcheck.fail()) {//already exists
			fcheck.close();
			file = rtrim(file, ".ppm") + "(" + "another" + ")" + ".ppm";
		}
		else {//not exists
			fcheck.close();
			break;
		}
	}
	// output the array sz1 x sz2 into a ppm (raw image) file 

	ofstream ppm_file;
	string row_data = "";

	ppm_file.open(file);

	ppm_file << (string("P3\n") + std::to_string(sz1) + " " + std::to_string(sz2) + "\n255\n");

	for (int i = 0; i < sz1; ++i) {
		row_data = "";
		for (int j = 0; j < sz2; ++j) {
			if (z_lat[i][j] == 1)
				row_data += "255 128 255 ";
			else if (z_lat[i][j] == 2)
				row_data += "255 0 0 ";
			else if (z_lat[i][j] == 3)
				row_data += "0 128 255 ";
			else
				row_data += "0 0 0 ";
		}
		ppm_file << (row_data + "\n");
	}
	ppm_file.close();
}


void output_functions::ArrayToPPM(unsigned int ** z_lat, bool ** visited, int i1, int i2, int j1, int j2, const char* filename)
{
	string file = string(filename);

	// check if the file exists
	ifstream fcheck;
	while (true) {
		fcheck.open(file);
		if (!fcheck.fail()) {//already exists
			fcheck.close();
			file = rtrim(file, ".ppm") + "(" + "another" + ")" + ".ppm";
		}
		else {//not exists
			fcheck.close();
			break;
		}
	}
	// output the subarray [i1, i2]x[j1,j2] into a ppm (raw image) file 

	ofstream ppm_file;
	string row_data = "";

	ppm_file.open(file);

	ppm_file << (string("P3\n") + std::to_string(i2 - i1 + 1) + " " + std::to_string(j2 - j1 + 1) + "\n255\n" );

	for (int i = i1; i <= i2; ++i){
		row_data = "";
		for (int j = j1; j <= j2; ++j){
			if (z_lat[i][j] == 1)
				row_data += "255 128 255 ";
			else if (z_lat[i][j] == 2)
				row_data += "255 0 0 ";
			else if (z_lat[i][j] == 3)	
				row_data += "0 128 255 ";
			else
				row_data += "0 0 0 ";				
		}
		ppm_file << (row_data + "\n");
	}
	ppm_file.close();
}

