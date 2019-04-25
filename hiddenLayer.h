#pragma once
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <vector>

using std::cout;
using std::endl;
using std::vector;
//#define DEFAULT_LAYER_SIZE 16;
//#define DEFAULT_INPUT_SIZE 784;

class HiddenLayer
{
public:
	HiddenLayer(int nNodes, int nInputs, int ID, vector<double> & rInputV);
	HiddenLayer(HiddenLayer & rLayer);
	~HiddenLayer();

	double x_dot_wk(int kthNode); // Computes dot product of input(x) and weights (wk)
	void setKthWeightVector(double * pVector, int k); // Sets the kth row equal to pVector
	void setKthBias(int k, double b);
	void initRandBias(); // Sets each entry of the bias vector to a random value 0 - 1
	void initRandomWeights(); // Initializes the weight matrix to all random values greater than or equal to zero and less than or equal to one
	double getBias(int kthNode); // Returns the bias of the kth node
	double activationFtanh(double & input); // Returns tanh(input)
	double activationF_ReLu(double & input); // Returns if x < 0: 0, else x
	virtual double activationF(double & input); 
	void updateNodeK(int k); // Replaces the kth node with activationF(x_dot_wk(k) + b_k)
	void updateAllNodes(); // Calls updatenodeK() for all nodes in the layer
	void printNodestocout();
	void printWeightstocout();
	double ReLuPrime(const double & input);

	const double getKthNode(int k);
//protected:
	int getID();
	int getnNodes();
	vector<double> & getNodeVector();
	//double ** getpNodes();

private:

	void initWeightMatrix(); // creates layersize by numberofinputs sized matrix of all zeros
	void initNodeVector();	 // Creates layersize by 1 vector of all zeros
	void normalizeVector(); // NOrmalizes the vector so that each entry is between -1 and 1

	int layerNum; // ID the layer
	int layerSize; // Numer of nodes in layer
	int numberOfInputs; // Size of input vector x

	vector<double> nodeVector; //double * pNodes; // Stores the each dotproduct of previous layer (vector x) and a row of the weight matrix, after going into the activation function
	vector<vector<double> *> weightMatrix;
	//double **pWeightMatrix; // Each row is the weight vector of the kth node
	double *pBiasVector; // Vector of biases for each node. Init to all 0
	vector<double> & rInputVector;	//double *& rpInputVector; // Reference to the pointer to the input of the layer
};