#pragma once

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>
#include <tchar.h>
#include "Structures.h"
#include "WindowStructures.h"

namespace wnd {

	typedef unsigned int uint;
	typedef DWORD Style;

	class Window {
	private:

		unsigned int width_;
		unsigned int height_;
		unsigned int x_;
		unsigned int y_;
		const wchar_t* win_caption_;
		HWND handle_;
		HINSTANCE app_intance_handle_;
		HDC device_context_;
		Style style_;
		int n_cmd_show_;
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM  wParam, LPARAM lParam);
		

	protected:

		int Create();
		bool RegisterWindowClass();
		void Show();
		virtual void WindowCreate() {};
		void SetParametrs(const uint width, const uint height, const uint x, const uint y, DWORD style);
		inline void SetStyle(Style style)noexcept { style_ = style; };
		inline void SetCaption(const wchar_t* caption) noexcept { win_caption_ = caption; };
		inline void SetHeight(uint height)noexcept { height_ = height; };
		inline void SetWidth(uint width)noexcept { width_ = width; };
		inline void SetPosition(uint x, uint y)noexcept { x_ = x; y_ = y; };

	public:
		static void StartMessageLoop();
		explicit Window(HINSTANCE appIntanceHandle)noexcept;
		~Window();



	};

};

#endif 