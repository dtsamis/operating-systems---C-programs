#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

	main(int argc, char *argv[]){ 

	int segment_id; //Shared Memory ID	
	int fork_returned_value;  	
	int i,n0=0,n1=1,naux; //Counter, Fib(n-1), Fib(n-2), Fib_Total
	int user_input_value; //The casted int from argv
	char *shared_memory; //Attached Shared Memory
	int string_length,total_chars=0;//Counters. Counting the total chars, they are needed to realloc.		
	
	char *srray; //Dynamic Array. All Fibo_numbers are added here.
	
      	char buffer2[1000]; //Static Array, helps to count the chars.
	

	segment_id= shmget(IPC_PRIVATE,4.096,S_IRUSR|S_IWUSR); //Return's the ID of Shared Memory     
	shared_memory=(char *)shmat(segment_id,NULL,0); //Return's the ID of Attached Shared Memory
	
	user_input_value=atoi(argv[1]);	//Casts the String argv, to int.

	srray=(char*)malloc(sizeof(char)*0); //Initiation of srray with NULL chars.	
	fork_returned_value=fork();	//Fork
	wait(0);			//Parent waits the child
		if (fork_returned_value==0){ //<---- CHILD	
			if(user_input_value==0){
				naux=0; //Fibo_total = 0
				goto case_0; //go to casting mechanism(ignores the loop)-									
			} //								|
  			for(i=0;i<user_input_value;i++){//				|
    				naux = n1;   // }					|
    				n1 = n0 + n1;// }==> Fibonacci				|
    				n0 = naux;   // }					|
				case_0:	     // goto continue from here	 <-------------_|     
				sprintf(buffer2,"%d ",naux); //Integer to String CASTING plus adds an "backspace" char		
				string_length=strlen(buffer2); //Count string's characters
				total_chars+=string_length; //	total_chars=total_chars+everything new char (taken from strlen)			
				srray=realloc(srray,sizeof(char)*total_chars); //adds more memory (array spots) upon demand
				strcat(srray,buffer2); //"ADDS" two strings together (In the end we will have one "big" string)		
			}
  			sprintf(shared_memory,"%s",srray); //puts the "big" string we added before into our shared memory 
			shmdt(shared_memory); //deattach memory		
		exit(0); //Successfull exit	
		}
		else if(fork_returned_value>0){ //<----PARENT
     			
		printf("%s\n",shared_memory); //Print whatever is in shared memory
		shmdt(shared_memory); //deattach memory			
		exit(0); //Successfull exit
		}
		else{ //<---ERROR     
     		printf("fork error!\n"); 
     		exit(1); //Unsuccessfull exit  
		}
	free(shared_memory); //free ^^
	}
