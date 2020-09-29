#include "window/Window.h"
#include "Button/Button.h"
#include "DialogWindow/DialogWindow.h"

class MyWindow :public wnd::Window {
private:
	

protected:

	void WindowCreate()override;
	void ButtonClicked(uint notification_code, HWND button_handle)override;
	Text text;
	Text text_2;
	Button button;
	DialogWindow open_file_;

public:

	explicit MyWindow(HINSTANCE hInstance) :Window(hInstance),
		text(hInstance),
		text_2(hInstance),
		button(hInstance),
		open_file_(hInstance)
	{


	}

};

void MyWindow::WindowCreate() {

	SetCaption(L"My caption.");
	SetStyle(WS_OVERLAPPEDWINDOW);
	SetShowState(SW_SHOWNORMAL);
	const Style text_style = WS_CHILD | WS_VISIBLE;
	const int show_state = SW_SHOWNORMAL;
	//uint wnd_height = GetHeight();
	//uint wnd_width = GetWidth();

	
	text.SetParametrs(0, 0, 100, 100);
	text.Create(WndHandle(), L"Some text_1.", text_style);
	text.Show(show_state);

	text_2.SetParametrs(0, 102, 100, 100);
	text_2.Create(WndHandle(), L"Some text_2.", text_style);
	text_2.Show(show_state);

	button.SetParametrs(100, 0, 100, 100);
	button.Create(WndHandle(), L"Button.", text_style);
	button.Show(show_state);

	open_file_.Create(self_handle_, L"some.txt");

}

void MyWindow::ButtonClicked(uint notification_code, HWND button_handle) {

	if (button_handle == button) {
		text.SetText(L"New text.");
	}

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	MyWindow main_window(hInstance);
	main_window.Create();
	main_window.Show();
	MyWindow::StartMessageLoop();
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