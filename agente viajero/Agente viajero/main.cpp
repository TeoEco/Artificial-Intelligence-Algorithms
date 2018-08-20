#include <iostream>
#include <time.h>
#include<stdlib.h>
#include<stdio.h>
#define MAX 100
using namespace std;

double cruza,mutacion,matrizViajero[MAX][MAX],fitness[MAX];
long poblacion,matrizRutas[MAX][MAX],ciudades;

void LEERDATOS()
{
    cout<<"Poblacion \nCruza \nMutacion\nCiudades\n";
    //cin>>poblacion>>cruza>>mutacion>>ciudades;
    poblacion=5;
    cruza=.5;
    mutacion=.5;
    ciudades=10;
}

void LLENARMATRIZ()
{
    double azar;
    freopen("output.txt","w",stdout);
    for(int i= 0;i<MAX;i++)
    {
        for(int j=0;j<MAX;j++)
        {
            if(i!=j)
            {
                azar=rand()%10;
                azar/=1;
                matrizViajero[i][j]=azar+1;
            }
            else
            {
                matrizViajero[i][j]=0;
            }
            cout<<matrizViajero[i][j]<<" ";
        }
    }
    cout<<"listo\n\n\n\n\n";


}

void MUTACION()
{
    int muta=mutacion*poblacion;
    long azar,azarMuta,auxiliar,azarMuta2;
    for(int i=0;i<muta;i++)
    {
        azar=rand()%poblacion;
        azarMuta=rand()%(ciudades-1);
        azarMuta2=rand()%(ciudades-1);
        auxiliar=matrizRutas[azar][azarMuta+1];
        matrizRutas[azar][azarMuta+1]=matrizRutas[azar][azarMuta2+1];
        matrizRutas[azar][azarMuta2+1]=auxiliar;
    }
}

void FITNESS()
{
    long auxiliar1,auxiliar2;
    for(int i=0;i<poblacion;i++)
    {
        fitness[i]=0;
    }
    for(int i=0;i<ciudades;i++)
    {
        for(int j=0;j<poblacion;j++)
        {
            fitness[j]+=matrizViajero[matrizRutas[j][i]][matrizRutas[j][i+1]];
        }
    }
}

