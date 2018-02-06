#include <windows.h>
int a=23;
int f(int b){
return b*b;
}
int g(int b){
return b*b*b;
}

BOOL WINAPI DllMain(
HANDLE hModule,
DWORD dwReason,
LPVOID lpReserved){
return TRUE;
}