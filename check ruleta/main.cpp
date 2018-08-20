#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int main()
{
    int i,seleccion=20;
    float azarf,valormax=106.67;
    cout << "Hello world!" << endl;
    for(i=0;i<seleccion;i++)
        {
            cout<<"vlaor max "<<valormax*100<<endl;
            azarf=rand()%int(valormax*100);
            cout<<"al azarf "<<azarf<<endl;
            azarf=azarf/100;
            cout<<"al azar "<<azarf<<endl;
    }
    return 0;
}
