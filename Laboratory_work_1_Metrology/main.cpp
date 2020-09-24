#include <windows.h>
#include "window/Window.h"

int WINAPI WINMAIN(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	using namespace wnd;
	Window main_window(hInstance);
	main_window.Create();

	return EXIT_SUCCESS;
}