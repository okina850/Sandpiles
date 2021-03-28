#include <iostream>
#include <vector>
#include <time.h>
#include <string>

#include "Abel.h"
#include "output.h"
#include "input.h"

using namespace std;
using namespace abel;
using namespace output_functions;
using namespace input_functions;

double abel::MoveStandard(unsigned int n, unsigned int ih)
{		
		// sandpile stabilization with n particles at the origin in a standard way, 
	    // with preallocated stack of moving vertices
		unsigned int** z_lat = new unsigned int*[kLatticeSize];      // models the standard lattice Z^2
		bool** v_sites = new bool*[kLatticeSize];                    // vertices of Z^2 which were visited during the process//for trimming non-visited area
		bool** to_be_moved = new bool*[kLatticeSize];                // vertices of Z^2 which are already in the walking stack
		unsigned int** odometer = new unsigned int*[kLatticeSize];   // total number of topplings of a given vertex of Z^2


		for (int k = 0; k < kLatticeSize; ++k){
			z_lat[k] = new unsigned int[kLatticeSize];
			v_sites[k] = new bool[kLatticeSize];
			odometer[k] = new unsigned int[kLatticeSize];
			to_be_moved[k] = new bool[kLatticeSize];

			for (int i = 0; i < kLatticeSize; ++i){
				z_lat[k][i] = ih;  
				to_be_moved[k][i] = false; 
				v_sites[k][i] = false;
			}
		}

		LCoord* walking_sites = new LCoord[kLatticeSize*kLatticeSize];  //pre-allocated stack of vertices which need to be toppled
		
		v_sites[kLatticeToBeAdded][kLatticeToBeAdded] = true;
		to_be_moved[kLatticeToBeAdded][kLatticeToBeAdded] = true;

		z_lat[kLatticeToBeAdded][kLatticeToBeAdded] += n;
		walking_sites[0].x = kLatticeToBeAdded;
		walking_sites[0].y = kLatticeToBeAdded;


		unsigned int x = 0, y = 0;
		int top = 0;

		unsigned int lx = 0, ly = 0;
		unsigned int d = 0;

		clock_t t1, t2;
		t1 = clock();

		unsigned int max_of_top = 0;
		unsigned long n_of_moves = 0;


		while (top >= 0)
		{
			n_of_moves += 1;

			if (max_of_top < top){
				max_of_top = top; 
			}
			//cout << "x:" << x << "," << "lx:" << lx << endl;
			//cout << "y:" << y << "," << "ly:" << ly << endl;
			x = walking_sites[top].x;
			y = walking_sites[top].y;
			
			top--; 
			to_be_moved[x][y] = false;
			
			d = (z_lat[x][y] >> 2);
			z_lat[x][y] = z_lat[x][y] - (d << 2);

			for (int k = 0; k < 4; ++k){
				lx = x + kDx[k];
				ly = y + kDy[k];

				if (!(0 <= lx && lx < kLatticeSize && 0 <= ly && ly < kLatticeSize)) {
					continue;
				}

				v_sites[lx][ly] = true;
				z_lat[lx][ly] += d;

				if (to_be_moved[lx][ly] == false && z_lat[lx][ly] >= 4){
					walking_sites[++top].x = lx; 
					walking_sites[top].y = ly; 
					to_be_moved[lx][ly] = true;
				}
			}	
		}

		t2 = clock();

		cout << "Now saving..." << endl;

		output_functions::BoxCoord b;
		b = TrimmedArray(v_sites, kLatticeSize, kLatticeSize);

		NonTrimmmingArrayToCSV(z_lat, kLatticeSize, kLatticeSize, ("Abel" + std::to_string(n) + "ih=" + std::to_string(ih) + "(noTrim)" + ".csv").c_str());
		//ArrayToCSV(z_lat, v_sites, b.i1, b.i2, b.j1, b.j2, ("Abel" + std::to_string(n) + "ih=" + std::to_string(ih) + ".csv").c_str());
		NonTrimmmingArrayToPPM(z_lat, kLatticeSize, kLatticeSize, ("Abel" + std::to_string(n) + "ih=" + std::to_string(ih) + "(noTrim)" + ".ppm").c_str());

		//ArrayToPPM(z_lat, v_sites, b.i1, b.i2, b.j1, b.j2, ("Abel" + std::to_string(n) + "ih=" + std::to_string(ih) + ".ppm").c_str());

		

		// clean-ups
		for (int k = 0; k<kLatticeSize; ++k){
			delete[] z_lat[k];
			delete[] v_sites[k];
			delete[] odometer[k];
			delete[] to_be_moved[k];
		}

		delete[] z_lat; 
		delete[] v_sites; 
		delete[] odometer; 
		delete[] to_be_moved; 
		delete[] walking_sites;

		std::cout<<"Maximal number in the stack was "<<max_of_top<<endl;
		std::cout<<"Number of moves in the main loop was "<<n_of_moves<<endl;

		return ((float)(t2)-(float)(t1)) * 0.001;
}

