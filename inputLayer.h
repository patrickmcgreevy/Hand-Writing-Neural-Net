#pragma once
#include <vector>

using std::vector;

class InputLayer
{
public:
	InputLayer(int layerID, int size);
	~InputLayer();

	void loadInput(double * rpInputVector);
	void loadInput(vector<double> & rInputVector);

	vector<double> & getNodeVector();

private:
	int layerNum; // ID the layer
	int layerSize; // Numer of nodes in layer
	//int numberOfInputs; // Size of input vector x

	vector<double> nodeVector;//double * pNodes; // Stores the value of each input
	//double **pWeightMatrix; // Each column is the weight vector of the kth node
	//double *& rpInputVector; // Reference to the pointer to the input of the layer
};