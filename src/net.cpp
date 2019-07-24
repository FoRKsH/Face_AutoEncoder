#include "net.h"


using namespace std;

net::net(int mynL, trainSet* myts)
{
    nL = mynL;
    ts = myts;
    pnIn = &(ts->nIn);
    pnOut= &(ts->nOut);
    nPatterns = &(ts->nPat);
    nForLayers = new int[mynL];
    nForLayers[nL-1]= *pnOut;
}
net::net(net** N, trainSet* myts, int nNet)     // not working while training !
{
    nL = N[0]->nL;
    ts = myts;
    pnIn = &(ts->nIn);
    pnOut= &(ts->nOut);
    nPatterns = &(ts->nPat);
    nForLayers = new int[nL];
    nForLayers[nL-1]= *pnOut;

    int i,s,j,z;
    for (i=0; i <nL-1; i++) nForLayers[i] = (N[0]->nForLayers[i]) * nNet ;
    Ls = new layer* [nL];
    Ls[0]= new layer(*pnIn, nForLayers[0], alfa, nPatterns,false);
    for (i=1; i<nL; i++)
    {
        Ls[i]= new layer(nForLayers[i-1], nForLayers[i], alfa, nPatterns,false);
        Ls[i-1]->makeBefore(Ls[i]);
    }
    for (j=0; j<nL; j++)
    {
        Ls[j]->active = N[0]->Ls[j]->active;
        z=-1;
        for (s=0; s<nForLayers[j]; s++)
            {
                if (s % (N[0]->nForLayers[j] ) == 0 )  z++;
                for (i=0; i < Ls[j]->nIn; i++)
                        if (i/N[z]->Ls[j]->nIn == z || j==0)
                            Ls[j]->w[s][i]= N[z]->Ls[j]->w[ s%N[z]->Ls[j]->nOut ][ i%N[z]->Ls[j]->nIn ];
                Ls[j]->b[s]= N[z]->Ls[j]->b[ s%N[z]->Ls[j]->nOut ];
            }
    }
    for (i=0; i<nNet; i++)  delete N[i];
    delete [] N;
}
net::~net()
{
    for (int i=0; i<nL; i++)
        delete Ls[i];
    delete [] nForLayers;
    delete []  Ls;
}
/////////////////////////////////////////////////////////////////////////
layer* net::operator [] (int i)
{   return Ls[i];    }
/////////////////////////////////////////////////////////////////////////
void net::Creat()
{
    int i;
    Ls = new layer* [nL];
    Ls[0]= new layer(*pnIn, nForLayers[0], alfa, nPatterns,true);
        for (i=1; i<nL; i++)
        {
            Ls[i]= new layer(nForLayers[i-1], nForLayers[i], alfa, nPatterns,true);
            Ls[i-1]->makeBefore(Ls[i]);
        }
}
/////////////////////////////////////////////////////////////////////////
void net::print()
{
    cout<<endl<<"number of layers : "<<nL<<endl;
    cout<<"No. of Layers : "<<nL<<endl;
    cout<<"No. of inputs : "<< *pnIn<<endl;
    cout<<"No. of outputs : "<< *pnOut<<endl;
    cout<<"No. of Patterns ; "<< *nPatterns<<endl;
    cout<<"No. of neurons of each layer"<<endl;
    cout<<"_______________________________"<<endl;
     for(int i=0; i<nL; i++)
        cout <<endl<<"layer number "<< i+1<< "  : "<<nForLayers[i]<<endl<<"-----------------------------";
}
/////////////////////////////////////////////////////////////////////////
void net::save()
{
    int s,L;
    ofstream backup;
    backup.open("Report\\weights.sav",ios::binary|ios::trunc);
    for (L=0; L<nL; L++)
    {
        for (s=0; s<Ls[L]->nOut; s++)
        {
                backup.write( (char*)  (Ls[L]->w[s]) , (Ls[L]->nIn)*sizeof(float) );
                backup.write( (char*) &(Ls[L]->b[s]) , sizeof(float) );
        }
    }
    backup.close();
}
/////////////////////////////////////////////////////////////////////////
void net::load()
{
    int s,L;
    ifstream backup;
    backup.open("Report\\weights.sav",ios::binary);
    for (L=0; L<nL; L++)
    {
        for (s=0; s<Ls[L]->nOut; s++)
        {
            backup.read( (char*)  (Ls[L]->w[s]) , (Ls[L]->nIn)*sizeof(float) );
            backup.read( (char*) &(Ls[L]->b[s]) , sizeof(float) );
        }
    }
    backup.close();
}
