#include <QtCore/QCoreApplication>

#include "qimage.h"
#include "ImagePreProcessing.h"
#include "NeuralNetwork.h"



#define ILOSC_ZNAKOW 15

void learnMatrix(vector<vector<int>> &matrix, vector<vector<int>> immatrix, int ii) {
	vector<int> convert;
	int col_count = 0;
	for (int i = 0; i < immatrix.size(); i++) {
		for (int j = 0; j < immatrix[0].size(); j++) {
				convert.push_back(immatrix[i][j]);
			}
		}

	for (const auto &count : convert) {
		matrix[ii][col_count]=convert[col_count];
		col_count++;
	}
}


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	vector<vector<int>> inputmatrix;

	ImagePreProcessing imagepreprocessing(16);/*("F:/softcomputing/znak2.png");*/
	NeuralNetwork neuralnetwork;
	
	for (int ii = 0; ii < ILOSC_ZNAKOW; ii++) {
		stringstream s;
		string ss;
		s << "scaled_znak" << ii + 1;
		ss = s.str();
		s.str("");

		imagepreprocessing.convertImageToMatrix(ss.c_str(), "F:/softcomputing/", ".png");
		inputmatrix.resize(ILOSC_ZNAKOW, vector<int>(imagepreprocessing.scaledSize()));
		learnMatrix(inputmatrix, imagepreprocessing.imagearray, ii);

	}


	neuralnetwork.setSize_all(imagepreprocessing.scaledSize(), inputmatrix);
	neuralnetwork.hebianLearning(inputmatrix);
	neuralnetwork.pseudoinversLearning(inputmatrix);
	//imagepreprocessing.maskCreation("znak21_ed", "f:/softcomputing/",".png","znak21_ed");
	//imagepreprocessing.scaledImage("b_znak21_ed", "f:/softcomputing/", ".png", "znak21_ed");

	imagepreprocessing.retreievingImage("F:/softcomputing/mud/mud_znak12_w_trybie1.png");
	neuralnetwork.retPhase(imagepreprocessing.retimagearray, neuralnetwork.pseudoinversWeight);

	return a.exec();
}



//int ccc = 0;
//for (auto i = 0; i < 16 * 16; ++i) {
//	if (ccc % 16 == 0) {
//		cout << endl;
//		ccc = 0;
//	}
//	if (inputmatrix[0][i] == 1)
//		cout << " " << inputmatrix[0][i] << " ";
//	else
//		cout << inputmatrix[0][i] << " ";
//	ccc++;
//}

//for (int j = 1; j < 22; j++) {
//	for (int i = 10; i > 1; i--) {

//		imagepreprocessing.noiseFunction("f:/softcomputing/scaled_znak", i, j);
//	}
//}