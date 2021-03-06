/*
Cat and Dog Classifier
By: Pascal Canuel, William Garneau & Isaac Fiset
*/

#include "AllIncludes.h"
#include <opencv2/core/eigen.hpp>

using namespace cv;
using namespace Eigen;

int main()
{
	/*DataLoader dl;
	auto test = dl.LoadData("../dataset/test");
	auto train = dl.LoadData("../dataset/train");*/

	/*
	Before refactoring:
		68-69 secs backprop test images
		13-14 secs evaluation test images
	*/

	std::vector<Mat> vecImages;
	vecImages.reserve(10000);
	MNIST::ReadImages("../MNIST/t10k-images.idx3-ubyte", vecImages);
	std::vector<int> vecLabels(10000);
	MNIST::ReadLabels("../MNIST/t10k-labels.idx1-ubyte", vecLabels);

	std::vector<Mat> vecImagesTrain;
	vecImagesTrain.reserve(60000);
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
	//model.Fit(train, test);
	model.Hyperparameter(30, 10, 1.0f);

	model.Train();

	model.SaveWeights("MNIST.dat");
	//model.LoadWeights("MNIST.dat");

	for (int i = 0; i < vecImages.size(); i++)
	{
		int prediction = model.Predict(vecImages[i]);
		Guess::Print(vecLabels[i], prediction, vecImages[i]);
		waitKey(0);
	}
	
	waitKey(0);
	return 0;
}