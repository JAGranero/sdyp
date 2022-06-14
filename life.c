#include<stdio.h>
#include<stdlib.h>
//Dimension de la matriz
int dim = 0;

//Nuestra la matriz
int mostrarMatriz(char **matriz){
	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			printf("%c\n", matriz[i][j]);
		}
		printf("\n");
	}
	return(0);
}

void main(int argc, char const *argv[])
{
	time_t t;

	//Controlo que se pase como parametro la dimension de la matriz
	if(argc == 1 ){
		printf("Falta dimension de la matriz\n");
		getchar();
		exit(-1);
	}
	dim = atoi(argv[1]);
	printf("%i, %i\n", argc,dim);
	

	//Inicializa la semilla del random
	srand((unsigned) time(&t));

	//Se crea la matriz
	char **matriz;
	matriz = (char**) malloc(sizeof(char *)*dim);
	for (int i = 0; i < dim; ++i)
	 {
	 	matriz[i] = (char*) malloc(sizeof(char)*dim);
	 	
	 	//Se inicializa la fila recien creada de la matriz
	 	for (int j = 0; j < dim; ++j)
	 	{
	 		if(rand()%100 < 30)
	 			matriz[i][j] = '*';
	 		else
	 			matriz[i][j] = '-';
	 	}
	 } 

	 mostrarMatriz(matriz);


	getchar();
}