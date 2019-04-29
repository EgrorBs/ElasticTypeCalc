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
	}

	return this->root->comp();
}


Calc::~Calc()
{
}
