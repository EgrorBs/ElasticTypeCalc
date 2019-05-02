#include "pch.h"
#include "CalcNode.h"

#include <functional>
#include <cctype>
#include <array>
#include <iostream>

CalcNode::CalcNode(std::string exp, CalcFncVarController* fncVar) :
	exp(exp),
	fncVar(fncVar) {
}

CalcNode::~CalcNode() {
	if (this->left)
		delete this->left;

	if (this->right)
		delete this->right;
}

void CalcNode::parse() {
	if (this->exp.length() == 0) {
		this->type = NUM;
		this->val = TypedNum("0");
		return;
	}

	bool isNamedAccepted = (this->fncVar != nullptr);

	bool isBrc = true, 
		 isNamed = true;
	int brc = 0,
		i = 0,
		nlen = 0,
		sym = ' ';
	for (; isNamedAccepted && i < this->exp.length(); i++) {
		sym = this->exp[i];

		if (sym == '(' && i > 0) {
			isNamed = true;
			nlen = i;
			break;
		}

		if (sym == '(' && i == 0) {
			isNamed = false;
			i = 0;
			break;
		}

		if (!std::isalpha(sym)) {
			isNamed = false;
			break;
		}
	}

	if (!(i < this->exp.length() - 1))
		isBrc = false;

	for (; i < this->exp.length() - 1; i++) {
		sym = this->exp[i];

		if (sym == '(') brc++;
		if (sym == ')') brc--;
		if (brc <= 0) {
			isBrc = false;
			break;
		}
	}


	if (isBrc) {
		std::string name = this->exp.substr(0, nlen);
		if (isNamedAccepted && isNamed && this->fncVar->isFnc(name)) {
			this->type = FNC;
			this->symName = name;
			this->left = new CalcNode(this->exp.substr(nlen + 1, this->exp.length() - nlen - 2), this->fncVar);
			this->left->parse();
			return;
		} else if (!isNamed) {
			this->type = BRC;
			this->left = new CalcNode(this->exp.substr(1, this->exp.length() - 2), this->fncVar);
			this->left->parse();
			return;
		}
	} else {
		if (isNamedAccepted && isNamed && this->fncVar->isVar(this->exp)) {
			this->type = VAR;
			this->symName = this->exp;
			return;
		}
	}
	brc = 0;
	for (int i = this->exp.length() - 1; i >= 0; i--) {
		sym = this->exp[i];

		if (sym == ')') brc++;
		if (sym == '(') brc--;
		if (brc != 0) continue;

		if (sym == '+' || sym == '-') {
			this->left = new CalcNode(this->exp.substr(0, i), this->fncVar);
			if (sym == '+')
				this->type = SUM;
			else
				this->type = SUB;
			this->right = new CalcNode(this->exp.substr(i + 1), this->fncVar);

			this->left->parse();
			this->right->parse();

			return;
		}
	}
	brc = 0;
	for (int i = this->exp.length() - 1; i >= 0; i--) {
		sym = this->exp[i];

		if (sym == ')') brc++;
		if (sym == '(') brc--;
		if (brc != 0) continue;

		if (sym == '*' || sym == '/') {
			this->left = new CalcNode(this->exp.substr(0, i), this->fncVar);
			if (sym == '*')
				this->type = MUL;
			else
				this->type = DIV;
			this->right = new CalcNode(this->exp.substr(i + 1), this->fncVar);

			this->left->parse();
			this->right->parse();

			return;
		}
	}
	brc = 0;
	for (int i = this->exp.length() - 1; i >= 0; i--) {
		sym = this->exp[i];

		if (sym == ')') brc++;
		if (sym == '(') brc--;
		if (brc != 0) continue;

		if (sym == '^') {
			this->left = new CalcNode(this->exp.substr(0, i), this->fncVar);
			this->type = POW;
			this->right = new CalcNode(this->exp.substr(i + 1), this->fncVar);

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
			case FNC: this->val = this->fncVar->compFnc(this->symName, this->left->comp()); break;
			case VAR: this->val = this->fncVar->compVar(this->symName); break;
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
		case FNC: return this->fncVar->compFnc(this->symName, this->left->comp());
		case VAR: return this->fncVar->compVar(this->symName);
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
		case NUM: std::cout << this->val.toString() << std::endl; break;
		case VAR: std::cout << "$" << this->symName << ": " << value << std::endl; break;
		case FNC: std::cout << "#" << this->symName << ": " << value << std::endl; break;
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
