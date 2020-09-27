#include "window/Window.h"

class MyWindow :public wnd::Window {
private:
	

protected:

	void WindowCreate()override;
	Text text;

public:

	explicit MyWindow(HINSTANCE hInstance):Window(hInstance),//, WS_OVERLAPPEDWINDOW),
		text(WndHandle(), AppInstanceHandle())
	{
		//SetCaption();
		//SetStyle();
		text.Show();

	}

};

void MyWindow::WindowCreate() {

	SetCaption(L"My caption.");
	SetStyle(WS_OVERLAPPEDWINDOW);
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	MyWindow main_window(hInstance);
	wnd::Window::StartMessageLoop();

	return EXIT_SUCCESS;
}

//����� ����
//WS_BORDER	0x00800000	���� ����� ������ ������� � ���� �����.
//WS_CAPTION	0x00C00000	���� ����� ������ ���������.
//WS_CHILD	0x40000000	���� �������� ��������.
//WS_DISABLED	0x08000000	���� �������� ���������� ����������.
//WS_GROUP	0x00020000	���� ���������� ������ ����������� ��������.
//WS_HSCROLL	0x00100000	���� �������� �������������� ������ ���������.
//WS_MAXIMIZE	0x01000000	�������� ������ ���� � �� ���� �����.
//WS_MINIMIZE	0x20000000	������� ���� ��������.
//WS_OVERLAPPED	0x00000000	���� ����� ���� ��������� ������� ������.
//WS_POPUP	0x80000000	����������� ����.
//WS_SYSMENU	0x00080000	���� ����� ��������� ���� � ������ ���������.
//WS_VISIBLE	0x10000000	���� ���������� �������.
//WS_VSCROLL	0x00200000	���� ����� ������������ ������ ���������.

///���� ������ ����
//SW_HIDE - �������� ���� � ������������ ������ ����.
//SW_MAXIMIZE - ������������ ������������ ����.
//SW_MINIMIZE - ���������� ������������ ���� � ������������ ��������� ���� �������� ������ � Z - ������������������.
//SW_RESTORE - ������������ � ���������� ����.���� ���� �������� ��� ����������, Windows ��������������� � ��� �������������� �������� � �������.���������� ��������� ������ ���������� ���� ������ ��� �������������� ���������� ����.
//SW_SHOW - ������������ ���� � ���������� ��� ������� ������� � �������.
//SW_SHOWDEFAULT - ������������� ��������� ������, ���������� �� ������ SW_, ������������ � ��������� STARTUPINFO, ���������� � ������� CreateProcess ����������, ������� ��������� ���������� ���������.
//SW_SHOWMAXIMIZED - ������������ ���� � ���������� ��� ��� ����������� ����.
//SW_SHOWMINIMIZED - ������������ ���� � ���������� ��� ��� ��������� ����.
//SW_SHOWMINNOACTIVE - ���������� ���� ��� ��������� ����.�������� ���� �������� ��������.
//SW_SHOWNA - ���������� ���� � ��� ������� ���������.�������� ���� �������� ��������.
//SW_SHOWNOACTIVATE - ���������� ���� � ��� ����� ����������� ������� � �������.�������� ���� �������� ��������.
//SW_SHOWNORMAL - ������������ � ���������� ����.���� ���� �������� ��� ����������, Windows ��������������� ��� � �������������� ������� � �������.���������� ��������� ������ ���������� ���� ������ ��� ����������� ���� �������.