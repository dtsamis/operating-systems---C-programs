#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>

int main()
{
    char *arg[9]; //dhlwsh pinaka alfarithmhtikwn gia apothikeysh orismatwn ths execvp
    int segp,segA,segB,segC,segrA,segrB,segcA,segcB; //dhlwsh metavlhtwn pou tha xrhsimopoihthoun san anagnwristika mhnmhs
    int *A;
    int *B;  //dhlwsh pinakwn akeraiwn (twn pollaplasiastewn kai tou ginomenou tous)
    int *C;
    FILE *fp;   //dhlwsh deikth gia diavasma twn pinakwn apo to arxeio
    int i,j,k,l,m,*rowA,*rowB,*columnA,*columnB,u,v,value,value2;  //dhlwsh metavlhtwn metrhtwn kai diastasewn pinaka
    int *product;//dhlwsh metablhths ginomenou
    arg[0]=(char*)malloc(8*sizeof(char));
    arg[1]=(char*)malloc(2*sizeof(char));
    arg[2]=(char*)malloc(2*sizeof(char));
    arg[3]=(char*)malloc(2*sizeof(char));
    arg[4]=(char*)malloc(8*sizeof(char));
    arg[5]=(char*)malloc(8*sizeof(char));
    arg[6]=(char*)malloc(8*sizeof(char));
    arg[7]=(char*)malloc(8*sizeof(char));
    arg[8]=(char*)malloc(8*sizeof(char));
    if ((fp=fopen("pinakas.txt","r"))==NULL)  //anoigma arxeiou gia diavasma kai taytoxronos elegxos sfalmatos
        printf("Adynamia anagnwshs arxeiou");  //emfanish mhnymatos lathous
    else
    {
        fscanf(fp,"%d %d",&l,&m);     //diavasma apo to arxeio twn duiastasewn tou prwtoy pinaka
        printf("\nl=%d kai m=%d\n",l,m);  //emfanish sthn othonh twn diastasewn tou pinaka
    }
    if ((segrA=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT))<0)  //dhmiourgia koinhs mnhmhs kai elegxos lathous
        printf("Memory fault!");
    else
    {
        rowA=(int*)shmat(segrA,NULL,0);    //antistoixish metablhths me koinh mnhmh
        rowA=(int*)malloc(sizeof(int));   //ekxwrhsh mnhmhs
        *rowA=l;   //apodosh timhs (epanalambanetai h idia diadikasia kathe fora pou theloume na dhmiourghsoume ena neo kommati koinhs mnhmhs)
    }


    if ((segcA=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT))<0)
        printf("Memory fault!");
    else
    {
        columnA=(int*)shmat(segcA,NULL,0);
        columnA=(int*)malloc(sizeof(int));
        *columnA=m;

    }
    if ((segp=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT))<0)
        printf("Memory fault!");
    else
    {
        product=(int*)shmat(segp,NULL,0);
        product=(int*)malloc(sizeof(int));
        *product=0;
    }
    if ((segA=shmget(IPC_PRIVATE,l*m*sizeof(int),IPC_CREAT))<0)
        printf("Memory fault!");
    else
    {
        A=(int*)shmat(segA,NULL,0);
        A=(int*)malloc(l*m*sizeof(int));
    }
    for (i=0;i<l*m;i++)
        fscanf(fp,"%d",&A[i]);      //diavasma tou prwtou pinaka kai ekxwrhsh timwn ston pinaka A

    for (i=0;i<l;i++)
    {
        printf("\n");
        for (j=0;j<m;j++)
            printf("%d  ",A[i*m+j]); //emfanish tou prwtou pinaka
    }



    fscanf(fp,"%d %d",&u,&v);   //diavasma diastasewn tou deyterou pinaka
    printf("\n\nu=%d kai v=%d\n",u,v);
    if ((segB=shmget(IPC_PRIVATE,u*v*sizeof(int),IPC_CREAT))<0)
        printf("Memory fault!");
    else
    {
        B=(int*)shmat(segB,NULL,0);
        B=(int*)malloc(u*v*sizeof(int));

        for (i=0;i<u*v;i++)        //diavasma tou deyterou pinaka
            fscanf(fp,"%d",&B[i]);
    }
    if ((segcB=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT))<0)
        printf("Memory fault!");
    else
    {
        columnB=(int*)shmat(segcB,NULL,0);
        columnB=(int*)malloc(sizeof(int));
        *columnB=v;
    }


    for (i=0;i<u;i++)
    {
        printf("\n");
        for (j=0;j<v;j++)
            printf("%d  ",B[i*v+j]);

    }
    printf("\n");
    printf("\n");

    if ((segC=shmget(IPC_PRIVATE,l*v*sizeof(int),IPC_CREAT))<0)
        printf("Memory fault!");
    else
    {
        C=(int*)shmat(segC,NULL,0);
        C=(int*)malloc(l*v*sizeof(int));
    }
    for (i=0;i<l;i++)

        for (j=0;j<v;j++)

            if ((value=fork())<0)
                printf("Error");
            else if (value==0)
            {
                sprintf(arg[0],"%s","compute");
                sprintf(arg[1],"%d",i);      //metatroph arithmwn se alfarithmhtika
                //gia thn xrhsh tous sthn execvp ws orismata
                sprintf(arg[2],"%d",j);
                sprintf(arg[3],"%d",segA);
                sprintf(arg[4],"%d",segB);
                sprintf(arg[5],"%d",segC);
                sprintf(arg[6],"%d",segrA);
                sprintf(arg[7],"%d",segrB);
                sprintf(arg[8],"%d",segcB);

                execvp("compute",arg,NULL);
                //printf("%d , %d",i,j);
                exit(0);
            }
            else
                wait(0);

    for (i=0;i<l;i++)  //ektypwsh pinaka apotelesmatos (ginomeno pinakwn A B)
    {
        printf("\n");
        for (j=0;j<v;j++)
            printf("%d  ",C[i*v+j]);
    }

    fclose(fp);
    return 0;
}








