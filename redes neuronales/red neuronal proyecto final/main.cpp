#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
FILE *Archivo;
FILE *PesosIniciales;
FILE *PesosFinales;
double Osalida[20];
struct datos{
	int Data[1024];
	int ArrayNum[10];
	int Num;
};

void InicialDatos(datos (*BasedeDatos)){
	int i,j;
	for(i=0;i<1934;i++){
		for(j=0;j<1024;j++){
			BasedeDatos[i].Data[j] = 0;
		}
		for(j=0;j<10;j++){
			BasedeDatos[i].ArrayNum[j] = 0;
		}
		BasedeDatos[i].Num = 0;
	}
}

void CachData(datos (*BasedeDatos),int (*Inferior),int (*Superior),int (*Posicion),int (*InferiorNum),int (*SuperiorNum))
{
	int i = 0,j = 0,k = 0;
	char caracter;
	while( (feof(Archivo)==0) && (i < (*SuperiorNum) ) ){
    	caracter=fgetc(Archivo);
    		if( (i > (*Inferior) ) && (i <= (*Superior) ) ){
				if(caracter == '0'){
					BasedeDatos[(*Posicion)].Data[j] = 0;
					j++;
				}
				else if(caracter == '1'){
					BasedeDatos[(*Posicion)].Data[j] = 1;
					j++;
				}
    		}
    	if( (i >= (*InferiorNum) ) && (i < (*SuperiorNum) ) ){
			switch(caracter){
				case '0':{
					BasedeDatos[(*Posicion)].Num = 0;
					break;
				}
				case '1':{
					BasedeDatos[(*Posicion)].Num = 1;
					break;
				}
				case '2':{
					BasedeDatos[(*Posicion)].Num = 2;
					break;
				}
				case '3':{
					BasedeDatos[(*Posicion)].Num = 3;
					break;
				}
				case '4':{
					BasedeDatos[(*Posicion)].Num = 4;
					break;
				}
				case '5':{
					BasedeDatos[(*Posicion)].Num = 5;
					break;
				}
				case '6':{
					BasedeDatos[(*Posicion)].Num = 6;
					break;
				}
				case '7':{
					BasedeDatos[(*Posicion)].Num = 7;
					break;
				}
				case '8':{
					BasedeDatos[(*Posicion)].Num = 8;
					break;
				}
				case '9':{
					BasedeDatos[(*Posicion)].Num = 9;
					break;
				}
				default:
					break;
			}
    	}
    	if(caracter == '\n'){
    		i = i;
    	}
    	else{
    		i++;
    	}
	}
	for(k=0;k<10;k++){
		if(k == BasedeDatos[(*Posicion)].Num)
			BasedeDatos[(*Posicion)].ArrayNum[k] = 1;
	}
}

void ImprimeDato(datos (*BasedeDatos), int (*Posicion))
{
	int i;
	for(i=0;i<1024;i++){
		printf("%d",BasedeDatos[(*Posicion)].Data[i]);
			if( (i+1) % 32 == 0 )
				printf("\n");
	}
	printf("%d\n",BasedeDatos[(*Posicion)].Num);
	for(i=0;i<10;i++)
		printf("%d",BasedeDatos[(*Posicion)].ArrayNum[i]);
	printf("\n");
}

void GenerarPesos(double *(*Wpesos),int (*NumEnt),int (*NumOcu),int (*NumSal))
{
	double numAle;
	int i,j;

	for(i=0;i<2000;i++)
		for(j=0;j<2000;j++)
			Wpesos[i][j] = 100;

	for(j=((*NumEnt)+1);j<=((*NumEnt)+(*NumOcu));j++){
		for(i=0;i<=(*NumEnt);i++){
			numAle = 1 + rand()%((1000-1)+1);
			numAle = numAle / 100000;
			Wpesos[i][j] = numAle;
		}
	}
	for(j=((*NumEnt)+(*NumOcu)+1);j<=((*NumEnt)+(*NumOcu)+(*NumSal));j++){
			for(i=(*NumEnt);i<=((*NumEnt)+(*NumOcu));i++){
				numAle = 1 + rand()%((1000-1)+1);
				numAle = numAle / 100000;
				if(i == (*NumEnt))
					Wpesos[0][j] = numAle;
				else
					Wpesos[i][j] = numAle;
			}
	}
}

void ImprimirPesosIniciales(double *(*Wpesos),int (*NumEnt),int (*NumOcu),int (*NumSal))
{
	int i,j;
	for(j=((*NumEnt)+1);j<=((*NumEnt)+(*NumOcu));j++){
		for(i=0;i<=(*NumEnt);i++){
			fprintf(PesosIniciales,"%.10f\n",Wpesos[i][j]);
		}
	}
	for(j=((*NumEnt)+(*NumOcu)+1);j<=((*NumEnt)+(*NumOcu)+(*NumSal));j++){
			for(i=(*NumEnt);i<=((*NumEnt)+(*NumOcu));i++){
				if(i == (*NumEnt))
					fprintf(PesosIniciales,"%.10f\n",Wpesos[0][j]);
				else
					fprintf(PesosIniciales,"%.10f\n",Wpesos[i][j]);
			}
	}
}

