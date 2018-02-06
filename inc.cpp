#include <windows.h>
#include <stdio.h>
#include <iostream>

int q = 0;

DWORD WINAPI Thread1(void* pg) {
	q = q + 1;
	std::cout<<"I am Thread1"<<std::endl;
	return 0;
}
DWORD WINAPI Thread2(void* pg) {
	q = q + 2;
	std::cout<<"I am Thread2"<<std::endl;
	return 0;
}
DWORD WINAPI Thread3(void* pg) {
	q = q + 3;
	std::cout<<"I am Thread3"<<std::endl;
	return 0;
}

int main(void) {
	HANDLE thread1 = CreateThread(
		NULL, // аттрибуты безопасности по умолчанию
		0, // размер стека потока по умолчанию
		Thread1, // функция потока
		NULL, // аргумент функции потока
		0, // флаги создания потока по умолчанию
		NULL); // возврат идентификатора потока
	//Sleep(20);
	HANDLE thread2 = CreateThread(NULL,0,Thread2,NULL,0,NULL);
	//Sleep(20);
	HANDLE thread3 = CreateThread(NULL,0,Thread3,NULL,0,NULL);
	//Sleep(20);
	std::cout<<q<<std::endl;
	return 0;
}