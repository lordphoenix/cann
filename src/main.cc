#include<bits/stdc++.h>
#include "../include/matrix.hh"
#include "../include/Neuron.hh"
#include "../include/NeuralNetwork.hh"

using namespace std;
using namespace std::chrono; 

int main()
{
    vector<int> topology;
    topology.push_back(3);
    topology.push_back(2);
    topology.push_back(3);

    vector<double> input;
    input.push_back(2.0);
    input.push_back(1.0);
    input.push_back(3.0);

    NeuralNetwork *nn = new NeuralNetwork(topology);
    nn->setCurrentInput(input);
    nn->setCurrentTarget(input);

    auto start = high_resolution_clock::now();
    nn->feedForward();
    nn->setErrors();
    nn->backPropagation();
    cout<<endl<<"Total Error for this Neural Network is : "<<nn->getTotalError()<<endl;
    ofstream errorsOP("output.txt");
    for(int i=0;i<999;i++){
        nn->feedForward();
        nn->setErrors();
        nn->backPropagation();
    }

    vector<double> histErrors = nn->getHistoricalError();

    for(int i=0;i<histErrors.size();i++){
        errorsOP<<i<<" "<<histErrors.at(i)<<endl;
    }

    cout<<"histErrors.size() = "<<histErrors.size()<<endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    long long time =  duration.count();
    double timeInSeconds = time/double(1000000);
    cout << "Time taken by function: "
        << timeInSeconds << " seconds" << endl; 
    cout<<endl<<"Total Error for this Neural Network is : "<<nn->getTotalError()<<endl;

    return 0;
}