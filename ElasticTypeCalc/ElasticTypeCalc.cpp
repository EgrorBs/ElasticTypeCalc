#include "pch.h"
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
		std::cout << "Enter your question with (+, -, *, /, ^): ";
		std::getline(std::cin, exp);
		exp = noSpace(exp);
		Calc calc(exp);
		try {
			std::cout << exp << " = " << calc.comp().toString() << std::endl << std::endl;
		}
		catch (std::string err) {
			std::cout << "Error: " << err << std::endl << std::endl;
		}
	}
}
