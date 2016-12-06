/**********************************
 *        OMADA EGRASIAS          *
 *  TZAKOS SPIRIDON      AM 1953  *
 *  KAKOURAS NIKOLAOS    AM 1922  *
 *                                *
 **********************************/
//eigagwgh aparaithtwn bibliothikwn
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    int value;     //Oi times pou pliktrologi8ikan apo8ikeuontai sto pedio value
    int flag;      //Provolh tou pinaka w me to pedio flag

}matrix;


void* function1(int *x)     // Synarthsh prwtwn nhmatwn
{   //Thetei 1 se kathe thesh tou pinaka "w"
    *x=1;
    pthread_exit(0);
}


void* function2(int array[2] )		   //Ylopoioume enan voithitikos pinakas 2 thesewn
{
    pthread_mutex_lock(&mutex);        //Kleidwma tis eisodou sthn CPU
    if (array[0]<array[1])		       //Ginontai sigriseis twn timwn "xi" kai "xj"
    {
        array[0]=0;			           //Orizei thn timh 0 sthn thesh 0 tou voithitikou pinaka
    }
    else  array[0]=1;		           //Orizei thn timh 1 sthn thesh 0 tou voithitikou pinaka

    pthread_mutex_unlock(&mutex);	   //Xekleidwma ths eisodou sthn CPU
    pthread_exit(0);
}


void* function3(int  x[2])
{
    if (x[0]==1)	//Elegxos timhs tou w[i]
    printf("\n*Megalyteros ari8mos = %d\n",x[1]);    //Emfanish tou max arithmou
    pthread_exit(0);
}

//kyrio programma
int main(int argc, char *argv[])
{
    pthread_t tid;
    pthread_attr_t attr;

    int harray[2];				   //Orizoume voithitiko pinaka harray gia na eisagoume metavlhtes stis synarthseis twn nhmatwn
    matrix numbers[argc-1];        //Orizoume pinaka domwn typou matrix gia tin kataxwrhsh timwn kai flag 0 h 1
    int i,j,k;                     //Pli8os twn threads
    k=0;
    for (i=1;i<argc;i++)
    {
        numbers[i-1].value=atoi(argv[i]);     //Allagh orismatwn se arithmous kai apothikeysh sto pedio value
    }
    printf("\n*Pli8os eisagwmenwn timwn = %d",argc-1);		//Emfanisi plithous arithmwn

    //Emfanish eisagomenwn timwn
    printf("\n*Eisagomenes times      x = ");
    for (i=0;i<argc-1;i++)
        printf("%d ",numbers[i].value);

    for (i=0;i<argc-1;i++)
    {
        pthread_attr_init(&attr);                      //Arxikopoihsh parametrwn tou nhmatos
        pthread_create(&tid,&attr,(void*)function1,&numbers[i].flag);	//Dhmiourgia nhmatos kai ektelesh synarthshs function1
        pthread_join(tid,NULL);					 //Anamonh ths main gia thn peratwsh tou nhmatos
    }

    printf("\n*Meta tin arxikopoihsh  w = ");	     //Emfanisi tou pinaka W meta thn arxikopoihsh tou
    for (i=0;i<argc-1;i++)
        printf("%d ",numbers[i].flag);
	printf("\n");
    for (i=0;i<argc-1;i++)
        for (j=0;j<argc-1;j++)
        {
            k++;
            harray[0]=numbers[i].value;          //Perasma twn dyo timwn ston pinaka harray gia xrhsh tous apo tis synarthseis
            harray[1]=numbers[j].value;	    	 //Ektelesh deyterwn nhmatwn

            pthread_attr_init(&attr);
            pthread_create(&tid,&attr,(void*)function2,&harray);
            pthread_join(tid,NULL);

            numbers[i].flag=harray[0];   		//Ekxwrhsh tis timhs pou epistrefetai san timh tou W[i]
            if (numbers[i].flag==0)   //Elegxos timhs W[i] kai diakoph sygkrisewn gia ton i arithmo
            {
                printf("\n- Thread T(%d,%d) sigrine tous ari8mous %d kai %d kai brike ton ari8mo %d<=%d",i,j,numbers[i].value,numbers[j].value,numbers[i].value,numbers[j].value);
                break;
            }
        }
    printf("\n\n*Ari8mos twn threads = %d",k);
    //Emfanish timwn W meta tis sygkriseis
    printf("\n*Meta to bhma 2 to w = ");
    for (i=0;i<argc-1;i++)
        printf("%d",numbers[i].flag);

    for (i=0;i<argc-1;i++)
    {
        harray[1]=numbers[i].value;          //Ekxwrhsh timwn ston voithitiko pinaka harray
        harray[0]=numbers[i].flag;
        pthread_attr_init(&attr);
        pthread_create(&tid,&attr,(void*)function3,&harray);          //Ektelesh tritwn nhmatwn
        pthread_join(tid,NULL);
    }
    return 0;
}





