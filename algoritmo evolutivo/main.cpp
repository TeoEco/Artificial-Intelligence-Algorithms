#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define PI 3.14159265
using namespace std;
float m,r,inf_x,inf_y,sup_x,sup_y,valfinal=0,valfinalx,valfinaly;
int tam_pob,opcion,N,landa;
void menu()
{
    int valido=0;
    while(valido != 1) //validacion para que solamente ingrese uno de las tres opciones posibles
    {
        cout<<"Introduce el numero de la funcion que deceas probar"<<endl;
        cout<<"1) f(x,y)=21.5+x*sin(4*pi*x)+y*sin(20*pi*y)"<<endl;
        cout<<"2) f(x,y)=(1+x)^2 * e^(-x^2 -(y+1)^2) -(x-x^3 -y^3) e^(-x^2 -y^2)"<<endl;
        cout<<"3) f(x,y)=[16*x*(1-x)*y*(1-y)*sin(n*pi*x)*sin(n*pi*y)]^2"<<endl;
        cin>>opcion;
        if(opcion == 3)
        {
            cout<<"dame valor de n"<<endl;
            cin >>N;
        }
        if(opcion < 4 && opcion > 0)
            valido++;
    }
    cout<<"INTRODUCE EL TAMAÑO DE LA POBLACION\n";
    //cin>>tam_pob;
    tam_pob=10;
    cout<<"INTRODUCE EL NUMERO DE INDIVIDUOS NUEVOS POR CRUZA Y MUTACION\n";
    //cin>>landa;
    landa=3;
    cout<<"INTRODUCE EL PORCENTAJE DE POBLACION PARA CRUZA\n";
    //cin>>r;
    r=0.4;
    cout<<"INTRODUCE EL PORCENTAJE DE POBLACION PARA MUTACION\n";
    //cin>>m;
    m=0.6;
    cout<<"INTRODUCE LOS LIMITES DE X\n";
    //cin>>inf_x>>sup_x;
    inf_x=0;
    sup_x=1;
    cout<<"INTRODUCE LOS LIMITES DE Y\n";
    //cin>>inf_y>>sup_y;
    inf_y=0;
    sup_y=1;
}

