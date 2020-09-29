#include "DialogWindow/DialogWindow.h"

DialogWindow::DialogWindow(HINSTANCE app_instance_handle)noexcept:
	Component(app_instance_handle),
	file_name_((wchar_t*) new wchar_t[20]{ L"Default_file_name.d" }),
	file_handle_(NULL)
{

	ZeroMemory(&init_struct_, sizeof(OPENFILENAME));
	init_struct_.lStructSize = sizeof(OPENFILENAME);
	init_struct_.hwndOwner = parent_handle_;
	init_struct_.lpstrFile = file_name_;
	init_struct_.lpstrFilter = L"\0";
	init_struct_.nFilterIndex = 1;
	init_struct_.nMaxFileTitle = NULL;
	init_struct_.lpstrInitialDir = NULL;
	init_struct_.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

}

void DialogWindow::Create(HWND parent_handle,const wchar_t* file_name)
{
	parent_handle_ = parent_handle;
	init_struct_.hwndOwner = parent_handle_;
	if (GetOpenFileName(&init_struct_)) {
		file_handle_ = CreateFile(init_struct_.lpstrFile,
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	}
	//else {
		uint error_info = CommDlgExtendedError();
	//}
}


