#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <streambuf>
#include <ostream>
#include <time.h>

#include "../include/utils/Math.hh"
#include "../include/Matrix.hh"
#include "../include/NeuralNetwork.hh"

using namespace std;

int main(int argc, char **argv){
    vector<double> input;
    input.push_back(0.2);
    input.push_back(0.5);
    input.push_back(0.1);

    vector<double> target;
    target.push_back(0.2);
    target.push_back(0.5);
    target.push_back(0.1);

    double learningRate = 0.05;
    double momentum = 1;
    double bias = 1;

    vector<int> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(3);

    NeuralNetwork *n = new NeuralNetwork(topology, bias, learningRate, momentum);
    
    ofstream errorsOP("output.txt");
    vector<double> histErrors;
    for(int i=0; i < 1000; i++){
        n->train(input, target, bias, learningRate, momentum);
        histErrors.push_back(n->error);
    }

    for(int i=0;i<histErrors.size();i++){
        errorsOP<<i<<" "<<histErrors.at(i)<<endl;
    }

    return 0;
}