#pragma once
#include "inputLayer.h"
#include "hiddenLayer.h"
#include "outputLayer.h"
#include "ImageClassifier.h"
#include "InputParser.h"

#define NUMBER_OF_OUTPUTS 10


class DeepNeuralNet
{
public:
	DeepNeuralNet(int nHiddenLayers, int hiddenLayerSize, const string & trainingFname, const string & testFname, const char delim);
	DeepNeuralNet();

	// Network controls
	void setNumberofHiddenLayers(int n);
	void setNoutputs(int n);
	void setHiddenLayerSize(int n);
	void setFileNameDelim(const string & rFileName, const char & rFileDelim);
	/*void setTrainingFile(const string & rTrainingFName);
	void setTestingFile(const string & rTestingFName)*/;
	void setModelFile(const string & rModelFName);

	void setInputParser(InputParser * pParser);
	void setClassifier(ImageClassifier * pClass);
	void setClassifier(vector<double> & rClassifierInput);

	// Network Functions
	void train();
	void test();

	void predict(); // Deathly Hallows


private:

	void initNetwork();

	void setInputParser(const string & rInputFName, const char delim); // Configures the input file and delimiter of the parser
	void initBackProp();
	void backPropagate(vector<double> & rCorrectOutput);


	bool loadInputLine(int index, vector<double> & rcInput, vector<double> & rCorrectOutput); // Loads data from InputParser to inputlayer. index is which input line net is on
	void loadInputMatrixToNet(); // Copies the inputparser's inputmatrix into the neural net.
	void feedFoward(); // Propagates values from inputlayer through to outputlayer

	double calculateCost(vector<double> & rCorrectOutput); // Calculates how far off the net is for training
	//void calculateOutputError()



	// Net specific variables
	int numberHiddenLayers;
	int hiddenLayerSize;
	int nOutputs;
	double learningRate;
	vector<vector<double>*> inputMatrix;

	// Input and classification classes
	InputParser * pInputParser;
	ImageClassifier * pClassifier;
	string inputFileName;
	char inputDelim;
	/*string testingFile;
	char testingDelim;*/

	// Neural network classes
	InputLayer * pInputLayer;
	OutputLayer * pOutPutLayer;
	vector<HiddenLayer *> hiddenLayerVector;

	// Back Propagation
	vector<double> inputLayerErrorV;
	vector<vector<double>*> hiddenLayerErrorV;
};