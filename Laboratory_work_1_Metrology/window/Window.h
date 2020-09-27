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
		HWND handle_;
		HINSTANCE app_intance_handle_;
		HDC device_context_;
		Style style_;
		int n_cmd_show_;
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM  wParam, LPARAM lParam);
		static uint window_id_;
		uint id_;
		wchar_t* GenerateDefaultClassName();

	protected:

		int CreateWnd();
		bool RegisterWindowClass();
		void Show();
		void SetParametrs(const uint width, const uint height, const uint x, const uint y, DWORD style);
		inline void SetStyle(Style style)noexcept { style_ = style; };
		void SetCaption(const wchar_t* caption);
		inline void SetHeight(uint height)noexcept { height_ = height; };
		inline void SetWidth(uint width)noexcept { width_ = width; };
		inline void SetPosition(uint x, uint y)noexcept { x_ = x; y_ = y; };
		HWND WndHandle() { return handle_; };
		HINSTANCE AppInstanceHandle() { return app_intance_handle_; };
		virtual void WindowCreate() {};

	public:

		static void StartMessageLoop();
		explicit Window(HINSTANCE appIntanceHandle)noexcept; //Style style)noexcept;
		~Window();

	};




};

#endif 