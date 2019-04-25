#include "inputLayer.h"

InputLayer::InputLayer(int layerID, int size)
{
	layerNum = layerID;
	layerSize = size;
}

InputLayer::~InputLayer()
{
	//delete pNodes;
}

void InputLayer::loadInput(double * rpInputVector)
{
	//pNodes = new double[layerSize];

	for (int i = 0; i < layerSize; ++i)
	{
		nodeVector.push_back(rpInputVector[i]);
		//pNodes[i] = rpInputVector[i];
	}
}

void InputLayer::loadInput(vector<double>& rInputVector)
{
	for (int i = 0; i < layerSize-1; ++i) // Breaks in this loop
	{
		if (nodeVector.size() <= i)
		{
			nodeVector.push_back(rInputVector[i]);
		}
		else
		{
			nodeVector[i] = rInputVector[i];
		}
	}
}

vector<double> &  InputLayer::getNodeVector()
{
	return nodeVector;
}
