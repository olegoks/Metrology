#pragma once
#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

static const string java_keywords[33] = { "abstract", "continue", "for", "new",
   "switch", "assert", "default", "goto",
"synchronized", "do", "if", "this", "break", "implements",
"protected", "throw", "else" , "throws", "case", "enum", "instanceof", "return",
"transient", "catch", "extends", "try", "interface",
"finally", "strictfp", "volatile", "native", "super", "while" };

static const string java_statements[39] = { ">>>=", ">>=", "<<=", "==", "<=", ">=", "!=", "&&", "||", "++", "--", "->", "::", "+=", "-=", "*=", "/=", "&=", "|=", "^=", "%=",
	 "@", ",", ";", "=", ">", "<", "!", "~", "?", ":","-", "*", "/", "&", "|", "^", "%" , "+" };

static const string not_operators[32] = { "void", "#", "integer", "string", "java", "System", "io", "IOException", "com",
	"company",  "NumberFormatException", "in", "public", "import", "static", "package", "class", "float", "short", "byte", "double",
	"const", "long", "word", "out", "boolean", "BufferedReader", "InputStreamReader", "int", "char", "final", "private" };

static const string not_in[33] = { "void", "#", "integer", "String", "string", "Integer", "java", "System", "io", "IOException", "com",
	"company", "Main", "NumberFormatException", "in", "public", "import", "static", "package", "class", "float", "short", "byte", "double",
	"const", "long", "word", "out", "boolean", "BufferedReader", "InputStreamReader", "int", "char" };

struct lexems {

	char lexem[50]; 
	int ammount;

};

class Parser final{
private:

	std::vector<lexems> operators, operands;
	std::vector<string> arr, arr2;
	std::string file_name_;
	void trim(string& str);
	int operandExists(string& operand);
	int operatorExists(string& operator1);
	void addOperand(string& operand);
	void addOperator(string& operator1);
	int lexemInJavaKeywords(string& lexem);
	int lexemInNotOperators(string& lexem);
	int overallOperators();
	int overallOperands();
	
protected:
public:

	void outputOperators();
	void outputOperands();
	void parseStrings();
	void parseLexems();
	int parseLexem();
	void SetFileName(const string& file_name)noexcept;
	explicit Parser(const string& file_name)noexcept:file_name_(file_name){}
	explicit Parser()noexcept = default;
	inline size_t GetOperatorsCount() const noexcept { return operators.size(); }
	inline size_t GetOperandsCount() const noexcept { return operands.size(); }
	const lexems& GetOperand(const size_t index)const noexcept { return operands[index]; };
	const lexems& GetOperator(const size_t index)const noexcept { return operators[index]; };
	void clear() { arr.clear(); arr2.clear(); operators.clear(); operands.clear(); }
};

#endif _PARSER_H_

