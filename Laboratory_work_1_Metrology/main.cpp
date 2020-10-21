#include "window/Window.h"
#include "Button/Button.h"
#include "DialogWindow/DialogWindow.h"
#include "Parser.h"
#include "Console.h"
#include <iostream>
#include <cmath>

class MyWindow :public wnd::Window {
private:
	
protected:

	void WindowCreate()override;
	void ButtonClicked(uint notification_code, HWND button_handle)override;
	Text text;
	Text text_2;
	Button open_file_dialog_;
	Button parse_program_;
	DialogWindow open_file_;
	Parser parser_;

	std::vector<Text> table_;

public:

	explicit MyWindow(HINSTANCE hInstance) :Window(hInstance),
		text(hInstance),
		text_2(hInstance),
		open_file_dialog_(hInstance),
		parse_program_(hInstance),
		open_file_(hInstance)
	{


	}

};
LRESULT CALLBACK ChildProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	if (Message == WM_DESTROY)
	{
		return 0;
	}
	return DefWindowProc(hwnd, Message, wparam, lparam);
}
void MyWindow::WindowCreate() {

	SetCaption(_T("Metrology. Java parsing."));
	SetStyle(WS_OVERLAPPEDWINDOW | WS_MAXIMIZE);
	size_t width = GetSystemMetrics(SM_CXSCREEN);
	SetWidth(GetSystemMetrics(SM_CXSCREEN)+ 200);
	SetHeight(GetSystemMetrics(SM_CYSCREEN));
	SetShowState(SW_SHOWNORMAL);
	const Style text_style = WS_CHILD | WS_VISIBLE;
	const int show_state = SW_SHOWNORMAL;

	
	/*text_2.SetParametrs(100, 102, 100, 100);
	text_2.Create(WndHandle(), _T("Some text_2."), text_style);
	text_2.Show(show_state);*/

	open_file_dialog_.SetParametrs(10, 10, 150, 70);
	open_file_dialog_.Create(WndHandle(), _T("Open file"), text_style);
	open_file_dialog_.Show(show_state);

	parse_program_.SetParametrs(10, 10 + 70 + 10, 150, 70);
	parse_program_.Create(WndHandle(), _T("Parse program"), text_style);
	parse_program_.Show(show_state);

}



