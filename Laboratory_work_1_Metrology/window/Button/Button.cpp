#include "Button/Button.h"

Button::Button(HINSTANCE app_instance_handle) noexcept:
	Component(app_instance_handle),
	text_((const wchar_t*) new wchar_t[10] {L"Click me!"})
{


}

void Button::SetParametrs(uint x, uint y, uint width, uint height) noexcept
{
	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;
}

void Button::Create(HWND parent_handle, const wchar_t* button_text, Style style) {

	if (self_handle_ == NULL) {

		parent_handle_ = parent_handle;
		style_ = style;
		delete[] text_;
		text_ = button_text;

		self_handle_ = CreateWindow(L"button", text_, style_,x_, y_, width_, height_, 
			parent_handle_, menu_handle_, app_instance_handle_, NULL);
		
	}

}

void Button::Show(int show_state) {

	show_state_ = show_state;

	ShowWindow(self_handle_, show_state);
}

bool operator==(HWND button_handle, const Button& button)
{
	return (button_handle == button.self_handle_);
}
