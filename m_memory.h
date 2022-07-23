#pragma once
#include <Windows.h>
#include <string.h>
#include <TlHelp32.h>
#include <stdlib.h>
#include <WinUser.h>
#include <string>
#include <thread>


namespace memory {

	struct GlowEntityColor {

		float red;
		float green;
		float blue;
		float alpha; 

	};


	HANDLE processHandle;
	DWORD processID;
	uint32_t engineBase;
	uint32_t clientBase;

	const wchar_t* process = L"dthp/fyf";
	const wchar_t* client = L"dmjfou/emm";
	const wchar_t* engine = L"fohjof/emm";

	std::wstring rProcess;
	std::wstring rClient;
	std::wstring rEngine;


	template <typename T>
	T readMemory( uint32_t adr) {
		T value;
		if (ReadProcessMemory(processHandle, (LPCVOID)adr, &value, sizeof(T), NULL))
			return value;
		return T();
	}

	template <typename T>
	int writeMemory( uint32_t adr, const T& patch) {
		return WriteProcessMemory(processHandle, (LPVOID)adr, &patch, sizeof(T), NULL);
	}

	DWORD getProcessID(const std::wstring& pProcessName) {
		HANDLE hToolHelper = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0x0);
		PROCESSENTRY32 p32ProcessEntry = { 0 };
		p32ProcessEntry.dwSize = sizeof(PROCESSENTRY32);

		if (hToolHelper == NULL) {
			return NULL;
		}

		if (!Process32First(hToolHelper, &p32ProcessEntry)) {
			CloseHandle(hToolHelper);
			return NULL;
		}

		do {
			if (!wcscmp(p32ProcessEntry.szExeFile, pProcessName.c_str())) {
				CloseHandle(hToolHelper);
				return p32ProcessEntry.th32ProcessID;
			}
		} while (Process32Next(hToolHelper, &p32ProcessEntry));

		return NULL;
	}

	LPVOID getModuleBaseAddress(DWORD dwProcessID, const std::wstring& lpszModuleName) {

		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcessID);

		if (hSnapshot == INVALID_HANDLE_VALUE)
			return NULL;

		MODULEENTRY32 ModuleEntry32 = { 0 };
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

		if (!Module32First(hSnapshot, &ModuleEntry32))
			return NULL;

		do
		{
			if (!wcscmp(ModuleEntry32.szModule, lpszModuleName.c_str()))
			{
				CloseHandle(hSnapshot);
				return ModuleEntry32.modBaseAddr;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32));



		return NULL;

	}


	DWORD init() {
		rProcess = process;
		rClient = client;
		rEngine = engine;

		for (wchar_t* i = const_cast<wchar_t*>(rProcess.c_str()); *i != 0; i++) {
			*i = (*i) - 1;
		}

		for (wchar_t* i = const_cast<wchar_t*>(rClient.c_str()); *i != 0; i++) {
			*i = (*i) - 1;
		}

		for (wchar_t* i = const_cast<wchar_t*>(rEngine.c_str()); *i != 0; i++) {
			*i = (*i) - 1;
		}


		processID = getProcessID(rProcess.c_str());
		if (!processID) return 0;

		processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
		if (!processHandle) return 0;

		clientBase = (uint32_t)getModuleBaseAddress(processID, rClient.c_str());
		if (!clientBase) return 0;

		engineBase = (uint32_t)getModuleBaseAddress(processID, rEngine.c_str());
		if (!engineBase) return 0;

		return 1;
	}
}