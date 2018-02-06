#include <windows.h>
#include <stdio.h>
#include <dos.h>

typedef int (*fun)(int);

int main(){
	while(1) {
	HINSTANCE hInst;
	fun pf,pg;
	int* pa;
	hInst=LoadLibrary("td2.dll");
	printf("Library loaded\n");
	pa=(int*)GetProcAddress(hInst, "a");
	pf=(fun)GetProcAddress(hInst, "f");
	pg=(fun)GetProcAddress(hInst, "g");
	printf("%i %i %i\n",*pa,pf(3),pg(3));
	FreeLibrary(hInst);
	Sleep(10000);
	printf("Library unloaded\n");
	Sleep(10000);
	printf("\n");
	}
	return 0;
}