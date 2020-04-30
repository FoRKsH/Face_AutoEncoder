#ifndef TRAINSET_H
#define TRAINSET_H
#include<fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
class trainSet
{
    public:
    const int trn=19618;
    const int tst=3924;
    const int cls=56;
    int nIn;    //input
    int nOut;   //output
    int nPat;   //patterns
    float** x; //input
    float** y; //output
    trainSet();
    ~trainSet();
    void Creat();    //to actually construct the TS
/** ---------------------face auto encoder-------------- **/
    void displayIm(int pI);
    void loadtrain( ); // load pictures ( )
    void loadtest();
    void loadOut();  //to load output layer from another network
    void loadtoclassify();
    int Pic ; 			// number of pics
    unsigned char* pics;
};

#endif // TRAINSET_H
