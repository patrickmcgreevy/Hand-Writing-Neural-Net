#include "ImageClassifier.h"

ImageClassifier::ImageClassifier(vector<double>& rInput) :
	rInputVector(rInput)
{
}

int ImageClassifier::getOutputValue()
{
	double max = rInputVector[0];
	int value = 0;

	for (int i = 1; i < rInputVector.size(); ++i)
	{
		if (rInputVector[i] > max)
		{
			max = rInputVector[i];
			value = i;
		}
	}


	return value;
}
