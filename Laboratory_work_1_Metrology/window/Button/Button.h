#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_
#include "Component/Component.h"

class Button :public Component {
private:
	const wchar_t* text_;
protected:
public:

	explicit Button(HINSTANCE app_instance_handle)noexcept;
	void SetParametrs(uint x, uint y, uint width, uint height)noexcept;
	void Create(HWND parent_handle, const wchar_t* button_text, Style style);
	void Show(int show_state);
	friend bool operator== (HWND button_handle, const Button& button);
};
#endif