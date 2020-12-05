#include "../include/NeuralNetwork.hh"
#include "../include/matrix.hh"
#include "../include/utils/MultiplyMatrix.hh"

NeuralNetwork::NeuralNetwork(vector<int> topology){
    this->topology = topology;
    this->topologySize = topology.size();
    for(int i=0;i<this->topologySize;i++){
        Layer *l = new Layer(topology.at(i));
        this->layers.push_back(l);
    }

    for(int i=0;i<this->topologySize-1;i++){
        Matrix *m = new Matrix(topology.at(i),topology.at(i+1),true);
        this->weightMatrices.push_back(m);
    }
}

void NeuralNetwork::feedForward(){
    for(int i=0;i<this->layers.size()-1;i++){
        Matrix *a = this->getNeuronMatrix(i);

        if(i!=0){
            a = this->getActivatedNeuronMatrix(i);
        }

        Matrix *b = this->getWeightMatrix(i);
        Matrix *c = (new utils::MultiplyMatrix(a,b))->execute();

        for(int c_index=0;c_index<c->getNumCols();c_index++)
            this->setNeuronValue(i+1,c_index,c->getValue(0,c_index));
    }
}

void NeuralNetwork::setCurrentInput(vector<double> input){
    this->currentInput = input;
    for(int i=0;i<input.size();i++){
        this->layers.at(0)->setVal(i,input.at(i));
    }
}

void NeuralNetwork::printToConsole(){
    for(int i=0;i<this->topologySize;i++){
        cout<<"Layer : "<<i<<endl;
        if(i==0){
            Matrix *m = this->layers.at(i)->matrixifyVals();
            m->printToConsole();
        }else{
            Matrix *m = this->layers.at(i)->matrixifyActivatedVals();
            m->printToConsole();
        }
    }
}