#pragma once

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>
#include <tchar.h>
#include "Structures.h"
#include "WindowStructures.h"
#include "Text/Text.h"
#include "Component/Component.h"

namespace wnd {

	class Window:public Component {
	private:

		const wchar_t* win_caption_;
		const wchar_t* sz_class_name_;
		HDC device_context_;
		uint id_;
		static uint number_of_windows_;
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM  wParam, LPARAM lParam);
		wchar_t* GenerateDefaultClassName();
		int CreateWnd();
		bool RegisterWindowClass();
		uint NewWindowId();

	protected:

		void SetParametrs(const uint width, const uint height, const uint x, const uint y, DWORD style);
		void SetStyle(Style style)noexcept;
		void SetCaption(const wchar_t* caption);
		inline void SetHeight(uint height)noexcept { height_ = height; };
		inline void SetWidth(uint width)noexcept { width_ = width; };
		inline void SetPosition(uint x, uint y)noexcept { x_ = x; y_ = y; };
		inline HWND WndHandle()const noexcept { return self_handle_; };
		inline HINSTANCE AppInstanceHandle()const noexcept { return app_instance_handle_; };
		virtual void WindowCreate() {};
		virtual void ButtonClicked(uint notification_code, HWND button_handle) {};
	public:

		void Create();
		void Show(int show_state);
		static void StartMessageLoop();
		explicit Window(HINSTANCE appIntanceHandle)noexcept;
		~Window();

	};

};

#endif 