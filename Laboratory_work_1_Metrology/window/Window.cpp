

#include "window.h"
#include <chrono>
#pragma warning(disable : 4996)

namespace wnd {

		LRESULT CALLBACK Window:: WndProc(HWND hWnd, UINT Message, WPARAM  wParam, LPARAM lParam) {

		Window* const window_ptr = reinterpret_cast<Window* const>(GetWindowLongPtr(hWnd, GWL_USERDATA));

		switch (Message) {

			/*case WM_KEYDOWN: {

				const unsigned int key = wParam;

				switch (key) {

				case VK_UP: { window_ptr->PushKeystroke(ArrowUp);break;}
				case VK_DOWN: { window_ptr->PushKeystroke(ArrowDown);break;}
				case VK_LEFT: { window_ptr->PushKeystroke(ArrowLeft);break;};
				case VK_RIGHT: { window_ptr->PushKeystroke(ArrowRight);break;}
				case VK_A: { window_ptr->PushKeystroke(A); break; };
				case VK_D: { window_ptr->PushKeystroke(D); break; };
				case VK_S: { window_ptr->PushKeystroke(S); break; };
				case VK_W: { window_ptr->PushKeystroke(W); break; };

				}
				
			break;
			
			}

			case WM_MOUSEWHEEL: {

				static int wheel_delta = 0;
				wheel_delta += GET_WHEEL_DELTA_WPARAM(wParam);
				
				while (wheel_delta > WHEEL_DELTA) {
					window_ptr->PushKeystroke(WheelUp);
					wheel_delta -= WHEEL_DELTA;
				}
				
				while (wheel_delta < 0) {
					window_ptr->PushKeystroke(WheelDown);
					wheel_delta += WHEEL_DELTA;
				}

				break;
			}*/

			case WM_CLOSE: {DestroyWindow(window_ptr->handle_);break;}

			case WM_DESTROY: {PostQuitMessage(0);break;}
		
			default: return DefWindowProc(hWnd, Message, wParam, lParam); 
		
		}

		}


		Window::Window(HINSTANCE app_intance_handle)noexcept: 
			app_intance_handle_ (app_intance_handle),
			x_(0),
			y_ (0),
			height_(500),
			width_(1000),
			device_context_(nullptr),
			win_caption_(nullptr),
			handle_(nullptr),
			style_(),
			n_cmd_show_(SW_SHOWNORMAL){

			

		}
		
		Window::~Window() {
			

		}


		bool Window::RegisterWindowClass() {

			TCHAR szClassName[] = L"Main window class"; // ������ � ������ ������
			WNDCLASSEX wc; //������� ��������� ������ WNDCLASSEX
			wc.cbSize = sizeof(wc);
			wc.style = CS_HREDRAW | CS_VREDRAW;
			wc.lpfnWndProc = WndProc;
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = app_intance_handle_;
			wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
			wc.hCursor = LoadCursor(NULL, IDC_ARROW);
			wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
			wc.lpszMenuName = NULL;
			wc.lpszClassName = szClassName;
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

		int  Window::Create()
		{
			
			TCHAR szClassName[] = L"Main window class";

			HWND HMainWnd;

			/*HMainWnd = CreateWindowEx(WS_EX_TOPMOST, szClassName, L"3D Application", WS_OVERLAPPEDWINDOW,
				0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), (HWND)NULL,
				(HMENU)NULL, (HINSTANCE)this->AppIntanceHandle, NULL);*/
			HMainWnd = CreateWindow(szClassName,
				win_caption_, //L"3D Application", // ��� ���� (�� ��� ������)
				style_,//WS_MAXIMIZE | WS_BORDER | WS_VISIBLE,  // ������ ����������� ������
				x_, // ��������� ���� �� ��� � (�� ���������)
				y_, // ������� ���� �� ��� � (��� ������ � �, �� ������ �� �����)
				width_, // ������ ������ (�� ���������)
				height_, // ������ ���� (��� ������ � ������, �� ������ �� �����)
				HWND(NULL), // ���������� ������������� ������
				NULL, // ���������� ���� 
				app_intance_handle_, // l���������� ���������� ����������
				NULL); // ������ �� ������� �� WndProc
			

			SetWindowLongPtr(HMainWnd, GWL_USERDATA, (LONG) this);

			if (!HMainWnd) {
				// � ������ ������������� �������� ���� (�������� ��������� � ��):
				MessageBox(NULL, L"�� ���������� ������� ����!", L"������", MB_OK);
				return EXIT_FAILURE; // ������� �� ����������
			}
			
			handle_ = HMainWnd;
			SetProcessDPIAware();//������� ��� ������� (SetProcessDPIAware), �� ��������� �������, ��� ��������� ������ ���������� ����� ��� ��������� ���������������� ��� ������� ��������� DPI (����� �� ����). ���� �� �� ��������� ���� ����, �� ��������� ������ ���������� ����� ��������� ������� ��� ������� ��������� DPI.
			device_context_ = GetDC(HMainWnd);//CreateDC(L"DISPLAY", NULL, NULL, NULL);

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

		void  Window::Show()
		{


			bool temp = ShowWindow(handle_, n_cmd_show_);


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

			MSG msg; // ����� ��������� ��������� MSG ��� ��������� ���������

			msg = { 0 }; // ������������� ��������� ��������� 

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




}