#include "Parser.h"

#include <iostream>
#include <fstream>

void Parser::trim(string& str) {
	int j = 0;
	while ((str[j] == ' ') && (j < str.size())) {
		j++;
	}
	str.erase(0, j);
}

int Parser::operandExists(string& operand)
{
	for (int i = 0; i < operands.size(); i++) {
		if (!strcmp(operands[i].lexem, operand.c_str())) return i + 1;
	}

	return 0;
}

int Parser::operatorExists(string& operator1)
{
	for (int i = 0; i < operators.size(); i++) {
		if (!strcmp(operators[i].lexem, operator1.c_str())) return i + 1;
	}

	return 0;
}

void Parser::addOperand(string& operand)
{
	int i;
	if (i = operandExists(operand)) {
		operands[i - 1].ammount++;
	}
	else {
		lexems buff;
		buff.ammount = 1;
		
		strcpy_s(buff.lexem, operand.c_str());
		operands.push_back(buff);
	}
}

void Parser::addOperator(string& operator1)
{
	int i = operatorExists(operator1);
	if (i) {

		operators[i - 1].ammount++;

	}
	else {

		lexems buff;
		buff.ammount = 1;
		strcpy_s(buff.lexem, operator1.c_str());
		operators.push_back(buff);

	}
}

int Parser::lexemInJavaKeywords(string& lexem)
{
	for (int i = 0; i < 33; i++) {
		if (lexem == java_keywords[i]) return 1;
	}
	return 0;
}

int Parser::lexemInNotOperators(string& lexem)
{
	for (int i = 0; i < 32; i++) {
		if (lexem == not_operators[i]) return 1;
	}
	return 0;
}

int Parser::overallOperators()
{
	int result = 0;
	for (int i = 0; i < operators.size(); i++) {
		result += operators[i].ammount;
	}
	return result;
}

int Parser::overallOperands()
{
	int result = 0;
	for (int i = 0; i < operands.size(); i++) {
		result += operands[i].ammount;
	}
	return result;
}

void Parser::outputOperators()
{
	using namespace std;

	for (int i = 0; i < operators.size(); i++) {
		cout << operators[i].lexem << endl;
		cout << operators[i].ammount << endl;
	}
}

void Parser::outputOperands()
{
	using namespace std;

	for (int i = 0; i < operands.size(); i++) {

		cout << operands[i].lexem << endl;
		cout << operands[i].ammount << endl;

	}
}

void Parser::parseStrings()
{
	string alphabet = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM "; // костыль
	int comment = 0, place = 0;
	string str1;
	std::ifstream infile(file_name_);

	while (getline(infile, str1)) {

		trim(str1);

		if ((str1.find("private") == 0) && (str1.find("(") != string::npos)) {
			string buff01 = "";
			for (int pt = 0; pt < str1.size(); pt++) {
				if (alphabet.find(str1[pt]) == string::npos) {
					buff01 += str1[pt];
				}
			}
			str1 = buff01;
		}


		if (comment) {
			if ((place = str1.find("*/")) != string::npos) {
				comment = 0;
			}
		}
		else
		{
			if ((place = str1.find("/*")) == string::npos) {
				if (str1.size() > 0) {
					arr.push_back(str1);
				}
			}
			else comment = 1;
		}
	}

	
}

void Parser::parseLexems()
{
	string inbuff;
	string outbuff;
	int size = arr.size();
	int length = 0;
	for (int i = 0; i < size; i++) {
		inbuff = arr[i];
		if ((inbuff.find("//")) == string::npos) {
		
			int start = 0;
			outbuff = "";
			for (int j = 0; j < inbuff.size(); j++) {
				if (inbuff[j] == ' ') {
					outbuff = inbuff.substr(start, (j - start));
					trim(outbuff);
					if (outbuff != "") {
						arr2.push_back(outbuff);
						
					}
					start = j + 1;
				}
				else if ((inbuff[j] == '(') || (inbuff[j] == '[')) {
					outbuff = inbuff.substr(start, (j - start + 1));
					trim(outbuff);
					if (outbuff != "") {
						arr2.push_back(outbuff);
					
					}
					start = j + 1;
				}

			}

			outbuff = inbuff.substr(start, (inbuff.size() - start));
			trim(outbuff);
			if (outbuff != "") {
				arr2.push_back(outbuff);
			
			}
		}

	}

}

