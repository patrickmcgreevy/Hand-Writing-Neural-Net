#pragma once
#include "hiddenLayer.h"

class OutputLayer : public HiddenLayer
{
public:
	OutputLayer(int nOutputs, int nInputs, int ID, vector<double> & rInpV);
	OutputLayer(HiddenLayer & rPrevLayer, int nOutputs);
	~OutputLayer();

	double activationF(double & input);

private:

//public:
//	OutputLayer(int nNodes, int nInputs, int ID, const double * pInput);
//	double x_dot_wk(int kthNode); // Computes dot product of input(x) and weights (wk)
//	double activationF(double & input); // Returns tanh(input)
//	void updateNodeK(int k); // Replaces the kth node with activationF(x_dot_wk(k))
//	void updateAllNodes(); // Calls updatenodeK() for all nodes in the layer
//
//private:
//	int layerNum; // ID the layer
//	int layerSize; // Numer of nodes in layer. Number of classifications
//	int numberOfInputs; // Size of input vector x
//
//	double * pNodes; // Stores the each dotproduct of previous layer (vector x) and a column of the weight matrix, after going into the activation function
//	double **pWeightMatrix; // Each column is the weight vector of the kth node
//	double *& rpInputVector; // Reference to the pointer to the input of the layer
};