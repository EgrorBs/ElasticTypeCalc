#include "pch.h"
#include "Calc.h"


Calc::Calc(std::string exp) {
	this->exp = exp;
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
	
	this->root = new CalcNode(this->exp);
	this->root->parse();
}

void Calc::print() const {
	if (this->root)
		return this->root->print();
	else
		throw "no parsed";
}

Calc::~Calc() {
	delete this->root;
}
