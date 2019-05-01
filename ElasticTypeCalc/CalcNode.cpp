#include "pch.h"
#include "CalcNode.h"

#include <functional>
#include <array>
#include <iostream>

CalcNode::CalcNode(std::string exp) {
	this->exp = exp;
}

CalcNode::~CalcNode()
{
	if (this->left)
		delete this->left;

	if (this->right)
		delete this->right;
}

void CalcNode::parse() {
	int brc = 0;
	bool isBrc = false;
	for (int i = this->exp.length() - 1; i >= 1; i--) {
		char sym = this->exp[i];

		if (sym == ')') brc++;
		if (sym == '(') brc--;
		if (brc == 0) {
			isBrc = false;
			break;
		}
		isBrc = true;
	}

	if (isBrc) {
		this->type = BRC;
		this->left = new CalcNode(this->exp.substr(1, this->exp.length() - 2));
		this->left->parse();
		return;
	}

	for (int i = this->exp.length() - 1; i >= 0; i--) {
		char sym = this->exp[i];

		if (sym == ')') brc++;
		if (sym == '(') brc--;
		if (brc != 0) continue;

		if (sym == '+' || sym == '-') {
			this->left = new CalcNode(this->exp.substr(0, i));
			if (sym == '+')
				this->type = SUM;
			else
				this->type = SUB;
			this->right = new CalcNode(this->exp.substr(i + 1));

			this->left->parse();
			this->right->parse();

			return;
		}
	}
	brc = 0;
	for (int i = this->exp.length() - 1; i >= 0; i--) {
		char sym = this->exp[i];

		if (sym == ')') brc++;
		if (sym == '(') brc--;
		if (brc != 0) continue;

		if (sym == '*' || sym == '/') {
			this->left = new CalcNode(this->exp.substr(0, i));
			if (sym == '*')
				this->type = MUL;
			else
				this->type = DIV;
			this->right = new CalcNode(this->exp.substr(i + 1));

			this->left->parse();
			this->right->parse();

			return;
		}
	}
	brc = 0;
	for (int i = this->exp.length() - 1; i >= 0; i--) {
		char sym = this->exp[i];

		if (sym == ')') brc++;
		if (sym == '(') brc--;
		if (brc != 0) continue;

		if (sym == '^') {
			this->left = new CalcNode(this->exp.substr(0, i));
			this->type = POW;
			this->right = new CalcNode(this->exp.substr(i + 1));

			this->left->parse();
			this->right->parse();

			return;
		}
	}

	this->type = NUM;
	this->val = TypedNum(this->exp);
}

TypedNum CalcNode::comp() {
	if (!isCached) {
		switch (this->type) {
			case NUM: break;
			case SUM: this->val = this->left->comp() + this->right->comp(); break;
			case SUB: this->val = this->left->comp() - this->right->comp(); break;
			case MUL: this->val = this->left->comp() * this->right->comp(); break;
			case DIV: this->val = this->left->comp() / this->right->comp(); break;
			case POW: this->val = this->left->comp() ^ this->right->comp(); break;
			case BRC: this->val = this->left->comp(); break;
			default: throw std::exception("Comp: unknown type!");
		}
		this->isCached = true;
	}
	return this->val;
}

TypedNum CalcNode::cComp() const
{
	switch (this->type) {
		case NUM: return this->val;
		case SUM: return this->left->cComp() + this->right->cComp();
		case SUB: return this->left->cComp() - this->right->cComp();
		case MUL: return this->left->cComp() * this->right->cComp();
		case DIV: return this->left->cComp() / this->right->cComp();
		case POW: return this->left->cComp() ^ this->right->cComp();
		case BRC: return this->left->cComp();
		default: throw std::exception("cComp: unknown type!");
	}
}

void CalcNode::print(int tabsC) const {
	std::string tabs;
	for (int i = 0; i < tabsC; i++)
		tabs += "|  ";

	if (this->left && this->type != BRC)
		this->left->print(tabsC + 1);

	if (this->left && this->type == BRC) {
		std::cout << tabs << " (" << std::endl;
		this->left->print(tabsC);
	}
	std::cout << tabs;

	std::string value;

	if (this->isCached)
		value = "(*" + this->val.toString() + "*)";

	switch (this->type) {
		case NUM: std::cout << "# " << this->val.toString() << std::endl; break;
		case SUM: std::cout << "|  + " << value << std::endl; break;
		case SUB: std::cout << "|  - " << value << std::endl; break;
		case MUL: std::cout << "|  * " << value << std::endl; break;
		case DIV: std::cout << "|  / " << value << std::endl; break;
		case POW: std::cout << "|  ^ " << value << std::endl; break;
		case BRC: std::cout << " )" << std::endl; break;
	}
	if (this->right)
		this->right->print(tabsC + 1);
}
