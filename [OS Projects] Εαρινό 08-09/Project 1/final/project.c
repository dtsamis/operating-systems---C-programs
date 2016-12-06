//Dhlwsh vivliothikwn

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


//dhlwsh metavlhtwn
FILE *keyfile;
FILE *simpletext;
FILE *encodedtext;
char *keyword,*text,*coded;
int n,i,value;


//arxh kiriou programmatos

int main(int argc, char *argv[])
{
    if ((value=fork())<0)   //dhmiourgia thygatrikhs diergasias kai parallhlos elegxos gia adynamia ekteleshs fork.
        printf("Cannot execute fork");
    else if (value>0)        //ekteleitai h patrikh diergasia
    {
        wait(0);             //anamonh termatismou ths thygatrikhs diergasias
        if ((keyfile=fopen(argv[1],"r"))==NULL)  //anoigma arxeiou pou periexei to kleidi. parallhla ginetai elegxos an dhmiourghthike to stream.
            printf("Cannot open file");                //emfanish mhnymatos lathous
        else
        {//arxh anagnwshs arxeiou kleidiou
            fscanf(keyfile,"%d",&n);         //anagnwsh prwtou xarakthra tou arxeiou (arithmos grammatwn ths lexhs kleidi)       
            keyword= (char*) malloc((n+1)*sizeof(char));         //ekxvrhsh mnhmhs analoga me to plhthos twn grammatwn
            i=0;
            while (!feof(keyfile))           //elegxos an exei ftasei sto telos tou to arxeio

            {
                fscanf(keyfile,"%c",&keyword[i]);    //antigrafh toy arxeiou keimenou se pinaka alpharithmhtiko
                i++;
            }
        }
        
        printf("Keyword=%s\n",keyword);          //Emfanish toy kleidiou
        
	//arxh anagnwshs arxeiou keimenou pros kwdikopoihsh
        if ((simpletext=fopen(argv[2],"r"))==NULL)     //anoigma arxeiou pou periexei to keimeno gia kwdikopoihsh. parallhla ginetai elegxos an dhmiourghthike to stream.
            printf("Cannot open file");		//emfanish mhnymatos lathous
        else
        {
            text= (char*) malloc(sizeof(char));//arxikh ekxwrhsh mnhmhs megethous enos xarakthra
            i=0;
            while (!feof(simpletext))  //elegxos an exei ftasei sto telos tou to arxeio

            {
                fscanf(simpletext,"%c",&text[i]);
                text=realloc(text,(i+1)*sizeof(char));    //epanekxwrhsh mnhmhs kathe fora ayxanetai kata to megethos enos  xarakthra
                i++;
            }
        
            printf("Text to be coded as follows:\n %s\n",text);  //emfanish keimenou pros kwdikopoihshs
}
	    if ((encodedtext=fopen(argv[3],"w"))==NULL)		//anoigma arxeiou gia eggrafh kwdikopoihmenou keimenou. parallhla ginetai elegxos an dhmiourghthike to stream.
            printf("Cannot open file");		//emfanish mhnymatos lathous
            else
            {
	       coded= (char*) malloc(sizeof(char));  		//arxikh ekxwrhsh mnhmhs megethous enos xarakthra

              for (i=0;i<strlen(text);i++)     //antigrafh olou tou keimenou opows einai sto arxeio exodou
              {
                coded[i]=text[i];

//kwdikopoihsh mono tvn latinikwn xarakthrwn

                if ((text[i]>='A')&&(text[i]<='Z')) 		//elegxos gia kefalaious xarakthres
                    coded[i]=((text[i]-'A'+keyword[i%n]-'A')%26)+'A';  //eyresh theshs xarakthrwn sto diasthma [A-Z] kai ektelesh vinegere 
                if ((text[i]>='a')&&(text[i]<='z')) 	//elegxos gia pezous xarakthres
                    coded[i]=((text[i]-'a'+keyword[i%n]-'A')%26)+'a';  	//prostithetai to 'a' giati o xarakthras einai pezos.
              }
              fprintf(encodedtext,"%s",coded);             //eggrafh tou kwdikopoihmenou keimenou sto arxeio exodou.

           }
     }
    else
   //ektelesh thygatrikhs diergasias
   { printf("Emfanizontai oi diergasies pou anhkoun sto idio group\n"); 	//emfanish mhnymatos
        system("mkdir result \n ps -A>result/result.txt \n ps -g 0"); 		//ektelesh entolwn grammhs entolwn mesa apo to programma. emfanish diergasiwn toy idiou group kai eggrafh olwn tvn diergasiwn sto arxeio exodou mesa sto neodhmioyrghthenta katalogo.
        exit(0); 			//dhlwsh termatismou ths thygatrikhs
    }
    return 0;
}
