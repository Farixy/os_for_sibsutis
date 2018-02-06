#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <imagehlp.h>
int main(int argc, char* argv[]){
	LOADED_IMAGE LoadedImage;
	PUCHAR BaseAddress;
	DWORD RVAExpDir, VAExpAddress;
	IMAGE_EXPORT_DIRECTORY* ExpTable;
	char* sName;
	DWORD nNames;
	char* pName;
	char** pNames;	
	DWORD i;
	std::ofstream eout("export.txt", std::ofstream::out);
	//��������� PE-����
	if(!MapAndLoad(argv[1], NULL, &LoadedImage, TRUE,TRUE)){
	printf("Something's wrong!\n");
	exit(1);
	}	
	//��������� ������� ����� ������������ ������
	BaseAddress=LoadedImage.MappedAddress;
	printf("0x%lx - Base Address\n",BaseAddress);
	//���������� ������������� ����������� ����� - RVA, ������� ��������
	RVAExpDir= LoadedImage.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	printf("0x%lx -RVA\n", RVAExpDir);
	//���������� ����������� ����� ������� ����� �� ��� RVA
	VAExpAddress=(DWORD)ImageRvaToVa(LoadedImage.FileHeader,BaseAddress, RVAExpDir,NULL);
	printf("0x%lx -VA\n",VAExpAddress);
	ExpTable=(IMAGE_EXPORT_DIRECTORY*)VAExpAddress;
	//���������� ����������� ����� ������ - ����� PE-�����, //�� ��� RVA
	sName=(char*)ImageRvaToVa(LoadedImage.FileHeader,BaseAddress, ExpTable->Name,NULL);
	printf("Name of PEF: %s\n",sName);
	//���������� ����������� ����� ������� ����� �� ��� RVA
	pNames=(char**)ImageRvaToVa(LoadedImage.FileHeader,
	BaseAddress, ExpTable->AddressOfNames,NULL);
	//��������� ���������� �������������� ���� �� ������� //��������
	nNames=ExpTable->NumberOfNames;
	printf("Exported data:\n",pName);
	for(i=0;i<nNames;i++){
	//���������� ����������� ����� i-��� ����� �� ��� RVA
	pName=(char*)ImageRvaToVa(LoadedImage.FileHeader,BaseAddress, (DWORD)*pNames,NULL);
	//printf("%s\n",pName);
	eout<<pName<<std::endl;
	*pNames++; //��������� � ��������� ������
	}
	eout.close();
	UnMapAndLoad(&LoadedImage);
	return 0;
}
	
	