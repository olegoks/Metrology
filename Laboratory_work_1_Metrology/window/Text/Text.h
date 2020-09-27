#pragma once
#ifndef _TEXT_H_
#define _TEXT_H_

#include "Component/Component.h"
#include "WindowStructures.h"

class Text :public Component {
private:

protected:

	HWND self_handle_;

public:

	Text(HWND handle, HINSTANCE app_intance_handle):
		Component(handle, app_intance_handle)
	{
		self_handle_ = CreateWindow(L"static", L"Hello world!", WS_CHILD | WS_VISIBLE,
			x_, y_, width_, height_, handle_, 0, app_intance_handle_, NULL);
	}

	/*Text(HINSTANCE app_intance_handle):Component(app_intance_handle) {

	}*/

	Text(HWND handle, HINSTANCE app_intance_handle, uint width, uint height, uint x, uint y):Component(handle, app_intance_handle, width, height, x, y) {
			//CreateWindowEx(WS_EX_CLIENTEDGE, L"edit", L"", WS_CHILD | WS_VISIBLE | ES_RIGHT,
			//10, 10, 80, 30, handle_, (HMENU)10000, app_intance_handle, NULL);

			ShowWindow(self_handle_, SW_SHOWNORMAL);
	}

	bool Show() {
		return ShowWindow(self_handle_, SW_SHOWNORMAL);
	}

};
#endif 