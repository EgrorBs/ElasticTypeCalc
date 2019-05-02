#include "pch.h"
#include "CalcNode.h"

#include <iomanip>
#include <sstream>
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

std::string CalcNode::getExp() const {
	return this->exp;
}

std::string centerAlign(int len, std::string text, char fill = ' ') {
	int empty = len - text.length();

	if (empty < 0 && len > 1)
		return text.substr(0, len - 1) + "#";

	if (empty < 0)
		return text.substr(0, len);

	std::string prev, post;

	for (int i = 0; i < empty / 2; i++)
		prev += fill;

	for (int i = 0; i < empty - prev.length(); i++)
		post += fill;

	return prev + text + post;
}

std::stringstream CalcNode::toLinedText(int level, char fillChar, char splitChar) const {
	std::stringstream ret;
	if (level < 0) {
		std::string tmp;
		bool isEmpty = true;
		for (int i = 0; i < 256; i++) {
			tmp = this->toLinedText(i, fillChar, splitChar).str();
			isEmpty = true;
			for (auto sym : tmp) {
				if (sym != ' ' && sym != fillChar && sym != splitChar) {
					isEmpty = false;
					ret << std::setw(2) << i << ": ";
					break;
				}
			}
			if (!isEmpty)
				ret << tmp << std::endl;
			else
				break;
		}

		return ret;
	}
	if (level > 0) {
		if (this->type == NUM || this->type == VAR)
			return std::stringstream();
		if (this->type == FNC) {
			int alN = int(this->symName.length() / 2. + 0.5) + 1;
			std::string align = centerAlign(alN, "", ' ');
			ret << align + splitChar + centerAlign(this->left->getExp().length(), this->left->toLinedText(level - 1, fillChar, splitChar).str(), ' ') + splitChar;
			return ret;
		}
		if (this->type == BRC) {
			ret << splitChar + centerAlign(this->left->getExp().length(), this->left->toLinedText(level - 1, fillChar, splitChar).str(), ' ') + splitChar;
			return ret;
		}
		if (this->left != nullptr)
			ret << centerAlign(this->left->getExp().length(), this->left->toLinedText(level - 1, fillChar, splitChar).str(), ' ');
		if (this->left != nullptr && this->right != nullptr)
			ret << splitChar;
		if (this->right != nullptr)
			ret << centerAlign(this->right->getExp().length(), this->right->toLinedText(level - 1, fillChar, splitChar).str(), ' ');
		return ret;
	}
	if (level == 0) {
		char oper = '\0';
		switch (this->type) {
		case NUM:
			return std::stringstream();
		break;
		case SUM: oper = '+'; break;
		case SUB: oper = '-'; break;
		case MUL: oper = '*'; break;
		case DIV: oper = '/'; break;
		case POW: oper = '^'; break;
		case BRC:
			ret << "("
				<< centerAlign(this->left->getExp().length(), this->left->cComp().toString(), fillChar)
				<< ")";
			break;
		case VAR:
			ret << this->symName;
		break;
		case FNC:
			ret << this->symName << '(' << centerAlign(this->left->getExp().length(), this->left->cComp().toString(), fillChar) << ')';
		break;
		}

		if (oper != '\0') {
			ret << std::setfill('.')
				<< centerAlign(this->left->getExp().length(), this->left->cComp().toString(), fillChar)
				<< oper
				<< centerAlign(this->right->getExp().length(), this->right->cComp().toString(), fillChar);
		}
	}

	return std::stringstream()
		<< centerAlign(this->exp.length(), ret.str(), fillChar);
}
