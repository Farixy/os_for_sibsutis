#include <windows.h>
#include <stdio.h>
#include <process.h>
#include <time.h>
#include <iostream>

// http://precious-cpp.blogspot.ru/2010/10/2-n.html
// Сделать для N потоков
int const N = 8;
int const M = 100;

void thread1(void *); void thread2(void *); void thread3(void *); void thread4(void *);
void thread5(void *); void thread6(void *); void thread7(void *); void thread8(void *);

void EnterCriticalRegion(int threadId);
void LeaveCriticalRegion(int threadId);

int sh=0;  
int flag[N]; 
int turn_last[N];  
int stage[N+1];

int main(){
	SYSTEMTIME st1,st2;
	
        int minute1, minute2;
	int second1, second2;
	clock_t start, finish;
	for (int i = 0; i < N; i++) flag[i] = 1;
	GetLocalTime(&st1);
	minute1=st1.wMinute;
	second1=st1.wSecond;
	start = clock(); //время начала выполнения программы 
	_beginthread(thread1,0,NULL); _beginthread(thread2,0,NULL); _beginthread(thread3,0,NULL); 
	_beginthread(thread4,0,NULL); 
	_beginthread(thread5,0,NULL); _beginthread(thread6,0,NULL); _beginthread(thread7,0,NULL); _beginthread(thread8,0,NULL);	
	while(flag[0] || flag[1] || flag[2] || flag[3] || flag[4] || flag[5] || flag[6] || flag[7]);
	//while(flag[0] || flag[1] || flag[2]);
	printf("%i\n",sh);
	finish = clock(); //время окончания выполнения программы 
	GetLocalTime(&st2);
	minute2=st2.wMinute;
	second2=st2.wSecond;
	printf("%f\n",(float)(finish - start) / CLOCKS_PER_SEC);  //время выполнения программы
	printf("%i - %i : %i - %i",minute1,second1,minute2,second2);
	return 0;
}

void EnterCriticalRegion(int threadId) {
	for (int i = 1; i <= N - 1; i++) { // перебор стадий
	stage[threadId] = i; // номер стадии в которой находится процесс threadId
	turn_last[i] = threadId; // зашедший последним в стадию под номером i
	//std::cout<<std::endl<<"Stage = "<<i<<" threadId = "<<threadId<<" stage threadId = "<<stage[threadId]<<" Last threadId = "<<turn_last[i]<<std::endl;;
		for (int j = 1; j <= N; j++) { // опрос остальных процессов
		if (j == threadId) continue;
		while (stage[j] >= i && turn_last[i] == threadId); // wait
		}
	}
}
void LeaveCriticalRegion(int threadId) {
	stage[threadId] = 0; // Сброс флага текущего потока
	//std::cout<<std::endl<<"I leave = "<<threadId<<std::endl;
}
void thread1(void * ignored){
	//std::cout<<std::endl<<"thread1 starting"<<std::endl;
	int i=0;
	for(; i < M; i++){
	EnterCriticalRegion(1);
	sh++; //критическая область
	LeaveCriticalRegion(1);
	Sleep(1); //некритическая область
	}
	//std::cout<<std::endl<<"thread1 finishing"<<std::endl;
	flag[0]=0;
}
void thread2(void * ignored){
	//std::cout<<std::endl<<"thread2 starting"<<std::endl;
	int i=0;
	for(;i<M;i++){
	EnterCriticalRegion(2);
	sh++; //критическая область
	LeaveCriticalRegion(2);
	Sleep(1); //Sleep(100); //некритическая область
	}
	//std::cout<<std::endl<<"thread2 finishing"<<std::endl;
	flag[1]=0;
}
void thread3(void * ignored){
	//std::cout<<std::endl<<"thread3 starting"<<std::endl;
	int i=0;
	for(;i<M;i++){
	EnterCriticalRegion(3);
	sh++; //критическая область
	LeaveCriticalRegion(3);
	Sleep(1); //Sleep(100); //некритическая область
	}
	//std::cout<<std::endl<<"thread3 finishing"<<std::endl;
	flag[2]=0;
}

void thread4(void * ignored){
	int i=0;
	for(;i<M;i++){
	EnterCriticalRegion(4);
	sh++; //критическая область
	LeaveCriticalRegion(4);
	Sleep(1); //Sleep(100); //некритическая область
	}
	flag[3]=0;
}

void thread5(void * ignored){
	int i=0;
	for(;i<M;i++){
	EnterCriticalRegion(5);
	sh++; //критическая область
	LeaveCriticalRegion(5);
	Sleep(1); //Sleep(100); //некритическая область
	}
	flag[4]=0;
}

void thread6(void * ignored){
	int i=0;
	for(;i<M;i++){
	EnterCriticalRegion(6);
	sh++; //критическая область
	LeaveCriticalRegion(6);
	Sleep(1); //Sleep(100); //некритическая область
	}
	flag[5]=0;
}

void thread7(void * ignored){
	int i=0;
	for(;i<M;i++){
	EnterCriticalRegion(7);
	sh++; //критическая область
	LeaveCriticalRegion(7);
	Sleep(1); //Sleep(100); //некритическая область
	}
	flag[6]=0;
}

void thread8(void * ignored){
	int i=0;
	for(;i<M;i++){
	EnterCriticalRegion(8);
	sh++; //критическая область
	LeaveCriticalRegion(8);
	Sleep(1); //Sleep(100); //некритическая область
	}
	flag[7]=0;
}

