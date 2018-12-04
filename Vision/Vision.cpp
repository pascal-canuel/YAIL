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

	// Data augmentation tests
	DataAugmentation shape(trainDog);
	Mat x = shape.GetAugmentedFrame();

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
	TestDependencies();

	DataLoader dl;
	auto test = dl.LoadData("../dataset/test");
	std::vector<cv::Mat> testImages = std::get<0>(test);
	std::vector<int> testLabels = std::get<1>(test);

	/*Eigen::Map<Eigen::Matrix<float, 64, 192, Eigen::RowMajor>> eigen_mat(reinterpret_cast<float*>(testImages[0].data));
	for (int y = 0; y < testImages[0].rows; y++)
	{
		for (int x = 0; x < testImages[0].cols; x++)
		{
			cv::Vec3f pix = testImages[0].at<Vec3f>(y, x);
			std::cout << pix[0] << pix[1] << pix[2] << std::endl;
			
			int i = x * 3;
			std::cout << eigen_mat(y, i) << eigen_mat(y, i + 1) << eigen_mat(y, i + 2) << std::endl;
		}	
	}*/

	Network model({
		new Layers::Input(4096),
		new Layers::Dense(64, sigmoid),
		new Layers::Dense(2, sigmoid)
		});

	//model.Add(new Layers::Dense(64, "sigmoid"));

	model.Compile(stochastic_gradient_descent, mean_squared_error);
	model.Summary();
	model.Fit(test, test); // first parameter should be training data
	model.Hyperparameter(30, 10, 1.0);
	model.Train();
	//std::vector<float> prediction = model.Predict(testImages[0]);

	//model.SaveWeights("weights.dat");
	//model.LoadWeights("weights.dat")

	//model.Plot();

	//GuessTest tst;
	//tst.StartTest(&testImages, &testLabels);
	/*
	// genius https://stackoverflow.com/questions/14783329/opencv-cvmat-and-eigenmatrix
	Eigen::Map<Eigen::Matrix<float, 64, 64>, Eigen::RowMajor, Eigen::Stride<3, 1>> red(testImages[0].ptr<float>());
	Eigen::Map<Eigen::Matrix<float, 64, 64>, Eigen::RowMajor, Eigen::Stride<3, 1>> green(testImages[0].ptr<float>() + 1);
	Eigen::Map<Eigen::Matrix<float, 64, 64>, Eigen::RowMajor, Eigen::Stride<3, 1>> blue(testImages[0].ptr<float>() + 2);

	// test of mapped data
	for (int i = 0; i < 25; i++)
	{
		std::cout << (float)testImages[0].at<Vec3f>(0, i)[0] << (float)testImages[0].at<Vec3f>(0, i)[1] << (float)testImages[0].at<Vec3f>(0, i)[2] << " vs " << red(0, i) << green(0, i) << blue(0, i) << std::endl;
	}
	for (int i = 0; i < 25; i++)
	{
		cv::Mat out = testImages[i];
		resize(testImages[i], out, cv::Size(200,200));
		cv::imshow(dl.ClassNames[testLabels[i]], out);
		waitKey(0);
	}
	auto train = dl.LoadData("../dataset/train");
	std::vector<cv::Mat> trainImages = std::get<0>(train);
	std::vector<int> trainLabels = std::get<1>(train);
	*/
	waitKey(0);
	return 0;

	waitKey(0);
	return 0;
}