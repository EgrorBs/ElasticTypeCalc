#include "pch.h"
#include "Calc.h"


Calc::Calc(std::string exp) {
	this->exp = exp;
}

TypedNum Calc::comp()
{
	if (!this->root) {
		this->root = new CalcNode(this->exp);
		this->root->parse();
		this->print();
	}

	return this->root->comp();
}

void Calc::print() {
	this->root->print(0);
}


Calc::~Calc()
{
}
