#include <iostream>
#include <string>
#include <Windows.h>
#include <tlhelp32.h>
using namespace std;

HANDLE getProcess(PCSTR processName) 
{
	DWORD processId = 0;
	PROCESSENTRY32 processEntry;
	ZeroMemory(&processEntry, sizeof(processEntry));
	processEntry.dwSize = sizeof(PROCESSENTRY32);
	
	HANDLE processSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (Process32First(processSnapshot, &processEntry)) 
	{
		while (Process32Next(processSnapshot, &processEntry))
		{
			if (string(processEntry.szExeFile) == string(processName))
			{

			}
		}
	}

	if (processId == 0)
	{
		return NULL;

	}

	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
};

int main()
{
	getProcess("ac_client.exe");
	return 0;
}
