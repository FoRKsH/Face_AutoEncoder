#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>
//#include<thread>
#include "layer.h"
#include "trainSet.h"
#include "net.h"
#include "trainer.h"
using namespace std;

class layer;
class net;
class trainer;
class trainSet;


void restart(net* N)
{
    char choice;
    int i=0;
    bool flag;
    bool structure = true;
    fstream stat;
    stat.open("Report\\Read Only.txt",ios::in);
    stat>>flag;
    if (flag==true)
    {
        // check network structure
        if (stat.eof()) return; // no network saved
        int temp;
        stat>>temp;
        if (temp!=N->nL) structure = false;
        while(!stat.eof())
        {
            stat>>temp;
            if (temp!= (N->nForLayers[i++])) structure = false;
        }

        if (structure==false)
        {
            cout<<"network structure changed ! continue training (y) or exit (n)  ?"<<endl;
            cout<<"warning restarting training will overwrite the previous weights and can't be restored !"<<endl;
            do
            {
                choice = getche();
                cout<<endl;
                if (choice=='y'||choice=='Y')
                {
                    stat.close();
                    stat.open("Report\\Read Only.txt" , ios::out|ios::trunc);
                    stat<<0;
                    stat.close();
                    return;
                }
                else if (choice=='n'||choice=='N')
                {
                   cout<<"old network structure ";
                   N->print();
                   exit(0);
                }
            }while (choice != 'y' && choice !='n' && choice !='Y'  && choice !='N');
        }

        cout<<endl<<"previous data found , do you want to continue training ? (y),(n)"<<endl;
        cout<<"warning restarting training will overwrite the previous weights and can't be restored !"<<endl;
        do
        {
                choice = getche();
                cout<<endl;
                if (choice=='y'||choice=='Y')
                {
                    cout<<"please wait while loading ...."<<endl;
                    N->load();
                    cout<<"weights has been loaded successfully :)"<<endl;
                    stat.close();
                    stat.open("Report\\Read Only.txt" , ios::out);
                    stat<<0;
                    stat.close();
                }
                else if (choice=='n'||choice=='N')
                {
                    stat.close();
                    stat.open("Report\\Read Only.txt" , ios::out|ios::trunc);
                    stat<<0;
                    stat.close();
                }
        }while (choice != 'y' && choice !='n' && choice !='Y'  && choice !='N');
    }
}

int main()
{
    int i=0;
    trainSet* TS = new trainSet();
    TS->loadtrain();
    net* N= new net(2,TS);
    N->alfa = 0.0005;      //learning rate
    N->nForLayers[0]=500;
    //N->nForLayers[1]=350;
    //N->nForLayers[2]=500;
    N->Creat();
    restart(N);
    trainer* tr = new trainer(N,TS);
    tr->train(999999999);

    /** Remove comment for testing **/
    //TS->loadtest();
    //i=tr->test();
    cout<<"error    :   " <<i<<endl;
    return 0;
}
