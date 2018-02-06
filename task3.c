#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
	pid_t child1, parent1;
	pid_t child2, parent2;
	pid_t child3, parent3;
	int i = 0;
	child1 = fork();
	while(i++<10) if (child!=0) {
		printf("Parent1 process %i \n",(int)getpid());
		sleep(5);
		child2 = fork();
		if (child2==0) {
			printf("Child2 process %i \n",(int)getpid());
			sleep(5);
		} else {
			printf("Parent Child1 process %i \n",(int)getpid());
			sleep(5);
		}
	}		else {
			printf("Child1 process %i \n",(int)getpid());
			sleep(5);
		}
		return 0;
}
