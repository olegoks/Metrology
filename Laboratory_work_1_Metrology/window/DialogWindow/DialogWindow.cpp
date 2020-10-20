#include "DialogWindow/DialogWindow.h"

DialogWindow::DialogWindow(HINSTANCE app_instance_handle)noexcept:
	Component(app_instance_handle),
	file_name_{L"Default_file_name.d"}
{

	ZeroMemory(&init_struct_, sizeof(OPENFILENAME));

	init_struct_.lStructSize = sizeof(OPENFILENAME);
	init_struct_.hwndOwner = NULL;
	init_struct_.lpstrFile = direct_;
	*(init_struct_.lpstrFile) = 0;
	init_struct_.nMaxFile = sizeof( direct_);
	init_struct_.lpstrFilter = NULL;
	init_struct_.nFilterIndex = 1;
	init_struct_.lpstrFileTitle = file_name_;
	*(init_struct_.lpstrFileTitle) = 0;
	init_struct_.nMaxFileTitle = sizeof(file_name_);
	init_struct_.lpstrInitialDir = NULL;
	init_struct_.Flags = OFN_EXPLORER;

}

const wchar_t*  DialogWindow::Create(HWND parent_handle)
{
	parent_handle_ = parent_handle;
	init_struct_.hwndOwner = parent_handle_;

	if (GetOpenFileName(&init_struct_)) {

		return direct_;
	
	}
	
	return nullptr;

}


