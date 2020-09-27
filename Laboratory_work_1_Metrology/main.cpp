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