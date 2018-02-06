#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//Roditelskiy process prodoljaet rabotat'

int main() {
	pid_t child_pid, parent_pid;
	int i = 0;
	printf("Parent_pid = %i\n", parent_pid=(int)getpid());
	child_pid = fork();
	while(i++<10) if (child_pid==0) {
		printf("Child process = %i\n",getpid());
		sleep(3);
	} else {
		printf("Parent process = %i\n",getpid());
		sleep(3);
	}
	return 0;
}