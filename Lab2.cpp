#include <windows.h>
#include <stdlib.h>
#include <iostream>

#define DIV 1024
#define WIDTH 7

using namespace std;

int main() {
	char path1[100];
	char path2[100];
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);
	GetSystemDirectory(path1,100);
	GetTempPath(100,path2);
	char *divisor = "K";
	MEMORYSTATUS stat;
	GlobalMemoryStatus (&stat);

	printf ("The MemoryStatus structure is %ld bytes long.\n", stat.dwLength);
  	printf ("It should be %d.\n", sizeof (stat));
	printf ("%ld percent of memory is in use.\n", stat.dwMemoryLoad);
	printf ("There are %*ld total %sbytes of physical memory.\n", WIDTH, stat.dwTotalPhys/DIV, divisor);
  	printf ("There are %*ld free %sbytes of physical memory.\n", WIDTH, stat.dwAvailPhys/DIV, divisor);
  	printf ("There are %*ld total %sbytes of paging file.\n", WIDTH, stat.dwTotalPageFile/DIV, divisor);
  	printf ("There are %*ld free %sbytes of paging file.\n", WIDTH, stat.dwAvailPageFile/DIV, divisor);
  	printf ("There are %*lx total %sbytes of virtual memory.\n", WIDTH, stat.dwTotalVirtual/DIV, divisor);
  	printf ("There are %*lx free %sbytes of virtual memory.\n", WIDTH, stat.dwAvailVirtual/DIV, divisor);
	cout<<"GetSystemDirectory - "<<path1<<endl;
	cout<<"GetTempPath - "<<path2<<endl;
	cout<<"Number of processors "<<siSysInfo.dwNumberOfProcessors<<endl;
	cout<<"wProcessorArchitecture "<<siSysInfo.wProcessorArchitecture<<endl;
	cout<<"dwProcessorType "<<siSysInfo.dwProcessorType<<endl;
	cout<<"lpMinimumApplicationAddress "<<siSysInfo.lpMinimumApplicationAddress<<endl;
	cout<<"lpMaximumApplicationAddress "<<siSysInfo.lpMaximumApplicationAddress<<endl;

	system("PAUSE");
	return 0;
}