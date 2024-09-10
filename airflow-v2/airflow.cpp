#include "dependencies.h"
#include "airflow.h"

namespace af
{
	void initialize(HMODULE module)
	{
#ifdef _DEBUG
		AllocConsole();
		SetConsoleTitleA(xorstr_("Airflow v2"));

		freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
		freopen_s(reinterpret_cast<FILE**>(stderr), "CONOUT$", "w", stderr);
		freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
#endif

		DEBUG_LOG("Initalizing SDK \n");
		sdk::initialize();

		DEBUG_LOG("Welcome to Airflow v2 \n");

#ifdef _DEBUG
		while (!GetAsyncKeyState(VK_END))
			Sleep(200);

		destroy(module);
#endif
	}

    void destroy(HMODULE module)
    {
#ifdef _DEBUG
        DEBUG_LOG("Destroying.. \n");

        sdk::destroy();

        HWND hwnd = GetConsoleWindow();
        HWND owner = GetWindow(hwnd, GW_OWNER);
        if (owner == NULL)
        {
            ShowWindow(hwnd, SW_HIDE); // Windows 10
            PostMessageA(hwnd, WM_CLOSE, 0, 0);
        }
        else
        {
            ShowWindow(owner, SW_HIDE);// Windows 11
            PostMessageA(owner, WM_CLOSE, 0, 0);
        }

        FreeConsole();

        FreeLibraryAndExitThread(module, 0);
#endif
    }
}