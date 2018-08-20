/*juan alberto gutierrez canto
  version 1
  */

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>


using namespace std;

int main()
{
    int num_fitnes,i,dim,pocicion;
    cin>>num_fitnes;
    float fitnes[num_fitnes][2],cont=0,azarf;
    int contfit[num_fitnes],j;
    srand(time(NULL));

    for(i=0;i<num_fitnes;i++)
    {
        cin>>fitnes[i][0];
        cont+=fitnes[i][0];
        fitnes[i][1]=cont;
        contfit[i]=0;
    }
    for(i=0;i<40;i++)
    {
        azarf=rand()%int(cont*1000);
        azarf=azarf/1000;
        j=0;
        dim=num_fitnes;
        while(j<dim)
        {
            //cout<<azarf<<" aleatorio para "<<fitnes[j][1]<<endl;
            if(fitnes[j][1]>azarf)
            {
                contfit[j]++;
                break;
            }
            j++;
        }
    }
    for(i=0;i<num_fitnes;i++)
    {
        cout<<"fitnes "<<fitnes[i][0]<<" total "<<contfit[i]<<endl;
    }
    return 0;
}
