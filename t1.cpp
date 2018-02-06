#include <windows.h>
#include <stdio.h>

extern __declspec(dllimport) int a;
int f(int);
int g(int);

int main(){
	while(1) { printf("%i %i %i\n",a,f(3),g(3));}
	return 0;
}