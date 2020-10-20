#pragma once
#ifndef _DIALOG_WINDOW_H_
#define _DIALOG_WINDOW_H_

#include "Component/Component.h"

class DialogWindow :public Component {
private:

	OPENFILENAME init_struct_;
	wchar_t file_name_[260];
	wchar_t direct_[260];

protected:

public:

	explicit DialogWindow(HINSTANCE app_instance_handle)noexcept;
	const wchar_t* Create(HWND parent_handle);

};

#endif