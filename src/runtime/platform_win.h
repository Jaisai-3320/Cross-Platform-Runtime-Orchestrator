#pragma once
#ifdef _WIN32
#include <windows.h>
inline void SetThreadName(const wchar_t* name){
using SetThreadDescription_t = HRESULT (WINAPI*)(HANDLE, PCWSTR);
static auto pSetThreadDescription = reinterpret_cast<SetThreadDescription_t>(
GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "SetThreadDescription"));
if (pSetThreadDescription) pSetThreadDescription(GetCurrentThread(), name);
}


inline void BoostRuntimeThread(){
// Improve responsiveness (balance carefully to avoid starving others)
SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
}


inline void PinToPerformanceCores(){
// Example: keep affinity to first group (parity adjustments may be required per machine)
GROUP_AFFINITY ga{}; ga.Mask = 1; ga.Group = 0; SetThreadGroupAffinity(GetCurrentThread(), &ga, nullptr);
}
#endif