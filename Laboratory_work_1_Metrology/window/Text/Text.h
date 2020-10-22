#pragma once
#ifndef _TEXT_H_
#define _TEXT_H_

#include "Component/Component.h"
#include "WindowStructures.h"

class Text :public Component {
private:

protected:

	const wchar_t* text_ = nullptr;

public:

	Text(HWND handle, HINSTANCE app_instance_handle);
	Text(HINSTANCE app_instance_handle);
	void SetText(const wchar_t* const new_text);
	void Create(HWND parent_handle, const wchar_t* text, Style style);
	void Destroy()const noexcept;
	void SetParametrs(uint x, uint y, uint width, uint height)noexcept;
	Text(HWND handle, HINSTANCE app_intance_handle, uint width, uint height, uint x, uint y):
		Component(handle, app_intance_handle, width, height, x, y) {

			ShowWindow(self_handle_, SW_SHOWNORMAL);
	}

	~Text();
	bool Show(int show_state) {

		show_state_ = show_state;
		return ShowWindow(self_handle_, show_state_);

	}

};
#endif 