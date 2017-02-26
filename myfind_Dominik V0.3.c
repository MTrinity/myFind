/**
 * @file MyFind.c
 * myfind
 * Beispiel 1
 *
 * @author Margot Hanserl <margot.hanserl@technikum-wien.at>
 * @author Jasna Ajdinovic <ic16b067@technikum-wien.at>
 * @author Dominik Francan <ic16b006@technikum-wien.at>
 * @date 2017/02/22
 *
 * @version $Revision: 0 $
 *
 * @todo Test it more seriously and more complete.
 * @todo Review it for missing error checks.
 * @todo Review it and check the source against the rules at
 *       https://cis.technikum-wien.at/documents/bic/2/bes/semesterplan/lu/c-rules.html
 *
 *
 * URL: $HeadURL$
 *
 * Last Modified: $Author: Margot $
 */


/*
 * -------------------------------------------------------------- includes --
 */

#include <stdio.h>
#include <stdlib.h> 	// EXIT_SUCCESS, EXIT_FAILURE
#include <string.h>
#include <dirent.h>
#include <errno.h>

// Required Include Files for lstat 
#include <unistd.h>
#include <sys/stat.h> 	// required for stat 
#include <sys/types.h>


/*
 * --------------------------------------------------------------- defines --
 */
#define DEBUG


/*
 * -------------------------------------------------------------- typedefs --
 */
typedef enum {
    SUCCESS = 0,         			//!< Success, no Error occured
    ERROR = 1,         				//!< stop and do not continue with the next parameter
    
	} ERROR_CODES;
 
 
/*
 * --------------------------------------------------------------- globals --
 */

/*
 * ------------------------------------------------------------- functions --
 */

static void do_file(const char * file_name, const char * const * parms);
static void do_dir(const char * dir_name, const char * const * parms);
static int do_print(const char * dir_name);
static int check_params(char ** name, int count);
static void usage(const char * dir_name, int error);

int main(int argc, char *argv[])
{
	int error = 0;
	const char * pname = NULL;
	const char * aname = NULL;
	int i = 0;

	pname = argv[0];
	
	//usage(name,error);
	error = check_params(argv, argc);
	if(error != 0)
		usage(pname, error);
	
	return 0;

}
static void do_file(const char * file_name, const char * const * parms)
{
}
static void do_dir(const char * dir_name, const char * const * parms)
{
}
static int do_print(const char * dir_name)
{
	DIR *dir;
	struct dirent *sd;
	char *dir2 = malloc(120*sizeof(char));
    char *dirt = malloc(120*sizeof(char));
    char *dirt2 = malloc(120*sizeof(char));
	int length;
	int error; 

    dir = opendir(dir_name);
    
	printf("%s\n",dir_name);
    while((sd = readdir(dir)) != NULL)
    {
      if(sd->d_type == DT_DIR)
	  {
	    dir2  = sd->d_name;
	    if((strcmp(dir2,".") == 0) || (strcmp(dir2,"..") == 0))
		continue;
	    
	    strcpy(dirt,dir_name);
	    length = strlen(dirt);
	    if(dirt[length-1] != 47)
	    {
		  strcat(dirt,"/");
		  strcat(dirt,dir2);
	    }
	    else
		strcat(dirt,dir2);
     	do_print(dirt);//Rekursion
	  }
      else
	  {
	    strcpy(dirt,dir_name);
	    length = strlen(dirt);
	    if(dirt[length-1] != 47)
	    {
		  strcat(dirt,"/");
	    }
        printf("%s%s\n",dirt,sd->d_name);
	  }
    }
    closedir(dir);
	return 1;
}
static int check_params(char ** name, int count)
{
	//const char ** pname = malloc(120*sizeof(char));
	DIR *dir;
	int error = 0;
	
	//printf("%s %d\n",*name,count);
	if((*(name+1) == NULL) && (count == 1))//0 Parameter
	{
		//printf("0 Parameter\n");
		 do_print(".");
	}
	else if(strcmp(*(name+1),"-print") == 0)// 1 Parameter = -print
	{
		//printf("1 Parameter + print\n");
		do_print(".");
	}
	else
	{
		dir = opendir(*(name+1));
		if(dir == NULL) 
		{
			error = errno;
			closedir(dir);
			if ((error == EACCES)||(error == ELOOP)||
			    (error == ENAMETOOLONG)||
				(error == ENOENT)||
				(error == ENOTDIR)||
				(error == ENFILE)||
				(error == EMFILE))
				return error;
			
		}
		if((dir != NULL) && (count == 2))//richtiger Pfad
		{
			//printf("Richtiger pfad\n");
			closedir(dir);
			do_print(*(name+1));
		}
		else if((dir != NULL) && (strcmp(*(name+2),"-print") == 0))//richtiger Pfad + -print
		{
			//printf("Richtiger pfad + print\n");
			closedir(dir);
			do_print(*(name+1));
		}
		closedir(dir);
	}
	return 0;
}
static void usage(const char * dir_name, int error)
{
	printf("%s %s\n",dir_name,strerror(error));
}