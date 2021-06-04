#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<mpi.h>

void master(int nproc, MPI_Comm comm);
void slave(int mytid, MPI_Comm comm);

void main(int argc, char **argv){
    int mytid, nproc;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &mytid);
    if(mytid == 0)
        master(nproc,MPI_COMM_WORLD);
    else
        slave(mytid,MPI_COMM_WORLD);

    MPI_Finalize();
}

void master(int nproc, MPI_Comm comm){
    //CREEMOS QUE UNO DE LOS PROBLEMAS ES EL TAMAÑO DE SIZE
    //AUNQUE CONSIDERAMOS ESTE EL QUE DEBERIA SER EL CORRECTO
    //PARECE FUNCIONAR MEJOR CON UN NUMERO MAYOR PERO AUN ASI
    //RECVBUF RECIBE NADA
    int size = sizeof(char)*20*(nproc-1);
    char recvbuf[size];
    char foo[20] = "Hola del proceso 0";
    //Hasta acá el valor de nproc es el valido, luego de gather se rompe.
    int success = MPI_Gather(foo, 18, MPI_CHAR, recvbuf, 18, MPI_CHAR, 0, comm);
    recvbuf[nproc*18]='\0';
    if(success==MPI_SUCCESS){
        //Siempre ha dado como resultado success pero recvbuf contiene basura y nproc se rompe misteriosamente
        printf("Hola, soy el proceso 0, hay %d procesos, y recibo:\n", nproc);
        printf("%s\n", recvbuf);
    }
    else{
        printf("Error\n");
    }
}

void slave(int mytid, MPI_Comm comm){
    const char* str1 = "Hola del proceso ";
    //El tamaño de 20 es porque "Hola del proceso [num]\n\0" tiene 20 caracteres
    char sendbuf[20];
    char num[2];
    char foo[20];
    sprintf(num, "%d", mytid);
    strcpy(sendbuf, str1);
    strcat(sendbuf, num);
    //strcat(sendbuf,"\n");
    //sendbuf tiene el mensaje de manera correcta. "Hola del proceso [num]\n"
    MPI_Gather(sendbuf, 18, MPI_CHAR, foo, 18, MPI_CHAR, 0, comm);
}

//int MPI_Gather(void* sendbuf, int sendcount, MPI_Datatype sendtype, void* recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm);

//Sólo el proceso raíz tiene que preocuparse de los parámetros recbuf,
//recvcount y recvtype. Sin embargo, todos los procesos (raíz incluido) tienen
//que facilitar valores válidos para sendbuf, sendcount y sendtype.
