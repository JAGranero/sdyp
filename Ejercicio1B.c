#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>
main(int argc, char **argv){
	int node, size,AUX;
	char rmessage[300];
	char smessage[30], mesg[30];
	char num[5];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &node);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	strcpy(rmessage,"");
	strcpy(smessage,"");
	if(node!=0){
		strcpy(smessage,"Hola desde el proceso ");
		sprintf(num,"%d",node);
		strcat(smessage,num);
		MPI_Send(smessage,30,MPI_CHAR,0,99,MPI_COMM_WORLD);
	}
	else{
		strcpy(smessage,"");
	}
	//MPI_Gather(smessage,30,MPI_CHAR,rmessage,30,MPI_CHAR,0,MPI_COMM_WORLD); NO funciona razon desconocida
	if(node==0){
		printf("Hola, soy el proceso 0 (hay %d procesos) y recibo:\n",size);
		for(int i=1; i<size; i++){
			MPI_Recv(mesg,30,MPI_CHAR,MPI_ANY_SOURCE,99,MPI_COMM_WORLD,&status);
			printf("(%s)\n",mesg);
		}
	}
	MPI_Finalize();
}