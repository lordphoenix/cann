#ifndef _NEURAL_NETWORK_HPP_
#define _NEURAL_NETWORK_HPP_

#include <bits/stdc++.h>
#include "matrix.hh"
#include "Layer.hh"

using namespace std;

class NeuralNetwork{
    public:
        NeuralNetwork(vector<int> topology);
        void setCurrentInput(vector<double> input);
        void printToConsole();
        void feedForward();

        Matrix *getNeuronMatrix(int index){ return this->layers.at(index)->matrixifyVals(); };
        Matrix *getActivatedNeuronMatrix(int index){ return this->layers.at(index)->matrixifyActivatedVals(); };
        Matrix *getDerivedNeuronMatrix(int index){ return this->layers.at(index)->matrixifyDerivedVals(); };
        Matrix *getWeightMatrix(int index){ return this->weightMatrices.at(index); };

        void setNeuronValue(int indexLayer, int indexNeuron, double val){ this->layers.at(indexLayer)->setVal(indexNeuron,val); };
    private:
        int topologySize;
        vector<int> topology;
        vector<Layer *> layers;
        vector<Matrix *> weightMatrices;
        vector<double> currentInput;        
};

#endif