void CRUZA()
{
    long cruz=cruza*poblacion,azarInicio,azarFin,azarPobla1,azarPobla2,valorCd;
    long matrizCruz[cruz*2][ciudades+1],matrizAux[2][ciudades+1];
    double minimo=fitness[0]*5,fitnessCruz[cruz*2];
    int esta=0;
    for(int v=0;v<cruz*2;v++)
        {
            for(int w=0;w<(ciudades+1);w++)
            {
                matrizCruz[v][w]=0;
            }
        }
    for(int i=0;i<cruz;i++)
    {
        minimo=fitness[0]*5;
        for(int y=0;y<poblacion;y++)
        {
            if(fitness[y]<minimo)
            {
                minimo=fitness[y];
                azarPobla1=y;
            }
        }
        fitness[azarPobla1]=100*ciudades;
        minimo=fitness[0]*5;
        for(int y=0;y<poblacion;y++)
        {
            if(fitness[y]<minimo && azarPobla1!=y)
            {
                minimo=fitness[y];
                azarPobla2=y;
            }
        }
        fitness[azarPobla2]=100*ciudades;
        azarInicio=rand()%(ciudades/2);
        azarInicio++;
        azarFin=(azarInicio+(ciudades/2));
        for(int j=azarInicio;j<=azarFin;j++)
        {
            matrizCruz[i][j]=matrizRutas[azarPobla1][j];
            matrizCruz[(cruz*2)-i-1][j]=matrizRutas[azarPobla2][j];
        }
        for(int j=1;j<azarInicio;j++)
        {
            valorCd=matrizRutas[azarPobla1][j];
            esta=0;
            for(int w=1;w<ciudades;w++)
            {
                if(valorCd==matrizCruz[(cruz*2)-i-1][w])
                {
                    esta=10;
                    break;
                }
            }
            if(esta == 0)
            {
                matrizCruz[(cruz*2)-i-1][j]=valorCd;
            }
            else
            {
                matrizCruz[(cruz*2)-i-1][j]=-1;
            }
            valorCd=matrizRutas[azarPobla2][j];
            esta=0;
            for(int w=1;w<ciudades;w++)
            {
                if(valorCd==matrizCruz[i][w])
                {
                    esta=10;
                    break;
                }
            }
            if(esta==0)
            {
                matrizCruz[i][j]=valorCd;
            }
            else
            {
                matrizCruz[i][j]=-1;
            }

        }
        for(int j=azarFin+1;j<ciudades;j++)
        {
            valorCd=matrizRutas[azarPobla1][j];
            esta=0;
            for(int w=1;w<ciudades;w++)
            {
                if(valorCd==matrizCruz[(cruz*2)-i-1][w])
                {
                    esta=10;
                    break;
                }
            }
            if(esta==0)
            {
                matrizCruz[(cruz*2)-i-1][j]=valorCd;
            }
            else
            {
                matrizCruz[(cruz*2)-i-1][j]=-1;
            }
            valorCd=matrizRutas[azarPobla2][j];
            esta=0;
            for(int w=1;w<ciudades;w++)
            {
                if(valorCd==matrizCruz[i][w])
                {
                    esta=10;
                    break;
                }
            }
            if(esta==0)
            {
                matrizCruz[i][j]=valorCd;
            }
            else
            {
                matrizCruz[i][j]=-1;
            }

        }
        cout<<"check matriz-1 "<<endl;
        for(int y=0;y<cruz*2;y++)
        {
            for(int j=0;j<ciudades+1;j++)
            {
                cout<<matrizCruz[y][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<endl;
        for(int j=1;j<ciudades;j++)
        {
            if(matrizCruz[i][j]==-1)
            {
                for(int y=1;y<ciudades;y++)
                {
                    if(matrizCruz[i][j]!= matrizRutas[azarPobla1][y])
                    {
                        matrizCruz[i][j]!= matrizRutas[azarPobla1][j];
                    }
                }
            }
            if(matrizCruz[(cruz*2)-i-1][j]==-1)
            {
                for(int y=1;y<ciudades;y++)
                {
                    if(matrizCruz[(cruz*2)-i-1][j]!= matrizRutas[azarPobla1][y])
                    {
                        matrizCruz[(cruz*2)-i-1][j]=matrizRutas[azarPobla2][j];
                    }
                }
            }

        }
        cout<<"check matriz-2 "<<endl;
        for(int y=0;y<cruz*2;y++)
        {
            for(int j=0;j<ciudades+1;j++)
            {
                cout<<matrizCruz[y][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<endl;
    }
    long auxiliar1,auxiliar2;
    for(int i=0;i<cruz*2;i++)
    {
        fitnessCruz[i]=0;
    }
    for(int i=0;i<ciudades;i++)
    {
        for(int j=0;j<cruz*2;j++)
        {
            fitnessCruz[j]+=matrizViajero[matrizCruz[j][i]][matrizCruz[j][i+1]];
        }
    }
    FITNESS();
    for(int i=0;i<poblacion;i++)
    {
        for(int j=0;j<cruz*2;j++)
        {
            if(fitness[i]>fitnessCruz[j])
            {
                for(int v=0;v<ciudades+1;v++)
                {
                    matrizAux[0][v]=matrizRutas[i][v];
                    matrizRutas[i][v]=matrizCruz[j][v];
                    matrizCruz[j][v]=matrizAux[0][v];
                }
            }
        }
    }
}

void CREAPOBLACION()
{
    for(int i = 0; i<poblacion;i++)
    {
        for(int j=0;j<ciudades+1;j++)
        {
            matrizRutas[i][j]=j;
        }
        matrizRutas[i][ciudades]=0;
    }
}

void IMPRIMEMATRIZ()
{
    for(int i=0;i<poblacion;i++)
    {
        for(int j=0;j<ciudades+1;j++)
        {
            cout<<matrizRutas[i][j]<<" ";
        }
        cout<<"\n";
    }
    for(int i=0;i<poblacion;i++)
    {
        cout<<fitness[i]<<endl;
    }
}

int main()
{
    double azar,minimo;
    long auxiliar,bestRute[ciudades+1];
    srand(time(NULL));
    LEERDATOS();
    LLENARMATRIZ();
    CREAPOBLACION();
    int i=0;
    FITNESS();
    //IMPRIMEMATRIZ();
    minimo=fitness[0]*poblacion;
    i=10;
    while(i--)
    {
       FITNESS();
       //cout<<"cruza"<<endl;
       CRUZA();
       //IMPRIMEMATRIZ();
       MUTACION();
       FITNESS();
       //IMPRIMEMATRIZ();
       for(int j=0;j<poblacion;j++)
       {
           if(fitness[j]<minimo)
           {
               minimo=fitness[j];
               for(int v=0;v<ciudades+1;v++)
               {
                   bestRute[v]=matrizRutas[j][v];
               }
               //i=0;
           }
       }
       //i++;
    }
    //IMPRIMEMATRIZ();
    cout << "la mejor ruta con un valor de " <<minimo<< endl;
    for(int i=0;i<ciudades;i++)
    {
        cout<<bestRute[i]<<" a "<<bestRute[i+1]<<" - "<<matrizViajero[bestRute[i]][bestRute[i+1]]<<endl;
    }
    return 0;
}
