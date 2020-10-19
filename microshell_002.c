#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>





int ms_cd (char **args) {


  if (args[1] == NULL) {

    chdir("/home/students/s452483");

  } else {

    if (chdir(args[1]) != 0) {

        perror(args[1]);

    }
  }

  return 1;

}



int ms_help () {

  int i;

  printf("\n\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");


  printf("\n\n\n                                                                          Welcome to Yurii Kulyzhskyi`s  microshell!!\n\n");

  printf("\n                                                                    A home directory is /home/students/s452483\n\n");

  printf("                                                                     The following commands are built in:\n");

  printf("\n\n");




  printf("                                            cd  -->  changes current directory if an argument is passed, otherwise goes back to a home directory");
  printf("\n                                            help  -->  shows the information about a microshell and currently available built in functions");
  printf("\n                                            exit  -->  exits a microshell");




  printf("\n\n---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");


  printf("\n\n");


  return 1;

}



int ms_exit () {

  return 0;

}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ms_launch(char **args) {

  pid_t pid, wpid;
  int check;

  pid = fork();
  if (pid == 0) {


    if (execvp(args[0], args) == -1) {


        perror(args[0]);


    }

    exit(EXIT_FAILURE);

  } else if (pid < 0) {

    perror("ms");

  } else {



      do {

      wpid = waitpid(pid, &check, WUNTRACED);

      } while (!WIFEXITED(check) && !WIFSIGNALED(check));

  }

  return 1;

}




/////////////////////////////////////////////////////////////////

int ms_exec (char **args) {


    int i;



  if (args[0] == NULL) {


      return 1;

  }



      if(strcmp(args[0], "cd") == 0) {

          return ms_cd(args);

      }

        if(strcmp(args[0], "help") == 0) {

           return ms_help(args);

       }

        if (strcmp(args[0], "exit") == 0) {

            return ms_exit(args);

                }



  return ms_launch(args);

}


/////////////////////////////////////////////////////////////


char **get_parce () {



      char  *input;

      fgets(input,256,stdin);



    char **tokens = malloc(2 * sizeof(char*));

    char* token = strtok(input, " \n");


    int p = 0;
    while (token != NULL) {

        tokens[p] = token;
        p++;

        token = strtok(NULL, " \n");
    }




    tokens[p] = NULL;

    return tokens;

}


////////////////////////////////////////////////////////////

void ms_loop (void) {


    char **args;
    int check = 1;


  while (check) {

    char cwd[PATH_MAX];
    getcwd(cwd,sizeof(cwd));
    printf ("[%s]~$ ", cwd);




    args = get_parce();
    check = ms_exec(args);



    free(args);

  }

}




//////////////////////////////////////////////////////////////

int main ( ) {

  ms_loop();


  return EXIT_SUCCESS;

}
