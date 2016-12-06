#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int segA,segB,segC,segrA,segrB,segcB;   //dhlwsh metavlhtwn
    int i,j,k,pro,*l,*m,*u,*v,rowA,colA,colB;

    int *A;
    int *B;
    int *C;
    i=atoi(argv[1]);
    j=atoi(argv[2]);
    segA=atoi(argv[3]);   //metatroph twn alfarithmhtikwn orismatwn se akeraious
    segB=atoi(argv[4]);
    segC=atoi(argv[5]);
    segrA=atoi(argv[6]);
    segrB=atoi(argv[7]);
    segcB=atoi(argv[8]);
    A=(int*)shmat(segA,NULL,0);
    B=(int*)shmat(segB,NULL,0);
    C=(int*)shmat(segC,NULL,0);

    l=(int*)shmat(segrA,NULL,0);
    rowA=*l;
    v=(int*)shmat(segcB,NULL,0);
    colB=*v;
    m=(int*)shmat(segrB,NULL,0);
    colA=*m;
    A=(int*)malloc(rowA*colA*sizeof(int));
    B=(int*)malloc(colA*colB*sizeof(int));
    C=(int*)malloc(rowA*colB*sizeof(int));

    for (k=0;k<colA;k++)
        pro=pro+(A[i* colA+k])*(B[colB *k+j]);

    C[(i*colB)+j]=pro;
    return 0;
}
