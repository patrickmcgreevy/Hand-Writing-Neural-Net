#include "InputParser.h"

InputParser::InputParser(const string fileName, const char inputDelim)
{
	delim = inputDelim;

	inputFile.open(fileName);

	importData();

	inputMatrix.shrink_to_fit();

	numberOfInputs = inputMatrix.size();
	inputDimension = inputMatrix[0]->size();
}

InputParser::~InputParser()
{
	inputFile.close();
}

void InputParser::getInputMatrix(vector<vector<double>*>& rOutputMatrix)
{
	//rOutputMatrix = inputMatrix;
	for (int i = 0; i < inputMatrix.size(); ++i)
	{
		rOutputMatrix.push_back(new vector<double>);
		*rOutputMatrix[i] = *inputMatrix[i];
	}
}

int InputParser::getInputSize()
{
	return inputDimension;
}

int InputParser::getNinputs()
{
	return numberOfInputs;
}

void InputParser::getMatrixRow(vector<double>& rOutputVector)
{
}

void InputParser::parseline(const string & inputString, vector<double>& rLineVector)
{
	istringstream inputStringStream(inputString);
	string token;

	while (std::getline(inputStringStream, token, delim))
	{
		double tokenDouble = std::stod(token);
		rLineVector.push_back(tokenDouble);
	}
}

void InputParser::importData()
{
	string cInputLine;
	int nLinesDone = 0;
	std::cout << "Importing data..." << std::endl;

	while (std::getline(inputFile, cInputLine))
	{
		inputMatrix.push_back(new vector<double>);
		parseline(cInputLine, *inputMatrix.back());
		if (++nLinesDone % 500 == 0)
			std::cout << nLinesDone << " lines done..." << std::endl;
		//std::cout << "working..." << std::endl;
	}
}
