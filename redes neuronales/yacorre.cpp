#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <windows.h>
FILE *Archivo;
FILE *PesosIniciales;
FILE *PesosFinales;
double Osalida[20];
struct datos
{
	int Vector[1024];
	int Numero;
	int VectorNumero[10];
};
void InicialDatos(datos (*Entrenamiento))
{
	int i,j;
	for(i=0;i<1934;i++)
	{
		for(j=0;j<1024;j++)
		{
			Entrenamiento[i].Vector[j] = 0;
		}
		for(j=0;j<10;j++)
		{
			Entrenamiento[i].VectorNumero[j] = 0;
		}
		Entrenamiento[i].Numero = 0;
	}
}
void CachData(datos (*Entrenamiento),int (*IndiceInferior),int (*IndiceSuperior),int (*Posicion),int (*IndiceNumeroInferior),int (*IndiceNumeroSuperior))
{
	int i = 0,j = 0,k = 0;
	char Caracter;
	while( (feof(Archivo)==0) && (i < (*IndiceNumeroSuperior) ) )
    {
    	Caracter=fgetc(Archivo);
    		if( (i > (*IndiceInferior) ) && (i <= (*IndiceSuperior) ) )
    		{
				if(Caracter == '0'){Entrenamiento[(*Posicion)].Vector[j] = 0;j++;}
					else if(Caracter == '1'){Entrenamiento[(*Posicion)].Vector[j] = 1;j++;}
    		}
    	if( (i >= (*IndiceNumeroInferior) ) && (i < (*IndiceNumeroSuperior) ) )
    	{
			if(Caracter == '0'){Entrenamiento[(*Posicion)].Numero = 0;}
			else if(Caracter == '1'){Entrenamiento[(*Posicion)].Numero = 1;}
			else if(Caracter == '2'){Entrenamiento[(*Posicion)].Numero = 2;}
			else if(Caracter == '3'){Entrenamiento[(*Posicion)].Numero = 3;}
			else if(Caracter == '4'){Entrenamiento[(*Posicion)].Numero = 4;}
			else if(Caracter == '5'){Entrenamiento[(*Posicion)].Numero = 5;}
			else if(Caracter == '6'){Entrenamiento[(*Posicion)].Numero = 6;}
			else if(Caracter == '7'){Entrenamiento[(*Posicion)].Numero = 7;}
			else if(Caracter == '8'){Entrenamiento[(*Posicion)].Numero = 8;}
			else if(Caracter == '9'){Entrenamiento[(*Posicion)].Numero = 9;}
    	}
    	if(Caracter == '\n'){
    		i = i;}
    		else{
    			i++;}
	}

	for(k=0;k<10;k++)
	{
		if(k == Entrenamiento[(*Posicion)].Numero)
			Entrenamiento[(*Posicion)].VectorNumero[k] = 1;
	}
}

/*La Funcion Imprimir Numero nos ayuda a corroborar que lo esta haciendo bien*/
void ImprimirNumero(datos (*Entrenamiento), int (*Posicion))
{
	int i;
	for(i=0;i<1024;i++)//Imprime el Numero
	{
		printf("%d",Entrenamiento[(*Posicion)].Vector[i]);
			if( (i+1) % 32 == 0 )
				printf("\n");
	}

	printf("%d\n",Entrenamiento[(*Posicion)].Numero);//Imprime el Numero

	for(i=0;i<10;i++)
		printf("%d",Entrenamiento[(*Posicion)].VectorNumero[i]);//Imprime vector Numero

	printf("\n");
}

