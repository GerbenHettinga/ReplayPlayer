#include <windows.h>

#define PROCESS_SUSPEND_RESUME (0x0800)
#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_SUSPEND_RESUME | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ)

// -------------------- Hooking Into The Game -------------------

HWND hook_in_window()							// Fetch the 'window hook'
{
	LPCWSTR a = L"gta_sa";
	LPCWSTR b = L"GTA: San Andreas";
	HWND window_hook = FindWindow(NULL, b);
	while (window_hook == NULL)
	{							
		// [if game not open, wait a bit, then try again...]
		Sleep(1000);
		window_hook = FindWindow(NULL, b);
	}
	
	return window_hook;
}

HANDLE hook_in_process(HWND window_hook)		// Fetch the 'process hook'
{
	unsigned long process_id;									// Get the 'process id' then the 'process handle'
	GetWindowThreadProcessId(window_hook, &process_id);			//  [used to simply use 'PROCESS_ALL_ACCESS', nowadays it has OS compatibility issues, so need to spell it out]

	process_hook = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_SUSPEND_RESUME | PROCESS_TERMINATE | PROCESS_CREATE_PROCESS | PROCESS_CREATE_THREAD, 0, process_id);
	return process_hook;
}

bool process_active(HANDLE process_hook)		// Check the process is still active [game not closed]
{
	DWORD active_status = 0;
	GetExitCodeProcess(process_hook, &active_status);
	if (active_status != STILL_ACTIVE) return false;			// [the function which does the check can fail; we treat this the same as it returning to say 'not active']
	return true;
}

// -------------------- Keypress --------------------

bool key_pressed(int key)
{
	return (GetAsyncKeyState(key) & 0x8000);
}

// -------------------- Memory Editing: GETs --------------------

int GetByte(unsigned long offset)
{
	BYTE TempValue;
	ReadProcessMemory(process_hook, (LPCVOID)offset, &TempValue, sizeof(TempValue), NULL);
	return TempValue;
}

int GetLong(unsigned long offset) 
{
	DWORD TempValue;
	ReadProcessMemory(process_hook, (LPCVOID)offset, &TempValue, sizeof(TempValue), NULL);
	return TempValue;
}

int GetInteger(unsigned long offset) 
{
	int TempValue;
	ReadProcessMemory(process_hook, (LPCVOID)offset, &TempValue, sizeof(TempValue), NULL);
	return TempValue;
}

float GetSingle(unsigned long offset) 
{
	float TempValue;
	ReadProcessMemory(process_hook, (LPCVOID)offset, &TempValue, sizeof(TempValue), NULL);
	return TempValue;
}

// -------------------- Memory Editing: SETs --------------------

void SetByte(unsigned long offset, BYTE Value) 
{
	DWORD d, ds;
	VirtualProtectEx(process_hook, (PVOID)offset, sizeof(Value), PAGE_EXECUTE_READWRITE, &d);
	WriteProcessMemory(process_hook, (LPVOID)offset, &Value, sizeof(Value), NULL);
	VirtualProtectEx(process_hook, (PVOID)offset, sizeof(Value), d, &ds);
}

void SetInteger(unsigned long offset, int Value) 
{
	WriteProcessMemory(process_hook, (LPVOID)offset, &Value, sizeof(Value), NULL);
}

void SetLong(unsigned long offset, DWORD Value) 
{
	DWORD d, ds;
	VirtualProtectEx(process_hook, (PVOID)offset, sizeof(Value), PAGE_EXECUTE_READWRITE, &d);
	WriteProcessMemory(process_hook, (LPVOID)offset, &Value, sizeof(Value), NULL);
	VirtualProtectEx(process_hook, (PVOID)offset, sizeof(Value), d, &ds);
}

void SetSingle(unsigned long offset, float Value) 
{
	DWORD d, ds;
	VirtualProtectEx(process_hook, (PVOID)offset, sizeof(Value), PAGE_EXECUTE_READWRITE, &d);
	WriteProcessMemory(process_hook, (LPVOID)offset, &Value, sizeof(Value), NULL);
	VirtualProtectEx(process_hook, (PVOID)offset, sizeof(Value), d, &ds);
}

	// (DAN'S WRITE BYTE STREAM FUNCTION)
void SetByteStream(unsigned long offset, BYTE stream[], long streamLength)
{
	DWORD d1, d2;
	VirtualProtectEx(process_hook, (PVOID)offset, streamLength, PAGE_EXECUTE_READWRITE, &d1);
	WriteProcessMemory(process_hook, (LPVOID)offset, stream, streamLength, NULL);
	VirtualProtectEx(process_hook, (PVOID)offset, streamLength, d1, &d2);
}
