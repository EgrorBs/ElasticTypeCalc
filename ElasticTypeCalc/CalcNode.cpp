#include "pch.h"
#include "CalcNode.h"

#include <array>

CalcNode::CalcNode(std::string exp) {
	this->exp = exp;
}

CalcNode::~CalcNode()
{
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
	/*for (int i = this->exp.length() - 1; i >= 0; i--) {
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
	}*/

	this->type = NUM;
	this->val = TypedNum(this->exp);
}

TypedNum CalcNode::comp() {
	switch (this->type) {
		case NUM: return this->val;
		case SUM: return this->left->comp() + this->right->comp();
		case SUB: return this->left->comp() - this->right->comp();
		case MUL: return this->left->comp() * this->right->comp();
		case DIV: return this->left->comp() / this->right->comp();
		case POW: return this->left->comp() ^ this->right->comp();
		case BRC: return this->left->comp();
		default:
			throw std::exception("Comp: unknown type!");
		break;
	}
}
