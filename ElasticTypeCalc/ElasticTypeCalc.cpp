#include "pch.h"
#include <iostream>
#include <string>
#include "Calc.h"

#define TN TypedNum

int main() {
	std::string exp = "1a/2-0b";
	while (true) {
		std::cout << "Enter your question with (+, -, *, /): ";
		std::cin >> exp;
		Calc calc(exp);
		std::cout << exp << " = " << calc.comp().toString() << std::endl;
	}
	//std::cout << (TN("2t") + TN("5")).toString();
}
