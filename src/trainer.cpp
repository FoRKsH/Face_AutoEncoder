#include "trainer.h"

using namespace std;
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
trainer::trainer(net* theNet, trainSet* Ts)
{
    show=false;
    Net= theNet;
    ts =Ts;
    px = ts->x;
    py = ts->y;
    nL = &(Net->nL);
    pnIn = Net->pnIn;
    pnOut = Net->pnOut;
    pnPat = Net->nPatterns;
    pa = Net->Ls[(*nL-1)]->mOutF;
    mda = new float [*pnOut];
    idx = new int[*pnPat];
    Net->Ls[(*nL-1)]->pInB = mda;


    for (int i=0; i<Net->nL; i++)   Net->Ls[i]->tr = this;      // link layer to trainer class
}
/////////////////////////////////////////////////////////////////////////
void trainer::Nreset()
{
  int i ;
  for (i = 0; i<*nL; i++)
        Net->Ls[i]->reset();
}
/////////////////////////////////////////////////////////////////////////
void trainer::NFF()
{
    int i ;
    for (i = 0; i<*nL; i++)
        Net->Ls[i]->FF();

}
/////////////////////////////////////////////////////////////////////////
void trainer::NBP()
{
    int i;
    for (i = *nL; i>0; i--)
        Net->Ls[i-1]->BP();
}
/////////////////////////////////////////////////////////////////////////
void trainer::Nupdate(int m)
{
  int i;
  for (i = *nL; i>0; i--)
        Net->Ls[i-1]->update(m);
}
/////////////////////////////////////////////////////////////////////////
void trainer::shuffle()
{
    int mn=0, mx=*pnPat-1,pos=0,x;
    bool* shfl = new bool[*pnPat];
    for (int i=0; i<*pnPat; i++) shfl[i] = true;
    while (pos<*pnPat)
    {
        x = mn + rand()%(mx-mn +1);
        if(shfl[x]==true)
        {
            if (x==mn)
            {
                mn++;
                while (shfl[mn]==false)
                    mn++;

            }
            if (x==mx)
            {
                mx--;
                while (shfl[mx]==false)
                    mx--;

            }
            idx[pos++]=x;
            shfl[x]=false;
        }
    }
    delete [] shfl;
}
/////////////////////////////////////////////////////////////////////////
void trainer::delta()
{
    if (kbhit()==1 )
        {
            char key = getch();
            if (key == 's')
            {
                autosave();
                cout<<endl<<"saving complete :)"<<endl;
                exit(0);
            }
            else if (key=='e')  show = !show;
            else if (key=='p')  savepics();
        }
    float error = 0;
    int s;
    for (s=0; s<*pnOut; s++)
    {
        mda[s] = py[m][s] - pa[s];
        error += abs(mda[s]);
    }
    error /= (float)*pnOut*2;
    if (show)   cout<<endl<<error;
    errorCount += (error>0.05); // allow to 10 pixels error
}
/////////////////////////////////////////////////////////////////////////
//****************************************************************************
float trainer::train (int cycles)
{
    /** Initializing train function **/
    int i;
    int g;        // update after g pattern

    /** start training **/
    for (int c=0; c<cycles; c++)
    {
        /** Autosave weights every 20 cycles **/
        if (c%20 ==0 )
        {
            cout<<"auto saving weights please wait ...."<<endl;
            autosave();
        }

        shuffle();  //shuffle index array
        Nreset();
        errorCount = 0; g=0;

        for (i=0; i<*pnPat; i++ )
        {
            g++;
            m = idx[i]; //random pattern from index matrix
            Net->Ls[0]->pInF = px[m];
            NFF();
            delta();
            NBP();
            /* update weights every g cycle */
            if (g>=20)
            {
                Nupdate(g);
                Nreset();
                g=0;
            }
        }
        if (g>0)    Nupdate(g);

        cout<<endl<<"training cycle "<<c+1; cout<<"  errors:"<<errorCount<<endl;

         if( errorCount==0 )
            break;
    }


    cout<<"auto saving weights please wait ...."<<endl;
    autosave();     // save weights every 100 cycles
    return errorCount;
}

/////////////////////////////////////////////////////////////////////////
void trainer::print()
{
    int cols=100;
    int rows=100;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if(pa[j+cols*i]<-.6 ) cout<<char(32)<<char(32);
            else if(pa[cols*i+j]<-.2) cout<<char(176)<<char(176);
            else if(pa[cols*i+j]<.2) cout<<char(177)<<char(177);
            else if(pa[cols*i+j]<.56) cout<<char(178)<<char(178);
            else cout<<char(219)<<char(219);
        }
        cout << endl;
    }
}
/////////////////////////////////////////////////////////////////////////
void trainer::autosave()
{
    int i;
    ofstream stat;
    stat.open("Report\\Read Only.txt",ios::trunc);
    stat<<endl<<1;  // set flag to be true
    stat<<endl<<Net->nL;
    for (i=0; i< (Net->nL)-1; i++) stat<<endl<<Net->nForLayers[i];
    stat.close();
    Net->save();
}
/////////////////////////////////////////////////////////////////////////
void trainer::savepics()
{
    int x;
    ofstream imagetxt;
    int num;
    cout<<endl<<"how many you want to save !"<<endl;
    cin>>num;
    if (num>*pnPat || num <1) num = 50;
    for (int h = 0; h <num; h++ )
       {
            Net->Ls[0]->pInF = py[h];
            NFF();
            imagetxt.open("../Project\\output\\Train" + to_string(h+1) + ".txt",ios::trunc);
            imagetxt.close();
            imagetxt.open("../Project\\output\\Train" + to_string(h+1) + ".txt",ios::trunc);
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < 100; j++)
                {
                    x= (int) (( 1+pa[100*i  +  j] )*127.5);
                    imagetxt << (int)x <<" ";
                }
            }
            imagetxt.close();
       }
}
/////////////////////////////////////////////////////////////////////////
float trainer::test()
{
    cout<<"Testing starts";
    errorCount=0;
    px = ts->x;
    py = ts->y;
    for (m=0; m<*pnPat; m++)
    {
        Net->Ls[0]->pInF = px[m];
        NFF();
        delta();
    }
    return errorCount;
}