double abel::ahaha(unsigned int n, unsigned int** previous_z_lat)
{
    string ih = "(under_construction)";
	// sandpile stabilization with n particles at the origin in a standard way, 
	// with preallocated stack of moving vertices
	unsigned int** z_lat = previous_z_lat;      // models the standard lattice Z^2
	bool** v_sites = new bool* [kLatticeSize];                    // vertices of Z^2 which were visited during the process//for trimming non-visited area
	bool** to_be_moved = new bool* [kLatticeSize];                // vertices of Z^2 which are already in the walking stack
	unsigned int** odometer = new unsigned int* [kLatticeSize];   // total number of topplings of a given vertex of Z^2

	for (int k = 0; k < kLatticeSize; ++k) {
		v_sites[k] = new bool[kLatticeSize];
		odometer[k] = new unsigned int[kLatticeSize];
		to_be_moved[k] = new bool[kLatticeSize];

		for (int i = 0; i < kLatticeSize; ++i) {
			to_be_moved[k][i] = false;
			v_sites[k][i] = false;
		}
	}


	LCoord* walking_sites = new LCoord[kLatticeSize * kLatticeSize];  //pre-allocated stack of vertices which need to be toppled

	v_sites[kLatticeToBeAdded][kLatticeToBeAdded] = true;
	//to_be_moved[kLatticeToBeAdded][kLatticeToBeAdded] = true;

	z_lat[kLatticeToBeAdded][kLatticeToBeAdded] += n;
	walking_sites[0].x = kLatticeToBeAdded;
	walking_sites[0].y = kLatticeToBeAdded;


	unsigned int x = 0, y = 0;
	int top = 0;

	unsigned int lx = 0, ly = 0;
	unsigned int d = 0;

	clock_t t1, t2;
	t1 = clock();

	unsigned int max_of_top = 0;
	unsigned long n_of_moves = 0;


	while (top >= 0)
	{
		n_of_moves += 1;

		if (max_of_top < top) {
			max_of_top = top;
		}
		//cout << "x:" << x << "," << "lx:" << lx << endl;
		//cout << "y:" << y << "," << "ly:" << ly << endl;
		x = walking_sites[top].x;
		y = walking_sites[top].y;

		top--;
		to_be_moved[x][y] = false;

		d = (z_lat[x][y] >> 2);
		z_lat[x][y] = z_lat[x][y] - (d << 2);
		
		for (int k = 0; k < 4; ++k) {
			lx = x + kDx[k];
			ly = y + kDy[k];

			if (!(0 <= lx && lx < kLatticeSize && 0 <= ly && ly < kLatticeSize)) {
				continue;
			}

			v_sites[lx][ly] = true;
			z_lat[lx][ly] += d;

			if (to_be_moved[lx][ly] == false && z_lat[lx][ly] >= 4) {
				walking_sites[++top].x = lx;
				walking_sites[top].y = ly;
				to_be_moved[lx][ly] = true;
			}
		}
	}

	t2 = clock();

	cout << "Now saving..." << endl;

	output_functions::BoxCoord b;
	b = TrimmedArray(v_sites, kLatticeSize, kLatticeSize);

	NonTrimmmingArrayToCSV(z_lat, kLatticeSize, kLatticeSize, ("Abel" + std::to_string(n) + "ih=" + ih + "(noTrim)" + ".csv").c_str());
	//ArrayToCSV(z_lat, v_sites, b.i1, b.i2, b.j1, b.j2, ("Abel" + std::to_string(n) + "ih=" + std::to_string(ih) + ".csv").c_str());
	NonTrimmmingArrayToPPM(z_lat, kLatticeSize, kLatticeSize, ("Abel" + std::to_string(n) + "ih=" + ih + "(noTrim)" + ".ppm").c_str());

	//ArrayToPPM(z_lat, v_sites, b.i1, b.i2, b.j1, b.j2, ("Abel" + std::to_string(n) + "ih=" + std::to_string(ih) + ".ppm").c_str());



	// clean-ups
	for (int k = 0; k < kLatticeSize; ++k) {
		delete[] z_lat[k];
		delete[] v_sites[k];
		delete[] odometer[k];
		delete[] to_be_moved[k];
	}

	delete[] z_lat;
	delete[] v_sites;
	delete[] odometer;
	delete[] to_be_moved;
	delete[] walking_sites;

	std::cout << "Maximal number in the stack was " << max_of_top << endl;
	std::cout << "Number of moves in the main loop was " << n_of_moves << endl;

	return ((float)(t2)-(float)(t1)) * 0.001;
}

