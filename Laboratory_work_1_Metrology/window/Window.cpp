

#include "window.h"
#include <chrono>
#pragma warning(disable : 4996)

namespace wnd {

		LRESULT CALLBACK Window:: WndProc(HWND hWnd, UINT Message, WPARAM  wParam, LPARAM lParam) {

		Window* const window_ptr = reinterpret_cast<Window* const>(GetWindowLongPtr(hWnd, GWL_USERDATA));

		switch (Message) {

		case WM_CREATE: {

			LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
			Window* wnd_ptr = (Window*) lpcs->lpCreateParams;
			wnd_ptr->WindowCreate();
			SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG)wnd_ptr);

			break;
		}
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


		Window::Window(HINSTANCE app_intance_handle)noexcept://, Style style)noexcept: 
			Component(NULL, app_intance_handle),
			app_intance_handle_ (app_intance_handle),
			device_context_(nullptr),
			win_caption_(nullptr),
			handle_(nullptr),
			style_(NULL),
			n_cmd_show_(SW_SHOWNORMAL){


			RegisterWindowClass();
			CreateWnd();
			Show();

			id_ = window_id_;
			window_id_++;

		}
		
		Window::~Window() {
			

		}

		bool Window::RegisterWindowClass() {

			sz_class_name_ = GenerateDefaultClassName();

			WNDCLASSEX wc; //Создаем экземпляр класса WNDCLASSEX
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
			wc.lpszClassName = sz_class_name_;
			wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

			if (!RegisterClassEx(&wc)) {

				MessageBox(nullptr,
					L"Не удалось зарегестрировать класс",
					L"Ошибка регистрации класса!",
					MB_OK);

				return EXIT_FAILURE;

			}

			return EXIT_SUCCESS;

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

			/*HMainWnd = CreateWindowEx(WS_EX_TOPMOST, szClassName, L"3D Application", WS_OVERLAPPEDWINDOW,
				0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), (HWND)NULL,
				(HMENU)NULL, (HINSTANCE)this->AppIntanceHandle, NULL);*/
			handle_ = CreateWindow(sz_class_name_,//(LPCWSTR)this,
				win_caption_, //L"3D Application", // имя окнa
				style_,//WS_MAXIMIZE | WS_BORDER | WS_VISIBLE,  // режимы отображения окошка
				x_, // положение окна по оси х
				y_, // позиция окна по оси у
				width_, // ширина окошка
				height_, // высота окна
				HWND(NULL), // дескриптор родительского окошка
				NULL, // дескриптор меню 
				app_intance_handle_, // lдескриптор экземпляра приложения
				this); // ничего не передаём из WndProc

			if (!handle_) {
				// в случае некорректного создания окна (неверные параметры и тп):
				MessageBox(NULL, L"Не получилось создать окно!", L"Ошибка", MB_OK);
				return EXIT_FAILURE; // выходим из приложения
			}
			
			SetProcessDPIAware();//Вызывая эту функцию (SetProcessDPIAware), вы сообщаете системе, что интерфейс вашего приложения умеет сам правильно масштабироваться при высоких значениях DPI (точки на дюйм). Если вы не выставите этот флаг, то интерфейс вашего приложения может выглядеть размыто при высоких значениях DPI.
			device_context_ = GetDC(handle_);//CreateDC(L"DISPLAY", NULL, NULL, NULL);

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

		void Window::SetCaption(const wchar_t* caption)
		{
			win_caption_ = caption; 
			//SetWindowText(handle_, win_caption_);
		}

		void  Window::Show()
		{
			bool temp = ShowWindow(handle_, n_cmd_show_);
		}


		void Window::StartMessageLoop()
		{
			
			
			/*
				typedef struct tagMSG {
				HWND hwnd; // дескриптор окна, которому адресовано сообщение
				UINT message; // номер (идентификатор ) сообщения
				WPARAM wParam; // параметр сообщения wParam
				LPARAM lParam; //параметр сообщения lParam
				DWORD time; // время отправки сообщения
				POINT pt; //позиция курсора(в экранных координатах) в момент
				//отправки сообщения
				} MSG;
			*/

			MSG msg; // создём экземпляр структуры MSG для обработки сообщений

			msg = { 0 }; // Инициализация структуры сообщения 

			while (GetMessage(&msg, NULL, NULL, NULL) != NULL) {

				TranslateMessage(&msg);
				DispatchMessage(&msg);

			}

			// BOOL GetMessage(
			// MSG lpMsg, - адрес структуры куда поместить сообщение
			// HWND hWnd, - значение этого параметра равно NULL, 
			// UINT wMsgFilterMin, - Определяет целочисленную величину самого маленького значения сообщения, которое будет извлечено.
			// UINT wMsgFilterMax - Определяет целочисленную величину самого большого значения сообщения, которое будет извлечено.
			// *Если wMsgFilterMin и wMsgFilterMax являются оба нулевыми, функция GetMessage возвращает все доступные сообщения (то есть никакой фильтрации в диапазоне значений не выполняется).

			//Функция TranslateMessage переводит сообщения виртуальных клавиш в символьные сообщения. 
			//Символьные сообщения помещаются в очереди сообщений вызывающего потока для прочтения в следующий раз, 
			//когда поток вызовет функцию GetMessage или PeekMessage.

			//Функция DispatchMessage распределяет сообщение оконной процедуре WndProc.

		}

		uint Window::window_id_ = 0;




}