#include "window/Window.h"
#include "Button/Button.h"
#include "DialogWindow/DialogWindow.h"
#include "Parser.h"


class MyWindow :public wnd::Window {
private:
	
protected:

	void WindowCreate()override;
	void ButtonClicked(uint notification_code, HWND button_handle)override;
	Text text;
	Text text_2;
	Button open_file_dialog_;
	Button parse_program_;
	DialogWindow open_file_;
	Parser parser_;

public:

	explicit MyWindow(HINSTANCE hInstance) :Window(hInstance),
		text(hInstance),
		text_2(hInstance),
		open_file_dialog_(hInstance),
		parse_program_(hInstance),
		open_file_(hInstance)
	{


	}

};
LRESULT CALLBACK ChildProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	if (Message == WM_DESTROY)
	{
		return 0;
	}
	return DefWindowProc(hwnd, Message, wparam, lparam);
}
void MyWindow::WindowCreate() {

	SetCaption(_T("Metrology. Java parsing."));
	SetStyle(WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_MAXIMIZE);
	size_t width = GetSystemMetrics(SM_CXSCREEN);
	SetWidth(GetSystemMetrics(SM_CXSCREEN)+ 200);
	SetHeight(GetSystemMetrics(SM_CYSCREEN));
	SetShowState(SW_SHOWNORMAL);
	const Style text_style = WS_CHILD | WS_VISIBLE;
	const int show_state = SW_SHOWNORMAL;

	
	text_2.SetParametrs(0, 102, 100, 100);
	text_2.Create(WndHandle(), _T("Some text_2."), text_style);
	text_2.Show(show_state);

	open_file_dialog_.SetParametrs(100, 0, 100, 50);
	open_file_dialog_.Create(WndHandle(), _T("Open file"), text_style);
	open_file_dialog_.Show(show_state);


	/*WNDCLASS w;
	memset(&w, 0, sizeof(WNDCLASS));
	w.lpfnWndProc = ChildProc;
	w.hInstance = app_instance_handle_;
	w.hbrBackground = NULL;
	w.lpszClassName = _T("ChildWClass");
	w.hCursor = LoadCursor(NULL, IDC_CROSS);
	RegisterClass(&w);
	HWND child;
	child = CreateWindowEx(0, _T("ChildWClass"), (LPCTSTR)NULL,
		WS_CHILD | WS_BORDER | WS_VISIBLE | WS_VSCROLL, 0, 0,
		500, 500, self_handle_, (HMENU)(int)(100), app_instance_handle_, NULL);
	ShowWindow(child, SW_NORMAL);
	UpdateWindow(child);*/

	text.SetParametrs(200, 200, 600, 300);
	text.Create(WndHandle(), _T("Some text_1."), text_style);
	text.Show(show_state);

	//open_file_.Create(WndHandle()ome.txt");

}



void MyWindow::ButtonClicked(uint notification_code, HWND button_handle) {

	if (button_handle == open_file_dialog_) {

		std::wstring w_dialog_file_name;
		w_dialog_file_name = open_file_.Create(WndHandle());
		std::string dialog_file_name(w_dialog_file_name.begin(), w_dialog_file_name.end());
		parser_.SetFileName(dialog_file_name);
		text.SetText(w_dialog_file_name.c_str());

	}

	if (button_handle == parse_program_) {
		parser_.parseStrings();
		parser_.parseLexems();
		parser_.parseLexem();
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