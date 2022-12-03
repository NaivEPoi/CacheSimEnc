#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void parsec_roi_begin() 
{

}

void parsec_roi_end() 
{

}


vector< vector<int> > read(string filename) {
	vector< vector<int> > src;
	string line;
	ifstream infile;
	infile.open (filename.c_str());

	int i = 0;
	while (getline(infile, line) && !line.empty()) {
		istringstream iss(line);
		src.resize(src.size() + 1);
		int a, j = 0;
		while (iss >> a) {
			src[i].push_back(a);
			j++;
		}
		i++;
	}

	i = 0;

	infile.close();
	return src;
}

vector< vector<int> > columncopy(vector< vector<int> > src) {
	int n = src.size();
	//Here src[n][n] is input tensor
	//of size=nxn passed by user
	vector<int> tmp(n, 0);
	vector< vector<int> > dst(n, tmp);
	parsec_roi_begin(); //Pintool will start recording memory access
	for (auto col = 0; col != n; col++) {	
		for (auto row = 0; row != n; row++) {
			dst[row][col] = src[row][col];
		}
	}
	parsec_roi_end(); //Pintool will stop recording memory access
	return dst;
}

void printMatrix(vector< vector<int> > matrix) {
	vector< vector<int> >::iterator it;
	vector<int>::iterator inner;
	for (it=matrix.begin(); it != matrix.end(); it++) {
		for (inner = it->begin(); inner != it->end(); inner++) {
			cout << *inner;
			if(inner+1 != it->end()) {
				cout << "\t";
			}
		}
		cout << endl;
	}
}

int main (int argc, char* argv[]) {
	string filename;
	if (argc < 3) {
		filename = "2000.in";
	} else {
		filename = argv[2];
	}
	vector< vector<int> > src = read (filename);
    parsec_roi_begin();
	vector< vector<int> > dst = columncopy(src);
    parsec_roi_end();
	// printMatrix(dst);
	return 0;
}
