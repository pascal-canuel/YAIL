#include "Layer.h"

Layer::Layer()
{
}

Layer::Layer(int neurons, Activation activation)
{
	Neurons = neurons;
	_Activation = activation;
}

Layer::Layer(int neurons)
{
	Neurons = neurons;
}


Layer::~Layer()
{
}

int Layer::Size()
{
	return Neurons;
}

std::string Layer::ToString()
{
	return std::string();
}

