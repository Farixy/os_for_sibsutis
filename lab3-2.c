#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	pid_t child_pid, parent_pid;
	double s = 0.0;
	child_pid = fork();
	if (child_pid!=0) {
		s+=3.154;
		fprintf(stdout,"CHILD: % s=%g & s=%u\n",(int)getpid(),s,&s);
	} else {
		s+=2.72;
		fprintf(stdout,"PARENT: %i s=%g & s=%u\n",(int)getpid(),s,&s);
	}
	return 0;
}