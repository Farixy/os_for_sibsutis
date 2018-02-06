#include <windows.h>
#include <stdio.h>
#include <psapi.h>
#include <string.h>
#define MAX_PROCESSES 1024 

DWORD FindProcess(__in_z LPCTSTR lpcszFileName) 
{ 
  	LPDWORD lpdwProcessIds; 
  	LPTSTR  lpszBaseName; 
  	HANDLE  hProcess; 
  	DWORD   i, cdwProcesses, dwProcessId = 0; 
	lpdwProcessIds = (LPDWORD)HeapAlloc(GetProcessHeap(), 0, MAX_PROCESSES*sizeof(DWORD)); 
  	if (lpdwProcessIds != NULL)  { 
        if (EnumProcesses(lpdwProcessIds, MAX_PROCESSES*sizeof(DWORD), &cdwProcesses)) { 
      	lpszBaseName = (LPTSTR)HeapAlloc(GetProcessHeap(), 0, MAX_PATH*sizeof(TCHAR)); 
      	if (lpszBaseName != NULL) { 
        cdwProcesses /= sizeof(DWORD); 
        for (i = 0; i < cdwProcesses; i++) { 
          hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, lpdwProcessIds[i]); 
          if (hProcess != NULL) { 
            if (GetModuleBaseName(hProcess, NULL, lpszBaseName, MAX_PATH) > 0) { 
              if (!lstrcmpi(lpszBaseName, lpcszFileName)) { 
                dwProcessId = lpdwProcessIds[i]; 
                CloseHandle(hProcess); 
                break; 
              } 
            } 
            CloseHandle(hProcess); 
          } 
        } 
        HeapFree(GetProcessHeap(), 0, (LPVOID)lpszBaseName); 
      	} 
    	} 
    	HeapFree(GetProcessHeap(), 0, (LPVOID)lpdwProcessIds); 
  	} 
  	return dwProcessId; 
}


int main(){
	while(1){
	DWORD pID;
	HANDLE pHndl;
	HMODULE* modHndls;
	DWORD b_alloc=8, b_needed;
	char modName[MAX_PATH];
	int i;
	//pID=GetCurrentProcessId();
	//pID = FindProcess("iexplore.exe");
	pID = FindProcess("t2.exe");
	pHndl=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pID);
	while(1){
	modHndls=(HMODULE*)malloc(b_alloc);
	EnumProcessModules(pHndl,modHndls,b_alloc,&b_needed);
	//printf("%u %u\n",pID,pHndl);
	//printf("%u %u\n",b_alloc, b_needed);
	if(b_alloc>=b_needed) break; else{
	free(modHndls);
	b_alloc=b_needed;
	}
	}
	printf("\n");
	
	for(i=0;i<b_needed/sizeof(DWORD);i++){
	GetModuleBaseName(pHndl, modHndls[i],(LPSTR)modName, sizeof(modName));
	printf("%u\t%s", modHndls[i],modName);
	GetModuleFileName(modHndls[i], (LPSTR)modName, sizeof(modName));
	printf("\t%s\n",modName);
	}
	Sleep(5000);
	}
	system("pause");
	return 0;
}