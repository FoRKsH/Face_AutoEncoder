#ifndef TRAINER_H
#define TRAINER_H
#include "net.h"
#include "trainSet.h"
#include "layer.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include<conio.h>
#include <cstdlib>
#include <ctime>

class trainSet;
class net;

class trainer
{
  public:
  bool show;
  int m;                //current pattern number
  trainSet* ts;         //pointer to training set
  net* Net;             //the net
  float errorCount;     //sum of pattern in error
  float* pa;           //the output of the last layer
  float* mda;          //dl/da
  int* idx;             //will be used for shuffled index
  //the upcoming pointers are to variables to improve computation
  int* pnIn;            //pointer #input
  int* pnOut;           //pointer #output
  int* pnPat;           //pointer #patterns
  int* nL;              //pointer #layers
  float** px;          //pointer to input
  float** py;          //pointer to output
  trainer(net* theNet, trainSet* Ts);
  void shuffle();
  void NFF();           //network feed forward
  void NBP();           //network back propagation
  void Nupdate(int m);       //network update b , w
  void Nreset();        //network reset db , dw
  void delta();         //to update dl/da
  float train (int cycles);       //to train
  float test();
  void print();
  void autosave();
  void savepics(); // need a folder "output" in project directory
};



#endif // TRAINER_H
