﻿#include "pch.h"
#include <iostream>
#include <string>
#include "Calc.h"

std::string noSpace(std::string in) {
	std::string out;
	for (auto sym : in) {
		if (sym != ' ')
			out.push_back(sym);
	}
	return out;
}

int main() {
	std::string exp;
	while (true) {
		std::cout << "Enter your question with (+, -, *, /, ^, sin, cos, sqrt, var='29deg'): ";
		std::getline(std::cin, exp);
		exp = noSpace(exp);
		Calc calc(exp);
		calc.controller()->setVar("var", TypedNum("29deg"));
		calc.parse();
		std::string ret;
		try {
			ret = calc.comp().toString();
		} catch (std::string err) {
			std::cout << "Error: " << err << std::endl << std::endl;
		}
		calc.print();
		std::cout << exp << " = " << ret << std::endl << std::endl;
	}
}
