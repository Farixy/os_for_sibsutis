#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <time.h>

int const M = 100;
int const N = 8;

void thread1(void *); void thread2(void *); void thread3(void *); void thread4(void *);
void thread5(void *); void thread6(void *); void thread7(void *); void thread8(void *);

CRITICAL_SECTION cs;

int sh=0;  
int flag[N];

int main(){
	SYSTEMTIME st1,st2;
        int minute1, minute2;
	int second1, second2;
	for (int i = 0; i < N; i++) flag[i]=1;
	InitializeCriticalSection( &cs );
	clock_t start, finish;
	GetLocalTime(&st1);
	minute1=st1.wMinute;
	second1=st1.wSecond;
	start = clock(); //время начала выполнения программы 
	_beginthread(thread1,0,NULL); _beginthread(thread2,0,NULL); _beginthread(thread3,0,NULL); _beginthread(thread4,0,NULL);
	_beginthread(thread5,0,NULL); _beginthread(thread6,0,NULL); _beginthread(thread7,0,NULL); _beginthread(thread8,0,NULL);	
	while(flag[0] || flag[1] || flag[2] || flag[3] || flag[4] || flag[5] || flag[6] || flag[7]);
	printf("%i\n",sh);
	DeleteCriticalSection( &cs );
	finish = clock(); //время окончания выполнения программы 
	GetLocalTime(&st2);
	minute2=st2.wMinute;
	second2=st2.wSecond;
	printf("%f\n",(float)(finish - start) / CLOCKS_PER_SEC);  //время выполнения программы
	printf("%i - %i : %i - %i",minute1,second1,minute2,second2);
	return 0;
}

void thread1(void * ignored){
	int i=0;
	for(; i < M; i++){
	EnterCriticalSection( &cs );
	sh++; //критическая область
	LeaveCriticalSection( &cs );
	Sleep(1); //некритическая область
	}
	flag[0]=0;
}
void thread2(void * ignored){
	int i=0;
	for(;i<M;i++){
	EnterCriticalSection( &cs );
	sh++; //критическая область
	LeaveCriticalSection( &cs );
	Sleep(1); //Sleep(100); //некритическая область
	}
	flag[1]=0;
}
void thread3(void * ignored){
	int i=0;
	for(;i<M;i++){
	EnterCriticalSection( &cs );
	sh++; //критическая область
	LeaveCriticalSection( &cs );
	Sleep(1); //Sleep(100); //некритическая область
	}
	flag[2]=0;
}

void thread4(void * ignored){
	int i=0;
	for(;i<M;i++){
	EnterCriticalSection( &cs );
	sh++; //критическая область
	LeaveCriticalSection( &cs );
	Sleep(1); //Sleep(100); //некритическая область
	}
	flag[3]=0;
}

void thread5(void * ignored){
	int i=0;
	for(;i<M;i++){
	EnterCriticalSection( &cs );
	sh++; //критическая область
	LeaveCriticalSection( &cs );
	Sleep(1); //Sleep(100); //некритическая область
	}
	flag[4]=0;
}

void thread6(void * ignored){
	int i=0;
	for(;i<M;i++){
	EnterCriticalSection( &cs );
	sh++; //критическая область
	LeaveCriticalSection( &cs );
	Sleep(1); //Sleep(100); //некритическая область
	}
	flag[5]=0;
}

void thread7(void * ignored){
	int i=0;
	for(;i<M;i++){
	EnterCriticalSection( &cs );
	sh++; //критическая область
	LeaveCriticalSection( &cs );
	Sleep(1); //Sleep(100); //некритическая область
	}
	flag[6]=0;
}

void thread8(void * ignored){
	int i=0;
	for(;i<M;i++){
	EnterCriticalSection( &cs );
	sh++; //критическая область
	LeaveCriticalSection( &cs );
	Sleep(1); //Sleep(100); //некритическая область
	}
	flag[7]=0;
}

