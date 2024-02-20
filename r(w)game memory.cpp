#include <iostream>
#include <string>
#include <Windows.h>
#include <tlhelp32.h>
#include <vector>
using namespace std;

DWORD getProcessId(PCWSTR processName) // def func as DWORD since return val of func (processid) is a DWORD (32bit int)
{
	DWORD processId = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // get process list with snapshot

	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 processEntry = {};
		processEntry.dwSize = sizeof(processEntry);

		if (Process32First(hSnapshot, &processEntry)) do // do = init a while loop
		{
			if (wcsstr(processEntry.szExeFile, processName)) // wcsstr is eq to string.find in lua(u)
			{
				processId = processEntry.th32ProcessID;
				break;
			}
		} while (Process32Next(hSnapshot, &processEntry));
	}
	else
	{
		CloseHandle(hSnapshot);
		return processId;
	}

	return processId;
}

DWORD_PTR getProcessBaseAddress(DWORD processId)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	MODULEENTRY32 moduleEntry;
	moduleEntry.dwSize = sizeof(moduleEntry);

	if (!Module32First(hSnapshot, &moduleEntry))
	{
		CloseHandle(hSnapshot);
		return 0;
	}

	CloseHandle(hSnapshot);
	return (DWORD_PTR)moduleEntry.modBaseAddr;
}

int main()
{
	DWORD processId = getProcessId(L"ac_client.exe");
	vector<DWORD> tProcessInfo = { processId };
	DWORD_PTR baseAddress = getProcessBaseAddress(tProcessInfo[0]);
	DWORD ammoAddress = baseAddress + 0x4C73EF; // this doesn't work since idk

	int* pointer = reinterpret_cast<int*>(ammoAddress);

	std::cout << std::hex << ammoAddress << "  value of address :  " << std::dec << *pointer << std::endl;

	return 0;
}
