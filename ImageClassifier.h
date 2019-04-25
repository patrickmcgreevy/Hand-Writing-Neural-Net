#pragma once
#include <vector>

using std::vector;

class ImageClassifier {
public:
	ImageClassifier(vector<double> & rInput);

	int getOutputValue();
private:
	vector<double> & rInputVector;
};