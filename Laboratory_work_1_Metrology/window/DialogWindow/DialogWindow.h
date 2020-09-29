#pragma once
#ifndef _DIALOG_WINDOW_H_
#define _DIALOG_WINDOW_H_

#include "Component/Component.h"

class DialogWindow :public Component {
private:
	OPENFILENAME init_struct_;
	HANDLE file_handle_;
	wchar_t* file_name_;
protected:
public:
	explicit DialogWindow(HINSTANCE app_instance_handle)noexcept;
	void Create(HWND parent_handle, const wchar_t* file_name);
};

#endif