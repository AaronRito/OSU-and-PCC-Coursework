#include <signal.h> /* signal */
#include <sys/wait.h> /* waitpid */
#include "rito_server.h"

void sig_chld(int signo)
{
	 pid_t pid;
	 int stat;
	 while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
	 printf("child %d terminated\n", pid);
	 return;
 }
 