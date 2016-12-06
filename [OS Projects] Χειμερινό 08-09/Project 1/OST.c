#include <stdio.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
main()
{
    struct ls
    {
        int id;
        char dirlist[10];
        char *filename;
    }*files;

    int proc_id; //Process ID
    int proc_priority; //Process Priority
    int proc_sprio_ret_val; //Set Priority Returning Value
    int proc_sys_pwd_ret_val; //System Returning Value for PWD Command
    int proc_sys_mkdir_ret_val; //System Returning Value for MKDIR Command
    int proc_sys_save_ret_val; //System Returning Value for LS Command
    int proc_fork_ret_val; //Fork Returning Value
    FILE *fp; //File Pointer
    int ch,previous_line='\n',total_lines=0; //ch=A temporary variable used in "Finding the Number of Lines" Part
    int garb_int; //Garbage_Integer Value
    char garb_text[50]; //Garbage_String Value
    int *c_array; //Temporary Array for Dir/File Declaration
    int strlen_val; //Temporary Variable for strlength()
    char buffer[100]; //Temporary Array for making filename dynamic
    int i; //Counter
    proc_fork_ret_val=fork(); //Makes Parent, wait until child procces complete
    wait(0);
    if (proc_fork_ret_val==0) //Fork() Successed
    {
        proc_id=getpid(); //Takes the PID of the current running application
        proc_priority=getpriority(PRIO_PROCESS,proc_id); //Takes the NICE Value of the current running application

        if (proc_priority<8) //If NICE Value < 8
        {
            proc_sprio_ret_val=setpriority(PRIO_PROCESS,proc_id,8); //Then make NICE Value = 8
        }

        proc_sys_pwd_ret_val=system("pwd"); //Display Home Directory
        proc_sys_mkdir_ret_val=system("mkdir temp"); //Creates temp Directory
        proc_sys_save_ret_val=system("ls -l -t>temp/contents.txt"); //Creates contents.txt in temp Directory



        proc_fork_ret_val=fork();
        wait(0); //Makes Parent, wait until child proccess complete
        if (proc_fork_ret_val==0) //Fork() Successed
        {
            //-----IS Finding the Number of Lines----------------
            fp=fopen("temp/contents.txt", "r");
            if (fp)
            {
                while ((ch = fgetc(fp))!=EOF) //Read all chars in the file, stops at the END.
                {
                    if ( ch == '\n' )
                    {
                        ++total_lines; // Bump the counter for every newline.
                    }
                    previous_line = ch; // Keep a copy to later test whether...
                }
                fclose(fp);
                if (previous_line!='\n') // ...the last line did not end in a newline.
                {
                    ++total_lines; //If so, add one more to the total.
                }

            }
            else
            {
                printf("ERROR: Cannot open destination file.\n");
            }
            //-----------------------------------------------------

            files=(struct ls *) malloc (total_lines*sizeof(struct ls)); // Is Creating (total_lines)*struct spots.
            c_array=(int *) malloc (total_lines*sizeof(int)); // Is Creating (total_lines)*int array spots.

            fp=fopen("temp/contents.txt", "r"); //Open FIle , READ ONLY
            fscanf(fp,"%s %d\n",&garb_text,&garb_int); //Takes the first line of the file . Example: Total 50
            for (i=0;i<total_lines-1;i++)
            {
                fscanf(fp,"%s %d %s %s %d %d-%d-%d %d:%d %s\n",&files[i].dirlist,&garb_int,&garb_text,&garb_text,&garb_int,&garb_int,&garb_int,&garb_int,&garb_int,&garb_int,&buffer); //Scanning each line for the needed information, everything else drop it in garb_values.
                strlen_val=strlen(buffer); //The Length of String
                files[i].filename=(char*)malloc(strlen_val*sizeof(char)); //Dynamic char array
                strcpy(files[i].filename,buffer); //Copy-Paste from Buffer --> Files.filename
            }
            fclose(fp);	//Close File




            for (i=0;i<total_lines-1;i++) //Tota_lines-1 coz the first line of file output its "total xx"
            {
                c_array[i]=files[i].dirlist[0];
                if (c_array[i]==100) //That means its always the letter "d" ||Source: ANSI Character Table||
                {
                    files[i].id=0; //Its a directory
                }
                else if (c_array[i]==45) //Always the char "-"
                {
                    files[i].id=1; //Its a file
                }
                else
                {
                    files[i].id=9; //Its something , we dont care what is it
                }

            }
            printf("\n\n\n");
            printf("Directories: \n");
            for (i=0;i<total_lines-1;i++) 				//
            {
                if (files[i].id==0) 				//Printing Directories
                {
                    printf("%s\n",files[i].filename);	//
                }
            }
            printf("\n\n\n");
            printf("Files: \n");						//
            for (i=0;i<total_lines-1;i++) 				//
            {
                if (files[i].id==1) 				//Printing Files
                {
                    printf("%s\n",files[i].filename);	//
                }
            }
        }
    }
    printf("\n");
}