double abel::MoveStandard_1Step(unsigned int n,unsigned int ih)
{
	unsigned int** z_lat = new unsigned int*[kLatticeSize];
	bool** v_sites = new bool*[kLatticeSize];
	bool** to_be_moved = new bool*[kLatticeSize]; 
	unsigned int** odometer = new unsigned int*[kLatticeSize];


	for (int k = 0; k<kLatticeSize; ++k){
		z_lat[k] = new unsigned int[kLatticeSize];
		v_sites[k] = new bool[kLatticeSize];
		odometer[k] = new unsigned int[kLatticeSize];
		to_be_moved[k] = new bool[kLatticeSize];

		for (int i = 0; i < kLatticeSize; ++i){
		    z_lat[k][i] = ih;  
			v_sites[k][i] = false; 
			odometer[k][i] = 0; 
			to_be_moved[k][i] = false;
		}
	}

	LCoord* walking = new LCoord[kLatticeSize * kLatticeSize];  // pre-allocated stack

	v_sites[kLatticeToBeAdded][kLatticeToBeAdded] = true;

	int top = -1;
	unsigned int x = 0, y = 0, lx = 0, ly = 0;


	clock_t t1, t2;
	t1 = clock();

	unsigned int max_of_top = 0;
	unsigned long n_of_moves = 0;

	for (unsigned int i = n ; i--;){
		if (++z_lat[kLatticeToBeAdded][kLatticeToBeAdded] >= 4){
			walking[++top].x = kLatticeToBeAdded; 
			walking[top].y = kLatticeToBeAdded;
		}

		while (top >= 0){
			n_of_moves += 1;

			if (max_of_top < top){
				max_of_top = top; 
			}

			x = walking[top].x;      
			y = walking[top].y;

			z_lat[x][y] = z_lat[x][y] - 4;
			if (z_lat[x][y] < 4){
				top --; 
				to_be_moved[x][y] = false;
			}


			for (int k = 0; k < 4; ++k){
				lx = x + kDx[k];
				ly = y + kDy[k];

				
				if (lx >= kLatticeSize || lx < 0 || ly >= kLatticeSize || ly < 0) {
					//cout << lx << "," << ly <<endl;
					
					continue; 
				}
				
				v_sites[lx][ly] = true;
				z_lat[lx][ly] ++;

				if (to_be_moved[lx][ly] == false && z_lat[lx][ly] >= 4){
					walking[++top].x = lx;
					walking[top].y = ly;
					to_be_moved[lx][ly] = true;
				}
			}
		}
	}
	

	// now running the process until stabilisation
	
	t2 = clock();

	std::cout<<endl;

	std::cout<<"Maximal number in the stack was "<<max_of_top<<endl;
	std::cout<<"Number of moves in the main loop was "<<n_of_moves<<endl;

	cout << "Now saving..." << endl;

	
	BoxCoord b = TrimmedArray(v_sites, kLatticeSize, kLatticeSize);
	//ArrayToJSON(z_lat, v_sites, b.i1, b.i2, b.j1, b.j2, ("Abel" + std::to_string(n) + "ih=" + std::to_string(ih) + ".json"));
	NonTrimmmingArrayToCSV(z_lat, kLatticeSize, kLatticeSize, ("Abel" + std::to_string(n) + "ih=" + std::to_string(ih) + "(noTrim)" + ".csv").c_str());
	//ArrayToCSV(z_lat, v_sites, b.i1, b.i2, b.j1, b.j2, ("Abel"  + std::to_string(n) + "ih=" + std::to_string(ih) + ".csv").c_str());
	//ArrayToPPM(z_lat, v_sites, b.i1, b.i2, b.j1, b.j2, ("Abel"  + std::to_string(n) + "ih=" + std::to_string(ih) + ".ppm").c_str());
	NonTrimmmingArrayToPPM(z_lat, kLatticeSize, kLatticeSize, ("Abel" + std::to_string(n) + "ih=" + std::to_string(ih) + "(noTrim)" + ".ppm").c_str());

	// clean-ups
	for (int k = 0; k<kLatticeSize; ++k){
		delete[] z_lat[k];
		delete[] v_sites[k];
		delete[] odometer[k];
		delete[] to_be_moved[k];
	}

	delete[] z_lat; 
	delete[] v_sites; 
	delete[] odometer; 
	delete[] to_be_moved; 
	delete[] walking;
	

	return ((double)(t2)-(double)(t1))*0.001;
}

