#include "dependencies.h"
#include "airflow.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        WINCALL(CreateThread)(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(af::initialize), hModule, NULL, NULL);
        break;
    }
    return TRUE;
}