int Parser::parseLexem()
{
	int strFlag = 0;
	string buff;
	size_t size = arr2.size();

	for (int i = 0; i < size; i++) {

		if (strFlag) {

			int j = 0;
			buff += " ";

			while ((j < arr2[i].size()) && strFlag) {

				if (arr2[i][j] != '"')buff += arr2[i][j];
			
				else
				{
					buff += arr2[i][j];
					strFlag = 0;
					addOperand(buff);
				}

				j++;
			}
			arr2[i].erase(0, j);
		}
		else if (arr2[i][0] == '"') {
			buff = '"';
			strFlag = 1;
			int j = 1;
			while ((j < arr2[i].size()) && strFlag) {
				if (arr2[i][j] != '"') {
					buff += arr2[i][j];
				}
				else
				{
					buff += arr2[i][j];
					strFlag = 0;
					addOperand(buff);
				}
				j++;
			}
			arr2[i].erase(0, j);
		}
		if (arr2[i].size() != 0) {
			if ((arr2[i].find("(") == arr2[i].size() - 1) && (arr2[i].find("(") > 1)) {
				// prev = (*src)[i];
				arr2[i].append(")");
				addOperator(arr2[i]);
				string tochka = ".";
				for (int j = 0; j < arr2[i].size(); j++) {
					if (arr2[i][j] == '.') addOperator(tochka);
				}
				string skobki = "()";
				addOperator(skobki);
				arr2[i] = "FUCK";
			}
			else {
				int statement_start;
				for (int j = 0; j < 39; j++) {
					if ((statement_start = arr2[i].find(java_statements[j])) != string::npos) {
						string buff = java_statements[j];
						addOperator(buff);
						arr2[i].erase(statement_start, buff.size());
					}
				}
				if ((statement_start = arr2[i].find("{")) != string::npos) {
					string skobki0 = "{}";
					addOperator(skobki0);
					arr2[i].erase(statement_start, 1);
				}
				if ((statement_start = arr2[i].find("}")) != string::npos) {
					arr2[i].erase(statement_start, 1);
				}
				if ((statement_start = arr2[i].find("[")) != string::npos) {
					string skobki1 = "[]";
					addOperator(skobki1);
					arr2[i].erase(statement_start, 1);
				}
				if ((statement_start = arr2[i].find("]")) != string::npos) {
					arr2[i].erase(statement_start, 1);
				}
				if ((statement_start = arr2[i].find("(")) != string::npos) {
					string skobki2 = "()";
					addOperator(skobki2);
					arr2[i].erase(statement_start, 1);
				}
				if ((statement_start = arr2[i].find(")")) != string::npos) {
					arr2[i].erase(statement_start, 1);
				}
				if ((statement_start = arr2[i].find(")")) != string::npos) {
					arr2[i].erase(statement_start, 1);
				}

				if ((statement_start = arr2[i].find(",")) != string::npos) {
					arr2[i].erase(statement_start, 1);
					string zapytaya = ",";
					addOperator(zapytaya);
				}

				if (lexemInJavaKeywords((arr2[i]))) {
					addOperator(arr2[i]);
					arr2[i] = "FUCK";
				}
				else if (lexemInNotOperators(arr2[i])) {
					continue;
				}
				else {
					if (arr2[i] != "") {
						addOperand((arr2[i]));
						string tochka = ".";
						for (int j = 0; j < arr2[i].size(); j++) {
							if (arr2[i][j] == '.') addOperator(tochka);
						}
						arr2[i] = "FUCK";

					}
				}

			}
		}
	}

	return 0;
}

void Parser::SetFileName(const string& file_name) noexcept
{
	file_name_ = file_name;

	arr.clear();
	arr2.clear();
	operands.clear();
	operators.clear();

}
