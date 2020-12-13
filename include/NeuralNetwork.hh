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
        void backPropagation();
        void setErrors();

        Matrix *getNeuronMatrix(int index){ return this->layers.at(index)->matrixifyVals(); };
        Matrix *getActivatedNeuronMatrix(int index){ return this->layers.at(index)->matrixifyActivatedVals(); };
        Matrix *getDerivedNeuronMatrix(int index){ return this->layers.at(index)->matrixifyDerivedVals(); };
        Matrix *getWeightMatrix(int index){ return this->weightMatrices.at(index); };

        void setNeuronValue(int indexLayer, int indexNeuron, double val){ this->layers.at(indexLayer)->setVal(indexNeuron,val); };

        double getTotalError() {return this->error;};
        vector<double> getError() { return this->errors; };
        void setCurrentTarget(vector<double> currTarget){this->target = currTarget;};
    private:
        int topologySize;
        vector<int> topology;
        vector<Layer *> layers;
        vector<Matrix *> weightMatrices;
        vector<Matrix *> gradientMatrices;
        vector<double> currentInput;
        vector<double> target;
        double error;
        vector<double> errors;
        vector<double> historicalErrors;
        
};

#endif