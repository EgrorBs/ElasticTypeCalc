#include "pch.h"
#include "Calc.h"

#include <regex>
#include <sstream>
#include <iostream>

#define ANSI_RGB_FG(r, g, b) \
	("\033[38;2;" + std::to_string((r)) + ";" + std::to_string((g)) + ";" + std::to_string((b)) + "m")

#define ANSI_RGB_BG(r, g, b) \
	("\033[48;2;" + std::to_string((r)) + ";" + std::to_string((g)) + ";" + std::to_string((b)) + "m")

#define ANSI_ULN ("\033[4m")

#define ANSI_CLR_VAL (ANSI_RGB_FG(0, 255, 255))
#define ANSI_CLR_OP (ANSI_RGB_FG(255, 255, 0))

#define ANSI_CLR_NULL ("\033[0m")

#define ANSI_SET_POS(x, y) ("\033[" + std::to_string((x)) + ";" + std::to_string((y)) + "H")

#define ANSI_CLRSCR ("\033[J")

Calc::Calc(std::string exp): 
	exp(exp) {
}

TypedNum Calc::comp() {
	if (!this->root)
		this->parse();

	return this->root->comp();
}

TypedNum Calc::cComp() const {
	if (this->root)
		return this->root->comp();
	else
		throw "no parsed";
}

void Calc::parse() {
	if (this->root)
		delete this->root;
	
	this->root = new CalcNode(this->exp, &this->varFnc);
	this->root->parse();
}

void Calc::print(char fillSym, char splitSym) const {
	if (this->root) {
		std::string out = this->root->toLinedText(-1, fillSym, splitSym).str();
		std::cout << "mapping colors...\n" << out;
		out = std::regex_replace(out, std::regex(R"(((\-|)([0-9])+(\.([0-9]))*))"), ANSI_CLR_VAL + ANSI_ULN + "$1" + ANSI_CLR_NULL);
		out = std::regex_replace(out, std::regex(R"((([a-ln-zA-Z])([a-zA-Z])*))"), ANSI_RGB_FG(255, 128, 255) + "$1" + ANSI_CLR_NULL);
		out = std::regex_replace(out, std::regex(R"((\+|\-|\*|\/)([^0-9]))"), ANSI_CLR_OP + ANSI_ULN + "$1" + ANSI_CLR_NULL + "$2");
		out = std::regex_replace(out, std::regex(R"((\)" + std::string(1, fillSym) + R"())"), ANSI_RGB_FG(255, 64, 64) + "$1" + ANSI_CLR_NULL);
		out = std::regex_replace(out, std::regex(R"((\(|\)))"), ANSI_RGB_FG(64, 255, 64) + "$1" + ANSI_CLR_NULL);
		out = std::regex_replace(out, std::regex(R"((\)" + std::string(1, splitSym) + R"())"), ANSI_RGB_FG(255, 64, 64) + "$1" + ANSI_CLR_NULL);
		std::cout << "mapped colors.\n" << out;
		return;
	} else
		throw "no parsed";
}

CalcFncVarController* Calc::controller()
{
	return &this->varFnc;
}

Calc::~Calc() {
	delete this->root;
}
