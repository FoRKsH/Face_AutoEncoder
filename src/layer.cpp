#include "layer.h"



layer::layer(int myin, int myout, float myalfa, int* mynPatterns,bool initializ)
{
    int i,s;
    nIn=myin;
    nOut=myout;
    alfa=myalfa;
    pnPat = mynPatterns;
    active = 1;
    // initialize arrays
    drop = new bool [nOut];
    w= new float* [nOut];
    dw= new float* [nOut];
    mOutB = new float [nIn];
    mOutF = new float [nOut];
    b= new float [nOut];
    db= new float [nOut];
    for ( s =0; s<nOut; s++)
    {
        w[s]= new float [nIn];
        dw[s]= new float [nIn];

    }
    // initialize random weights and bias
    if (initializ)
    {
         for (s=0; s<nOut; s++ )
         {
             for (i=0; i<nIn; i++)
                    w[s][i]=((rand()%100)-50)/1000.00;
             b[s]=((rand()%100)-50)/1000.00;
         }
    }
    // set all weights and bias to zero
    else if (!initializ)
    {
        for (s=0; s<nOut; s++ )
         {
             for (i=0; i<nIn; i++)
                    w[s][i]=0.0;
             b[s]=0.0;
         }
    }

}
layer::~layer ()
{
    int s;
    for ( s =0; s<nOut; s++)
    {
        delete w[s];
        delete dw[s];
    }
    delete [] w;
    delete [] dw;
    delete [] b;
    delete [] db;
    delete [] mOutB;
    delete [] mOutF;
}
/////////////////////////////////////////////////////////////////////////
void layer::makeBefore(layer* L)
{
    L->pInF = mOutF;
    pInB = L->mOutB;
}
/////////////////////////////////////////////////////////////////////////
void layer::FF()
{
    int i,s;
    float z;
        for ( s=0; s<nOut; s++)
        {
            z=b[s];
            for (i=0; i<nIn; i++)   z+=w[s][i] * pInF[i];
            switch (active)
            {
                case 0: // satliner
                    {
                        if (z<=-1)
                            mOutF[s]=-1;
                        else if (z>=1)
                            mOutF[s]=1;
                        else
                            mOutF[s]=z;
                    break;
                    }
                case 1:     {   mOutF[s] = tanh(z); break;  }   //tanh function
            }
        }
}
/////////////////////////////////////////////////////////////////////////
void layer::BP()
{
    int i,s;
    float* dz = new float [nOut]; // as it is delta in
        for (i=0; i<nIn; i++) mOutB[i] = 0.0;    //initializing mOutB with 0
        for (s=0; s<nOut; s++)
        {
            dz[s] = pInB[s] * ( 1 - ( mOutF[s] * mOutF[s] ) );
            //dz[s] = pInB[s] * ( 1.2 - abs(mOutF[s]) );
            db[s] += dz[s];
            for (i=0; i<nIn; i++)
            {
                dw[s][i] += (dz[s]*pInF[i]);
                mOutB[i] += w[s][i]*dz[s];
            }
        }
        delete [] dz;
}
/////////////////////////////////////////////////////////////////////////
void layer::update(int m)
{
    int i,s;
    for (s=0; s<nOut; s++ )
    {
        b[s]+= db[s] * alfa/ m;
        for (i=0; i<nIn; i++)
            w[s][i]+= dw[s][i] * alfa/ m;
    }
}
/////////////////////////////////////////////////////////////////////////
void layer::reset()
{
    int i,s;
  for (s=0; s<nOut; s++ )
    {
        db[s]=0.0;
        for (i=0; i<nIn; i++)   dw[s][i]=0.0;
    }
}
/////////////////////////////////////////////////////////////////////////
