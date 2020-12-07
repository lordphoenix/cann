#include<bits/stdc++.h>
#include "../include/matrix.hh"
#include "../include/Neuron.hh"
#include "../include/NeuralNetwork.hh"

using namespace std;

int main()
{
    vector<int> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(3);

    vector<double> input;
    input.push_back(1.0);
    input.push_back(0.0);
    input.push_back(1.0);

    NeuralNetwork *nn = new NeuralNetwork(topology);
    nn->setCurrentInput(input);
    nn->setCurrentTarget(input);
    nn->feedForward();
    nn->setErrors();

    nn->printToConsole();

    cout<<endl<<"Total Error for this Neural Network is : "<<nn->getTotalError()<<endl;
    return 0;
}