void GenerarPesos(double *(*Neuronas),int (*NeuronasEntrada),int (*NeuronasOculta),int (*NueronasSalida))
{
	int i,j;
	double naleatorio;

	for(i=0;i<2000;i++)//reseteamos el puntero de puntero
		for(j=0;j<2000;j++)
			Neuronas[i][j] = 100;


	for(j=((*NeuronasEntrada)+1);j<=((*NeuronasEntrada)+(*NeuronasOculta));j++)//asigna el peso de las neuronas de entrada y acultas
	{
		for(i=0;i<=(*NeuronasEntrada);i++)
		{
			naleatorio = 1 + rand()%((1000-1)+1);
			naleatorio = naleatorio / 100000;
			Neuronas[i][j] = naleatorio;
		}
	}

	for(j=((*NeuronasEntrada)+(*NeuronasOculta)+1);j<=((*NeuronasEntrada)+(*NeuronasOculta)+(*NueronasSalida));j++)//asigna el peso de las neuronas de ocultas a salida
	{
			for(i=(*NeuronasEntrada);i<=((*NeuronasEntrada)+(*NeuronasOculta));i++)
			{
				naleatorio = 1 + rand()%((1000-1)+1);
				naleatorio = naleatorio / 100000;
				if(i == (*NeuronasEntrada))
					Neuronas[0][j] = naleatorio;
				else
					Neuronas[i][j] = naleatorio;
			}
	}
}
/*Esta funcion imprime los pesos generado con su posicion*/
void ImprimirPesosIniciales(double *(*Neuronas),int (*NeuronasEntrada),int (*NeuronasOculta),int (*NueronasSalida))
{
		int i,j;

	for(j=((*NeuronasEntrada)+1);j<=((*NeuronasEntrada)+(*NeuronasOculta));j++)//asigna el peso de las neuronas de entrada y acultas
	{
		for(i=0;i<=(*NeuronasEntrada);i++)
		{
			fprintf(PesosIniciales,"%.10f\n",Neuronas[i][j]);
		}
	}

	for(j=((*NeuronasEntrada)+(*NeuronasOculta)+1);j<=((*NeuronasEntrada)+(*NeuronasOculta)+(*NueronasSalida));j++)//asigna el peso de las neuronas de ocultas a salida
	{
			for(i=(*NeuronasEntrada);i<=((*NeuronasEntrada)+(*NeuronasOculta));i++)
			{
				if(i == (*NeuronasEntrada))
					fprintf(PesosIniciales,"%.10f\n",Neuronas[0][j]);
				else
					fprintf(PesosIniciales,"%.10f\n",Neuronas[i][j]);
			}
	}
}
/*Esta funcion es la que se encarga de entrenar a la red neuronal*/
double Backpropagation(double *(*Neuronas),int (*NeuronasEntrada),int (*NeuronasOculta),int (*NeuronasSalida),datos (*Entrenamiento),int (*Posicion),double (*CoeficienteAprendisaje))
{
	int i=0,j=0,k = 0,l=0;
	double Ooculta[20], f = 0, ErrorSalida[20], ErrorOculta[20], x0 = -1;
	double SumatoriaErrorOculta = 0, SumaError[20], PromedioError = 0, SumaTotalError = 0;
	for(i=0;i<20;i++){
		Ooculta[i] = 0; Osalida[i] = 0;ErrorSalida[i] = 0;ErrorOculta[i] = 0;SumaError[i] = 0;}
	/*Se calculan las o de la capa de entrada a oculta*/
	for(j=((*NeuronasEntrada)+1);j<=((*NeuronasEntrada)+(*NeuronasOculta));j++)
	{
		for(i=0;i<=(*NeuronasEntrada);i++)
		{
			if(i==0)
				f += (x0)*Neuronas[i][j];
				else
					f += (Entrenamiento[(*Posicion)].Vector[i-1]) * Neuronas[i][j];
		}
		Ooculta[k] = 1 /(1 + exp(-f));
		k++;
		f = 0;
	}
	k = 0;
	l = 0;
	/*Se calculan las o de la capa oculta a la de salida*/
	for(j=((*NeuronasEntrada)+(*NeuronasOculta)+1);j<=((*NeuronasEntrada)+(*NeuronasOculta)+(*NeuronasSalida));j++)
	{
		for(i=(*NeuronasEntrada);i<=((*NeuronasEntrada)+(*NeuronasOculta));i++)
		{
			if(i == (*NeuronasEntrada)){
				f += (x0)*Neuronas[0][j];}
				else{
					f += Ooculta[k]*Neuronas[i][j]; k++;}
		}
		Osalida[l] = 1 /(1 + exp(-f));
		k = 0;
		f = 0;
		l++;
	}
	/*Se calcula el error de salida*/
	for(i=0;i<(*NeuronasSalida);i++)
	{
		ErrorSalida[i] = Osalida[i] * (1 - Osalida[i]) * (Entrenamiento[(*Posicion)].VectorNumero[i] - Osalida[i]);
		SumaError[i] = (Entrenamiento[(*Posicion)].VectorNumero[i] - Osalida[i]);
		SumaError[i] = pow(SumaError[i],2);
	}
	/*Se calcula el error de ocultas ji*/
	l=0;
	k=0;
	for(j=((*NeuronasEntrada)+1);j<=((*NeuronasEntrada)+(*NeuronasOculta));j++)
	{
		for(i=((*NeuronasEntrada)+(*NeuronasOculta)+1);i<=((*NeuronasEntrada)+(*NeuronasOculta)+(*NeuronasSalida));i++)
		{
			SumatoriaErrorOculta += Neuronas[j][i]*ErrorSalida[k];
			k++;
		}
		ErrorOculta[l] = Ooculta[l] * (1 - Ooculta[l]) * SumatoriaErrorOculta;
		SumatoriaErrorOculta = 0;
		l++;
		k=0;
	}
	/*Se actualizan los pesos de Entrada-Oculta*/
	l =0;
	for(j=((*NeuronasEntrada)+1);j<=((*NeuronasEntrada)+(*NeuronasOculta));j++)
	{
		for(i=0;i<=(*NeuronasEntrada);i++)
		{
			if(i == 0)
				Neuronas[i][j] += ((*CoeficienteAprendisaje)*(ErrorOculta[l])*(x0));
			else
				Neuronas[i][j] += ((*CoeficienteAprendisaje)*(ErrorOculta[l])*Entrenamiento[(*Posicion)].Vector[i-1]);
		}
		l++;
	}
	/*Se actualizan los pesos Oculta-Salida*/
	l = 0;
	k = 0;
	for(j=((*NeuronasEntrada)+(*NeuronasOculta)+1);j<=((*NeuronasEntrada)+(*NeuronasOculta)+(*NeuronasSalida));j++)
	{
		for(i=(*NeuronasEntrada);i<=((*NeuronasEntrada)+(*NeuronasOculta));i++)
		{
			if(i == (*NeuronasEntrada))
				Neuronas[0][j] += ((*CoeficienteAprendisaje)*(ErrorSalida[k])*(x0));
			else
				Neuronas[i][j] +=  ((*CoeficienteAprendisaje)*(ErrorSalida[k])*(Osalida[l-1]));
			l++;
		}
		l = 0;
		k++;
	}
	/*Se cacula el error*/
	for(i=0;i<(*NeuronasSalida);i++)
		SumaTotalError += SumaError[i];

	PromedioError = ( SumaTotalError / (*NeuronasSalida) );

	return PromedioError;
}

