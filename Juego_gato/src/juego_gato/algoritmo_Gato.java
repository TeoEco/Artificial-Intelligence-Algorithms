/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package juego_gato;

/**
 *
 * @author cheche
 */
public class algoritmo_Gato {
    
    
    int X=0,O=0;
    int contO=0,contX=0;
    int [] aX= new int [9];
    int [] aO= new int [9];
    public int ganaO(int arreglo[]){
           if(arreglo[0]==1 && arreglo[1]==1 && arreglo[2]==1){
                return 1;}
            if(arreglo[3]==1 && arreglo[4]==1 && arreglo[5]==1){
                return 1;}
            if(arreglo[6]==1 && arreglo[7]==1 && arreglo[8]==1){
                return 1;}
            if(arreglo[0]==1 && arreglo[3]==1 && arreglo[6]==1){
                return 1;}
            if(arreglo[1]==1 && arreglo[4]==1 && arreglo[7]==1){
                return 1;}
            if(arreglo[2]==1 && arreglo[5]==1 && arreglo[8]==1){
                return 1;}
            if(arreglo[0]==1 && arreglo[4]==1 && arreglo[8]==1){
                return 1;}
            if(arreglo[2]==1 && arreglo[4]==1 && arreglo[6]==1){
                return 1;}
            return 0;
    }
    
    public int ganaX(int arreglo[]){
        if(arreglo[0]==-1 && arreglo[1]==-1 && arreglo[2]==-1){
                return 1;}
            if(arreglo[3]==-1 && arreglo[4]==-1 && arreglo[5]==-1){
                return 1;}
            if(arreglo[6]==-1 && arreglo[7]==-1 && arreglo[8]==-1){
                return 1;}
            if(arreglo[0]==-1 && arreglo[3]==-1 && arreglo[6]==-1){
                return 1;}
            if(arreglo[1]==-1 && arreglo[4]==-1 && arreglo[7]==-1){
                return 1;}
            if(arreglo[2]==-1 && arreglo[5]==-1 && arreglo[8]==-1){
                return 1;}
            if(arreglo[0]==-1 && arreglo[4]==-1 && arreglo[8]==-1){
                return 1;}
            if(arreglo[2]==-1 && arreglo[4]==-1 && arreglo[6]==-1){
                return 1;}
            return 0;
    }
    public int tablerolleno(int arreglo[]){
        int cont=0;
        for(int i=0; i<9;i++){
            if(arreglo[i]==3)
                cont++;
        }
        if(cont == 0)
            return 1;
        return 0;
    }
    
    public int isGameOver(int arreglo[]){
        if(ganaX(arreglo) == 1)
            return -1;
        if(ganaO(arreglo) == 1)
            return 1;
        if(tablerolleno(arreglo) == 1)
            return 0;
        return 3;
    }
   
    public int movimiento(int jugador,int arreglo[]){
        contO=contX=0;
        for(int i=0;i<9;i++){
            aX[i]=10;
            aO[i]=10;
        }
        if(jugador==1){
            play_O(arreglo);
                    return aO[1];
        }
        if(jugador==-1){
            play_X(arreglo);
            return aX[1];
        }
        return 0;
    }
    
    public int play_O(int tablero[]){
        int mejor_opcion=0,cont=0,max=-1;
        int [] arreglo = new int[9];
        if(Gameover(tablero) == 1)
            return isGameOver(tablero);
        for(int j=0;j<9;j++){
            if(tablero[j]==3){
                arreglo[cont]=j;
                cont++;
            }
        }
        for(int j=0;j<cont;j++){
            if(tablero[arreglo[j]]==3){
                tablero[arreglo[j]]=1;
                contO++;
                mejor_opcion=play_X(tablero);
                if(mejor_opcion > max){
                    max = mejor_opcion;
                    aO[contO]=arreglo[j];
                }
                tablero[arreglo[j]]=3;
                
            }
            contO--;
        }
        return max;
    }
    
    public int play_X(int tablero[]){
        int cont=0,mejor_opcion=0,min=1;
        int [] arreglo = new int [9];
        if(Gameover(tablero) == 1)
            return isGameOver(tablero);
        for(int j=0;j<9;j++){
            if(tablero[j]==3){
                arreglo[cont]=j;
                cont++;
            }
        }
        for(int j=0;j<cont;j++){
            if(tablero[arreglo[j]]==3){
                tablero[arreglo[j]]=-1;
                contX++;
                mejor_opcion=play_O(tablero);
                if(mejor_opcion < min){
                    min=mejor_opcion;
                    aX[contX]=arreglo[j];
                    
                }
                tablero[arreglo[j]]=3;
                contX--;
            }
        }
        return min;
    }
    
    public int Gameover(int arreglo[]){
        if(ganaX(arreglo) == 1)
            return 1;
        if(ganaO(arreglo) == 1)
            return 1;
        if(tablerolleno(arreglo) == 1)
            return 1;
        return 0;
    }
    
}
