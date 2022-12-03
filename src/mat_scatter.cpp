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

vector< vector<int> > scatter(
	vector< vector<int> > src, vector<int> indices, vector<int> data) {
	int dim = src.size();
	int n = indices.size();
	parsec_roi_begin(); //Pintool will start recording memory access
	for (auto i = 0; i != n; i++) {	
		int index = indices[i];
		int row = index / dim;
		int col = index % dim;
		src[row][col] = data[i];
	}
	parsec_roi_end(); //Pintool will stop recording memory access
	return src;
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
		printf("please enter input filename");
	} else {
		filename = argv[2];
	}
	vector< vector<int> > src = read (filename);
	vector<int> indices(50, 0);
	for (auto i = 0; i != 50; i++) {
		indices[i] = rand() % 100;
	}
	vector<int> data(100, 0);
	for (auto i = 0; i != 100; i++) {
		data[i] = rand() % 1000;
	}
    parsec_roi_begin();
	vector< vector<int> > dst = scatter(src, indices, data);
    parsec_roi_end();
	// printMatrix(dst);
	return 0;
}
