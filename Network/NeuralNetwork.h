#pragma once

#include<iostream>
#include<vector>
#include<math.h>
#include<armadillo>


using namespace std;

class NeuralNetwork
{
private:
	int size_all;
	int images;
public:
	vector<vector<double>> hebianWeight;
	vector<vector<double>> pseudoinversWeight;

	void hebianLearning(vector<vector<int>> inputmatrix);
	void pseudoinversLearning(vector<vector<int>> inputmatrix);
	void retPhase(vector<vector<int>>, vector<vector<double>> weigth2);

	void setSize_all(int a, vector<vector<int>>b);
};
