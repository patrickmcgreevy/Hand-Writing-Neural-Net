#include "outputLayer.h"

OutputLayer::OutputLayer(int nOutputs, int nInputs, int ID, vector<double> & rInputV) : 
	HiddenLayer(nOutputs, nInputs, ID, rInputV)
{

}

OutputLayer::OutputLayer(HiddenLayer & rPrevLayer, int nOutputs) :
	HiddenLayer(nOutputs, rPrevLayer.getnNodes(), rPrevLayer.getID() + 1, rPrevLayer.getNodeVector())
{
}

OutputLayer::~OutputLayer()
{
	//~HiddenLayer();
}

double OutputLayer::activationF(double & input)
{
	return activationFtanh(input);
}
