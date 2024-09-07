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

		// https://stackoverflow.com/questions/622592/win32-programming-hiding-console-window
		auto stealth = FindWindowA("ConsoleWindowClass", NULL);
		ShowWindow(stealth, 0);

		PostMessageA(stealth, WM_CLOSE, 0, 0);
		FreeConsole();

		FreeLibraryAndExitThread(module, 0);
#endif
	}
}