double abel::ahaha2(unsigned int n, unsigned int** previous_z_lat)
{
	string ih = "(under_construction)";
	// sandpile stabilization with n particles at the origin in a standard way, 
	// with preallocated stack of moving vertices
	unsigned int** z_lat = previous_z_lat;      // models the standard lattice Z^2
	bool** v_sites = new bool* [kLatticeSize];                    // vertices of Z^2 which were visited during the process//for trimming non-visited area
	bool** to_be_moved = new bool* [kLatticeSize];                // vertices of Z^2 which are already in the walking stack
	unsigned int** odometer = new unsigned int* [kLatticeSize];   // total number of topplings of a given vertex of Z^2

	for (int k = 0; k < kLatticeSize; ++k) {
		v_sites[k] = new bool[kLatticeSize];
		odometer[k] = new unsigned int[kLatticeSize];
		to_be_moved[k] = new bool[kLatticeSize];

		for (int i = 0; i < kLatticeSize; ++i) {
			v_sites[k][i] = false;
			odometer[k][i] = 0;
			to_be_moved[k][i] = false;
		}
	}

	LCoord* walking = new LCoord[kLatticeSize * kLatticeSize];  // pre-allocated stack

	v_sites[kLatticeToBeAdded][kLatticeToBeAdded] = true;

	int top = -1;
	unsigned int x = 0, y = 0, lx = 0, ly = 0;


	clock_t t1, t2;
	t1 = clock();

	unsigned int max_of_top = 0;
	unsigned long n_of_moves = 0;

	//in case of n = 0
	bool nIsZero = false;
	if (n == 0) nIsZero = true;

	for (unsigned int i = n;i > 0;i--) {

		if (++z_lat[kLatticeToBeAdded][kLatticeToBeAdded] >= 4) {
			walking[++top].x = kLatticeToBeAdded;
			walking[top].y = kLatticeToBeAdded;
		}

		while (top >= 0) {
			n_of_moves += 1;

			if (max_of_top < top) {
				max_of_top = top;
			}

			x = walking[top].x;
			y = walking[top].y;

			z_lat[x][y] = z_lat[x][y] - 4;
			if (z_lat[x][y] < 4) {
				top--;
				to_be_moved[x][y] = false;
			}


			for (int k = 0; k < 4; ++k) {
				lx = x + kDx[k];
				ly = y + kDy[k];


				if (lx >= kLatticeSize || lx < 0 || ly >= kLatticeSize || ly < 0) {
					//cout << lx << "," << ly <<endl;

					continue;
				}

				v_sites[lx][ly] = true;
				z_lat[lx][ly] ++;

				if (to_be_moved[lx][ly] == false && z_lat[lx][ly] >= 4) {
					walking[++top].x = lx;
					walking[top].y = ly;
					to_be_moved[lx][ly] = true;
				}
			}
		}
	}


	// now running the process until stabilisation

	t2 = clock();

	std::cout << endl;

	std::cout << "Maximal number in the stack was " << max_of_top << endl;
	std::cout << "Number of moves in the main loop was " << n_of_moves << endl;

	std::cout << "Now saving..." << endl;


	BoxCoord b = TrimmedArray(v_sites, kLatticeSize, kLatticeSize);
	//ArrayToJSON(z_lat, v_sites, b.i1, b.i2, b.j1, b.j2, ("Abel" + std::to_string(n) + "ih=" + std::to_string(ih) + ".json"));
	NonTrimmmingArrayToCSV(z_lat, kLatticeSize, kLatticeSize, ("Abel" + std::to_string(n) + "ih=" + ih + "(noTrim)" + ".csv").c_str());
	//ArrayToCSV(z_lat, v_sites, b.i1, b.i2, b.j1, b.j2, ("Abel"  + std::to_string(n) + "ih=" + std::to_string(ih) + ".csv").c_str());
	//ArrayToPPM(z_lat, v_sites, b.i1, b.i2, b.j1, b.j2, ("Abel"  + std::to_string(n) + "ih=" + std::to_string(ih) + ".ppm").c_str());
	NonTrimmmingArrayToPPM(z_lat, kLatticeSize, kLatticeSize, ("Abel" + std::to_string(n) + "ih=" + ih + "(noTrim)" + ".ppm").c_str());

	// clean-ups
	for (int k = 0; k < kLatticeSize; ++k) {
		delete[] z_lat[k];
		delete[] v_sites[k];
		delete[] odometer[k];
		delete[] to_be_moved[k];
	}

	delete[] z_lat;
	delete[] v_sites;
	delete[] odometer;
	delete[] to_be_moved;
	delete[] walking;


	return ((double)(t2)-(double)(t1)) * 0.001;
}

