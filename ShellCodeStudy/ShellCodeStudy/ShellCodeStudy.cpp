// ShellCodeStudy.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<Windows.h>


typedef FARPROC(WINAPI * PFN_GetProcAddress)(
	_In_ HMODULE hModule,
	_In_ LPCSTR lpProcName
);


typedef
HMODULE
(WINAPI
*PNF_LoadLibraryA)(
	_In_ LPCSTR lpLibFileName
);

typedef int(WINAPI *PNF_MessageBoxA)(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType);


//获取keenel32模块 https://xz.aliyun.com/t/10478
HMODULE GetKernelBase() {


	HMODULE hMod = nullptr;
	__asm {
		mov  eax, dword ptr fs : [0x30]
		mov  eax, dword ptr [eax + 0x0C]
		mov  eax, dword ptr  [eax + 0x0C]
		mov  eax, dword ptr [eax]
		mov  eax, dword ptr  [eax]
		mov  eax, dword ptr  [eax + 0x18]
		mov hMod, eax
	}
	return hMod;
}

void* MyGetProcAddress(HMODULE hMod, LPCSTR lpFunName)
{
	IMAGE_DOS_HEADER* pDosHeader = (IMAGE_DOS_HEADER*)hMod;
	IMAGE_NT_HEADERS32* pNtHeader = (IMAGE_NT_HEADERS32*)((DWORD)hMod + pDosHeader->e_lfanew);
	IMAGE_DATA_DIRECTORY* pExportDirectoty = &pNtHeader->OptionalHeader.DataDirectory[0];
	IMAGE_EXPORT_DIRECTORY* pExport = (IMAGE_EXPORT_DIRECTORY*)((DWORD)hMod + pExportDirectoty->VirtualAddress);
	if ((DWORD)lpFunName > 0xffff)
	{
		//名称查找
		for (size_t i = 0; i < pExport->NumberOfNames; i++)
		{
			char* pName = (char*)(*(DWORD*)((DWORD)hMod + pExport->AddressOfNames + i * sizeof DWORD)+ (DWORD)hMod);
			if (strcmp(lpFunName, pName) == 0)
			{
				DWORD  dwOrdinals = *(WORD*)((DWORD)hMod + pExport->AddressOfNameOrdinals+ i * sizeof WORD);
				return (void*)(*(DWORD*)((DWORD)hMod+pExport->AddressOfFunctions+ dwOrdinals* sizeof DWORD)+(DWORD)hMod);
			}
		}
	}
	else {  
		DWORD  dwOrdinals = (DWORD)lpFunName - pExport->Base;
		if (dwOrdinals>=pExport->NumberOfFunctions)
		{
			return 0;
		}
		return (void*)(*(DWORD*)((DWORD)hMod + pExport->AddressOfFunctions + dwOrdinals * sizeof DWORD) + (DWORD)hMod);

	}
}

int Entry()
{

	char szText[] = { 'h',' e',' l',' l',' o','\0' };
	char szText2[] = "sdas";
	char szTitle[] = { 'w',' o',' r',' l',' d','\0' };

	char szGetProcAddress[] = { 'G','e','t','P','r','o','c','A', 'd','d','r','e','s','s','\0'};
					
	char szLoadLibraryA[] = { 'L','o','a','d','L','i','b','r', 'a','r','y','A','\0' };

	char szUser32[] = {'u','s','e','r','3','2','\0' };

	char szMessageBoxA[] = { 'M','e','s','s','a','g','e','B','o','x','A','\0'};


	HMODULE hKernnel32 = GetKernelBase();
	
	PFN_GetProcAddress pfnGetProcAddress =(PFN_GetProcAddress)MyGetProcAddress(hKernnel32, szGetProcAddress);

	PNF_LoadLibraryA pfnLoadLibraryA = (PNF_LoadLibraryA)pfnGetProcAddress(hKernnel32, szLoadLibraryA);

	HMODULE hUser32 = pfnLoadLibraryA(szUser32);


	PNF_MessageBoxA pnfMessageBoxA = (PNF_MessageBoxA)pfnGetProcAddress(hUser32,szMessageBoxA);


	return  pnfMessageBoxA(NULL, szText, szTitle, MB_OK);

}
