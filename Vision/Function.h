#pragma once
#include <Eigen/Dense>
#include "Activation.h"
#include "Loss.h"

class Function
{
public:
	static Eigen::VectorXf ActivationFunction(Activation activation, Eigen::VectorXf src);
	static Eigen::VectorXf ErrorFunction(Loss loss, Eigen::VectorXf y, Eigen::VectorXf output);
	
	static Eigen::VectorXf ActivationFunctionPrime(Activation activation, Eigen::VectorXf src);
	static Eigen::VectorXf ErrorFunctionPrime(Loss loss, Eigen::VectorXf y, Eigen::VectorXf output);
private:
	// activation
	static Eigen::VectorXf Sigmoid(Eigen::VectorXf src);

	// loss
	static Eigen::VectorXf MeanSquaredError(Eigen::VectorXf y, Eigen::VectorXf output);

	// activation prime
	static Eigen::VectorXf SigmoidPrime(Eigen::VectorXf src);

	// loss prime
	static Eigen::VectorXf MeanSquaredErrorPrime(Eigen::VectorXf y, Eigen::VectorXf output);
};

