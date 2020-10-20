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

//Стили окна
//WS_BORDER	0x00800000	Окно имеет тонкую границу в виде линии.
//WS_CAPTION	0x00C00000	Окно имеет строку заголовка.
//WS_CHILD	0x40000000	Окно является дочерним.
//WS_DISABLED	0x08000000	Окно является изначально неактивным.
//WS_GROUP	0x00020000	Окно группирует другие управляющие элементы.
//WS_HSCROLL	0x00100000	Окно содержит горизонтальную полосу прокрутки.
//WS_MAXIMIZE	0x01000000	Исходный размер окна – во весь экран.
//WS_MINIMIZE	0x20000000	Исходно окно свернуто.
//WS_OVERLAPPED	0x00000000	Окно может быть перекрыто другими окнами.
//WS_POPUP	0x80000000	Всплывающее окно.
//WS_SYSMENU	0x00080000	Окно имеет системное меню в строке заголовка.
//WS_VISIBLE	0x10000000	Окно изначально видимое.
//WS_VSCROLL	0x00200000	Окно имеет вертикальную полосу прокрутки.

///Типы показа окна
//SW_HIDE - Скрывает окно и активизирует другое окно.
//SW_MAXIMIZE - Развертывает определяемое окно.
//SW_MINIMIZE - Свертывает определяемое окно и активизирует следующее окно верхнего уровня в Z - последовательности.
//SW_RESTORE - Активизирует и отображает окно.Если окно свернуто или развернуто, Windows восстанавливает в его первоначальных размерах и позиции.Прикладная программа должна установить этот флажок при восстановлении свернутого окна.
//SW_SHOW - Активизирует окно и отображает его текущие размеры и позицию.
//SW_SHOWDEFAULT - Устанавливает состояние показа, основанное на флажке SW_, определенном в структуре STARTUPINFO, переданной в функцию CreateProcess программой, которая запустила прикладную программу.
//SW_SHOWMAXIMIZED - Активизирует окно и отображает его как развернутое окно.
//SW_SHOWMINIMIZED - Активизирует окно и отображает его как свернутое окно.
//SW_SHOWMINNOACTIVE - Отображает окно как свернутое окно.Активное окно остается активным.
//SW_SHOWNA - Отображает окно в его текущем состоянии.Активное окно остается активным.
//SW_SHOWNOACTIVATE - Отображает окно в его самом современном размере и позиции.Активное окно остается активным.
//SW_SHOWNORMAL - Активизирует и отображает окно.Если окно свернуто или развернуто, Windows восстанавливает его в первоначальном размере и позиции.Прикладная программа должна установить этот флажок при отображении окна впервые.