void MyWindow::ButtonClicked(uint notification_code, HWND button_handle) {

	if (button_handle == open_file_dialog_) {

		std::wstring w_dialog_file_name;
		w_dialog_file_name = open_file_.Create(WndHandle());
		std::string dialog_file_name(w_dialog_file_name.begin(), w_dialog_file_name.end());
		parser_.SetFileName(dialog_file_name);
		for (const auto& obj:table_)obj.Destroy();
		table_.clear();

	}

	if (button_handle == parse_program_) {
		
		parser_.clear();
		parser_.parseStrings();
		parser_.parseLexems();
		parser_.parseLexem();

		const size_t operators_count = parser_.GetOperatorsCount();
		const size_t operands_count = parser_.GetOperandsCount();

		parser_.outputOperands();
		std::cout << std::endl;
		parser_.outputOperators();
		std::cout << std::endl;
		
		const size_t separator = 10;
		const size_t index_width = 30;
		const size_t index_height = 20;
		const size_t count_width = 30;
		const size_t count_height = 20;
		const size_t x_table = 200;
		const size_t y_table = 10;
		const size_t text_height = 20;
		const size_t text_width = 300;
		const size_t lines_in_column = 49;
		const size_t new_column = separator + index_width + text_width + count_width;

		//table_.reserve(x_table + y_table);

		const Style text_style = WS_CHILD | WS_VISIBLE;
		const int show_state = SW_SHOWNORMAL;
		int offset_x = 0;
		int offset_y = 0;

		for (size_t i = 0; i < operators_count; i++)
		{

			Text index(app_instance_handle_);
			index.SetParametrs(x_table + offset_x, y_table + i * text_height +offset_y, index_width, index_height);
			std::string index_s = std::to_string(i);
			std::wstring index_w(index_s.begin(), index_s.end());
			index.Create(WndHandle(), index_w.c_str(), text_style);
			index.Show(show_state);
			table_.push_back(index);

			Text text_operator(app_instance_handle_);
			text_operator.SetParametrs(x_table + offset_x + index_width, y_table + i * text_height + offset_y, text_width, text_height);
			lexems current_lexem = parser_.GetOperator(i);
			std::string lexem_s(current_lexem.lexem);
			std::wstring lexem(lexem_s.begin(), lexem_s.end());
			text_operator.Create(WndHandle(), lexem.c_str(), text_style);
			text_operator.Show(show_state);
			table_.push_back(text_operator);

			Text text_operator_count(app_instance_handle_);
			text_operator_count.SetParametrs(x_table + offset_x + index_width + text_width + separator, y_table + i * text_height + offset_y, count_width, index_height);
			current_lexem = parser_.GetOperator(i);
			lexem_s = std::to_string(current_lexem.ammount);
			std::wstring lexem_w(lexem_s.begin(), lexem_s.end());
			text_operator_count.Create(WndHandle(), lexem_w.c_str(), text_style);
			text_operator_count.Show(show_state);
			table_.push_back(text_operator_count);

			if (i+3 > lines_in_column ) {
				offset_x = new_column + separator;
				offset_y = -(int)(lines_in_column * text_height);
			}
		}

		offset_x = 0;
		offset_y = 0;

		for (size_t i = 0; i < operands_count; i++)
		{

			Text index(app_instance_handle_);
			index.SetParametrs(x_table + offset_x + 2 * new_column + 2 * separator, y_table + i * text_height + offset_y, index_width, index_height);
			std::string index_s = std::to_string(i);
			std::wstring index_w(index_s.begin(), index_s.end());
			index.Create(WndHandle(), index_w.c_str(), text_style);
			index.Show(show_state);
			table_.push_back(index);
			
			Text text_operand(app_instance_handle_);
			text_operand.SetParametrs(x_table + offset_x + 2*new_column + 2 * separator + index_width, y_table + i * text_height + offset_y, text_width, text_height);
			lexems current_lexem = parser_.GetOperand(i);
			std::string lexem_s(current_lexem.lexem);
			std::wstring lexem(lexem_s.begin(), lexem_s.end());
			text_operand.Create(WndHandle(), lexem.c_str(), text_style);
			text_operand.Show(show_state);
			table_.push_back(text_operand);
			
			Text text_operand_count(app_instance_handle_);
			text_operand_count.SetParametrs(x_table + offset_x + 2 * new_column + 2 * separator + index_width + text_width + separator, y_table + i * text_height + offset_y, count_width, text_height);
			current_lexem = parser_.GetOperand(i);
			lexem_s = std::to_string(current_lexem.ammount);
			std::wstring lexem_w(lexem_s.begin(), lexem_s.end());
			text_operand_count.Create(WndHandle(), lexem_w.c_str(), text_style);
			text_operand_count.Show(show_state);
			table_.push_back(text_operand_count);

			if (i+3 > lines_in_column + 1){
				offset_x = new_column + separator;
				offset_y = -(int)(lines_in_column * text_height);
			}

		}

		size_t all_operators = 0;
		size_t all_operands = 0;

		size_t unique_operators = parser_.GetOperatorsCount();
		size_t unique_operands = parser_.GetOperandsCount();

		for (size_t i = 0; i < unique_operators; i++ )all_operators += parser_.GetOperator(i).ammount;
		for (size_t i = 0; i < unique_operands; i++)all_operands += parser_.GetOperand(i).ammount;
		
		Text unique(app_instance_handle_);
		unique.SetParametrs(separator, 170, 150, 150);
		std::wstring unique_metrics = (L"Уникальных операторов: " + std::to_wstring(unique_operators) + L" \nВхождения операторов: " + std::to_wstring(all_operators) + L"\nУникальные операнды: " + std::to_wstring(unique_operands) + L"\nВхождения операндов: " + std::to_wstring(all_operands));
		unique.Create(WndHandle(), unique_metrics.c_str(), text_style);
		unique.Show(show_state);
		table_.push_back(unique);

		Text program_metrics(app_instance_handle_);
		program_metrics.SetParametrs(separator, 170 + 150 + separator, 150, 150);
		std::wstring program_metrics_w = (L"Объем программы: " + std::to_wstring( static_cast<size_t>( (all_operators + all_operands) * (log(unique_operators + unique_operands)/log(2)))) + L" \nДлина программы: " + std::to_wstring(all_operators + all_operands) + L"\nСловарь программы: " + std::to_wstring(unique_operators + unique_operands));
		program_metrics.Create(WndHandle(), program_metrics_w.c_str(), text_style);
		program_metrics.Show(show_state);
		table_.push_back(program_metrics);

	}

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//Console console("Log console.");
	MyWindow main_window(hInstance);
	main_window.Create();
	main_window.Show();
	MyWindow::StartMessageLoop();
	return EXIT_SUCCESS;
}

