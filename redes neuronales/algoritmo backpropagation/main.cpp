#include <iostream>
#include <string.h>
#include<stdio.h>
#include<cstdlib>
#include<time.h>
#include<math.h>
#define MAX 10000
using namespace std;
double matP[MAX][MAX]={0};
double matW[MAX][MAX]={0};

void cachNewdata(long numIn)
{
    for(long i=1;i<=numIn;i++)
    {
        cin>>matP[i][0];
    }
}

void cachData(long numIn,long numOut,long numHi)
{
    double ran;
    srand(time(0));
    int sig;
    cout<<"Entrada - Salida\n";
    matP[0][0]=-1;
    for(long i=1;i<=numIn;i++)
    {
        cin>>matP[i][0];
    }
    for(long i=0;i<numOut;i++)
    {
        cin>>matP[i][3];
    }
    long row=max(numHi,numOut);
    long col=max(numHi,numIn);
    /*for(long i=0;i<row;i++)
    {
        for(long j=0;j<col;j++)
        {
            ran=rand()%1000;
            sig=rand()%2;
            if(sig==0)
            {
                ran=ran/20000;
            }
            else
            {
                ran=ran/20000*-1;
            }
            matW[i][j];
        }
    }*/

}

void imprime(long row,long col)
{
    for(long i=0;i<=row;i++)
    {
        for(long j=0;j<col;j++)
        {
            cout<<matP[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
    for(long i=0;i<3;i++)
    {
        for(long j=0;j<3;j++)
        {
            cout<<matW[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void calOc(long numHi,long numIn)
{
    for(long i=0;i<numHi;i++)
    {
        double f=0;
        for(long j=0;j<numIn;j++)
        {
            f+=matP[j][0]*matW[i][j];
        }
        matP[i][1]=(1/(1+exp(-f)));
    }
}
void calOf(long numHi,long numOut)
{
    for(long i=0;i<numOut;i++)
    {
        double f=matP[0][0]*matW[i+numHi][0];
        for(long j=0;j<numHi;j++)
        {
            f+=matP[j][1]*matW[i+numHi][j+1];
        }
        matP[i][2]=(1/(1+exp(-f)));
    }
}
void calSf(long numOut)
{
    for(long i=0;i<numOut;i++)
    {
        matP[i][4]=matP[i][2]*(1-matP[i][2])*(matP[i][3]-matP[i][2]);
    }
}
void calSc(long numOut,long numHi)
{
    for(long i=0;i<numHi;i++)
    {
        matP[i][5]=matP[i][1]*(1-matP[i][1])*(matW[numOut+numHi-1][i+1]*matP[0][4]);
    }
}
void calW(long numOut,long numHi,long numIn,double landa)
{
    for(long i=0;i<numHi;i++)
    {
        for(long j=0;j<numIn+1;j++)
        {
            matW[i][j]=matW[i][j]+(landa*matP[i][5]*matP[i][0]);
        }
    }
    for(long i=numHi;i<numHi+numOut;i++)
    {
        matW[i][0]=matW[i][0]+(landa*matP[0][4]*matP[0][0]);
        for(long j=1;j<numHi+1;j++)
        {
            matW[i][j]=matW[i][j]+(landa*matP[0][4]*matP[i-numHi][5]);
        }
    }
}

int main()
{
    double landa;
    long numIn,numHi,numOut,numEnt;
    matW[0][0]=0.8;
    matW[0][1]=0.5;
    matW[0][2]=0.4;
    matW[1][0]=-0.1;
    matW[1][1]=0.9;
    matW[1][2]=1;
    matW[2][0]=0.3;
    matW[2][1]=-1.2;
    matW[2][2]=1.1;
    //freopen("input.txt","r",stdin);
    cout<<"Datos de entrada a la red\n";
    cin>>landa>>numIn>>numHi>>numOut>>numEnt;
    long row=max( max(numHi,numIn),numOut);
    while(numEnt--)
    {
        cout<<numEnt<<endl;
        cachData(numIn,numOut,numHi);
        calOc(numHi,numIn);
        calOf(numHi,numOut);
        calSf(numOut);
        calSc(numOut,numHi);
        calW(numOut,numHi,numIn,landa);
    }
    imprime(row,6);
    //freopen("out.txt","w",stdout);
    numEnt=10;
    while(numEnt--)
    {
        cout<<"introduce tu operacion\n";
        cachNewdata(numIn);
        calOc(numHi,numIn);
        calOf(numHi,numOut);
        if(matP[0][2] < 0.5)
            cout<<matP[0][2]<<"resultado 1\n";
        else
            cout<<matP[0][2]<<"resultado 0\n";
    }
    return 0;
}
