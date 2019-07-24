#ifndef LAYER_H
#define LAYER_H
#include "trainer.h"
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <fstream>

class trainer;
class layer;

class layer
{
    public:
    int active;     // 0 for linersat , 1 for tanh
    int nIn;
    int nOut;
    float alfa;
    bool* drop;
    float** w;
    float** dw;
    float* b;
    float* db;
    float* mOutF; //output a
    float* mOutB; // dl/da1
    float* pInF;  //input a
    float* pInB;  // da/da
    int* pnPat;     //pointer patterns
    trainer* tr;    //trainer pointer

    layer(int myin, int myout, float myalfa, int* mynPatern,bool initializ);
    ~layer();
    void makeBefore(layer* L);  //phantom before L
    void FF();      //to FeedForward
    void BP();      //to Back propagation
    void update(int m);
    void reset();
};

#endif // LAYER_H
