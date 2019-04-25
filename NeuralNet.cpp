#include "NeuralNet.h"
using std::sqrt;
using std::pow;


DeepNeuralNet::DeepNeuralNet()
{
	numberHiddenLayers = 0;
	pInputLayer = nullptr;
	pOutPutLayer = nullptr;
	pInputParser = nullptr;
	pClassifier = nullptr;
}

void DeepNeuralNet::initNetwork()
{
	pInputParser = new InputParser(inputFileName, inputDelim);
	pInputLayer = new InputLayer(0, pInputParser->getInputSize());
	loadInputMatrixToNet();

	for (int i = 0; i < numberHiddenLayers; ++i)
	{
		if (i == 0)
		{
			hiddenLayerVector.push_back(new HiddenLayer(hiddenLayerSize, pInputLayer->getNodeVector().size(), i + 1, pInputLayer->getNodeVector()));
		}
		else
		{
			hiddenLayerVector.push_back(new HiddenLayer(*hiddenLayerVector[i - 1]));
		}

		hiddenLayerVector[i]->initRandomWeights();
		hiddenLayerVector[i]->initRandBias();
	}

	pOutPutLayer = new OutputLayer(*hiddenLayerVector[numberHiddenLayers - 1], NUMBER_OF_OUTPUTS);
	pOutPutLayer->initRandomWeights();
	pOutPutLayer->initRandBias();
	pClassifier = new ImageClassifier(pOutPutLayer->getNodeVector());

	initBackProp();
}

void DeepNeuralNet::initBackProp()
{
	for (int i = 0; i < hiddenLayerVector.size(); ++i)
	{
		hiddenLayerErrorV.push_back(new vector<double>);
		for (int j = 0; j < hiddenLayerVector[i]->getnNodes(); ++j)
		{
			hiddenLayerErrorV[i]->push_back(0);
		}
	}

	for (int i = 0; i < hiddenLayerVector[0]->getnNodes(); ++i)
	{
		inputLayerErrorV.push_back(0);
	}
}

void DeepNeuralNet::train()
{
	vector<double> currentInput, correctOutput;
	double cost = 0;
	int imageValue = -1;
	initNetwork();

	loadInputMatrixToNet();

	for (int i = 0; loadInputLine(i, currentInput, correctOutput); ++i)
	{
		pInputLayer->loadInput(currentInput);
		feedFoward();
		cost = calculateCost(correctOutput);
		for (int i = 0; i < NUMBER_OF_OUTPUTS; ++i)
		{
			if (correctOutput[i] == 1)
			{
				imageValue = i;
				break;
			}
		}

		backPropagate(correctOutput);
		//std::cout << "cost " << cost << std::endl;
		//std::cout << "This is a " << imageValue <<  " AI thinks it is a " << pClassifier->getOutputValue() << std::endl;
		//currentInput.clear();
	}
}

void DeepNeuralNet::backPropagate(vector<double> & rCorrectOutput)
{
	// for each layer
	//  relu prime each node
	//vector<double> outputLayerErrorV;
	//vector<double> inputLayerErrorV;
	//vector<vector<double>*> hiddenLayerErrorV;
	/*for (int cHiddenLayerError = hiddenLayerErrorV.size() - 1; cHiddenLayerError >= 0; --cHiddenLayerError)
	{
		if (cHiddenLayerError == hiddenLayerErrorV.size() - 1)
		{
			for (int i = 0; i < pOutPutLayer->getnNodes(); ++i)
			{
				hiddenLayerErrorV[cHiddenLayerError]->at(i) = (pOutPutLayer->getKthNode(i) - rCorrectOutput[i]) * pOutPutLayer->ReLuPrime(pOutPutLayer->getKthNode(i));
			}
		}
		else
		{
			for (int i = 0; i < hiddenLayerVector[cHiddenLayerError + 1]->getnNodes(); ++i)
			{
				hiddenLayerErrorV[cHiddenLayerError]->at(i) = 0;
				for (int j = 0; j < pOutPutLayer->getnNodes(); ++j)
				{
					hiddenLayerErrorV[cHiddenLayerError]->at(i) += hiddenLayerErrorV[cHiddenLayerError + 1]->at(j) * hiddenLayerVector[cHiddenLayerError]->ReLuPrime(hiddenLayerVector[cHiddenLayerError]->getKthNode(i));
				}
			}

		}
	}

	for (int i = 0; i < hiddenLayerVector.size(); ++i)
	{
	}*/


}

void DeepNeuralNet::feedFoward()
{
	for (int i = 0; i < hiddenLayerVector.size(); ++i)
	{
		hiddenLayerVector[i]->updateAllNodes();
		//hiddenLayerVector[i]->printNodestocout();
	}
	pOutPutLayer->updateAllNodes();
	//pOutPutLayer->printNodestocout();
}

double DeepNeuralNet::calculateCost(vector<double> & rCorrectOutput)
{
	double cost = 0;

	for (int i = 0; i < pOutPutLayer->getnNodes(); ++i)
	{
		cost += pow(pOutPutLayer->getNodeVector()[i] - rCorrectOutput[i], 2);
	}

	return sqrt(cost) * 0.5;
}

void DeepNeuralNet::loadInputMatrixToNet()
{
	pInputParser->getInputMatrix(inputMatrix);
	inputMatrix.shrink_to_fit();
}

bool DeepNeuralNet::loadInputLine(int index, vector<double> & rcInput, vector<double> & rCorrectOutput)
{
	//vector<vector<double>*> inputMatrix;
	//pInputParser->getInputMatrix(inputMatrix);

	if (inputMatrix.size() <= index || inputMatrix[index]->size() == 0)
		return false;

	for (int i = 0; i < pOutPutLayer->getnNodes(); ++i)
	{
		if (i == inputMatrix[index]->at(0)) // The indexth line of input's first entry is the correct result of that line
		{
			if (rCorrectOutput.size() <= i)
			{
				rCorrectOutput.push_back(1);
			}
			else {
				rCorrectOutput[i] = 1;
			}
		}
		else
		{
			if (rCorrectOutput.size() <= i)
			{
				rCorrectOutput.push_back(0);
			}
			else
			{
				rCorrectOutput[i] = 0;
			}
		}
	}

	for (int i = 1; i < inputMatrix[index]->size(); ++i)
	{
		if (rcInput.size() <= i)
		{
			rcInput.push_back(inputMatrix[index]->at(i));
		}
		else
		{
			rcInput[i] = inputMatrix[index]->at(i);
		}
	}

	return true;
}

void DeepNeuralNet::setNumberofHiddenLayers(int n)
{
	numberHiddenLayers = n;
}

void DeepNeuralNet::setNoutputs(int n)
{
	nOutputs = n;
}

void DeepNeuralNet::setHiddenLayerSize(int n)
{
	hiddenLayerSize = n;
}

void DeepNeuralNet::setFileNameDelim(const string & rFileName, const char & rFileDelim)
{
	inputFileName = rFileName;
	inputDelim = rFileDelim;
}

//void DeepNeuralNet::setTrainingFile(const string & rTrainingFName)
//{
//	trainingFile = rTrainingFName;
//}
//
//void DeepNeuralNet::setTestingFile(const string & rTestingFName)
//{
//	testingFile = rTestingFName;
//}

void DeepNeuralNet::setInputParser(InputParser * pParser)
{
	pInputParser = pParser;
}

void DeepNeuralNet::setInputParser(const string & rInputFName, const char delim)
{
	pInputParser = new InputParser(rInputFName, delim);
}

//void DeepNeuralNet::setInputParserTraining()
//{
//	setInputParser(trainingFile, trainingDelim);
//}
