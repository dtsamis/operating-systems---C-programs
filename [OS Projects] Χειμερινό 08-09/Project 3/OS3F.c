#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int s;
void *func(void *syn);
int main(int argc, char* argv[])
{
pthread_t nhma_1, nhma_2;/*Dhlosh ton 2 nhmaton */
pthread_attr_t attr;/*Idiotites nhmatos*/
if (argc!=2) /*Elegxos gia ton an exei ginei sosth eisagogh ton argc*/
   {
    printf("Error!!Lathos parametroi 3anadose\n");
   return -1;   
 }
pthread_attr_init(&attr);/*Default idiotites*/
pthread_create(&nhma_1,&attr,func,argv[1]);/*Creation of fist thread*/
pthread_create(&nhma_2,&attr,func,argv[1]);/*Creation of second thread*/
pthread_join(nhma_1,NULL);/*O 1os gonios perimenei na oloklhrothei to "paidi" tou*/
pthread_join(nhma_2,NULL);/*O 2os gonios perimenei na oloklhrothei to "paidi" tou*/
printf("\nTo athroisma einai : %d\n",s);/*Emfanisi katholikis metablitis*/
exit(0);
return 0;
} 
/*Synartisi gia thn kataxosisi tou string kai gia thn emfanisi tou*/
void *func(void* syn)
{
int i;
char *string;
string = (char *)syn;
for(i=0; i<30; i++)
{  
 printf("%d. %s\n ",i+1, syn);
 s=s+1;/*Plithos emfaniseon tou string!*/
}
pthread_exit(0);/*exit*/
}