/*Esta funcion imprime los pesos generado con su posicion*/
void ImprimirPesosFinales(double *(*Neuronas),int (*NeuronasEntrada),int (*NeuronasOculta),int (*NueronasSalida))
{
	int i,j;

	for(j=((*NeuronasEntrada)+1);j<=((*NeuronasEntrada)+(*NeuronasOculta));j++)//asigna el peso de las neuronas de entrada y acultas
	{
		for(i=0;i<=(*NeuronasEntrada);i++)
		{
			fprintf(PesosFinales,"%.10f\n",Neuronas[i][j]);
		}
	}

	for(j=((*NeuronasEntrada)+(*NeuronasOculta)+1);j<=((*NeuronasEntrada)+(*NeuronasOculta)+(*NueronasSalida));j++)//asigna el peso de las neuronas de ocultas a salida
	{
			for(i=(*NeuronasEntrada);i<=((*NeuronasEntrada)+(*NeuronasOculta));i++)
			{
				if(i == (*NeuronasEntrada))
					fprintf(PesosFinales,"%.10f\n",Neuronas[0][j]);
				else
					fprintf(PesosFinales,"%.10f\n",Neuronas[i][j]);
			}
	}
}

int main(int argc, char *argv[])
{
	int NeuronasEntrada = 1024, NeuronasOculta = 10, NeuronasSalida = 10;
	int IndiceInferior = 0, IndiceSuperior = 1023, Posicion;
	int IndiceNumeroInferior = 0, IndiceNumeroSuperior = 0;
	int i,j,k,NumeroEvaluado,MatrizConfusion[10][10];

	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			MatrizConfusion[i][j]=0;
		}
	}
	double CoeficienteAprendisaje = 0.1, Error = 0, PromedioError = 0;
	datos * BasedeDatos = (datos*)malloc(sizeof(datos)*1934);//reservo memoria para la estructura
	double ** Neuronas = (double**)malloc(sizeof(double*)*2000);//reservo memoria en i
	for(i=0;i<2000;i++)
		Neuronas[i] = (double*)malloc(sizeof(double)*2000);//reservo memoria en j
	PesosIniciales = fopen("PesosIniciales.txt","w+");//imprime pesos iniciales
	PesosFinales = fopen("PesosFinales.txt","w+");//imprime los pesos finales
	InicialDatos(BasedeDatos);//evita agarrar basura
	/*En esta parte del codigo se carga el Archivo a la Estructura*/
	printf("***********************Leyendo Numeros para Entrenamiento***********************\n");
	for(i=0;i<1934;i++)
	{
		IndiceNumeroInferior = IndiceSuperior + 2;
		IndiceNumeroSuperior = IndiceNumeroInferior + 1;

		Archivo = fopen("NumerosPrueba.txt","r");//Abre el Archivo

		Posicion = i;

		CachData(BasedeDatos,&IndiceInferior,&IndiceSuperior,&Posicion,&IndiceNumeroInferior,&IndiceNumeroSuperior);

		fclose(Archivo);//Cierra el Archivo

		Posicion = i;
		//ImprimirNumero(Entrenamiento,&Posicion);//se imprime el numero cargado
		//printf("[%d] de [%d]\n",i+1,1934);

		IndiceInferior = IndiceSuperior + 3;
		IndiceSuperior = IndiceInferior + 1023;

	}
	GenerarPesos(Neuronas,&NeuronasEntrada,&NeuronasOculta,&NeuronasSalida);
	ImprimirPesosIniciales(Neuronas,&NeuronasEntrada,&NeuronasOculta,&NeuronasSalida);

	fclose(PesosIniciales);
	printf("****************************Entrenamiento de la Red****************************\n");
	j = 0;
	do
	{

		for(i=0;i<1934;i++)
		{
			Posicion = i;
			Error += Backpropagation(Neuronas,&NeuronasEntrada,&NeuronasOculta,&NeuronasSalida,BasedeDatos,&Posicion,&CoeficienteAprendisaje);
		}
		PromedioError = (Error/1934);
		Error = 0;
		printf("Epoca [%d] Error -> [%.10f]\n",j,PromedioError);
		j++;

	}
	while(PromedioError > 0.001);
	printf("%d Epocas\n",j-1);
	printf("Error final -> %.10f\n\n",PromedioError);

	ImprimirPesosFinales(Neuronas,&NeuronasEntrada,&NeuronasOculta,&NeuronasSalida);
	printf("\t\tRevise el Archivo PesosFinales.txt\n");
	fclose(PesosFinales);
	printf("\t\tPruebas de la red...\n");
	fclose(PesosFinales);
	IndiceInferior = 0;
	IndiceSuperior = 1023;
	for(i=0;i<100;i++)
	{
		IndiceNumeroInferior = IndiceSuperior + 2;
		IndiceNumeroSuperior = IndiceNumeroInferior + 1;

		Archivo = fopen("Prueba.txt","r");//Abre el Archivo

		Posicion = i;

		CachData(BasedeDatos,&IndiceInferior,&IndiceSuperior,&Posicion,&IndiceNumeroInferior,&IndiceNumeroSuperior);

		fclose(Archivo);//Cierra el Archivo

		Posicion = i;
		//ImprimirNumero(Entrenamiento,&Posicion);//se imprime el numero cargado
		//printf("[%d] de [%d]\n",i+1,1934);

		IndiceInferior = IndiceSuperior + 3;
		IndiceSuperior = IndiceInferior + 1023;

	}

	printf("\t\tfin carga de archivos\n");


	printf("\t\tBackpropagation...\n");
	int istrue=0;
	for(i=0;i<100;i++)
		{
			Posicion = i;
			Error += Backpropagation(Neuronas,&NeuronasEntrada,&NeuronasOculta,&NeuronasSalida,BasedeDatos,&Posicion,&CoeficienteAprendisaje);
			printf("\t\tcheck\n");
			for(j=0;j<10;j++)
			{
				printf("%.2f\n",Osalida[j] );
				if(Osalida[j] > .5)istrue=j;

			}
			MatrizConfusion[istrue][BasedeDatos[Posicion].Numero]++;
			printf("%d\n",BasedeDatos[Posicion].Numero );

		}

	printf("\t\tMatriz Confucion...\n");
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			printf("%d ",MatrizConfusion[i][j]);
		}
		printf("\n");
	}
	return 0;
}
