#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

main(){
     pid_t pid;
     char *const parmList[] = {"./of", "text", NULL};

     if ((pid = fork()) == -1)
        perror("fork error");
     else if (pid == 0) {
        execvp("./of", parmList);
     }
     wait(0);
  }