//Стили окна
//WS_BORDER	0x00800000	Окно имеет тонкую границу в виде линии.
//WS_CAPTION	0x00C00000	Окно имеет строку заголовка.
//WS_CHILD	0x40000000	Окно является дочерним.
//WS_DISABLED	0x08000000	Окно является изначально неактивным.
//WS_GROUP	0x00020000	Окно группирует другие управляющие элементы.
//WS_HSCROLL	0x00100000	Окно содержит горизонтальную полосу прокрутки.
//WS_MAXIMIZE	0x01000000	Исходный размер окна – во весь экран.
//WS_MINIMIZE	0x20000000	Исходно окно свернуто.
//WS_OVERLAPPED	0x00000000	Окно может быть перекрыто другими окнами.
//WS_POPUP	0x80000000	Всплывающее окно.
//WS_SYSMENU	0x00080000	Окно имеет системное меню в строке заголовка.
//WS_VISIBLE	0x10000000	Окно изначально видимое.
//WS_VSCROLL	0x00200000	Окно имеет вертикальную полосу прокрутки.

///Типы показа окна
//SW_HIDE - Скрывает окно и активизирует другое окно.
//SW_MAXIMIZE - Развертывает определяемое окно.
//SW_MINIMIZE - Свертывает определяемое окно и активизирует следующее окно верхнего уровня в Z - последовательности.
//SW_RESTORE - Активизирует и отображает окно.Если окно свернуто или развернуто, Windows восстанавливает в его первоначальных размерах и позиции.Прикладная программа должна установить этот флажок при восстановлении свернутого окна.
//SW_SHOW - Активизирует окно и отображает его текущие размеры и позицию.
//SW_SHOWDEFAULT - Устанавливает состояние показа, основанное на флажке SW_, определенном в структуре STARTUPINFO, переданной в функцию CreateProcess программой, которая запустила прикладную программу.
//SW_SHOWMAXIMIZED - Активизирует окно и отображает его как развернутое окно.
//SW_SHOWMINIMIZED - Активизирует окно и отображает его как свернутое окно.
//SW_SHOWMINNOACTIVE - Отображает окно как свернутое окно.Активное окно остается активным.
//SW_SHOWNA - Отображает окно в его текущем состоянии.Активное окно остается активным.
//SW_SHOWNOACTIVATE - Отображает окно в его самом современном размере и позиции.Активное окно остается активным.
//SW_SHOWNORMAL - Активизирует и отображает окно.Если окно свернуто или развернуто, Windows восстанавливает его в первоначальном размере и позиции.Прикладная программа должна установить этот флажок при отображении окна впервые.