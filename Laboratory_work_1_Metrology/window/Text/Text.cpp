#include "Text.h"

Text::Text(HWND handle, HINSTANCE app_intance_handle) :
	Component(handle, app_intance_handle),
	text_((wchar_t*)new wchar_t[14] { L"Default text." })
{



}

Text::Text(HINSTANCE app_instance_handle) :
	Component(app_instance_handle),
	text_(nullptr)
{

}

void Text::SetText(const wchar_t* const new_text) {

	//delete[] text_;
	text_ = new_text;
	SetWindowText(self_handle_, new_text);
}
Text::~Text() {

	//DestroyWindow(self_handle_);
	//SendMessage(self_handle_, WM_DESTROY, NULL, NULL);

}
void Text::Create(HWND parent_handle, const wchar_t* text, Style style) {

	if (self_handle_ == NULL) {

		parent_handle_ = parent_handle;
		
		delete[] text_;
		text_ = text;
		style_ = style;

		self_handle_ = CreateWindow(L"static", text_, style_,
			x_, y_, width_, height_, parent_handle_, NULL, app_instance_handle_, NULL);

	}



}

void Text::Destroy() const noexcept
{

	bool sw = ShowWindow(self_handle_,SW_HIDE);
	DestroyWindow(self_handle_); 

}

void Text::SetParametrs(uint x, uint y, uint width, uint height)noexcept{

	x_ = x;
	y_ = y;
	width_ = width;
	height_ = height;

}