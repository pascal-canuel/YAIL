/*
Cat and Dog Classifier
By: Pascal Canuel, William Garneau & Isaac Fiset

Dataset: https://www.kaggle.com/c/dogs-vs-cats/data
Eigen: http://eigen.tuxfamily.org/index.php?title=Main_Page
*/

#include "AllIncludes.h"
#include <opencv2/core/eigen.hpp>

using namespace cv;
using namespace Eigen;

void SaveEigenMatrix(std::string filename, Eigen::MatrixXf mat)
{
	std::ofstream of;
	of.open(filename, std::ios::binary | std::ios::out);

	int rows = mat.rows();
	of.write((char*)&rows, sizeof(int));

	int cols = mat.cols();
	of.write((char*)&cols, sizeof(int));

	float* data = mat.data();
	of.write((char*)&data[0], sizeof(float) * rows * cols);
}

void LoadEigenMatrix(std::string filename, Eigen::MatrixXf& mat)
{
	std::ifstream inf;
	inf.open(filename, std::ios::binary | std::ios::in);

	int rows = mat.rows();
	inf.read((char*)&rows, sizeof(int));

	int cols = mat.cols();
	inf.read((char*)&cols, sizeof(int));

	float* data = mat.data();
	inf.read((char*)&data[0], sizeof(float)* rows * cols);
}

void SaveEigenVector(std::string filename, Eigen::VectorXf mat)
{
	std::ofstream of;
	of.open(filename, std::ios::binary | std::ios::out);

	int rows = mat.rows();
	of.write((char*)&rows, sizeof(int));

	float* data = mat.data();
	of.write((char*)&data[0], sizeof(float) * rows);

	of.close();
}

void LoadEigenVector(std::string filename, Eigen::VectorXf& mat)
{
	std::ifstream inf;
	inf.open(filename, std::ios::binary | std::ios::in);

	int rows = mat.rows();
	inf.read((char*)&rows, sizeof(int));

	float* data = mat.data();
	inf.read((char*)&data[0], sizeof(float)* rows);

	inf.close();
}

int main()
{
	Eigen::MatrixXf matTest = Eigen::MatrixXf::Random(6, 6);
	SaveEigenMatrix("silly.dat", matTest);
	std::cout << matTest << std::endl;

	Eigen::MatrixXf matTestI = Eigen::MatrixXf(6, 6);
	SaveEigenMatrix("silly.dat", matTestI);
	std::cout << "\r\n" << matTestI << std::endl;

	//DataLoader dl;
	//auto test = dl.LoadData("../dataset/test");
	//std::vector<cv::Mat> testImages = std::get<0>(test);
	//std::vector<int> testLabels = std::get<1>(test);

	std::vector<cv::Mat> vecImages;
	MNIST::ReadImages("../MNIST/t10k-images.idx3-ubyte", vecImages);
	std::vector<int> vecLabels(10000);
	MNIST::ReadLabels("../MNIST/t10k-labels.idx1-ubyte", vecLabels);

	std::vector<cv::Mat> vecImagesTrain;
	MNIST::ReadImages("../MNIST/train-images.idx3-ubyte", vecImagesTrain);
	std::vector<int> vecLabelsTrain(60000);
	MNIST::ReadLabels("../MNIST/train-labels.idx1-ubyte", vecLabelsTrain);

	Network model({
		new Layers::Input(784),
		new Layers::Dense(30, sigmoid),
		new Layers::Dense(10, sigmoid)
		});



	model.Compile(stochastic_gradient_descent, mean_squared_error);
	model.Summary();
	model.Fit({ vecImagesTrain, vecLabelsTrain }, { vecImages, vecLabels });
	model.Hyperparameter(40, 10, 3.0);
	model.Train();

	waitKey(0);
	return 0;
}