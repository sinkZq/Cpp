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
		} 
		while (Process32Next(hSnapshot, &processEntry));
	}
	else
	{
		std::cout << "process not found, returning processid as 0" << std::endl;
		return processId;
	}

	return processId;
};

int main()
{
	DWORD processInfo1 = getProcessId(L"EADesktop.exe"); // call func with L"str" L converts it to a C literal
	DWORD processInfo2 = getProcessId(L"Agent.exe");

	vector<DWORD> tProcessInfo = { processInfo1, processInfo2 }; // def vector to create tbl

	for (int processId : tProcessInfo) // iterate through tbl as processId = v, works as in pairs or any other iter call in lua
	{
		std::cout << processId << " " << std::endl;
	}

	return 0;
}
