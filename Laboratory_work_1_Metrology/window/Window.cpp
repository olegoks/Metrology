

#include "window.h"
#include <chrono>
#pragma warning(disable : 4996)

namespace wnd {

	LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT Message, WPARAM  wParam, LPARAM lParam) {

		Window* const window_ptr = reinterpret_cast<Window * const>(GetWindowLongPtr(hWnd, GWL_USERDATA));

		switch (Message) {

		case WM_CREATE: {

			LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
			Window* const wnd_ptr = (Window*)lpcs->lpCreateParams;
			wnd_ptr->self_handle_ = hWnd;
			wnd_ptr->WindowCreate();
			SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG)wnd_ptr);

			break;
		}	

		case WM_COMMAND: {
			
			if (LOWORD(wParam) == ID_BUTTON) {
				window_ptr->ButtonClicked(HIWORD(wParam), (HWND)lParam);
			}

			break;
		}

		case WM_CLOSE: {DestroyWindow(window_ptr->self_handle_); break; }

		case WM_DESTROY: {PostQuitMessage(0); break; }

		default: return DefWindowProc(hWnd, Message, wParam, lParam);

		}

	}


	Window::Window(HINSTANCE app_instance_handle)noexcept: 
		Component(app_instance_handle),
		device_context_(nullptr),
		win_caption_((const wchar_t*) new wchar_t[17] {L"Default caption."})
	{

		id_ = NewWindowId(); number_of_windows_;
		number_of_windows_++;

	}

	void Window::Create() {

		RegisterWindowClass();
		CreateWnd();

	}

	Window::~Window() {
			

	}

		bool Window::RegisterWindowClass() {

			sz_class_name_ = GenerateDefaultClassName();

			WNDCLASSEX wc; //������� ��������� ������ WNDCLASSEX
			wc.cbSize = sizeof(wc);
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = WndProc;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = app_instance_handle_;
			wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
			wc.lpszMenuName = NULL;
			wc.lpszClassName = sz_class_name_;
			wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

			if (!RegisterClassEx(&wc)) {

				MessageBox(nullptr,
					L"�� ������� ���������������� �����",
					L"������ ����������� ������!",
					MB_OK);

				return EXIT_FAILURE;

			}

			return EXIT_SUCCESS;

		}
		uint Window::NewWindowId()
		{
			uint new_id = number_of_windows_;
			number_of_windows_++;
			return new_id;
		}
		wchar_t* Window::GenerateDefaultClassName() {

			wchar_t id_wide[2];
			_itow(id_, id_wide, 10);
			wchar_t default_name[] = L"Window class name ";
			unsigned int size_of_default_name = wcslen(default_name);
			wchar_t* class_name;
			class_name = (wchar_t*)malloc( sizeof(wchar_t) * (size_of_default_name + 2) );
			wcscpy(class_name, default_name);
			wcscpy(class_name + size_of_default_name, id_wide);
			return class_name;

		}

		int  Window::CreateWnd()
		{
			CreateWindow(sz_class_name_, win_caption_, style_, x_,  y_, width_, height_,
							parent_handle_, menu_handle_,app_instance_handle_,this);

			if (!self_handle_) {
				MessageBox(NULL, L"�� ���������� ������� ����!", L"������", MB_OK);
				return EXIT_FAILURE;
			}
			
			SetProcessDPIAware();//������� ��� ������� (SetProcessDPIAware), �� ��������� �������, ��� ��������� ������ ���������� ����� ��� ��������� ���������������� ��� ������� ��������� DPI (����� �� ����). ���� �� �� ��������� ���� ����, �� ��������� ������ ���������� ����� ��������� ������� ��� ������� ��������� DPI.
			device_context_ = GetDC(self_handle_);

			return EXIT_SUCCESS;
		}

		void Window::SetParametrs(const uint width, const uint height, const uint x, const uint y, DWORD style)
		{
			width_ = width;
			height_ = height;
			x_ = x;
			y_ = y;
			style_ = style;
		}

		void Window::SetStyle(Style style) noexcept
		{ 
			style_ = style; 
			SetWindowLongPtr(self_handle_, GWL_STYLE, style_);
		}

		void Window::SetCaption(const wchar_t* caption)
		{
			win_caption_ = caption; 
			SetWindowText(self_handle_, win_caption_);
		}

		void  Window::Show(int show_state)
		{
			show_state_ = show_state;
			bool temp = ShowWindow(self_handle_, show_state_);
		}


		void Window::StartMessageLoop()
		{
			
			
			/*
				typedef struct tagMSG {
				HWND hwnd; // ���������� ����, �������� ���������� ���������
				UINT message; // ����� (������������� ) ���������
				WPARAM wParam; // �������� ��������� wParam
				LPARAM lParam; //�������� ��������� lParam
				DWORD time; // ����� �������� ���������
				POINT pt; //������� �������(� �������� �����������) � ������
				//�������� ���������
				} MSG;
			*/

			MSG msg;
			msg = { 0 };
			while (GetMessage(&msg, NULL, NULL, NULL) != NULL) {

				TranslateMessage(&msg);
				DispatchMessage(&msg);

			}

			// BOOL GetMessage(
			// MSG lpMsg, - ����� ��������� ���� ��������� ���������
			// HWND hWnd, - �������� ����� ��������� ����� NULL, 
			// UINT wMsgFilterMin, - ���������� ������������� �������� ������ ���������� �������� ���������, ������� ����� ���������.
			// UINT wMsgFilterMax - ���������� ������������� �������� ������ �������� �������� ���������, ������� ����� ���������.
			// *���� wMsgFilterMin � wMsgFilterMax �������� ��� ��������, ������� GetMessage ���������� ��� ��������� ��������� (�� ���� ������� ���������� � ��������� �������� �� �����������).

			//������� TranslateMessage ��������� ��������� ����������� ������ � ���������� ���������. 
			//���������� ��������� ���������� � ������� ��������� ����������� ������ ��� ��������� � ��������� ���, 
			//����� ����� ������� ������� GetMessage ��� PeekMessage.

			//������� DispatchMessage ������������ ��������� ������� ��������� WndProc.

		}

		uint Window::number_of_windows_ = 0;

}