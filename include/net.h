#ifndef NET_H
#define NET_H
#include "layer.h"
#include "trainSet.h"
#include <iostream>

class layer;
class trainSet;

class net
{   // we assume the input is not a layer but output is

    public:
    int nL;             //number of layers
    int* pnIn;          //pointer to number of inputs
    int* pnOut;         //pointer to number of outputs
    int* nForLayers;    //size of all layers
    int* nPatterns;     //number of patterns
    float alfa;
    trainSet* ts;
    layer** Ls;

    net(int mynL, trainSet* myts);
    net(net** N, trainSet* myts, int nNet);
    ~net();
    layer* operator [] (int i);     //pointer to a layer
    void Creat();
    void print();
    void save();
    void load();
};

#endif // NET_H
