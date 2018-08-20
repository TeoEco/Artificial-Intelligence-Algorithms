/*Juan alberto gutierrez canto
  version 1.6
  */
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#define PI 3.14159265
int opcion,N,i,rangex=0,rangey=0,nx,ny,azarp,numiteraciones=0;
float infx,infy,supx,supy,R,M,n,maximofitness=0,valorencontrado=0,auxx,auxy,finx,finy;

void menu()     //menu para pedir datos
{
    int valido=0;
    while(valido != 1) //validacion para que solamente ingrese uno de las tres opciones posibles
    {
        cout<<"Introduce el numero de la funcion que deceas probar"<<endl;
        cout<<"1) f(x,y)=21.5+x*sin(4*pi*x)+y*sin(20*pi*y)"<<endl;
        cout<<"2) f(x,y)=(1+x)^2 * e^(-x^2 -(y+1)^2) -(x-x^3 -y^3) e^(-x^2 -y^2)"<<endl;
        cout<<"3) f(x,y)=[16*x*(1-x)*y*(1-y)*sin(n*pi*x)*sin(n*pi*y)]^2"<<endl;
        cin>>opcion;
        if(opcion < 4 && opcion > 0)
            valido++;
    }
    cout<<"Introduce el rango para x inferios - superior"<<endl;
    cin>>infx>>supx;
    cout<<"Introduce el rango para y inferios - superior"<<endl;
    cin>>infy>>supy;
    //cout<<"Introduce numero de poblacion"<<endl;
    //cin>>N;
    N=20;
    //cout<<"Introduce fraccion de poblacion para cruza"<<endl;
    //cin>>R;
    R=.8;
    cout<<"Introduce tasa de mutacion"<<endl;
    cin>>M;
    //cout<<"Introduce el numero de iteraciones"<<endl;
    // cin>>numiteraciones;
    numiteraciones=2000;
}

void rango()    //generamos rango para crear tamaño de la poblacion
{
    for(i=infx;i<supx;i++)
        rangex++;
    for(i=infy;i<supy;i++)
        rangey++;
    nx=log2((rangex * pow(10,6))+1)+1;
    ny=log2((rangey * pow(10,6))+1)+1;
}

