/*
Cat and Dog Classifier
By: Pascal Canuel, William Garneau & Isaac Fiset

Dataset: https://www.kaggle.com/c/dogs-vs-cats/data
Eigen: http://eigen.tuxfamily.org/index.php?title=Main_Page
*/

#include "AllIncludes.h"
#include <opencv2/core/eigen.hpp>
#include "Matrice.h"
using namespace cv;
using namespace Eigen;

void TestDependencies()
{
	/*std::vector<cv::Mat> vecImages;
	MNIST::ReadImages("../MNIST/t10k-images.idx3-ubyte", vecImages);
	std::vector<int> vecLabels(10000);
	MNIST::ReadLabels("../MNIST/t10k-labels.idx1-ubyte", vecLabels);

	std::vector<cv::Mat> vecImagesTrain;
	MNIST::ReadImages("../MNIST/train-images.idx3-ubyte", vecImagesTrain);
	std::vector<int> vecLabelsTrain(60000);
	MNIST::ReadLabels("../MNIST/train-labels.idx1-ubyte", vecLabelsTrain);*/

	MatrixXd m(2, 2);
	m(0, 0) = 3;
	m(1, 0) = 2.5;
	m(0, 1) = -1;
	m(1, 1) = m(1, 0) + m(0, 1);
	std::cout << m << std::endl;
	
	Size size(200, 200);

	Mat trainCat = imread("../dataset/train/cat/0.jpg");
	Mat trainDog = imread("../dataset/train/dog/0.jpg");

	resize(trainCat, trainCat, size);
	resize(trainDog, trainDog, size);
	imshow("train/cat", trainCat);
	imshow("train/dog", trainDog);

	Mat testCat = imread("../dataset/test/cat/10000.jpg", 0);
	Mat testDog = imread("../dataset/test/dog/10000.jpg");
	resize(testCat, testCat, size);
	resize(testDog, testDog, size);
	imshow("test/cat", testCat);
	imshow("test/dog", testDog);
	
	MatrixXf X = MatrixXf(testCat.rows, testCat.cols);
	cv::cv2eigen(testCat, X);
}

int main()
{
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
		new Layers::Dense(64, sigmoid),
		new Layers::Dense(10, sigmoid)
		});

	model.Compile(stochastic_gradient_descent, mean_squared_error);
	model.Summary();
	model.Fit({ vecImagesTrain , vecLabelsTrain }, { vecImages , vecLabels });
	//model.Fit(test, test); // first parameter should be training data
	model.Hyperparameter(30, 10, 1.0);
	model.Train();
	
	cv::waitKey(0);
	return 0;
}