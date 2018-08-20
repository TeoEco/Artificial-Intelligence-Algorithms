#include <iostream>
#include <string.h>
#include<stdio.h>
#include<cstdlib>
#include<time.h>
#include<math.h>
#define MAX 10000
using namespace std;
double matP[MAX][MAX]= {0};
double matW[MAX][MAX]= {0};

void cachNewdata(long numIn)
{
    for(long i=1; i<=numIn; i++)
    {
        cin>>matP[i][0];
    }
}

void cachData(long numIn,long numOut,long numHi,int val)
{
    int sig;
    char data;
    matP[0][0]=-1;
    matP[1][0]=val;
    for(long i=2; i<=numIn; i++)
    {
        cin>>data;
        //cout<<data<<"-";
        if(data=='1')
            matP[i][0]=1;
        else
            matP[i][0]=0;
       //cout<<matP[i][0]<<endl;
    }
    cin>>data;
    //cout<<data<<endl;
    switch(data)
    {
    case '0':
    {
        matP[0][3]=0;
        matP[1][3]=0;
        matP[2][3]=0;
        matP[3][3]=0;
        break;
    }
    case '1':
    {
        matP[0][3]=1;
        matP[1][3]=0;
        matP[2][3]=0;
        matP[3][3]=0;
        break;
    }
    case '2':
    {
        matP[0][3]=0;
        matP[1][3]=1;
        matP[2][3]=0;
        matP[3][3]=0;
        break;
    }
    case '3':
    {
        matP[0][3]=1;
        matP[1][3]=1;
        matP[2][3]=0;
        matP[3][3]=0;
        break;
    }
    case '4':
    {
        matP[0][3]=0;
        matP[1][3]=0;
        matP[2][3]=1;
        matP[3][3]=0;
        break;
    }
    case '5':
    {
        matP[0][3]=1;
        matP[1][3]=0;
        matP[2][3]=1;
        matP[3][3]=0;
        break;
    }
    case '6':
    {
        matP[0][3]=0;
        matP[1][3]=1;
        matP[2][3]=1;
        matP[3][3]=0;
        break;
    }
    case '7':
    {
        matP[0][3]=1;
        matP[1][3]=1;
        matP[2][3]=1;
        matP[3][3]=0;
        break;
    }
    case '8':
    {
        matP[0][3]=0;
        matP[1][3]=0;
        matP[2][3]=0;
        matP[3][3]=1;
        break;
    }
    case '9':
    {
        matP[0][3]=1;
        matP[1][3]=0;
        matP[2][3]=0;
        matP[3][3]=1;
        break;
    }
    default:
    {
        cout<<"dato"<<data<<endl;
        break;
    }

    }



}

void imprime(long row,long col)
{
    for(long i=0; i<=row; i++)
    {
        for(long j=0; j<col; j++)
        {
            cout<<matP[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
    for(long i=0; i<row; i++)
    {
        for(long j=0; j<3; j++)
        {
            cout<<matW[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void calOc(long numHi,long numIn)
{
    for(long i=0; i<numHi; i++)
    {
        double f=0;
        for(long j=0; j<numIn; j++)
        {
            f+=matP[j][0]*matW[j][i];
            //cout<<i<<" "<<j<<" ";
        }
        //cout<<endl;
        matP[i][1]=(1/(1+exp(-f)));
    }
}
void calOf(long numHi,long numOut)
{
    for(long i=0; i<numOut; i++)
    {
        double f=matP[0][0]*matW[0][i+numHi];
        for(long j=0; j<numHi; j++)
        {
            f+=matP[j][1]*matW[i+1][j+numHi];
            //cout<<i<<" "<<j+numHi<<" ";
        }
        //cout<<endl;
        matP[i][2]=(1/(1+exp(-f)));
    }
}
void calSf(long numOut)
{
    for(long i=0; i<numOut; i++)
    {
        matP[i][4]=matP[i][2]*(1-matP[i][2])*(matP[i][3]-matP[i][2]);
    }
}
void calSc(long numOut,long numHi)
{
    for(long i=0; i<numHi; i++)
    {
        //cout<<matP[i][1]<<endl;
        //cout<<1-matP[i][1]<<endl;
        //cout<<matW[numOut+numHi-1][i+1]<<endl;
        //cout<<matP[0][4]<<endl;
        double f=0;
        for(long j=0; j<numOut; j++)
        {
            f+=matP[j][2]*matW[j][i+numHi];

        }
        matP[i][5]=matP[i][1]*(1-matP[i][1])*(f);
        //cout<<matP[i][5]<<endl<<endl;
    }
}
void calW(long numOut,long numHi,long numIn,double landa)
{
    for(long i=0; i<numHi; i++)
    {
        for(long j=0; j<numIn+1; j++)
        {
            //cout<<matP[j][0]<<" ";
            matW[j][i]=matW[j][i]+(landa*matP[i][5]*matP[j][0]);

        }
        //cout<<matP[i][5]<<" //"<<endl;
    }
    for(long i=numHi; i<numHi+numOut; i++)
    {
        matW[i][0]=matW[i][0]+(landa*matP[0][4]*matP[0][0]);
        for(long j=1; j<numHi+1; j++)
        {
            matW[i][j]=matW[i][j]+(landa*matP[j][5]*matP[j][1]);
        }
    }
}

int main()
{
    double landa;
    long numIn,numHi,numOut,numEnt;
    cout<<"Datos de entrada a la red\n";
    //cin>>landa>>numIn>>numHi>>numOut;
    landa=0.01;
    numIn=1024;
    numHi=10;
    numOut=4;
    numEnt=1900;
    freopen("Entrenamiento.txt","r",stdin);
    long row=max(numHi,numOut);
    long col=max(numHi,numIn);
    double ran,sig;
    srand(time(NULL));
    for(long i=0; i<row; i++)
    {
        for(long j=0; j<col; j++)
        {
            ran=rand()%1000;
            sig=rand()%2;
            if(sig==0)
            {
                ran=ran/2000;
            }
            else
            {
                ran=ran/2000*-1;
            }
            matW[i][j]=ran;
        }
    }
    row=max( max(numHi,numIn),numOut);
    char data;
    int val;
    long cont=0;
    imprime(10,6);
    cout<<endl;
    while(numEnt--)
    {
        cin>>data;
        cont++;
        if(data== '1')val=1;
        else val=0;
        cachData(numIn,numOut,numHi,val);
        calOc(numHi,numIn);
        calOf(numHi,numOut);
        calSf(numOut);
        calSc(numOut,numHi);
        calW(numOut,numHi,numIn,landa);
    }
    imprime(10,6);
    //freopen("Prueba.txt","r",stdin);
    numEnt=2;
    cont=0;
    bool istrue;
    cout<<"pruebas"<<endl;
    while(cin>>data)
    {
        cont++;
        cout<<" cont"<<cont<<endl;
        if(data== 1)val=1;
        else val=0;
        cachData(numIn,numOut,numHi,val);
        calOc(numHi,numIn);
        calOf(numHi,numOut);
        istrue=true;
        for(int i=0; i<numOut; i++)
        {
            cout<<matP[i][2]<<endl;
            if(matP[i][2]<.5)matP[i][2]=0;
            else matP[i][2]=1;

            if( matP[i][2] != matP[i][3] )
            {
                istrue=false;
            }


        }
        if(istrue)
            cout<<matP[0][2]<<"resultado bueno\n";
        else
            cout<<matP[0][2]<<"resultado malo\n";
    }
    return 0;
}