double Backpropagation(double *(*Wpesos),int (*NumEnt),int (*NumOcu),int (*NumSal),datos (*BasedeDatos),int (*Posicion),double (*Landa))
{
	int i=0;
	int j=0;
	int k=0;
	int l=0;
	double Ooculta[20];
	double f=0;
	double ErrorSalida[20];
	double ErrorOculta[20];
	double Xneg = -1;
	double SumatoriaErrorOculta = 0;
	double SumaError[20];
	double PromedioError =0;
	double SumaTotalError = 0;
	for(i=0;i<20;i++){
		Ooculta[i] = 0;
		Osalida[i] = 0;
		ErrorSalida[i] = 0;
		ErrorOculta[i] = 0;
		SumaError[i] = 0;
	}
	for(j=((*NumEnt)+1);j<=((*NumEnt)+(*NumOcu));j++){
		for(i=0;i<=(*NumEnt);i++){
			if(i==0)
				f += (Xneg)*Wpesos[i][j];
			else
				f += (BasedeDatos[(*Posicion)].Data[i-1]) * Wpesos[i][j];
		}
		Ooculta[k] = 1 /(1 + exp(-f));
		k++;
		f = 0;
	}
	k = 0;
	l = 0;
	for(j=((*NumEnt)+(*NumOcu)+1);j<=((*NumEnt)+(*NumOcu)+(*NumSal));j++){
		for(i=(*NumEnt);i<=((*NumEnt)+(*NumOcu));i++){
			if(i == (*NumEnt)){
				f += (Xneg)*Wpesos[0][j];
			}
			else{
				f += Ooculta[k]*Wpesos[i][j];
				k++;
			}
		}
		Osalida[l] = 1 /(1 + exp(-f));
		k = 0;
		f = 0;
		l++;
	}
	for(i=0;i<(*NumSal);i++){
		ErrorSalida[i] = Osalida[i] * (1 - Osalida[i]) * (BasedeDatos[(*Posicion)].ArrayNum[i] - Osalida[i]);
		SumaError[i] = (BasedeDatos[(*Posicion)].ArrayNum[i] - Osalida[i]);
		SumaError[i] = pow(SumaError[i],2);
	}
	l=0;
	k=0;
	for(j=((*NumEnt)+1);j<=((*NumEnt)+(*NumOcu));j++){
		for(i=((*NumEnt)+(*NumOcu)+1);i<=((*NumEnt)+(*NumOcu)+(*NumSal));i++){
			SumatoriaErrorOculta += Wpesos[j][i]*ErrorSalida[k];
			k++;
		}
		ErrorOculta[l] = Ooculta[l] * (1 - Ooculta[l]) * SumatoriaErrorOculta;
		SumatoriaErrorOculta = 0;
		l++;
		k=0;
	}
	l =0;
	for(j=((*NumEnt)+1);j<=((*NumEnt)+(*NumOcu));j++){
		for(i=0;i<=(*NumEnt);i++){
			if(i == 0)
				Wpesos[i][j] += ((*Landa)*(ErrorOculta[l])*(Xneg));
			else
				Wpesos[i][j] += ((*Landa)*(ErrorOculta[l])*BasedeDatos[(*Posicion)].Data[i-1]);
		}
		l++;
	}
	l = 0;
	k = 0;
	for(j=((*NumEnt)+(*NumOcu)+1);j<=((*NumEnt)+(*NumOcu)+(*NumSal));j++){
		for(i=(*NumEnt);i<=((*NumEnt)+(*NumOcu));i++){
			if(i == (*NumEnt))
				Wpesos[0][j] += ((*Landa)*(ErrorSalida[k])*(Xneg));
			else
				Wpesos[i][j] +=  ((*Landa)*(ErrorSalida[k])*(Osalida[l-1]));
			l++;
		}
		l = 0;
		k++;
	}
	for(i=0;i<(*NumSal);i++)
		SumaTotalError += SumaError[i];
	PromedioError = ( SumaTotalError / (*NumSal) );
	return PromedioError;
}

