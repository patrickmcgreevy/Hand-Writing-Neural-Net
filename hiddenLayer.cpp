#include "hiddenLayer.h"

HiddenLayer::HiddenLayer(int nNodes, int nInputs, int ID, vector<double> & rInpV) 
	: rInputVector(rInpV)
{
	layerNum = ID;
	layerSize = nNodes;
	numberOfInputs = nInputs;

	//pNodes = new double[layerSize]; // Allocates an array of doubles of size nNodes
	initNodeVector();

	pBiasVector = new double[layerSize];
	for (int i = 0; i < layerSize; ++i)
	{
		pBiasVector[i] = 0;
	}

	initWeightMatrix();
	//pWeightMatrix = new double*[numberOfInputs]; // Allocates an array of pointers to doubles of size nInputs
	//for (int i = 0; i < numberOfInputs; ++i) // For each column of the weight matrix, allocate an array of doubles of size nNodes
	//{
	//	pWeightMatrix[i] = new double[layerSize];

	//	for (int j = 0; j < layerSize; ++j)
	//	{
	//		pWeightMatrix[i][j] = 0; // sets all weights to 0. Maybe should initialize to random on creation?
	//	}
	//}
}

HiddenLayer::~HiddenLayer()
{
	//delete pNodes;
	delete pBiasVector;
	for (int i = 0; i < layerSize; ++i)
	//for(int i = layerSize - 1; i >= 0; --i)
	{
		//cout << "deleting ROW " << i << endl;
		delete weightMatrix[i];
		//cout << pWeightMatrix[i];
		//delete[] pWeightMatrix[i];
	}
}

HiddenLayer::HiddenLayer(HiddenLayer & rLayer) : rInputVector(rLayer.nodeVector)
{
	this->layerNum = rLayer.layerNum + 1;
	this->layerSize = rLayer.layerSize;
	this->numberOfInputs = rLayer.layerSize;
	
	//pNodes = new double[layerSize]; // Allocates an array of doubles of size nNodes
	initNodeVector();

	pBiasVector = new double[layerSize];
	for (int i = 0; i < layerSize; ++i)
	{
		pBiasVector[i] = 0;
	}

	initWeightMatrix();
	//pWeightMatrix = new double*[numberOfInputs]; // Allocates an array of pointers to doubles of size nInputs
	//for (int i = 0; i < numberOfInputs; ++i) // For each column of the weight matrix, allocate an array of doubles of size nNodes
	//{
	//	pWeightMatrix[i] = new double[layerSize];

	//	for (int j = 0; j < layerSize; ++j)
	//	{
	//		pWeightMatrix[i][j] = 0; // sets all weights to 0. Maybe should initialize to random on creation?
	//	}
	//}
}

void HiddenLayer::initWeightMatrix()
{
	for (int row = 0; row < layerSize; ++row)
	{
		weightMatrix.push_back(new vector<double>);
		
		for (int col = 0; col < numberOfInputs; ++col)
		{
			weightMatrix[row]->push_back(0);
		}
	}
		
}

void HiddenLayer::initNodeVector()
{
	for (int i = 0; i < layerSize; ++i)
	{
		nodeVector.push_back(0);
	}
}

void HiddenLayer::normalizeVector()
{
	double sum = 0;
	for (int i = 0; i < layerSize; ++i)
	{
		sum += nodeVector[i];
	}

	if (sum != 0)
	{
		for (int i = 0; i < layerSize; ++i)
		{
			nodeVector[i] /= sum;
		}
	}
}

double HiddenLayer::x_dot_wk(int kthNode)
{
	double xdotWk = 0;

	for (int i = 0; i < numberOfInputs; ++i)
	{
		xdotWk += (rInputVector[i]) * (weightMatrix[kthNode]->at(i));
	}

	return xdotWk;
}

void HiddenLayer::setKthWeightVector(double * pVector, int k)
{
	for (int i = 0; i < numberOfInputs; ++i)
	{
		weightMatrix[k]->at(i) = pVector[i];
	}
}

void HiddenLayer::setKthBias(int k, double b)
{
	pBiasVector[k] = b;
}

void HiddenLayer::initRandBias()
{
	srand(time(NULL));
	double c = 0;

	for (int i = 0; i < layerSize; ++i)
	{
		//c = ((double)(rand() % 100)) / 100;
		c  = (((double)rand()) / RAND_MAX) * 2 - 1;

		pBiasVector[i] = c;
	}
}

void HiddenLayer::initRandomWeights()
{
	srand(time(NULL));
	double *randVec = new double[numberOfInputs];

	for (int i = 0; i < layerSize; i++)
	{
		for (int j = 0; j < numberOfInputs; ++j)
		{
			//randVec[j] = ((double)(rand() % 200) - 100) / 100;
			//randVec[j] = ((double)(rand() % 200) - 100) / 100;
			randVec[j] = (((double)rand()) / RAND_MAX) * 2 - 1;
		}
		setKthWeightVector(randVec, i);
	}

	delete randVec;
}

double HiddenLayer::getBias(int kthNode)
{
	return pBiasVector[kthNode];
}

double HiddenLayer::activationFtanh(double & input)
{

	return 1 / (1 + tanh(input));
}

double HiddenLayer::activationF_ReLu(double & input)
{
	if (input < 0)
		return 0;

	return input;
}

double HiddenLayer::ReLuPrime(const double & input)
{
	if (input < 0)
	{
		return 0;
	}

	return 1;
}

const double HiddenLayer::getKthNode(int k)
{
	return nodeVector[k];
}

double HiddenLayer::activationF(double & input)
{
	normalizeVector();
	return activationF_ReLu(input);
	//return activationFtanh(input);
}

void HiddenLayer::updateNodeK(int k)
{
	double a = x_dot_wk(k); // sets a to product of inputs and weights
	a += getBias(k); // adds bias to a
	nodeVector[k] = activationF(a); // sets k to ReLu of a
}

void HiddenLayer::updateAllNodes()
{
	for (int i = 0; i < layerSize; ++i)
	{
		updateNodeK(i);
	}
	printNodestocout();
}

void HiddenLayer::printNodestocout()
{
	cout << "Layer " << this->layerNum << endl;
	for (int i = 0; i < layerSize; ++i)
	{
		cout << nodeVector[i] << endl;
	}
}

void HiddenLayer::printWeightstocout()
{
	cout << "Layer : " << this->layerNum << endl;
	for (int i = 0; i < layerSize; ++i)
	{
		cout << "ROW " << i << "	";
		for (int j = 0; j < numberOfInputs; ++j)
		{
			cout << weightMatrix[i]->at(j) << "   ";
		}
		cout << endl;
	}
}

int HiddenLayer::getID()
{
	return layerNum;
}

int HiddenLayer::getnNodes()
{
	return layerSize;
}

vector<double> & HiddenLayer::getNodeVector()
{
	return nodeVector;
}
