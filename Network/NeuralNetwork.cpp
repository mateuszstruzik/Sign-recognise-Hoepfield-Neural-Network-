#include "NeuralNetwork.h"

void NeuralNetwork::hebianLearning(vector<vector<int>> inputmatrix)
{
	double Alg = 0, sum_Alg = 0, fin_Alg = 0;
	hebianWeight.resize(size_all , vector<double>(size_all ));
	for (int i = 0; i < size_all; i++) {
		for (int j = 0; j < size_all; j++) {
			if (hebianWeight[i][j] == 0) {
				if (i == j) {
					hebianWeight[i][j] = 0;
				}
				else
				{
					///////
					for (int k = 0; k < images; k++) {
						Alg = inputmatrix[k][i] * inputmatrix[k][j];
						sum_Alg += Alg;
					}
					fin_Alg = sum_Alg / size_all;
					sum_Alg = 0;
					///////

					hebianWeight[i][j] = fin_Alg;
					hebianWeight[j][i] = fin_Alg;
				}
			}
		}
	}

	//for (int i = 0; i < size_all; i++) {
	//	for (int j = 0; j < size_all; j++) {
	//		cout << hebianWeight[i][j] << " ";
	//	}
	//	cout << endl;
	//}
}

void NeuralNetwork::pseudoinversLearning(vector<vector<int>> inputmatrix)
{
	int sx = inputmatrix.size();
	int sy = inputmatrix[0].size();
	arma::mat M(sx, sy);
	pseudoinversWeight.resize(size_all,vector<double>(size_all));
	for (int i = 0; i < sx; i++) {
		for (int j = 0; j < sy; j++) {
			M(i, j) =inputmatrix[i][j];
		}
	}
	arma::mat Wt;
	int i = arma::det(M.t()*M);
	if(i==0)
	Wt = arma::pinv(M)*M;
	else {
	Wt = M*arma::inv(M.t()*M)*M.t();
	}
	
	for (int i = 0; i < size_all; i++) {
		for (int j = 0; j < size_all; j++) {
			pseudoinversWeight[i][j] = Wt(i, j);
		}
	}
}

void NeuralNetwork::retPhase(vector<vector<int>> rettmatrix, vector<vector<double>> weigth2)
{
	vector<int> ret_vect;
	int newheight = rettmatrix.size(), newwidth = rettmatrix[0].size();
	for (int i = 0; i < rettmatrix.size(); i++) {
		for (int j = 0; j < rettmatrix[0].size(); j++) {
			ret_vect.push_back(rettmatrix[i][j]);
		}
	}

	cout << "obrazek wczytany " << endl;
	for (int i = 0; i < newheight*newwidth; i++) {

		if (i % (newheight) == 0)
			std::cout << std::endl;

		if (ret_vect[i] == 1)
			std::cout << " " << ret_vect[i] << " ";
		else
			std::cout << ret_vect[i] << " ";

	}
	cout << endl;

	double sila = 0;
	int iteruj = 1;
	int count = 0;
	vector<int> buc_ret_vect = ret_vect;

	while (iteruj)
	{

		for (int i = 0; i < newheight*newwidth; i++) {
			sila = 0;
			for (int j = 0; j < newheight*newwidth; j++) {
				//sila += weight_matrix[i][j] * ret_vect[j];
				sila += weigth2[i][j] * buc_ret_vect[j];
			}
			if (sila > 0) {
				ret_vect[i] = 1;
				count++;
			}
			else if (sila < 0)
			{
				ret_vect[i] = -1;
				count++;
			}
			else
			{
				ret_vect[i] = ret_vect[i];
				count++;
			}

			//std::wcout << "neuron : " << count;
		}
		std::cout << "-------------------------------"<< "kolejna iteracja"<<endl;
		for (int i = 0; i < newheight*newwidth; i++) {

			if (i%(newheight) == 0)
				std::cout << std::endl;

			if (ret_vect[i] == 1)
				std::cout << " " << ret_vect[i] << " ";
			else
				std::cout << ret_vect[i] << " ";

		}
		cout << endl;

		if (buc_ret_vect == ret_vect)
			iteruj = 0;
		buc_ret_vect = ret_vect;

	}

	std::cout << std::endl << "-------------------------------"<<"rozpoznawanie zakonczone"<<endl;
	for (int i = 0; i <newheight*newwidth; i++) {

		if (i%(newheight) == 0)
			std::cout << std::endl;

		if (ret_vect[i] == 1)
			std::cout << " " << ret_vect[i] << " ";
		else
			std::cout << ret_vect[i] << " ";

	}

}

void NeuralNetwork::setSize_all(int a, vector<vector<int>>b)
{
	images = b.size();
	size_all = a;

}
