#pragma once
#include "inputLayer.h"
#include "outputLayer.h"
#include "hiddenLayer.h"
#include "InputParser.h"
#include "ImageClassifier.h"
#include "NeuralNet.h"

int main()
{
	double testInputVector[20] = { .9,.24,.53,.4,.15,.86,.77,.38,.49,.149,.611,.912,.013,.214,.574,.716,.845,.963,.123,.474 }, 
		testWeightVector[16] = {.1,.2,.3,.4,.5,.6,.7,.8,.9,.11,.12,.13,.14,.15,.16,.17};

	//InputParser imageInput("mnist_test.csv", ',');

	DeepNeuralNet net;

	net.setFileNameDelim("mnist_test.csv", ',');
	net.setNumberofHiddenLayers(2);
	net.setHiddenLayerSize(16);
	net.setNoutputs(10);
	net.train();
	
	//net.setClassifier()

	//InputLayer inputLayer(0, 20);
	//inputLayer.loadInput(testInputVector);
	//HiddenLayer hLayer1(16, 20, 1, inputLayer.getNodeVector());
	//hLayer1.initRandBias();
	//hLayer1.initRandomWeights();
	//hLayer1.updateAllNodes();
	//hLayer1.printNodestocout();
	//HiddenLayer hLayer2(hLayer1);
	//hLayer2.initRandBias();
	//hLayer2.initRandomWeights();
	//hLayer2.updateAllNodes();
	//hLayer2.printNodestocout();
	//HiddenLayer hLayer3(hLayer2);
	//hLayer3.initRandBias();
	//hLayer3.initRandomWeights();
	//hLayer3.updateAllNodes();
	//hLayer3.printNodestocout();

	//OutputLayer oLayer(hLayer3, 10);
	//oLayer.initRandomWeights();
	//oLayer.updateAllNodes();
	//oLayer.printNodestocout();

	//ImageClassifier classifier(oLayer.getNodeVector());

	//std::cout << "Network believes that this is a " << classifier.getOutputValue() << std::endl;
	//oLayer.printWeightstocout();
	//HiddenLayer l1(16, 16, 1, testInputVector);

	//l1.setKthWeightVector(testWeightVector, 0);
	////l1.x_dot_wk(0);
	////l1.setKthBias(0, -25);
	//l1.initRandBias();
	////l1.updateNodeK(0);
	//l1.updateAllNodes();
	//HiddenLayer l2(l1);
}

