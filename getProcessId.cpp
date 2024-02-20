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
}

HANDLE getProcess(DWORD processId) // open process handle by processid
{
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId); // [0] access, [1] inheritance, [2] pid
}

int main()
{
	DWORD processId = getProcessId(L"Notepad.exe");
	vector<DWORD> tProcessInfo = { processId }; // def vector to create tbl

	HANDLE process = getProcess(tProcessInfo[0]);

	TerminateProcess(process, 1); // self exp
	CloseHandle(process); // closes handle to the process

	for (int processId : tProcessInfo) // iterate through tbl as processId = v, works as in pairs or any other iter call in lua (this is only for practice)
	{
		std::cout << processId << " " << std::endl;
	}

	return 0;
}
