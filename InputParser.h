#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


using std::vector;
using std::ifstream;
using std::string;
using std::istringstream;

class InputParser
{
public:
	InputParser(const string fileName, const char inputDelim);
	~InputParser();

	void getInputMatrix(vector<vector<double> *> & rOutputMatrix);
	int getInputSize();
	int getNinputs();

private:
	void getMatrixRow(vector<double> & rOutputVector); // Parses and inserts a line of the input into a matrix row
	void parseline(const string & inputString, vector<double> & rLineVector); // Parses a line and sets rLinevector to the output
	void importData(); // Loads data from input file to the matrix

	int numberOfInputs;
	int inputDimension;

	ifstream inputFile;
	char delim;

	vector<vector<double> *> inputMatrix;
};