int main()
{
    freopen("input.txt","r",stdin);
    menu();
    freopen ( "miarchivo.txt" , "w" , stdout);
    rangex=0;
    rangey=0;
    rango();
    int poblacion[N][nx+ny],j,x,w;
    float ruleta[N][4];
    srand(time(NULL));
    for(i=0;i<N;i++)        //llenamos poblacion con valores aleatorios 1 y 0
    {
        for(j=0;j<nx+ny;j++)
        {
            azarp=rand()%2;
            poblacion[i][j]=azarp;
        }
    }
    for(w=0;w<numiteraciones;w++)   //realizamos algoritmo genetico para encontrar el mejor valor
    {
        maximofitness=0;
        for(j=0;j<N;j++)    //encontramos valores de x en la poblacion y guardamos en la fila 0 de ruleta
        {
            x=0;
            for(i=0;i<nx;i++)
            {
                x+=poblacion[j][i]*exp2(i);
            }
            ruleta[j][0]= infx+(x*((supx-infx)/(pow(2,nx)-1)));
        }
        for(j=0;j<N;j++)    //encontramos valores de y en la poblacion y guardamos en la fila 1 de ruleta
        {
            x=0;
            for(i=nx;i<nx+ny;i++)
            {
                x+=poblacion[j][i]*exp2(i-nx);
            }
            ruleta[j][1]=infy+(x*((supy-infy)/(pow(2,ny)-1)));
        }
        switch(opcion)      //metemoa valores de x & y a la formula seleccionada para encoantrar el numero de fitnees y guardarlos en la fila 2 de ruleta
        {
            case 1:
                {
                    for(i=0;i<N;i++)
                    {
                        ruleta[i][2]=(21.5 + (ruleta[i][0]*sin(4*PI*ruleta[i][0])) + ruleta[i][1]* sin(20 * PI * ruleta[i][1]));
                    }
                    break;
                }
            case 2:
                {
                    for(i=0;i<N;i++)
                    {
                        ruleta[i][2]=pow((1-ruleta[i][0]),2) * (exp(-pow(ruleta[i][0],2)-pow(ruleta[i][1]+1,2))) - ((ruleta[i][0] - pow(ruleta[i][0],3) - pow(ruleta[i][1],3)) * (exp(-(pow(ruleta[i][0],2)-(pow(ruleta[i][1],2)) ))));
                    }
                    break;
                }
            case 3:
                {
                    for(i=0;i<N;i++)
                    {
                        ruleta[i][2]=pow(16*ruleta[i][0]*(1-ruleta[i][0])*ruleta[i][1]*(1-ruleta[i][1])* sin(N*PI*ruleta[i][0]) * sin(N*PI*ruleta[i][1]),2);
                    }
                    break;
                }
            default :
                {
                    cout<<"La ecuacion no se encontro"<<endl;
                    break;
                }
        }
        float auxiliar=0,azarf,valormax;
        int poblacionmod[N][nx+ny],seleccion,crossover,contpob=0,u;
        for(i=0;i<N;i++)    //encontramos el maximo valor para desde ahi hacer nuestra ruleta
        {
            auxiliar=auxiliar+ruleta[i][2];
        }
        valormax=auxiliar;
        auxiliar=0;
        for(i=0;i<N;i++)    //creamos ruleta en la fila 3 de la varibla ruleta
        {
           auxiliar+=ruleta[i][2]*1/valormax;
           ruleta[i][3]=auxiliar;
        }
        printf ( "%f\n",valormax/N);
        crossover=trunc((R*N)/2);
        seleccion=N-(crossover*2);
        contpob=0;
        for(i=0;i<seleccion;i++)           //seleccionamos elementos de la ruleta que pasaran al azar
        {
            azarf=rand()%1000;
            azarf=azarf/1000;
            for(j=0;j<N;j++)
            {
                if(ruleta[j][3]>azarf)
                {
                    for(u=0;u<nx+ny;u++)
                    {
                        poblacionmod[contpob][u]=poblacion[j][u];
                    }
                    contpob++;
                    break;
                }
            }
        }
        maximofitness=0;
        for(j=0;j<crossover;j++)        //seleccionamos los mejores elementos para cruzar
        {
            valormax=0;
            int pos=0,posant=0;
            for(i=0;i<N;i++)            //encontramamos el mejor candidato
            {
                if(ruleta[i][2]>valormax)
                {
                    valormax=ruleta[i][2];
                    pos=i;
                }
            }
            if(maximofitness <valormax )
            {
                maximofitness=valormax;
                auxx=ruleta[pos][0];
                auxy=ruleta[pos][1];
            }
            ruleta[pos][2]=0;
            valormax=0;
            for(i=0;i<N;i++)
            {
                if(ruleta[i][2]>valormax)
                {
                    valormax=ruleta[i][2];
                    posant=i;
                }
            }

            ruleta[posant][2]=0;
            azarp=rand()%nx+ny;
            for(i=0;i<azarp;i++)
            {
                poblacionmod[contpob][i]=poblacion[pos][i];
                poblacionmod[contpob+1][i]=poblacion[posant][i];
            }
            for(i=azarp;i<nx+ny;i++)
            {
                poblacionmod[contpob][i]=poblacion[posant][i];
                poblacionmod[contpob+1][i]=poblacion[pos][i];
            }
            //cout<<"contador poblacion "<<contpob<<endl;
            contpob+=2;
        }
        for(i=0;i<N;i++)                //funcion que imprime la poblacion
        {
            for(j=0;j<nx+ny;j++)
            {
                //cout<<poblacionmod[i][j]<<" ";
            }
            //cout<<endl;
        }
        int mutacion,azarm;
        mutacion=ceil(M*N);
        for(i=0;i<mutacion;i++)         //mutacion en los elementos de la poblacion ya establecidos
        {
            azarp=rand()%6;
            azarm=rand()%nx+ny;
            if(poblacionmod[azarp][azarm]==0)
                poblacionmod[azarp][azarm]=1;
            else
                poblacionmod[azarp][azarm]=0;
        }
        for(i=0;i<N;i++)                //guardamos la nueva poblacion
        {
            for(j=0;j<nx+ny;j++)
            {
                poblacion[i][j]=poblacionmod[i][j];
            }
        }
        if(valorencontrado<maximofitness)   //guardamos el maximo valor encontrado por iteracion asi como su respectiva x & y
        {
            valorencontrado=maximofitness;
            finx=auxx;
            finy=auxy;
        }
    }
    cout<<"maximo valor encontrado "<<valorencontrado<<endl<<"para x:"<<finx<<" y:"<<finy<<endl;
    fclose (stdout);
    return 0;
}
