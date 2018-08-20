#include <iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#define MAX 100
using namespace std;

long matrizViajero[MAX][MAX],numPoblacion,numCiudades,matrizRutas[MAX][MAX+1];
double tasaMutacion,tasaCruza,fitness[MAX+1];

void DATOS()
{
    cout<<"Poblacion \nCruza \nMutacion\nCiudades\n";
    //cin>>poblacion>>cruza>>mutacion>>ciudades;
    numPoblacion=5;
    tasaCruza=.5;
    tasaMutacion=.5;
    numCiudades=10;
    for(int i=0;i<MAX;i++)
    {
        for(int j=0;j<MAX;j++)
        {
            cin>>matrizViajero[i][j];
        }
    }
}

void IMPRIME()
{
    for(int i=0;i<numCiudades;i++)
    {
        for(int j=0;j<numCiudades;j++)
        {
            cout<<matrizViajero[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"matriz viajero"<<endl;
}
void CREARUTAS()
{
    for(int i=0;i<numPoblacion;i++)
    {
        for(int j=1;j<numCiudades;j++)
        {
            matrizRutas[i][j]=j;
        }
        matrizRutas[i][0]=0;
        matrizRutas[i][numCiudades]=0;
    }
}

void IMPRIMERUTAS()
{
    for(int i=0;i<numPoblacion;i++)
    {
        for(int j=0;j<numCiudades+1;j++)
        {
            cout<<matrizRutas[i][j]<<" ";
        }
       cout<<endl;
    }
    cout<<"matriz rutas"<<endl;
}
void FITNESS()
{
    for(int i=0;i<numPoblacion;i++)
    {
        fitness[i]=0;
        for(int j=0;j<numCiudades;j++)
        {
            fitness[i]+=matrizViajero[matrizRutas[i][j]][matrizRutas[i][j+1]];
        }
    }
}


void CRUZA()
{
    long cruzados=trunc(tasaCruza*numPoblacion),bloque;
    long matrizCRUZA[cruzados*2][numCiudades+1],inicioBloc=0,finBloc=0;
    for(int i=0;i<cruzados*2;i++)
    {
        for(int j=0;j<numCiudades+1;j++)
        {
            matrizCRUZA[i][j]=0;
        }
    }
    if((numCiudades+1) %2 == 0)             //calculamos el bloque para las ciudades pares
    {
        bloque=2*(((numCiudades+1)/2)-3);
        if(bloque<1)
        {
            bloque=0;
        }
        else
        {
            inicioBloc=((numCiudades-1)/2)-((bloque/2)-1);
            finBloc=inicioBloc+bloque-1;
        }
    }
    else                                    //calculamos el bloque para las ciudades inpares
    {
        bloque=((((numCiudades)/2)-4)*2)+3;
        if(bloque<1)
        {
            bloque=0;
        }
        else
        {
            inicioBloc=(numCiudades/2)-trunc(bloque/2);
            finBloc=inicioBloc+bloque-1;
        }
    }
    for(int j=0;j<cruzados;j++)             //Colocamos la ciudad de salida y regreso
    {
        matrizCRUZA[j][0]=0;
        matrizCRUZA[j][numCiudades]=0;
    }
    long casos=cruzados,primerCruzado,segundoCruzado,cruzadoAnt=0,cruzadoPos=cruzados*2-1;
    double minimoValor;
    int existeSeg,existePri;
    while(casos--)
    {
        minimoValor=100;
        for(int j=0;j<numPoblacion;j++)    //calculamos el mejor fitness a cruzar
        {
            if(fitness[j]<minimoValor && fitness[j] != -1)
            {
                primerCruzado=j;
            }
        }
        fitness[primerCruzado]=-1;
        minimoValor=100;
        for(int j=0;j<numPoblacion;j++)   //calculamos el mejor segundo fitness a cruzar
        {
            if(fitness[j]<minimoValor && fitness[j] != -1)
            {
                segundoCruzado=j;
            }
        }
        fitness[segundoCruzado]=-1;
        for(int j=inicioBloc;j<finBloc+1;j++)   //colocamos los valores de cruza del bloque en el primercruzado y en el segundocruzado
        {
            matrizCRUZA[cruzadoAnt][j]=matrizRutas[primerCruzado][j];
            matrizCRUZA[cruzadoPos][j]=matrizRutas[segundoCruzado][j];
        }
        for(int j=1;j<inicioBloc;j++)   //colocamos los valores de cruza antes del bloque en el primercruzado y en el segundocruzado
        {
            existeSeg=0;
            existePri=0;
            for(int i=0;i<numCiudades+1;i++)    //buscamos el valor en la matriz
            {
                if(matrizRutas[segundoCruzado][j] == matrizCRUZA[cruzadoAnt][i])
                {
                    existeSeg=1;
                }
                if(matrizRutas[primerCruzado][j] == matrizCRUZA[cruzadoPos][i])
                {
                    existePri=1;
                }

            }
            if(!existeSeg)                      //si no existe guardamos el valor si existe ponemos -1 en el cruzado Ant
            {
                matrizCRUZA[cruzadoAnt][j]=matrizRutas[segundoCruzado][j];
            }
            else
            {
                matrizCRUZA[cruzadoAnt][j]=-1;
            }
            if(!existePri)                      //si no existe guardamos el valor si existe ponemos -1 en el cruzadopos
            {
               matrizCRUZA[cruzadoPos][j]=matrizRutas[primerCruzado][j];
            }
            else
            {
                matrizCRUZA[cruzadoPos][j]=-1;
            }
        }
        for(int j=finBloc+1;j<numCiudades;j++)   //colocamos los valores de cruza despues del bloque en el primercruzado y en el segundocruzado
        {
            existeSeg=0;
            existePri=0;
            for(int i=0;i<numCiudades+1;i++)    //buscamos el valor en la matriz
            {
                if(matrizRutas[segundoCruzado][j] == matrizCRUZA[cruzadoAnt][i])
                {
                    existeSeg=1;
                }
                if(matrizRutas[primerCruzado][j] == matrizCRUZA[cruzadoPos][i])
                {
                    existePri=1;
                }

            }
            if(!existeSeg)                      //si no existe guardamos el valor si existe ponemos -1 en el cruzado Ant
            {
                matrizCRUZA[cruzadoAnt][j]=matrizRutas[segundoCruzado][j];
            }
            else
            {
                matrizCRUZA[cruzadoAnt][j]=-1;
            }
            if(!existePri)                      //si no existe guardamos el valor si existe ponemos -1 en el cruzadopos
            {
               matrizCRUZA[cruzadoPos][j]=matrizRutas[primerCruzado][j];
            }
            else
            {
                matrizCRUZA[cruzadoPos][j]=-1;
            }

        }
        long identifica;
        for(int i=0;i<cruzados*2;i++)           //buscamos y remplamazamos los valores repetidos que estan como -1
        {
            for(int j=0;j<numCiudades+1;j++)
            {
                if(matrizCRUZA[i][j]==-1)
                {
                    identifica=0;
                    for(int u=0;u<numCiudades+1;u++)
                    {
                        if(matrizCRUZA[i][u]== identifica)
                        {
                            u=0;
                            identifica++;
                        }
                    }
                    matrizCRUZA[i][j]=identifica;

                }
            }
        }
        cruzadoAnt++;
        cruzadoPos--;
    }
    double fitnessCruza[cruzados*2];
    for(int i=0;i<cruzados*2;i++)           //calculamos el fitnees de la matrizCruza
    {
        fitnessCruza[i]=0;
        for(int j=0;j<numCiudades;j++)
        {
            fitnessCruza[i]+=matrizViajero[matrizCRUZA[i][j]][matrizCRUZA[i][j+1]];
        }
    }
    long auxiliar;
    FITNESS();
    for(int i=0;i<cruzados*2;i++)
    {
        for(int j=0;j<numPoblacion;j++)
        {
            if(fitnessCruza[i]<fitness[j])
            {
                for(int u=0;u<numCiudades;u++)
                {
                    auxiliar=matrizRutas[j][u];
                    matrizRutas[j][u]=matrizCRUZA[i][u];
                    matrizCRUZA[i][u]=auxiliar;
                }
                auxiliar=fitness[j];
                fitness[j]=fitnessCruza[i];
                fitnessCruza[i]=auxiliar;
            }
        }
    }
}

void MUTACION()
{
    long mutados=tasaMutacion*numPoblacion,azarPob,azarCiu1,azarCiu2,auxiliar;
    while(mutados --)
    {
        azarPob=(rand()%numPoblacion);
        azarCiu1=(rand()%(numCiudades-1))+1;
        azarCiu2=(rand()%(numCiudades-1))+1;
        auxiliar=matrizRutas[azarPob][azarCiu1];
        matrizRutas[azarPob][azarCiu1]=matrizRutas[azarPob][azarCiu2];
        matrizRutas[azarPob][azarCiu2]=auxiliar;
    }
}

int main()
{
    long val=1,mejorRuta[numCiudades+1]={0},i;
    double minimo;
    int posicion;
    srand(time(NULL));
    minimo=1000;
    freopen("input.txt","r",stdin);
    DATOS();
    IMPRIME();
    CREARUTAS();
    FITNESS();
    posicion=-1;
    while(val!= 200)
    {
        FITNESS();
        CRUZA();
        MUTACION();
        FITNESS();
        for(i=0;i<numPoblacion;i++)
        {
            if(minimo>fitness[i])
            {
                minimo=fitness[i];
                posicion=i;
                val=0;
            }
        }
        if(val == 0)
        {
            for(int i=0;i<numCiudades+1;i++)
            {
                mejorRuta[i]=matrizRutas[posicion][i];

            }
        }
        val++;
    }
    if(posicion==-1)
    {
        cout<<"no hay mejor ruta\n";
    }
    else
    {
        cout<<"La mejor ruta es de "<<minimo<<" costos y la ruta es \n ";
        IMPRIMERUTAS();
    }
    return 0;
}