int main()
{
    menu();
    float poblacion[tam_pob][3],azar,rango_x=0,rango_y=0,azarc,pob_landa[landa][3],z1,z2;
    int i,pares_cruza,mutacion;
    srand(time(NULL));
    for(float j=inf_x;j<sup_x-.1;j+=.1)rango_x+=.1;
    for(float j=inf_y;j<sup_y-.1;j+=.1)rango_y+=.1;
    //cout<<"RANGOS x "<<rango_x<<" y "<<rango_y<<endl;
    for(i=0;i<tam_pob;i++)
    {
        azar=rand()% int(1000*rango_x);
        poblacion[i][0]=inf_x+(azar/1000);
        azar=rand()% int(1000*rango_y);
        poblacion[i][1]=inf_y+(azar/1000);
        //cout<<"pob x "<<poblacion[i][0]<<" y "<<poblacion[i][1]<<endl;
    }
    switch(opcion)      //metemoa valores de x & y a la formula seleccionada para encoantrar el numero de fitnees y guardarlos en la fila 2 de ruleta
        {
            case 1:
                {
                    for(i=0;i<tam_pob;i++)
                    {
                        poblacion[i][2]=(21.5 + (poblacion[i][0]*sin(4*PI*poblacion[i][0])) + poblacion[i][1]* sin(20 * PI * poblacion[i][1]));
          //              cout<<"fit "<<poblacion[i][2]<<endl;
                    }
                    break;
                }
            case 2:
                {
                    for(i=0;i<tam_pob;i++)
                    {
                        poblacion[i][2]=pow((1-poblacion[i][0]),2) * (exp(-pow(poblacion[i][0],2)-pow(poblacion[i][1]+1,2))) - ((poblacion[i][0] - pow(poblacion[i][0],3) - pow(poblacion[i][1],3)) * (exp(-(pow(poblacion[i][0],2)-(pow(poblacion[i][1],2)) ))));
            //            cout<<"fit "<<poblacion[i][2]<<endl;
                    }
                    break;
                }
            case 3:
                {
                    for(i=0;i<tam_pob;i++)
                    {
                        poblacion[i][2]=(16*poblacion[i][0]*(1-poblacion[i][0])*poblacion[i][1]*(1-poblacion[i][1])* sin(N*PI*poblacion[i][0]) * sin(N*PI*poblacion[i][1]))*(16*poblacion[i][0]*(1-poblacion[i][0])*poblacion[i][1]*(1-poblacion[i][1])* sin(N*PI*poblacion[i][0]) * sin(N*PI*poblacion[i][1]));
              //          cout<<"fit "<<poblacion[i][2]<<endl;
                    }
                    break;
                }
            default :
                {
                //    cout<<"La ecuacion no se encontro"<<endl;
                    break;
                }
        }
        freopen ( "miarchivo.txt" , "w" , stdout);
    int iteraciones=0;
    while(iteraciones != 100)
    {
        mutacion=round(landa*r);
        pares_cruza=round(landa*m);
        //cout<<"mutacion "<<mutacion<<" cruza "<<pares_cruza<<endl;
        int landa_cont=landa;
        landa=0;
        //cout<<"landas "<<landa<<" da "<<landa_cont<<endl;
        for(i=0;i<pares_cruza;i++)
        {
            azar=rand()%(tam_pob);
            azarc=rand()%(tam_pob);
            pob_landa[landa][0]=(poblacion[int(azar)][0]+poblacion[int(azarc)][0])/2;
          //  cout<<"cruz x "<<pob_landa[landa][0]<<" = "<<poblacion[int(azar)][0]<<" + "<<poblacion[int(azarc)][0]<<endl;
            pob_landa[landa][1]=(poblacion[int(azar)][1]+poblacion[int(azarc)][1])/2;
            //cout<<"cruz y "<<pob_landa[landa][1]<<" = "<<poblacion[int(azar)][1]<<" + "<<poblacion[int(azarc)][1]<<endl;
            landa++;
        }
        for(i=0;i<mutacion;i++)
        {
            azar=rand()%10;
            z1=azar/10;
            azar=rand()%10;
            z2=azar/10;
            azar=rand()%(tam_pob);
            //cout<<"z1 "<<z1<<" z2 "<<z2<<endl<<"azar "<<azar<<endl;
            pob_landa[landa][0]=poblacion[int(azar)][0]+(sqrt(-2*log(z1)) * cos(2*PI*z2));
           // cout<<"muta x "<<pob_landa[landa][0]<<endl<<(sqrt(-2*log(z1)) * cos(2*PI*z2))<<endl;
            pob_landa[landa][1]=poblacion[int(azar)][1]+(sqrt(-2*log(z1)) * sin(2*PI*z2));
           // cout<<"muta y "<<pob_landa[landa][1]<<endl<<(sqrt(-2*log(z1)) * sin(2*PI*z2))<<endl;
            landa++;

       //     cout<<"landas "<<landa<<" da "<<landa_cont<<endl;
        }
        switch(opcion)      //metemoa valores de x & y a la formula seleccionada para encoantrar el numero de fitnees y guardarlos en la fila 2 de ruleta
        {
            case 1:
                {
                    for(i=0;i<landa_cont;i++)
                    {
                        pob_landa[i][2]=(21.5 + (pob_landa[i][0]*sin(4*PI*pob_landa[i][0])) + pob_landa[i][1]* sin(20 * PI * pob_landa[i][1]));
         //               cout<<"fitlanda "<<pob_landa[i][2]<<endl;
                    }
                    break;
                }
            case 2:
                {
                    for(i=0;i<landa;i++)
                    {
                        pob_landa[i][2]=pow((1-pob_landa[i][0]),2) * (exp(-pow(pob_landa[i][0],2)-pow(pob_landa[i][1]+1,2))) - ((pob_landa[i][0] - pow(pob_landa[i][0],3) - pow(pob_landa[i][1],3)) * (exp(-(pow(pob_landa[i][0],2)-(pow(pob_landa[i][1],2)) ))));
           //             cout<<"fitlanda "<<pob_landa[i][2]<<endl;
                    }
                    break;
                }
            case 3:
                {
                    for(i=0;i<landa;i++)
                    {
                        pob_landa[i][2]=pow(16*pob_landa[i][0]*(1-pob_landa[i][0])*pob_landa[i][1]*(1-pob_landa[i][1])* sin(N*PI*pob_landa[i][0]) * sin(N*PI*pob_landa[i][1]),2);
             //           cout<<"fitlanda "<<pob_landa[i][2]<<endl;
                    }
                    break;
                }
            default :
                {
               //     cout<<"La ecuacion no se encontro"<<endl;
                    break;
                }
        }
        for(i=0;i<landa_cont;i++)
        {
           // cout<<pob_landa[i][2]<<endl;
        }
        //cout<<"---------------------------------------------"<<endl;
        for(i=0;i<tam_pob;i++)
        {
          //  cout<<poblacion[i][2]<<endl;
        }
        float aux1,aux2,aux0;
        for(i=0;i<landa_cont;i++)
        {
            for(int u=0;u<tam_pob;u++)
            {
                if(pob_landa[i][2]>poblacion[u][2])
                {
                    aux0=poblacion[u][0];
                    aux1=poblacion[u][1];
                    aux2=poblacion[u][2];
                    poblacion[u][0]=pob_landa[i][0];
                    poblacion[u][1]=pob_landa[i][1];
                    poblacion[u][2]=pob_landa[i][2];
                    pob_landa[i][0]=aux0;
                    pob_landa[i][1]=aux1;
                    pob_landa[i][2]=aux2;
                }
            }
        }
        //cout<<"----------------------------------------------------"<<endl;
        float prom_iteracion=0,maxval=-10000;
        float posfinx,posfiny;
        for(i=0;i<tam_pob;i++)
        {
            //cout<<poblacion[i][2]<<endl;
            prom_iteracion+=poblacion[i][2];
            if(poblacion[i][2]>maxval)
            {
                maxval=poblacion[i][2];
                posfinx=poblacion[i][0];
                posfiny=poblacion[i][1];

            }

        }
        prom_iteracion=prom_iteracion/tam_pob;
        cout<<prom_iteracion<<endl;
        if(valfinal<maxval)
        {
            valfinal=maxval;
            valfinalx=posfinx;
            valfinaly=posfiny;
        }
        else if(valfinal == maxval)
        {
            iteraciones++;
        }

    }
    cout <<valfinal<< endl<<valfinalx<<endl<<valfinaly<<endl;
    return 0;
}
