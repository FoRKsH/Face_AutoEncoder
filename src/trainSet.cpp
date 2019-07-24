#include "trainSet.h"

trainSet::trainSet()
{
    x = NULL;
    nIn = 10000;
    pics = new unsigned char[nIn];
    nOut=nIn;
}
////////////////////////////////////////////////////////////////////////
void trainSet::Creat()
{}
////////////////////////////////////////////////////////////////////////
void trainSet::loadtrain()
{
        Pic = 0;
        nPat = trn;
        x = new float*[nPat];
        for(int i = 0; i < nPat; i++)    x[i] = new float[nIn];

		ifstream imagetxt("../Datatxt\\Train.bin",ios::binary);
		if (imagetxt.fail()) {cout<<"Train.bin not found"; exit(0);}

		for(int i =0; i<nPat; i++,Pic++) // Pic++ = to avoid dublication
		{
			if(Pic==trn) // if we reach final pic load from 1
            imagetxt.seekg(Pic*10000*sizeof(unsigned char));
            imagetxt.read(reinterpret_cast<char*>(pics),10000*sizeof(unsigned char));
			for(int j=0; j< nIn &&!imagetxt.eof(); j++)
			{
			    x[i][j] = pics[j];
				x[i][j] = (x[i][j] - 127.5 )/ 127.5;			}
		}

		imagetxt.close();
		y=x;
}
////////////////////////////////////////////////////////////////////////
void trainSet::loadtest()
{
        Pic=0;
        if (x!=NULL)    // Free memory from TrainSet
        {   for (int i=trn; i--;) delete x[i];    delete [] x;   }

        nPat = tst;
        x = new float* [nPat];
        for(int i = 0; i < nPat; i++)   x[i] = new float[nIn];


		ifstream imagetxt("../Datatxt\\Test.bin",ios::binary);
		if (imagetxt.fail()) {cout<<"Test.bin not found"; exit(0);}

		for(int i =0; i<nPat; i++,Pic++) // Pic++ = to avoid dublication
		{
			if(Pic==tst) // if we reach final pic load from 1
            imagetxt.seekg(Pic*10000*sizeof(unsigned char));
            imagetxt.read(reinterpret_cast<char*>(pics),10000*sizeof(unsigned char));
			for(int j=0; j< nIn &&!imagetxt.eof(); j++)
			{
			    x[i][j] = pics[j];
				x[i][j] = (x[i][j] - 127.5 )/ 127.5;			}
		}
		imagetxt.close();
		y=x;
}
////////////////////////////////////////////////////////////////////////
 void trainSet::displayIm(int pI ) //pI image number at loaded train set (x(pI))
{
	int rows = sqrt(nIn); // size of image
	int cols = rows ;
	if (pI >= nPat)   // for safety
		return;
	for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if(x[pI][j+cols*i]<-.6 ) cout<<char(32)<<char(32);
            else if(x[pI][cols*i+j]<-.2) cout<<char(176)<<char(176);
            else if(x[pI][cols*i+j]<.2) cout<<char(177)<<char(177);
            else if(x[pI][cols*i+j]<.56) cout<<char(178)<<char(178);
            else cout<<char(219)<<char(219);
        }
        cout << endl;
    }
}
