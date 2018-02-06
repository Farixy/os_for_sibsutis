#include <windows.h>  
#include <stdio.h>  
#include <iostream>  
  
using namespace std;  
  
PIMAGE_SECTION_HEADER GetEnclosingSectionHeader(DWORD rva, PIMAGE_NT_HEADERS pNTHeader) {  
	PIMAGE_SECTION_HEADER section = IMAGE_FIRST_SECTION(pNTHeader);  
	for (unsigned i=0; i<pNTHeader->FileHeader.NumberOfSections; i++, section++)   {  
             if ((rva >= section->VirtualAddress) && (rva < (section->VirtualAddress + section->Misc.VirtualSize)))  
             return section;  
        }  
        return 0;  
}  
/*
typedef struct _IMAGE_IMPORT_DESCRIPTOR { 
union { 
DWORD Characteristics; 
DWORD OriginalFirstThunk; 
}; 
DWORD TimeDateStamp; 

DWORD ForwarderChain; 
DWORD Name; 
DWORD FirstThunk; 
} IMAGE_IMPORT_DESCRIPTOR
*/   
void DumpFile(LPSTR filename) {  
    HANDLE hFile;     HANDLE hFileMapping;    LPVOID lpFileBase;    ULONG ulSize;  
    PIMAGE_THUNK_DATA thunk;    PIMAGE_IMPORT_BY_NAME pOrdinalName;    PIMAGE_DOS_HEADER pDOSHeader;    PIMAGE_NT_HEADERS pNTHeader;  
    PIMAGE_IMPORT_DESCRIPTOR importDesc;    PIMAGE_SECTION_HEADER pSection;    
    hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0); //открываем файл  
    if (hFile == INVALID_HANDLE_VALUE) return;    
    hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL); //отображаем файл в память  
        if (!hFileMapping) {  
                CloseHandle(hFile);  
                return;  
        }  	     
    lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0); // преобразовать в указатель  
        if (!lpFileBase) {  
                CloseHandle(hFileMapping);  
                CloseHandle(hFile);  
                return;  
   }  
   printf("DLL's and Function's of file %s:\n", filename);    
   pDOSHeader = (PIMAGE_DOS_HEADER)lpFileBase;  //указатель на DOS-заголовок 
   if (pDOSHeader->e_magic != IMAGE_DOS_SIGNATURE) return;     
   pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pDOSHeader + pDOSHeader->e_lfanew); //находим адрес NT заголовка  
   if (pNTHeader->Signature != IMAGE_NT_SIGNATURE) return;  
   int importsStartRVA = pNTHeader-> OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress; //RVA-адрес таблицы импорта  
   if (!importsStartRVA) return;    
   pSection = GetEnclosingSectionHeader(importsStartRVA, pNTHeader); //определяем адрес секции  
   if (!pSection) return;  
   int delta = pSection->VirtualAddress - pSection->PointerToRawData;  
   importDesc = (PIMAGE_IMPORT_DESCRIPTOR) (importsStartRVA - delta + (DWORD)lpFileBase);    
   while (importDesc->TimeDateStamp || importDesc->Name) { //перебираем список dll	   
       printf("%s\n", (PBYTE)(importDesc->Name) - delta + (DWORD)lpFileBase); //название dll  
       //RVA-смещение на массив указателей на функции  
       thunk = (PIMAGE_THUNK_DATA)importDesc->Characteristics;  
       if (!thunk) thunk = (PIMAGE_THUNK_DATA)importDesc->FirstThunk;  
       thunk = (PIMAGE_THUNK_DATA)( (PBYTE)thunk - delta + (DWORD)lpFileBase);  	  
       while (thunk->u1.AddressOfData) { //перебираем функции  
              if (!(thunk->u1.Ordinal & IMAGE_ORDINAL_FLAG)) {  
               pOrdinalName = (PIMAGE_IMPORT_BY_NAME)thunk->u1.AddressOfData;  
               pOrdinalName = (PIMAGE_IMPORT_BY_NAME)((PBYTE)pOrdinalName - delta + (DWORD)lpFileBase);  
	       printf("     %s\n", pOrdinalName->Name); //выводим имя функции 
               }  
               thunk++;  
            }  
         importDesc++;  
        }  
        UnmapViewOfFile(lpFileBase);  
        CloseHandle(hFileMapping);  
        CloseHandle(hFile);  
}  
  
int main(int argc, char *argv[])  
{     
       TCHAR Buffer2[] = TEXT("C:\\Windows\\system32\\notepad.exe");
       DumpFile(Buffer2);  
}  