void ImprimirPesosFinales(double *(*Wpesos),int (*NumEnt),int (*NumOcu),int (*NumSal))
{
	int i,j;
	for(j=((*NumEnt)+1);j<=((*NumEnt)+(*NumOcu));j++){
		for(i=0;i<=(*NumEnt);i++){
			fprintf(PesosFinales,"%.10f\n",Wpesos[i][j]);
		}
	}
	for(j=((*NumEnt)+(*NumOcu)+1);j<=((*NumEnt)+(*NumOcu)+(*NumSal));j++){
			for(i=(*NumEnt);i<=((*NumEnt)+(*NumOcu));i++){
				if(i == (*NumEnt))
					fprintf(PesosFinales,"%.10f\n",Wpesos[0][j]);
				else
					fprintf(PesosFinales,"%.10f\n",Wpesos[i][j]);
			}
	}
}

int main(int argc, char *argv[])
{
	int NumEnt = 1024;
	int NumOcu = 10;
	int NumSal = 10;
	int Inferior = 0;
	int Superior = 1023;
	int Posicion,i,j,k;
	int IndiceNumeroInferior = 0;
	int IndiceNumeroSuperior = 0;
	int MatConfusion[10][10];
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			MatConfusion[i][j]=0;
		}
	}
	double Landa = 0.1;
	double Error = 0;
	double PromedioError = 0;
	datos * BasedeDatos = (datos*)malloc(sizeof(datos)*1934);
	double ** Wpesos = (double**)malloc(sizeof(double*)*2000);
	for(i=0;i<2000;i++)
		Wpesos[i] = (double*)malloc(sizeof(double)*2000);
	//PesosIniciales = fopen("PesosIniciales.txt","w+");
	//PesosFinales = fopen("PesosFinales.txt","w+");
	InicialDatos(BasedeDatos);
	printf("Cargando BasedeDatos...\n");
	for(i=0;i<1934;i++){
		IndiceNumeroInferior = Superior + 2;
		IndiceNumeroSuperior = IndiceNumeroInferior + 1;
		Archivo = fopen("NumerosPrueba.txt","r");//Abre el Archivo
		Posicion = i;
		CachData(BasedeDatos,&Inferior,&Superior,&Posicion,&IndiceNumeroInferior,&IndiceNumeroSuperior);
		fclose(Archivo);
		Posicion = i;
		//ImprimirDato(BasedeDatos,&Posicion);//se imprime el numero cargado
		//printf("[%d] de [%d]\n",i+1,1934);
		Inferior = Superior + 3;
		Superior = Inferior + 1023;
	}
	GenerarPesos(Wpesos,&NumEnt,&NumOcu,&NumSal);
	//ImprimirPesosIniciales(Wpesos,&NumEnt,&NumOcu,&NumSal);
	//fclose(PesosIniciales);
	printf("Entrenamiento red...\n");
	j = 0;
	do
	{
		for(i=0;i<1934;i++){
			Posicion = i;
			Error += Backpropagation(Wpesos,&NumEnt,&NumOcu,&NumSal,BasedeDatos,&Posicion,&Landa);
		}
		PromedioError = (Error/1934);
		Error = 0;
		printf("Epoca [%d] Error -> [%.10f]\n",j,PromedioError);
		j++;
	}while(PromedioError > 0.000001);
	printf("%d Epocas\n",j-1);
	printf("Error final -> %.10f\n\n",PromedioError);
	//ImprimirPesosFinales(Wpesos,&NumEnt,&NumOcu,&NumSal);
	//fclose(PesosFinales);
	printf("Cargando pruebas de la red a la Base de Datos...\n");
	Inferior = 0;
	Superior = 1023;
	for(i=0;i<1700;i++){
		IndiceNumeroInferior = Superior + 2;
		IndiceNumeroSuperior = IndiceNumeroInferior + 1;
		Archivo = fopen("Prueba.txt","r");//Abre el Archivo
		Posicion = i;
		CachData(BasedeDatos,&Inferior,&Superior,&Posicion,&IndiceNumeroInferior,&IndiceNumeroSuperior);
		fclose(Archivo);//Cierra el Archivo
		Posicion = i;
		//ImprimirNumero(BasedeDatos,&Posicion);//se imprime el numero cargado
		//printf("[%d] de [%d]\n",i+1,1934);
		Inferior = Superior + 3;
		Superior = Inferior + 1023;
	}
	printf("Probando datos en algoritmo...\n");
	int istrue=0;
	for(i=0;i<1700;i++){
		Posicion = i;
		Error += Backpropagation(Wpesos,&NumEnt,&NumOcu,&NumSal,BasedeDatos,&Posicion,&Landa);
		for(j=0;j<10;j++){
			if(Osalida[j] > .5)istrue=j;
		}
		MatConfusion[istrue][BasedeDatos[Posicion].Num]++;
	}
	int efectividad=0;
	printf("Creando matriz de confucion...\n");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			printf("%d ",MatConfusion[i][j]);
			if(i==j)efectividad+=MatConfusion[i][j];
		}
		printf("\n");
	}
	printf("La efectividad de la matriz es de %d% \nResolviendo %d de 1700\n",efectividad,efectividad );

	return 0;
}
